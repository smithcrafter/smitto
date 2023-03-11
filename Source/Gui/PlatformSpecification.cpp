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

#include "PlatformSpecification.h"
#include <QtCore/QSize>

namespace Smitto {
namespace Ui {

QSize iconSize()
{
#ifdef Q_OS_ANDROID
	return QSize(128, 128);
#endif

	return QSize(32, 32);
}

int panelSize()
{
#ifdef Q_OS_ANDROID
	return 128+10;
#endif
	return 32+10;
}

QSize panelIconSize()
{
#ifdef Q_OS_ANDROID
	return QSize(96, 96);
#endif
	return QSize(24, 24);
}

int panelMargin()
{
#ifdef Q_OS_ANDROID
	return 8;
#endif
	return 4;
}

int panelSpacing()
{
#ifdef Q_OS_ANDROID
	return 8;
#endif
	return 6;
}

} // Ui ::
} // Smitto ::
