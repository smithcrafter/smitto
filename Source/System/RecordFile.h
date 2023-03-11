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

#include <QtCore/QFile>
#include <Data/KeyValueRecord.h>

namespace Smitto {

/**
 * auto record = readFile<Quik::TradeRecord>(foldername % filename);
 */
template<typename RecordClass>
QList<RecordClass> readRecordsFromFile(const QString& filepath)
{
	QList<RecordClass> res;
	QFile file(filepath);
	if (file.open(QIODevice::ReadOnly))
	{
		while (!file.atEnd()) {
			QString str(file.readLine(4096));
			if (!str.isEmpty())
				res.append(RecordClass(KeyValueRecord(str)));
		}
		file.close();
	}
	return res;
}

} // Smitto::

