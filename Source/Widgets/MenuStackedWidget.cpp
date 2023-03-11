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

#include "MenuStackedWidget.h"
#include <Gui/Global.h>
// Qt5
#include <QtWidgets/QStackedWidget>
#include <QtCore/QEvent>

namespace Smitto {

MenuStackedWidget::MenuStackedWidget(const QString& activeStyleSheet, const QString& backgroundStyleSheet,
									 Qt::Orientation orientation, QWidget* parent)
	: QWidget(parent)
{
	QBoxLayout* layout = orientation == Qt::Horizontal ? static_cast<QBoxLayout*>(new QHBoxLayout(this)) :  static_cast<QBoxLayout*>(new QVBoxLayout(this));
	UI_SET_ZERO_MARGINSPACING(layout);
	baseMenuWidget_ = new QWidget(this);
	menuLayout_ = orientation == Qt::Horizontal ? static_cast<QBoxLayout*>(new QVBoxLayout(baseMenuWidget_)) : static_cast<QBoxLayout*>(new QHBoxLayout(baseMenuWidget_));
	UI_SET_ZERO_MARGINSPACING(menuLayout_);
	layout->addWidget(baseMenuWidget_);

	auto* stackedLayout = new QVBoxLayout();
	layout->addLayout(stackedLayout);
	stackedLayout->addLayout(topStackedLayout_ = new QVBoxLayout);
	auto hlayout = new QHBoxLayout();
	stackedLayout->addLayout(hlayout);
	hlayout->addWidget(stackedWidget_ = new QStackedWidget(this));
	hlayout->addLayout(rigthStackedLayout_ = new QVBoxLayout);
	stackedLayout->addLayout(bottomStackedLayout_ = new QVBoxLayout);
	setStyleSheets(activeStyleSheet, backgroundStyleSheet);
}

MenuStackedWidget::~MenuStackedWidget() = default;

void MenuStackedWidget::selectMenuItem(QWidget* watched)
{
	if (!widgets_.contains(watched))
		return;
	QWidget* content = widgets_[watched];
	int index = stackedWidget_->indexOf(content);
	if (index == -1)
	{
		content->setHidden(false);
		index = stackedWidget_->addWidget(content);
	}

	stackedWidget_->setCurrentIndex(index);

	if (lastActiveMenu_)
		lastActiveMenu_->setStyleSheet(emptyss);
	lastActiveMenu_ = static_cast<QWidget*>(watched);
	lastActiveMenu_ ->setStyleSheet(activeStyleSheet_);
}

void MenuStackedWidget::selectWidgetItem(QWidget* watched)
{
	for (auto it = widgets().begin(); it != widgets().end(); ++it)
		if (it.value() == watched)
		{
			selectMenuItem(it.key());
			return;
		}
}

void MenuStackedWidget::selectFirstMenuItem()
{
	if (!widgets_.isEmpty())
		selectMenuItem(widgets_.firstKey());
}

QWidget* MenuStackedWidget::insertMenuWidget(const QString& menutext, QWidget* content, int pos)
{
	auto* menuLabel = new QLabel(menutext);
	menuLabel->setMinimumSize(80, 40);
	insertMenuWidget(menuLabel, content, pos);
	return menuLabel;
}

void MenuStackedWidget::insertMenuWidget(QWidget* menu, QWidget* content, int pos)
{
	widgets_.insert(menu, content);
	if (pos == -1 || pos >= widgets_.count())
		menuLayout_->addWidget(menu);
	else
		menuLayout_->insertWidget(pos, menu);
	menu->installEventFilter(this);
	content->setParent(this);
	content->setHidden(true);
}

void MenuStackedWidget::insertMenuStretch()
{
	menuLayout_->addStretch();
}

QWidget* MenuStackedWidget::currentWidget() const
{
	return stackedWidget_->currentWidget();
}

void MenuStackedWidget::setStyleSheets(const QString& activeStyleSheet, const QString& backgroundStyleSheet)
{
	activeStyleSheet_ = activeStyleSheet;
	backgroundStyleSheet_ = backgroundStyleSheet;

	baseMenuWidget_->setStyleSheet(backgroundStyleSheet_);
	if (lastActiveMenu_)
		lastActiveMenu_ ->setStyleSheet(activeStyleSheet_);
}

bool MenuStackedWidget::eventFilter(QObject* watched, QEvent* event)
{
	if (event->type() == QEvent::MouseButtonRelease)
	{
		selectMenuItem(static_cast<QWidget*>(watched));
		return true;
	}
	return QWidget::eventFilter(watched, event);
}

} // Smitto::
