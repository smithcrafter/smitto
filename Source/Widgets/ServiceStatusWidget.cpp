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

#include "ServiceStatusWidget.h"
#include <Services/Service.h>
#include "ToogleWidget.h"
#include <ramio/gui/global.h>
#include <ramio/settings/config.h>
#include <QtWidgets/QLabel>
#include <QtWidgets/QToolButton>

namespace Smitto {

ServiceStatusWidget::ServiceStatusWidget(Service& service, QWidget* parent)
	: QWidget(parent)
{
	UI_CREATE_HLAYOUT(layout);
	layout->addWidget(new QLabel(H3(service.name())));
	layout->addStretch();
	layout->addWidget(stateLabel_ = new QLabel(this));
	layout->addWidget(startButton_ = new QToolButton(this));
	startButton_->setText(tr("Старт"));
	layout->addWidget(stopButton_ = new QToolButton(this));
	stopButton_->setText(tr("Стоп"));
	connect(&service, &Service::activeChanged, this, &ServiceStatusWidget::onActiveChanged);
	connect(startButton_, &QToolButton::clicked, &service, &Service::start);
	connect(stopButton_, &QToolButton::clicked, &service, &Service::stop);
	layout->addWidget(dlogBox_ = new ToogleWidget("dlog", false, this));
	connect(dlogBox_, &QAbstractButton::toggled, &service, &Service::setDlog);
	onActiveChanged(service.started());
}

void ServiceStatusWidget::setDlogBoxHidden()
{
	dlogBox_->setHidden(true);
}

void ServiceStatusWidget::onActiveChanged(bool value)
{
	startButton_->setEnabled(!value);
	stopButton_->setEnabled(value);
	if (value)
		stateLabel_->setText(GREENTEXT(BOLD("Активен")));
	else
		stateLabel_->setText(GRAYTEXT("Отключён"));
}

ServicesStatusWidget::ServicesStatusWidget(QList<Service*> services, QWidget* parent)
	: QWidget(parent)
{
	UI_CREATE_VLAYOUT(layout);
	for (auto service: services)
		layout->addWidget(new ServiceStatusWidget(*service, this));
	layout->addStretch();
	layout->addWidget(checkbox_ = new ToogleWidget(
				tr("Сохранять статусы сервисов"), Ramio::config().value("Application/SaveServicesStatus").toInt(), this));
}

ServicesStatusWidget::~ServicesStatusWidget()
{
	 Ramio::changeConfig().setValue("Application/SaveServicesStatus", int(checkbox_->isChecked()));
}

} // Smitto::
