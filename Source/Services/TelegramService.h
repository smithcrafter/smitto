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

#pragma once

#include "Service.h"
class QNetworkAccessManager;
class QNetworkReply;

namespace Smitto {

/**
 * @brief The TelegramBot class
 * Справочник по Bot API https://tlgrm.ru/docs/bots/api
 */
class TelegramService : public Service
{
	Q_OBJECT
public:
	TelegramService(QObject* parent = Q_NULLPTR);
	~TelegramService() Q_DECL_OVERRIDE;

	int chatId() {return chatId_;}
	void setChatId(int chatid) {chatId_ = chatid;}

	void auth();
	void getUpdates();
	void sendMessage(const QString& text, int chatid = 0);

signals:
	void messageReceived(const QString& message);

protected:
	bool prepareStart() Q_DECL_OVERRIDE;
	void processWork() Q_DECL_OVERRIDE;
	void processStop() Q_DECL_OVERRIDE;

private:
	void onGetAuth();
	void onGetUpdates();
	void onSendMessage();

private:
	QString login_;
	QString token_;
	QNetworkAccessManager& manager_;
	QNetworkReply *getUpdatesReply_ = Q_NULLPTR;
	int chatId_ = 0;
	int updateId_ = 0;
};

} // Smitto::
