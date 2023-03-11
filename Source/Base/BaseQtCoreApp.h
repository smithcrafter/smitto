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
#include <QtCore/QCoreApplication>

namespace Smitto {

class SMITTO_LIB_EXPORT BaseQtCoreApp : public QCoreApplication
{
public:
	BaseQtCoreApp(int& argc, char** argv, int af = ApplicationFlags);
	~BaseQtCoreApp() Q_DECL_OVERRIDE;

protected:
	bool notify(QObject* receiver, QEvent* event) Q_DECL_OVERRIDE;
};

} // Smitto::
