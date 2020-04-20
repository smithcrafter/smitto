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
	case SmittoBaseColors::lelev01 : return "#151c2a";
	case SmittoBaseColors::lelev02 : return "#21293a";
	case SmittoBaseColors::lelev03 : return "#313a4c";
	case SmittoBaseColors::lelev04 : return "#414a5e";
	case SmittoBaseColors::lelev05 : return "#606d88";
	case SmittoBaseColors::lelev06 : return "#7281a0";
	case SmittoBaseColors::lelev07 : return "#8996b0";
	case SmittoBaseColors::lelev08 : return "#96a2b9";
	case SmittoBaseColors::lelev09 : return "#a0acc4";
	case SmittoBaseColors::lelev10 : return "#bfc7d9";
	case SmittoBaseColors::lelev11 : return "#e8ebf0";
	case SmittoBaseColors::lelev12 : return "#f6f7f9";
	case SmittoBaseColors::Red : return "#CC0000";
	case SmittoBaseColors::BoldRed : return "#EF2929";
	case SmittoBaseColors::Green : return "#4E9A06";
	case SmittoBaseColors::BoldGreen : return "#9FD873";
	case SmittoBaseColors::Yellow : return "#C4A000";
	case SmittoBaseColors::BoldYellow : return "#FCE94F";
	case SmittoBaseColors::Blue : return "#3465A4";
	case SmittoBaseColors::BoldBlue : return "#739FCF";
	case SmittoBaseColors::Purple : return "#75507B";
	case SmittoBaseColors::BoldPurple : return "#AD7FA8";
	case SmittoBaseColors::Cyan : return "#06989A";
	case SmittoBaseColors::BoldCyan : return "#34E2E2";
	}
	return "#000000";
}

} // Smitto::
