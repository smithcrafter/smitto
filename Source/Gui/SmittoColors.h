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

#include <smitto.h>

namespace Smitto {

enum class SmittoBaseColors : int
{
	Unset = 0,
	level01,
	level02,
	level03,
	level04,
	level05,
	level06,
	level07,
	level08,
	level09,
	level10,
	level11,
	level12,
	Red,
	BoldRed,
	Green,
	BoldGreen,
	Yellow,
	BoldYellow,
	Blue,
	BoldBlue,
	Purple,
	BoldPurple,
	Cyan,
	BoldCyan
};

QString scolor(SmittoBaseColors color);

enum class ConsoleColors : int
{
	Black,
	Red,
	Green,
	Yellow,
	Blue,
	Purple,
	Cyan,
	White
};

QString ccolor(ConsoleColors color, bool bold);

} // Smitto::
