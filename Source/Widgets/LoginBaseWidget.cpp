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

#include "LoginBaseWidget.h"
#include <Sets/Config.h>
#include <Sets/UISets.h>
#include <Sets/Arg.h>
#include <Global/Text.h>
#include <Gui/Global.h>
#include <Log/Log.h>
// Qt5
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QGridLayout>
#include <QtCore/QTimer>

namespace Smitto {

LoginBaseWidget::LoginBaseWidget(const QString& title, QWidget* parent)
	: QWidget(parent)
{
	this->setWindowTitle(title);
	UI_CREATE_GLAYOUT(layout)
	QLabel* label;
	layout->addWidget(label = new QLabel, 0, 0, 3, 1);
	layout->addWidget(label = new QLabel(H1(title)), 0, 1, 1, 3);
	layout->addWidget(label = new QLabel(tr("Пользователь")), 1, 1);
	layout->addWidget(label = new QLabel(tr("Пароль")), 2, 1);
	layout->addWidget(loginEdit_ = new QLineEdit(), 1, 2);
	layout->addWidget(passEdit_ = new QLineEdit(), 2, 2);
	passEdit_->setEchoMode(QLineEdit::PasswordEchoOnEdit);
	QPushButton* button;
	layout->addWidget(button = new QPushButton(tr("Вход")), 1, 3, 2, 1);
	connect(button, &QPushButton::clicked, this, &LoginBaseWidget::checkLogin);
	button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	if (APP_ARG_CONTAINS(APP_ARGUMENT("AUTOLOGIN")))
		QTimer::singleShot(200, this, &LoginBaseWidget::autoLogin);
	loginEdit_->setFocus();
}

void LoginBaseWidget::autoLogin()
{
	QString login = Ramio::config().value("User/Login");
	if (login.isEmpty())
		login = APP_ARG("Login");
	if (login.isEmpty())
		login = "user1";

	QString password = Ramio::config().value("User/Password");
	if (password.isEmpty())
		password = APP_ARG("Password");
	if (password.isEmpty())
		password = "1";

	loginEdit_->setText(login);
	passEdit_->setText(password);

	DLOG_POINT;
	checkLogin();
}

void LoginBaseWidget::checkLogin()
{
	if (loginEdit_->text().isEmpty())
		loginEdit_->setFocus();
	else if (passEdit_->text().isEmpty())
		passEdit_->setFocus();
	else
		emit accepted(loginEdit_->text(), passEdit_->text());
}

} // Smitto::
