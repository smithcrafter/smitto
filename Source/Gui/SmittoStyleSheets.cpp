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

#include "SmittoStyleSheets.h"
// Qt5
#include <QtCore/QString>

namespace Smitto {

const QString emptyStyleSheet;
const QString l1StyleSheet("QWidget {background: #C4CACA;}"); // C4CACA, текст D9D9D9
const QString l2StyleSheet("QWidget {background: #E3E3E3;}"); // E3E3E3, текст EEEEEE
const QString l3StyleSheet("QWidget {background: #F2F2F2;}"); // F2F2F2
const QString l4StyleSheet("QWidget {background: #FEFEFE;}"); // FEFEFE

} // Smitto::
