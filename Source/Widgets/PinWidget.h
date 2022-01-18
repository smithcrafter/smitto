/*
 * Copyright (C) 2020-2022 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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
class QPushButton;

namespace Smitto {

enum class PinButtons
{
	B0 = 0, B1, B2, B3, B4, B5, B6, B7, B8, B9,
	Clear
};

class PointCircleWidget : public QWidget
{
public:
	explicit PointCircleWidget(const QColor& color, qint8 size, QWidget* parent = Q_NULLPTR);

	void change(const QColor& color, qint8 size);

private:
	void paintEvent(QPaintEvent* event);

private:
	QColor color_;
	qint8 size_;
};


class PinWidget : public QWidget
{
	Q_OBJECT
public:
	explicit PinWidget(QWidget* parent = Q_NULLPTR);

	void onButtonPressed(PinButtons button);

signals:
	void pinEntered(const QList<quint8>& numbers);

private:
	void showEvent(QShowEvent* event) Q_DECL_OVERRIDE;
	void keyPressEvent(QKeyEvent* event) Q_DECL_OVERRIDE;

private:
	PointCircleWidget* points_[4];
	QPushButton* numbuttons_[11];
	QList<quint8> numbers_;
};

} // Smitto::
