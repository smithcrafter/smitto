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

#include "ServiceStatusWidget.h"
#include <Base/Service.h>
// Ramio
#include <Global/Text.h>
#include <Gui/Global.h>
// Qt5
#include <QtWidgets/QToolButton>
#include <QtWidgets/QLabel>

namespace Smitto {

ServiceStatusWidget::ServiceStatusWidget(Service& service, const QString& name, QWidget* parent)
	: QWidget(parent),
	  service_(service)
{
	UI_CREATE_HLAYOUT(layout);
	layout->addWidget(stateLabel_ = new QLabel(this));
	layout->addWidget(new QLabel(H3(name)));
	layout->addStretch();
	layout->addWidget(startButton_ = new QToolButton(this));
	startButton_->setText(tr("Старт"));
	layout->addWidget(stopButton_ = new QToolButton(this));
	stopButton_->setText(tr("Стоп"));
	connect(&service, &Service::activeChanged, this, &ServiceStatusWidget::onActiveChanged);
	onActiveChanged(service.started());
}

void ServiceStatusWidget::onActiveChanged(bool value)
{
	startButton_->setEnabled(!value);
	stopButton_->setEnabled(value);
	if (value)
		stateLabel_->setText(GREENTEXT("Активен"));
	else
		stateLabel_->setText(GRAYTEXT("Отключён"));
}

} // Smitto::
