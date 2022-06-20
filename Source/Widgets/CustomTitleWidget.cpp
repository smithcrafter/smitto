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

#include "CustomTitleWidget.h"
#include "../Gui/PlatformSpecification.h"
#include <ramio/gui/global.h>
// Qt5
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QStyleOption>
#include <QtGui/QMouseEvent>
#include <QtGui/QPainter>

namespace Smitto {
namespace Ui {

CustomTitleWidget::CustomTitleWidget(const QString& title, TiltleButtons butons, QWidget* parent)
	: QWidget(parent)
{
	UI_CREATE_HLAYOUT_ZERO_MARGINSPACING(layout);
	layout->addWidget(titleLabel_ = new QLabel(title));
	layout->addStretch();
	layout->addLayout(cornLayout_ = new QHBoxLayout());
	QToolButton* tb;
	if (butons & TiltleButton::Collapce)
	{
		layout->addWidget(tb = new QToolButton());
		tb->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
		tb->setText("^");
		tb->setFixedSize(iconSize());
		buttons_.insert(TiltleButton::Collapce, tb);
	}
	if (butons & TiltleButton::Min)
	{
		layout->addWidget(tb = new QToolButton());
		tb->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
		tb->setText("_");
		tb->setFixedSize(iconSize());
		connect(tb, &QToolButton::clicked, this, [this](){
			this->maxParent()->showMinimized();
		});
		buttons_.insert(TiltleButton::Min, tb);
	}
	if (butons & TiltleButton::NormMax)
	{
		layout->addWidget(tb = new QToolButton());
		tb->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
		tb->setText("☐");
		tb->setFixedSize(iconSize());
		connect(tb, &QToolButton::clicked, this, [this](){
			auto maxParent = this->maxParent();
			maxParent->showMinimized();
			bool isMax = maxParent->isMaximized() || maxParent->property("isMaximized").toBool();
			(isMax) ? maxParent->showNormal() : maxParent->showMaximized();
			maxParent->setProperty("isMaximized", !isMax);
		});
		buttons_.insert(TiltleButton::NormMax, tb);
	}
	if (butons & TiltleButton::Close)
	{
		layout->addWidget(tb = new QToolButton());
		tb->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
		tb->setText("X");
		tb->setFixedSize(iconSize());
		connect(tb, &QToolButton::clicked, this, [this](){this->maxParent()->close();});
		buttons_.insert(TiltleButton::Close, tb);
	}
	this->setMinimumHeight(panelSize());

	titleLabel_->installEventFilter(this);
}

CustomTitleWidget::~CustomTitleWidget()
{
}

QToolButton* CustomTitleWidget::addButtonToCornLayout(const QString& text)
{
	auto* button = new QToolButton(this);
	button->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
	button->setText(text);
	button->setFixedSize(iconSize());
	cornLayout_->addWidget(button);
	return button;
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
	if (this->maxParent()->isMaximized() ) {
		this->maxParent()->showMinimized();
		this->maxParent()->showNormal();
	}
	else
		this->maxParent()->showMaximized();
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

void CustomTitleWidget::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);
	QStyleOption opt;
#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
	opt.initFrom(this);
#else
	opt.init(this);
#endif
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

bool CustomTitleWidget::eventFilter(QObject* watched, QEvent* event)
{
	if (titleLabel_ == watched)
	{
		if (event->type() == QEvent::MouseButtonPress)
			mousePressEvent(static_cast<QMouseEvent*>(event));
		else if (event->type() == QEvent::MouseButtonRelease)
			mouseReleaseEvent(static_cast<QMouseEvent*>(event));
		else if (event->type() == QEvent::MouseMove)
			mouseMoveEvent(static_cast<QMouseEvent*>(event));
		else
			return false;
		return true;
	}
	return false;
}

} // Ui ::
} // Smitto ::
