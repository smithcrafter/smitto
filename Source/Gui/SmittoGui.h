/*
 * Copyright (C) 2019-2023 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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

#include "PlatformSpecification.h"
#include "SmittoTheme.h"
#include "SmittoStyleSheets.h"
#include "SmittoColors.h"
class QGraphicsDropShadowEffect;

namespace Smitto {
namespace Ui {

QString clipboardText();

QGraphicsDropShadowEffect* addDropShadowEffect(QWidget& widget, const QColor& color, qreal BlurRadius,
											   qreal xOffset, qreal yOffset);

} // Ui ::
} // Smitto ::
