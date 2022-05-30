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
#include <QtWidgets/QLabel>
#include <QtGui/QMouseEvent>

namespace Smitto {

class MQLabel : public QLabel
{
public:
	MQLabel(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags())
		: QLabel (parent, f) {}
	MQLabel(const QString& text, QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags())
		: QLabel (text, parent, f) {}

	void mousePressEvent(QMouseEvent* event) Q_DECL_OVERRIDE {QLabel::mousePressEvent(event); event->ignore();}
	void mouseReleaseEvent(QMouseEvent* event) Q_DECL_OVERRIDE {QLabel::mouseReleaseEvent(event); event->ignore();}
	void mouseMoveEvent(QMouseEvent* event) Q_DECL_OVERRIDE {QLabel::mouseMoveEvent(event); event->ignore();}
};

} // Smitto::
