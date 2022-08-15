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

#include "LogLabelsListWidget.h"
#include <ramio/global/text.h>
#include <ramio/log/log.h>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>

namespace Smitto {

LogLabelsListWidget::LogLabelsListWidget(QWidget* parent)
	: QWidget(parent)
{
	auto layout = new QVBoxLayout(this);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->addWidget(listWidget_ = new QListWidget(this));
	listWidget_->setStyleSheet("QListWidget{border:0px;}");

	labelsPallete_ = this->palette();
	labelsPallete_.setColor(QPalette::ColorRole::Text, QColor(Qt::gray));
	connect(listWidget_, &QListWidget::doubleClicked, [this](){
		for (int i = 0; i < listWidget_->model()->rowCount(); ++i)
			listWidget_->itemWidget(listWidget_->item(i))->setPalette(labelsPallete_);
	});
	auto* button = new QPushButton(tr("Очистить"), this);
	layout->addWidget(button);
	connect(button, &QPushButton::clicked, listWidget_, &QListWidget::clear);
}

LogLabelsListWidget::~LogLabelsListWidget()
{
}

void LogLabelsListWidget::addMessageFromConsoleFormat(const QString& msg)
{
	QString text = msg;
	text.replace(RC_GREEN, txt_colorStartStr % txt_color_greenStr % txt_colorMiddleStr);
	text.replace(RC_RED, txt_colorStartStr % txt_color_redStr % txt_colorMiddleStr);
	text.replace(RC_NC, txt_colorEndStr);
	addMessage(text);
}

void LogLabelsListWidget::addMessage(const QString& msg)
{
	QLabel* label = new QLabel(msg, listWidget_);
	listWidget_->insertItem(0, "");
	listWidget_->setItemWidget(listWidget_->item(0), label);
	connect(label, &QLabel::linkActivated, this, &LogLabelsListWidget::linkActivated);

	int rowCount = listWidget_->count();
	if (rowCount > 100)
	{
		listWidget_->removeItemWidget(listWidget_->item(rowCount-1));
		listWidget_->model()->removeRow(rowCount-1);
	}
}

} // Smitto::
