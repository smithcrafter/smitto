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

#include "MaterialButton.h"
#include <Gui/PlatformSpecification.cpp>
#include <QtWidgets/QStyleOption>
#include <QtGui/QPainter>
#include <QtGui/QMouseEvent>
#include <QtCore/QDateTime>

namespace Smitto {
namespace Ui {

MaterialButton::MaterialButton(QWidget* parent)
	: QToolButton(parent)
{
	connect(&timer_, &QTimer::timeout,
			this, static_cast<void (MaterialButton::*)()>(&MaterialButton::update));
	this->setStyleSheet("QToolButton{border: 0px;}");
	this->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	this->setIconSize(panelIconSize());
	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

MaterialButton::MaterialButton(const QString& text, const QIcon& icon, QWidget* parent)
	: MaterialButton(parent)
{
	this->setIcon(icon);
	this->setText(text);
}

MaterialButton::~MaterialButton()
{
	timer_.stop();
}

void MaterialButton::mousePressEvent(QMouseEvent *event)
{
	pressPos_ = event->pos();
	pressTime_ = QDateTime::currentMSecsSinceEpoch();
	QToolButton::mousePressEvent(event);
	timer_.start(25);
	setActive(true);
}

void MaterialButton::paintEvent(QPaintEvent *e)
{
	QToolButton::paintEvent(e);
	if (active_)
	{
		QPainter p(this);
		p.setPen(QPen(QColor::fromRgb(0xA0,0xA0,0xA0, 100)));
		p.setBrush(QBrush(QColor::fromRgb(0xA0,0xA0,0xA0, 100)));
		int x = 4+(QDateTime::currentMSecsSinceEpoch() - pressTime_)/50;
		x = x*x*2;
		QRect rect(pressPos_.x() - x, pressPos_.y() - x, 2*x, 2*x);
		p.drawRoundedRect(rect, rect.height()/2-1, rect.height()/2-1);
		if (x > this->width())
			timer_.stop();
	}
}

void MaterialButton::setActive(bool active)
{
	active_ = active;
	repaint();
	this->setAutoFillBackground(!active);
}

} // Ui ::
} // Smitto ::
