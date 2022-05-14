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
#include <QtCore/QPointer>
class QPropertyAnimation;
class QVBoxLayout;

namespace Smitto {
namespace Ui {

class BlowWidget : public QWidget
{
	Q_OBJECT
	Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity )
public:
	explicit BlowWidget(qreal opacity = 0.0, QWidget* parent = Q_NULLPTR);
	~BlowWidget() Q_DECL_OVERRIDE;

	qreal opacity() const {return opacity_;}
	void setOpacity(qreal opacity) {opacity_ = opacity; update();/*this->repaint();*/}

signals:
	void clicked();

private:
	void mousePressEvent(QMouseEvent* event);
	void paintEvent(QPaintEvent* event);

private:
	qreal opacity_ = 0.0;
};

enum class MenuStatus
{
	Closed,
	Opening,
	Open,
	Closing
};


class SMITTO_LIB_EXPORT DrawerMenuWidget : public QWidget
{
	Q_OBJECT
public:
	explicit DrawerMenuWidget(QWidget* parent = Q_NULLPTR);
	~DrawerMenuWidget();

	void addMenuButton(qint32 butId, const QString& text);

	void addBottomMenu(qint32 butId, const QString& text);

	void showDrawlerMenu();
	void hideDrawlerMenu();

signals:
	void drawlerClosed();
	void buttonActivated(qint32 butId);
	void logout();

private:
	void showDrawlerMenuFinished();
	void hideDrawlerMenuFinished();
	void cliarAnimations();

	void showEvent(QShowEvent* event);

private:
	QWidget* menuWidget_;
	class BlowWidget* blowWidget_;
	MenuStatus status = MenuStatus::Closed;
	QPointer<QPropertyAnimation> animation1_;
	QPointer<QPropertyAnimation> animation2_;
	QPointer<QPropertyAnimation> animation3_;
	QVBoxLayout* buttonLayout_, *buttomLayout_;
};

} // Ui ::
} // Smitto ::
