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

class QSize;
#include <smitto.h>

namespace Smitto {
namespace Ui {

SMITTO_LIB_EXPORT
int panelSize();

SMITTO_LIB_EXPORT
QSize panelIconSize();

SMITTO_LIB_EXPORT
int panelMargin();

SMITTO_LIB_EXPORT
int panelSpacing();

SMITTO_LIB_EXPORT
QSize iconSize();

} // Ui ::
} // Smitto ::
