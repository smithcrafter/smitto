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

#include "CustomTitleWidget.h"
// Qt5
#include <QtGui/QMouseEvent>

namespace Ui {

QWidget* CustomTitleWidget::maxParent()
{
	QWidget* maxParent = this;
	while (maxParent->parent()) {
		maxParent = maxParent->parentWidget();
	}
	return maxParent;
}

void CustomTitleWidget::mousePressEvent(QMouseEvent *event)
{
	if(event->button()==Qt::LeftButton)
	{
		mouseClickPos_=event->globalPos();
		parentPos_ = maxParent()->pos();
		move_ = true;
	}
	QWidget::mousePressEvent(event);
}

void CustomTitleWidget::mouseReleaseEvent(QMouseEvent* event)
{
	move_ = false;
	QWidget::mouseReleaseEvent(event);
}

void CustomTitleWidget::mouseMoveEvent(QMouseEvent* event)
{
	if (move_ && (event->buttons() & Qt::LeftButton) )
		maxParent()->move(parentPos_+event->globalPos()-mouseClickPos_);
	QWidget::mouseMoveEvent(event);
}

}
