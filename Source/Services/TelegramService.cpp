/*
 * Copyright (C) 2016-2022 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
 *
 * This file is part of the Smitto.
 *
 * Smitto is free software; you can redistribute it and/or modify it under the terms of the
 * GNU Lesser General Public License as published by the Free Software Foundation;
 * either version 3 of the License, or (at your option) any later version.
 *
 * Smitto is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Smitto; see the file LICENSE. If not, see <http://www.gnu.org/licenses/>.
 */

#include "TelegramService.h"
#include <ramio/settings/settings.h>
#include <ramio/settings/config.h>
#include <ramio/log/log.h>
#include <System/File.h>
// Qt5
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QtCore/QCoreApplication>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include <QStringBuilder>

namespace Smitto {

TelegramService::TelegramService(QObject* parent)
	: Smitto::Service("TelegramService", 1000, parent),
	  login_(Ramio::config().value("Telegram/Botname")),
	  token_(Smitto::readAllFile(qApp->applicationDirPath() % QString("/Confidentially/tgbot.key")).trimmed()),
	  manager_(*new QNetworkAccessManager(this))
{
}

TelegramService::~TelegramService()
{
}

void TelegramService::auth()
{
	QNetworkRequest request;
	QString url = QString("https://api.telegram.org/bot%1/getMe").arg(token_);
	request.setUrl(QUrl(url));
	auto reply = manager_.get(request);
	connect(reply, &QNetworkReply::finished, this, &TelegramService::onGetAuth);
}

void TelegramService::getUpdates()
{
	if (getUpdatesReply_)
		return;
	QNetworkRequest request;
	QString url = QString("https://api.telegram.org/bot%1/getUpdates?offset=%2").arg(token_).arg(updateId_+1);
	request.setUrl(QUrl(url));
	getUpdatesReply_ = manager_.get(request);
	connect(getUpdatesReply_, &QNetworkReply::finished, this, &TelegramService::onGetUpdates);
}

void TelegramService::sendMessage(const QString& text, int chatid)
{
	if (!chatid)
		chatid = chatId_;
	if (!chatid || token_.isEmpty())
		return;

	QNetworkRequest request;
	QString url = QString("https://api.telegram.org/bot%1/sendMessage").arg(token_);
	request.setRawHeader("Content-Type", "application/json");
	request.setRawHeader("Connection", "close");
	request.setUrl(QUrl(url));

	QJsonDocument jsdoc;
	QJsonObject jsObject;
	jsObject.insert("chat_id", chatid);
	jsObject.insert("text", text);
	jsdoc.setObject(jsObject);

	auto reply = manager_.post(request, jsdoc.toJson());
	connect(reply, &QNetworkReply::finished, this, &TelegramService::onSendMessage);
}

void TelegramService::onGetAuth()
{
	auto* reply = reinterpret_cast<QNetworkReply*>(sender());
	if (reply->error() != QNetworkReply::NetworkError::NoError)
	{
		ELOG(QString("err %1, str %2").arg(reply->error()).arg(reply->errorString()));
		reply->deleteLater();
		return;
	}
	QByteArray ba = reply->readAll();
	QJsonDocument doc = QJsonDocument::fromJson(ba);
	if (doc.object().value("ok").toBool() == true)
	{
		QJsonObject joValue = doc.object().value("result").toObject();
		MLOG("TelegramBot", QString("%1 {username:%2} id:%3").arg(joValue.value("first_name").toString(), joValue.value("username").toString())
			 .arg(joValue.value("id").toInt()));
		// is_bot can_join_groups can_read_all_group_messages supports_inline_queries
	}
	else
		qDebug().noquote()<<doc.toJson();
	reply->deleteLater();
}

void TelegramService::onGetUpdates()
{
	auto* reply = reinterpret_cast<QNetworkReply *>(sender());
	if (reply->error() != QNetworkReply::NetworkError::NoError)
	{
		ELOG(QString("err %1, str %2").arg(reply->error()).arg(reply->errorString()));
		reply->deleteLater();
		return;
	}
	QByteArray ba = reply->readAll();
	QJsonDocument doc = QJsonDocument::fromJson(ba);
	QJsonObject codeObject = doc.object();

	if (codeObject.value("ok").toBool() == true)
	{
		QJsonArray updateArray = codeObject.value("result").toArray();
		for (const QJsonValue& value: updateArray)
		{
			int update_id = value.toObject().value("update_id").toInt();
			if (update_id > updateId_)
			{
				updateId_ = update_id;
				QJsonValue valMessage = value.toObject().value("message");
				if (valMessage.isObject())
				{
					QJsonObject joMessage = valMessage.toObject();
					if (joMessage.value("from").toObject().value("id").toInt() == chatId_)
					{
						emit messageReceived(joMessage.value("text").toString());
					}
				}
			}
		}
	}
	else
		qDebug().noquote()<<doc.toJson();
	reply->deleteLater();
	getUpdatesReply_ = Q_NULLPTR;
}

void TelegramService::onSendMessage()
{
	auto* reply = reinterpret_cast<QNetworkReply *>(sender());
	if (reply->error() != QNetworkReply::NetworkError::NoError)
	{
		ELOG(QString("err %1, str %2").arg(reply->error()).arg(reply->errorString()));
		reply->deleteLater();
		return;
	}
	QByteArray ba = reply->readAll();
	QJsonDocument doc = QJsonDocument::fromJson(ba);
	QJsonObject codeObject = doc.object();
	if (codeObject.value("ok").toBool() == true)
	{

	}
	else
		qDebug().noquote()<<doc.toJson();
	reply->deleteLater();
}

bool TelegramService::prepareStart()
{
	if (token_.isEmpty())
	{
		EMLOG("TelegramBot", QString("Подготовка сервиса, токен не установлен"));
		return false;
	}

	updateId_ = Sets.get("TelegramBot/update_id").toInt();
	MLOG("TelegramBot", QString("Подготовка сервиса, update_id=%1").arg(updateId_));
	auth();
	return true;
}

void TelegramService::processWork()
{
	getUpdates();
}

void TelegramService::processStop()
{
	Sets.set("TelegramBot/update_id", QString::number(updateId_));
}

} // Smitto::

