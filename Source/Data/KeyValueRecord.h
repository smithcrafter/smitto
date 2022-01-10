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

#pragma once

#include <smitto.h>
#include <QtCore/QMap>
#include <QStringList>

namespace Smitto {

struct SMITTO_LIB_EXPORT KeyValueRecord
{
	KeyValueRecord() = default;
	KeyValueRecord(const QString& str);
	~KeyValueRecord();

	const QMap<QString, QString>& values() const {return values_;}
	const QStringList& keywords() const {return keywords_;}

	QString value(const QString& key, const QString& defaultValue = QString()) const;
	bool contains(const QString& key) const {return containsKey(key) || containsKeyword(key);}
	bool containsKey(const QString& key) const {return values_.contains(key);}
	bool containsKeyword(const QString& key) const {return keywords_.contains(key);}
	bool isEmpty() const {return values_.isEmpty() && keywords_.isEmpty();}

	void setKeyValue(const QString& key, const QString& value);
	void setKeyValue(const QString& key, qint32 value);
	void setKeyValue(const QString& key, qint64 value);
	void addKeyWord(const QString& keyword);

	QString createStr() const;

private:
	QMap<QString, QString> values_;
	QStringList keywords_;
};

} // Smitto::
