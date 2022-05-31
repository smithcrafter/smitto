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

#include "SmittoTheme.h"

namespace Smitto {

QString themeName(Themes theme)
{
	switch (theme) {
		case Themes::Light : return QObject::tr("Ligth");
		case Themes::Dark : return QObject::tr("Dark");
	}
	return QString();
}

QList<Themes> themes()
{
	return {Themes::Light, Themes::Dark};
}

Themes nextTheme(Themes current)
{
	return current == Smitto::Themes::Light ? Smitto::Themes::Dark : Smitto::Themes::Light;
}

} // Smitto::
