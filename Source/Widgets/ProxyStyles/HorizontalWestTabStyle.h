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

#pragma once

#include <smitto.h>
#include <QtWidgets/QProxyStyle>
#include <QtWidgets/QTabBar>
class QStyleOption;

namespace Smitto {

class SMITTO_LIB_EXPORT HorizontalWestTabStyle : public QProxyStyle
{
public:
	HorizontalWestTabStyle(float kx = 1.5, float ky = 2);

protected:
	QSize sizeFromContents(ContentsType type, const QStyleOption* option, const QSize& size, const QWidget* widget) const Q_DECL_OVERRIDE;
	void drawControl(ControlElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget) const Q_DECL_OVERRIDE;

private:
	float kx_;
	float ky_;
};

} // Smitto::
