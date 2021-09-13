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


#include "MobileScrollArea.h"
#include <QtWidgets/QScrollBar>
#include <QtGui/QMouseEvent>

namespace Smitto {

MobileScrollArea::MobileScrollArea(QWidget* parent)
	: QScrollArea(parent)
{
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void MobileScrollArea::mousePressEvent(QMouseEvent *event)
{
	startScroll_ = event->pos();
}

void MobileScrollArea::mouseMoveEvent(QMouseEvent *event)
{
	auto pos = event->pos();
	int y = pos.y() - startScroll_.y();
	this->verticalScrollBar()->setValue(this->verticalScrollBar()->value()-y);
	startScroll_ = event->pos();
}

} // Smitto::
