/*
 * Copyright (C) 2016-2019 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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
// Qt5
#include <QtCore/QTimer>

namespace Smitto {

Service::Service(QObject* parent)
	: QObject(parent),
	  timer_(new QTimer(this))
{
	timer_->setInterval(1000);
}

Service::~Service()
{
	if (started())
		stop();
}

void Service::start()
{
	if (prepareStart())
	{
		timer_->start();
		emit activeChanged(true);
	}
}

void Service::stop()
{
	timer_->stop();
	processStop();
	emit activeChanged(false);
}

bool Service::started() const
{
	return timer_->isActive();
}

} // Smitto::
