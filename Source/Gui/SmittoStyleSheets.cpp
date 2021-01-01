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

#include "SmittoStyleSheets.h"
#include "SmittoColors.h"
// Qt5
#include <QtCore/QString>

namespace Smitto {

const QString emptyss;
const QString l01ss = QString("QWidget {background: %1; color: %2;}")
					  .arg(scolor(SmittoBaseColors::level01), scolor(SmittoBaseColors::level07));
const QString l02ss = QString("QWidget {background: %1; color: %2;}")
					  .arg(scolor(SmittoBaseColors::level02), scolor(SmittoBaseColors::level08));
const QString l03ss = QString("QWidget {background: %1; color: %2;}")
					  .arg(scolor(SmittoBaseColors::level03), scolor(SmittoBaseColors::level09));
const QString l04ss = QString("QWidget {background: %1; color: %2;}")
					  .arg(scolor(SmittoBaseColors::level04), scolor(SmittoBaseColors::level10));
const QString l05ss = QString("QWidget {background: %1; color: %2;}")
					  .arg(scolor(SmittoBaseColors::level05), scolor(SmittoBaseColors::level11));
const QString l06ss = QString("QWidget {background: %1; color: %2;}")
					  .arg(scolor(SmittoBaseColors::level06), scolor(SmittoBaseColors::level12));
const QString l07ss = QString("QWidget {background: %1;}").arg(scolor(SmittoBaseColors::level07));
const QString l08ss = QString("QWidget {background: %1;}").arg(scolor(SmittoBaseColors::level08));
const QString l09ss = QString("QWidget {background: %1;}").arg(scolor(SmittoBaseColors::level09));
const QString l10ss = QString("QWidget {background: %1;}").arg(scolor(SmittoBaseColors::level10));
const QString l11ss = QString("QWidget {background: %1;}").arg(scolor(SmittoBaseColors::level11));
const QString l12ss = QString("QWidget {background: %1;}").arg(scolor(SmittoBaseColors::level12));

} // Smitto::
