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

#include "AuthorizationMobileWidgets.h"
#include <Connection/Connection.h> // ramio
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QLabel>

namespace Smitto {

LoginMobileWidget::LoginMobileWidget(const Ramio::ConnectionParameters& params, QWidget* parent, bool requestPort)
	: QWidget(parent)
{
	auto* loginLayout = new QHBoxLayout(this);
	loginLayout->addStretch();
	auto* layout = new QVBoxLayout();
	layout->addStretch();
	layout->addWidget(new QLabel("IP"));
	layout->addWidget(hostEdit_ = new QLineEdit);
	layout->addWidget(new QLabel("User"));
	layout->addWidget(loginEdit_ = new QLineEdit);
	layout->addWidget(new QLabel("Password"));
	layout->addWidget(passwordEdit_ = new QLineEdit);
	hostEdit_->setText(params.host);
	loginEdit_->setText(params.login);
	passwordEdit_->setText(params.password);
	passwordEdit_->setEchoMode(QLineEdit::EchoMode::Password);
	QPushButton* button;
	layout->addWidget(button = new QPushButton("\nPress\n"));
	layout->addStretch();
	connect(button, &QPushButton::clicked, this, &LoginMobileWidget::onButtonClicked);
	loginLayout->addLayout(layout);
	loginLayout->addStretch();
}

LoginMobileWidget::~LoginMobileWidget()
{
}

void LoginMobileWidget::checkAndPress()
{
	if (!hostEdit_->text().isEmpty() && !loginEdit_->text().isEmpty() && !passwordEdit_->text().isEmpty())
		onButtonClicked();
}

void LoginMobileWidget::onButtonClicked()
{
	Ramio::ConnectionParameters params;
	params.host = hostEdit_->text();
	params.login = loginEdit_->text().trimmed();
	params.password = passwordEdit_->text().trimmed();
	emit acepted(params);
}

ConnectingWidget::ConnectingWidget(QWidget* parent)
	: QWidget(parent)
{
	auto* connectingLayout = new QHBoxLayout(this);
	connectingLayout->addStretch();
	auto* layout = new QVBoxLayout();
	layout->addStretch();
	layout->addWidget(new QLabel(tr("Подключение..."), this));
	QPushButton* button;
	layout->addWidget(button = new QPushButton("\n" + tr("Отмена") + "\n"));
	layout->addStretch();
	connect(button, &QPushButton::clicked, this, &ConnectingWidget::canceled);
	connectingLayout->addLayout(layout);
	connectingLayout->addStretch();
}

ConnectingWidget::~ConnectingWidget()
{
}

} // Smitto::
