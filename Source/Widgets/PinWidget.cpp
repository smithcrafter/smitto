/*
 * Copyright (C) 2020-2022 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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

#include "PinWidget.h"
#include <ramio/gui/global.h>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtGui/QPainter>
#include <QtGui/QPaintEvent>

namespace Smitto {

#ifdef Q_OS_ANDROID
#define POINTSIZE 16
#else
#define POINTSIZE 8
#endif

PinWidget::PinWidget(QWidget* parent)
	: QWidget(parent)
{
	UI_CREATE_VLAYOUT(layout);
	layout->setContentsMargins(0, 0 , 0, 0);
	layout->setSpacing(0);
	layout->addSpacing(20);
	layout->addStretch(1);

	QWidget* pointsWidget = new QWidget(this);
	auto* pointsLayout = new QHBoxLayout(pointsWidget);
	pointsLayout->setContentsMargins(5, 5 , 5, 5);
	pointsLayout->setSpacing(5);
	pointsLayout->addStretch(100);
	pointsLayout->addWidget(points_[0] = new PointCircleWidget(Qt::lightGray, POINTSIZE, pointsWidget), 2);
	pointsLayout->addStretch(1);
	pointsLayout->addWidget(points_[1] = new PointCircleWidget(Qt::lightGray, POINTSIZE, pointsWidget), 2);
	pointsLayout->addStretch(1);
	pointsLayout->addWidget(points_[2] = new PointCircleWidget(Qt::lightGray, POINTSIZE, pointsWidget), 2);
	pointsLayout->addStretch(1);
	pointsLayout->addWidget(points_[3] = new PointCircleWidget(Qt::lightGray, POINTSIZE, pointsWidget), 2);
	pointsLayout->addStretch(100);

	layout->addWidget(pointsWidget);
	layout->addStretch(2);
	layout->addSpacing(20);

	QFont font = this->font();
	if (font.pointSize() != 0)
		font.setPointSize(font.pointSize()*3);
	else
		font.setPixelSize(font.pixelSize()*3);

	QGridLayout* glayout = new QGridLayout();
	for (quint8 i = 0; i <= 10; i++)
	{
		QPushButton* but = Q_NULLPTR;
		if(i == 0)
			glayout->addWidget(but = numbuttons_[i] = new QPushButton("0"), 1+4, 1);
		else if (i <= 9)
			glayout->addWidget(but = numbuttons_[i] = new QPushButton(QString::number(i)), 1+(i-1)/3+1, (i-1)%3);
		else if (i == 10)
			glayout->addWidget(but = numbuttons_[i] = new QPushButton("<"), 1+4, 2);

		connect(but, &QPushButton::clicked, [this, i](){this->onButtonPressed(PinButtons(i));});
		but->setFont(font);
	}
	glayout->setColumnStretch(0, 1);
	glayout->setColumnStretch(1, 1);
	glayout->setColumnStretch(2, 1);
	glayout->setContentsMargins(0, 0 , 0, 0);
	glayout->setSpacing(2);

	layout->addLayout(glayout, 4);
	glayout->setAlignment(Qt::AlignCenter);

	updatePinButtonSize();
}

PinWidget::~PinWidget()
{
}

void PinWidget::clear()
{
	while (numbers_.count()) {
		onButtonPressed(PinButtons::Clear);
	}
}

void PinWidget::onButtonPressed(PinButtons button)
{
	int count = numbers_.count();

	if (count < 4 && button >= PinButtons::B0 && button <= PinButtons::B9)
	{
		numbers_.append(quint8(button));
		points_[count]->change(Qt::darkGray, POINTSIZE*1.5);
	}
	else if(count > 0 && button == PinButtons::Clear)
	{
		numbers_.removeLast();
		points_[count-1]->change(Qt::lightGray, POINTSIZE);
	}

	if (numbers_.count() == 4)
		emit pinEntered(numbers_);
}

void PinWidget::keyPressEvent(QKeyEvent* event)
{
	if (event->key() >= Qt::Key_0 && event->key() <= Qt::Key_9)
		onButtonPressed(PinButtons(event->key() - Qt::Key_0));
	else if (event->key() == Qt::Key_Backspace)
		onButtonPressed(PinButtons::Clear);
	else if (event->key() == Qt::Key_Back)
		clear();
	else
	{
		QWidget::keyPressEvent(event);
		return;
	}
	event->accept();
}

void PinWidget::updatePinButtonSize()
{
	int size = this->width()/3.14;
	for (quint8 i = 0; i <= 10; ++i)
		numbuttons_[i]->setMinimumSize(size, size);
}

PointCircleWidget::PointCircleWidget(const QColor& color, qint8 size, QWidget* parent)
	: QWidget(parent),
	  color_(color),
	  size_(size)
{
	this->setMinimumSize(size_*4, size_*4);
}

void PointCircleWidget::change(const QColor& color, qint8 size)
{
	color_ = color;
	size_ = size;
	repaint();
}

void PointCircleWidget::paintEvent(QPaintEvent* event)
{
	QPainter p(this);
	p.setBrush(QBrush(color_, Qt::SolidPattern));
	QPen pen;
	pen.setColor(color_);
	p.setPen(pen);
	QRect rect = event->rect();
	p.drawEllipse(QPoint(rect.x()+rect.width()/2, rect.y()+rect.height()/2), size_, size_);
}

} // Smitto::
