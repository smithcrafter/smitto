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
#include <QtGui/QPalette>

#ifndef POINTSIZE
#ifdef Q_OS_ANDROID
#define POINTSIZE 2
#else
#define POINTSIZE 1
#endif
#endif

namespace Smitto {

enum class Themes : int
{
	Light = 0,
	Dark
};

QList<Themes> themes();

QString themeName(Themes theme);

Themes nextTheme(Themes current);

struct Theme
{
	Themes theme = Themes::Light;
	QPalette pallete;

	QString name() const {return themeName(theme);}
};

} // Smitto::
