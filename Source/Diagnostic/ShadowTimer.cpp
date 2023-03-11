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

#include "ShadowTimer.h"
#include <ramio/log/log.h>
// Qt5
#include <QtCore/QTimer>

namespace Smitto {

ShadowTimer::ShadowTimer(int time, QObject* parent)
	: QObject(parent),
	  timer_(new QTimer(this)),
	  time_(time)
{
	connect(timer_, &QTimer::timeout, this, &ShadowTimer::onTimeOut);
	elapsedTimer_.start();
	timer_->start(time);
}

ShadowTimer::~ShadowTimer()
{
	timer_->stop();
	delete timer_;
}

void ShadowTimer::onTimeOut()
{
	auto elapsed = elapsedTimer_.elapsed();
	if (elapsed > (time_+5))
		DLOG(QString("[ShadowTimer] timeouted %1 (%2)").arg(elapsed).arg(elapsedTimer_.nsecsElapsed()));
	elapsedTimer_.restart();
}

} // Smitto::
