/*
 * Copyright (C) 2016-2021 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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

#include "Service.h"
#include <ramio/log/log.h>
// Qt5
#include <QtCore/QTimer>
#include <QtCore/QElapsedTimer>

namespace Smitto {

Service::Service(const QString& name, int timer, QObject* parent)
	: QObject(parent),
	  name_(name),
	  timer_(new QTimer(this))
{
	timer_->setInterval(timer);
	connect(timer_, &QTimer::timeout, this, &Service::work);
}

Service::~Service()
{
	stop();
}

bool Service::started() const
{
	return timer_->isActive();
}

void Service::start()
{
	if (!started())
	{
		QElapsedTimer timer;
		if (prepareStart())
		{
			timer_->start();
			emit activeChanged(true);
		}
		auto elapsed = timer.nsecsElapsed();
		if (elapsed > 200000)
			DLOG(QString("[Service-%1] processStart - %2 ns").arg(name_).arg(elapsed));
	}
}

void Service::stop()
{
	if (started())
	{
		QElapsedTimer timer;
		timer.start();
		timer_->stop();
		processStop();
		emit activeChanged(false);
		auto elapsed = timer.nsecsElapsed();
		if (elapsed > 200000)
			DLOG(QString("[Service-%1] processStop - %2 ns").arg(name_).arg(elapsed));
	}
}

void Service::work()
{
	QElapsedTimer timer;
	timer.start();
	processWork();
	auto elapsed = timer.nsecsElapsed();
	if (elapsed > 100000)
		DLOG(QString("[Service-%1] processWork - %2 ns").arg(name_).arg(elapsed));
}

} // Smitto::
