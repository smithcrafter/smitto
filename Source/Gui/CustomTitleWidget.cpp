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
#include "PlatformSpecification.h"
// Qt5
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QStyleOption>
#include <QtGui/QMouseEvent>
#include <QtGui/QPainter>

namespace Ui {

CustomTitleWidget::CustomTitleWidget(const QString& title, bool onlyClose, QWidget* parent)
	:QWidget(parent)
{
	auto layout = new QHBoxLayout(this);
	layout->setMargin(0);
	layout->setSpacing(0);
	layout->addWidget(new QLabel(title));
	layout->addStretch();
	layout->addLayout(cornLayout_ = new QHBoxLayout());
	QToolButton* tb;
	if (!onlyClose)
	{
		layout->addWidget(tb = new QToolButton());
		tb->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
		tb->setText("_");
		tb->setFixedSize(iconSize());
		connect(tb, &QToolButton::clicked, this, [this](){this->maxParent()->showMinimized();});
		layout->addWidget(tb = new QToolButton());
		tb->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
		tb->setText("☐");
		tb->setFixedSize(iconSize());
		connect(tb, &QToolButton::clicked, this, [this](){
			if (this->maxParent()->isMaximized()) {this->maxParent()->showMaximized();this->maxParent()->showNormal();}
			else this->maxParent()->showMaximized();});
	}

	layout->addWidget(tb = new QToolButton());
	tb->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
	tb->setText("X");
	tb->setFixedSize(iconSize());
	connect(tb, &QToolButton::clicked, this, [this](){this->maxParent()->close();});
	this->setMinimumHeight(panelSize());
}

QWidget* CustomTitleWidget::maxParent()
{
	QWidget* maxParent = this;
	while (maxParent->parent()) {
		maxParent = maxParent->parentWidget();
	}
	return maxParent;
}

void CustomTitleWidget::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		mouseClickPos_ = event->globalPos();
		parentPos_ = maxParent()->pos();
		move_ = true;
	}
	QWidget::mousePressEvent(event);
}

void CustomTitleWidget::mouseDoubleClickEvent(QMouseEvent* event)
{
	this->maxParent()->isMaximized() ? this->maxParent()->showNormal() : this->maxParent()->showMaximized();
	QWidget::mouseDoubleClickEvent(event);
}

void CustomTitleWidget::mouseReleaseEvent(QMouseEvent* event)
{
	move_ = false;
	QWidget::mouseReleaseEvent(event);
}

void CustomTitleWidget::mouseMoveEvent(QMouseEvent* event)
{
	if (move_ && (event->buttons() & Qt::LeftButton))
		maxParent()->move(parentPos_+event->globalPos()-mouseClickPos_);
	QWidget::mouseMoveEvent(event);
}

void CustomTitleWidget::paintEvent(QPaintEvent *)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

}
