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


#pragma once

#include <QtWidgets/QAbstractButton>
class QLabel;

namespace Smitto {

class ToogleWidget : public QAbstractButton
{
public:
	ToogleWidget(QWidget* parent = Q_NULLPTR);
	ToogleWidget(bool checked, QWidget* parent = Q_NULLPTR) : ToogleWidget (parent) {setChecked(checked);}
	ToogleWidget(const QString& text, bool checked, QWidget* parent = Q_NULLPTR);
	ToogleWidget(const QString& text, QWidget* parent = Q_NULLPTR) : ToogleWidget (text, false, parent) {}

protected:
	void mousePressEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
	void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;
	QSize sizeHint() const Q_DECL_OVERRIDE;

private:
	QTimer* timer_;
	quint8 pos = 0;
	QLabel* label_ = Q_NULLPTR;
};

} // Smitto::