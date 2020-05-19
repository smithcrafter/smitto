/*
 * Copyright (C) 2016-2019 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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

#include "SmittoColors.h"
// Qt5
#include <QtCore/QString>

namespace Smitto {

QString scolor(SmittoBaseColors color)
{
	switch (color) {
	case SmittoBaseColors::Unset : return "#000000";
	case SmittoBaseColors::level01 : return "#151c2a";
	case SmittoBaseColors::level02 : return "#21293a";
	case SmittoBaseColors::level03 : return "#313a4c";
	case SmittoBaseColors::level04 : return "#414a5e";
	case SmittoBaseColors::level05 : return "#606d88";
	case SmittoBaseColors::level06 : return "#7281a0";
	case SmittoBaseColors::level07 : return "#8996b0";
	case SmittoBaseColors::level08 : return "#96a2b9";
	case SmittoBaseColors::level09 : return "#a0acc4";
	case SmittoBaseColors::level10 : return "#bfc7d9";
	case SmittoBaseColors::level11 : return "#e8ebf0";
	case SmittoBaseColors::level12 : return "#f6f7f9";
	case SmittoBaseColors::Red : return "#cc0000";
	case SmittoBaseColors::BoldRed : return "#ef2929";
	case SmittoBaseColors::Green : return "#4e9a06";
	case SmittoBaseColors::BoldGreen : return "#8ae234";
	case SmittoBaseColors::Yellow : return "#c4a000";
	case SmittoBaseColors::BoldYellow : return "#fce94f";
	case SmittoBaseColors::Blue : return "#3465a4";
	case SmittoBaseColors::BoldBlue : return "#739fcf";
	case SmittoBaseColors::Purple : return "#75507b";
	case SmittoBaseColors::BoldPurple : return "#ad7fa8";
	case SmittoBaseColors::Cyan : return "#06989a";
	case SmittoBaseColors::BoldCyan : return "#34e2e2";
	}
	return "#000000";
}

QString ccolor(ConsoleColors color, bool bold)
{
	switch (color) {
		case ConsoleColors::Black : return scolor(!bold ? SmittoBaseColors::level01: SmittoBaseColors::level03);
		case ConsoleColors::Red : return scolor(!bold ? SmittoBaseColors::Red: SmittoBaseColors::BoldRed);
		case ConsoleColors::Green : return scolor(!bold ? SmittoBaseColors::Green: SmittoBaseColors::BoldGreen);
		case ConsoleColors::Yellow : return scolor(!bold ? SmittoBaseColors::Yellow: SmittoBaseColors::BoldYellow);
		case ConsoleColors::Blue : return scolor(!bold ? SmittoBaseColors::Blue: SmittoBaseColors::BoldBlue);
		case ConsoleColors::Purple : return scolor(!bold ? SmittoBaseColors::Purple: SmittoBaseColors::BoldPurple);
		case ConsoleColors::Cyan : return scolor(!bold ? SmittoBaseColors::Cyan: SmittoBaseColors::BoldCyan);
		case ConsoleColors::White : return scolor(!bold ? SmittoBaseColors::level12: SmittoBaseColors::level09);
	}
	return "#000000";
}

} // Smitto::
