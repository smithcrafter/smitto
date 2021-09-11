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

#include "File.h"
#include <ramio/log/log.h>
// Qt5
#include <QtCore/QByteArray>
#include <QtCore/QFile>

namespace Smitto {

QByteArray readAllFile(const QString& filepath)
{
	QByteArray result;
	QFile file(filepath);
	if (file.open(QIODevice::ReadOnly))
	{
		result = file.readAll();
		file.close();
	}
	else
		WLOG(QString("File %1 not opened").arg(filepath));
	return result;
}

void writeToFile(const QString& filepath, const QByteArray& data)
{
	QFile file(filepath);
	if (file.open(QIODevice::WriteOnly))
	{
		file.write(data);
		file.close();
	}
}

} // Smitto::
