/*
 * Copyright (C) 2016-2023 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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

#include "LibLoaderWidget.h"
#include <ramio/log/log.h>
#include <ramio/settings/uisettings.h>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QFile>
#include <QFileInfo>
#include <QTimer>
#include <QProcess>
#include <QPainter>
#include <QStyleOption>
#include <dlfcn.h>

namespace Smitto {

LibLoaderWidget::LibLoaderWidget(const QString& libPath, const QString& libUrl, QWidget *parent)
	: QWidget(parent), libPath_(libPath), libUrl_(libUrl)
#ifdef USE_QLIB
	, library_(libPath_)
#endif
{
	auto layout = new QVBoxLayout(this);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->setSpacing(0);
	layout->addWidget(stackedWidget_ = new QStackedWidget(this));

	stackedWidget_->addWidget(checkWidget_ = new QWidget());
	auto vlayout = new QVBoxLayout(checkWidget_);
	vlayout->addWidget(new QLabel("Проверка версии.."), 0, Qt::AlignCenter);
	vlayout->addWidget(checkLabel_ = new QLabel(), 0, Qt::AlignCenter);

	stackedWidget_->addWidget(donwloadWidget_ = new QWidget());
	vlayout = new QVBoxLayout(donwloadWidget_);
	vlayout->addWidget(new QLabel("Получение версии.."), 0, Qt::AlignCenter);
	vlayout->addWidget(donwloadLabel_ = new QLabel());

	stackedWidget_->addWidget(updateWidget_ = new QWidget());
	vlayout = new QVBoxLayout(updateWidget_);
	vlayout->addWidget(new QLabel("Обвноление версии.."), 0, Qt::AlignCenter);

	stackedWidget_->addWidget(errorWidget_ = new QWidget());
	vlayout = new QVBoxLayout(errorWidget_);
	vlayout->addWidget(errorLabel_ = new QLabel(errorWidget_), 0, Qt::AlignCenter);
	connect(errorLabel_, &QLabel::linkActivated, this, &LibLoaderWidget::check, Qt::QueuedConnection);


	QProcess::execute("rm", {QString( "%1.*").arg(libPath_)});
	QProcess::execute("cp", {libPath_, QString( "%1.%2").arg(libPath_).arg(ver)});
}

LibLoaderWidget::~LibLoaderWidget()
{
	unload();
	QProcess::execute("rm", {QString( "%1.*").arg(libPath_)});
}

void LibLoaderWidget::loadSettings()
{
	LOAD_GEOMETRY(this);
}

void LibLoaderWidget::saveSettings()
{
	SAVE_GEOMETRY(this);
}

void LibLoaderWidget::check()
{
	QString path = libPath_ + QString(".%1").arg(ver);
	DLOG(QString("start check %1 %2").arg(path).arg(QFileInfo(path).size()));
#ifdef USE_QLIB
	library_.setFileName(path);
	if (library_.load())
	{
		createEngineFPrt createEngine = reinterpret_cast<createEngineFPrt>(library_.resolve("createEngine"));
		createWidgetFPtr createWidget = reinterpret_cast<createWidgetFPtr>(library_.resolve("createWidget"));
#else
	qDebug()<<"try dlopen"<<path.toStdString().data();
	handle = dlopen(path.toStdString().data(), RTLD_NOW);
	qDebug()<<"handle"<<handle;

	if (handle)
	{
		createEngineFPrt createEngine = (createEngineFPrt)dlsym(handle, "createEngine");
		createWidgetFPtr createWidget = (createWidgetFPtr)dlsym(handle, "createWidget");
#endif
		if (createEngine && createWidget)
		{
			DLOG("functions finded");
			engine_ = createEngine();
			DLOG("engine_ created");
			widget_ = createWidget(*engine_);
			DLOG("widget_ created");

			stackedWidget_->addWidget(widget_);
			stackedWidget_->setCurrentWidget(widget_);
			connect(engine_, SIGNAL(requestUpdate()), this, SLOT(downoad()), Qt::QueuedConnection);
		}
		else
			ELOG("no functions");
	}
	else
	{
#ifdef USE_QLIB
		ELOG("no lib " % library_.errorString());
		//library_.unload();
		qDebug()<<path<<"exists"<<QFile(QString( "%1.%2").arg(libPath_).arg(ver)).exists();
#else
		qDebug()<<path<<"exists"<<QFile(QString( "%1.%2").arg(libPath_).arg(ver)).exists();
		QString errStr(dlerror());
		qDebug()<<path<<"dlerror"<<errStr;
		checkLabel_->setText(QString("dlopen err dlerror=%1").arg(errStr));
#endif
		QTimer::singleShot(1000, this, &LibLoaderWidget::downoad);
	}
}

void LibLoaderWidget::downoad()
{
	qDebug()<<"start downoad";
	donwloadLabel_->clear();
	stackedWidget_->setCurrentWidget(donwloadWidget_);
	if (!manager_)
		manager_ = new QNetworkAccessManager(this);

	auto reply = manager_->get(QNetworkRequest(QUrl(libUrl_)));
	connect(reply, &QNetworkReply::finished, this, &LibLoaderWidget::onFinished);
}

void LibLoaderWidget::onFinished()
{
	stackedWidget_->setCurrentWidget(updateWidget_);

	auto* reply = reinterpret_cast<QNetworkReply*>(sender());
	if (reply->error() != QNetworkReply::NetworkError::NoError)
	{
		donwloadLabel_->setText(QString("err %1, str %2").arg(reply->error()).arg(reply->errorString()));
		ELOG(donwloadLabel_->text());
		reply->deleteLater();

		QTimer::singleShot(5000, this, &LibLoaderWidget::check);
		return;
	}

	QByteArray ba = reply->readAll();
	reply->deleteLater();
#ifdef USE_QLIB
	if (library_.isLoaded())
#else
	if (handle)
#endif
	{
		checkLabel_->clear();
		stackedWidget_->setCurrentWidget(checkWidget_);
		if (widget_)
		{
			stackedWidget_->removeWidget(widget_);
			delete widget_;
			widget_ = Q_NULLPTR;
			delete engine_;
			engine_ = Q_NULLPTR;

			qDebug()<<"widgets cleared";
		}
		unload();
	}

	QFile file(libPath_);
	if (file.open(QIODevice::WriteOnly))
	{
		file.write(ba);
		file.flush();
		file.close();
		QString ln = QString("%1.%2").arg(libPath_).arg(++ver);
		QProcess::execute("cp", {libPath_, ln});
		DLOG(QString( "File: %1 exists %2").arg(ln).arg(QFile(ln).exists()));
		QTimer::singleShot(1000, this, &LibLoaderWidget::check);
	}
	else
	{
		errorLabel_->setText(QString("<h1>Ошибка</h1><p>Ошибка записи новой версии в файл %1.</p>"
									 "<center><a href=\"check\">повторить</a></center>").arg(libPath_));
		stackedWidget_->setCurrentWidget(errorWidget_);
	}
}

void LibLoaderWidget::unload()
{
#ifdef USE_QLIB
	if (library_.isLoaded())
		qDebug()<<"unload"<<library_.unload();
#else
	if (handle)
	{
		qDebug()<<"unload"<<dlclose(handle);
		handle = Q_NULLPTR;
	}
#endif
}

void LibLoaderWidget::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);
	QStyleOption opt;
	opt.initFrom(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

} // Smitto::
