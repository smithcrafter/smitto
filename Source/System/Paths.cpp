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

#include "Paths.h"
// Qt5
#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtCore/QStandardPaths>

namespace Smitto {

#ifdef Q_OS_LINUX
	const QString tmppath = "/tmp/";
#elif defined Q_OS_WIN
	const  QString tmppath = "C:/tmp/";
#endif


QString appDataPath()
{
	QString path = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation).first();
	QDir(path).mkpath(path);
	return path;
}

QString appObjectsPath()
{
	QString path = QCoreApplication::applicationDirPath() + "/Objects";
	QDir(path).mkpath(path);
	return path;
}

} // Smitto::
