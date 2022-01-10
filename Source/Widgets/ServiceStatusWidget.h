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

#pragma once

#include <smitto.h>
#include <QtWidgets/QWidget>
class QLabel;
class QToolButton;
class QAbstractButton;

namespace Smitto {

class Service;

class ServiceStatusWidget : public QWidget
{
public:
	ServiceStatusWidget(Service& service, QWidget* parent = Q_NULLPTR);

	void setDlogBoxHidden();

private:
	void onActiveChanged(bool value);

private:
	QToolButton* startButton_;
	QToolButton* stopButton_;
	QAbstractButton* dlogBox_;
	QLabel* stateLabel_;
};

class ServicesStatusWidget : public QWidget
{
public:
	ServicesStatusWidget(QList<Service*> services, QWidget* parent = Q_NULLPTR);
	~ServicesStatusWidget() Q_DECL_OVERRIDE;

private:
	QAbstractButton* checkbox_;
};

} // Smitto::
