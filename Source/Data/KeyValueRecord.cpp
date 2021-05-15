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

#include "KeyValueRecord.h"
// Ramio
#include <Global/Strings.h>
// Qt5
#include <QStringBuilder>

#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
#define QRegExp QRegularExpression
#endif

namespace Smitto {

KeyValueRecord::KeyValueRecord(const QString& str)
{
	if (str.isEmpty())
		return;

	QStringList list;
	qint32 pos = 0, splitLIndex = -1;
	do {
		splitLIndex = str.indexOf(QRegExp("[;]"), splitLIndex+1);
		if (splitLIndex+1 != str.length() && str[splitLIndex+1] == QChar(';'))
			splitLIndex++;
		else
		{
			qint32 size = (splitLIndex == -1) ? -1 : splitLIndex - pos;
			list.append(str.mid(pos, size));
			pos = splitLIndex + 1;
		}

	} while (splitLIndex != -1);

	for (const QString& value: list)
	{
		QString strValue = value.trimmed().replace(Ramio::doubleSemicolonStr, Ramio::semicolonStr);

		if (!strValue.isEmpty())
		{
			qint32 splitIndex = strValue.indexOf(QRegExp("[^:][:][^:]"));
			if (splitIndex == -1)
				keywords_.append(strValue.replace(Ramio::doubleColonStr, Ramio::colonStr));
			else if (splitIndex == 0)
			{
				QString v = value.trimmed().mid(1);
				if (!v.isEmpty())
					keywords_.append(v);
			}
			else
			{
				QString k = strValue.mid(0, 1+splitIndex).trimmed()
						.replace(Ramio::doubleColonStr, Ramio::colonStr);
				QString v = strValue.mid(1+splitIndex+1).trimmed()
						.replace(Ramio::doubleColonStr, Ramio::colonStr).replace(Ramio::doubleSemicolonStr, Ramio::semicolonStr);
				if (!k.isEmpty() && !v.isEmpty())
					values_[k] = v;
				else if (!k.isEmpty())
					keywords_.append(k);
				else if (!v.isEmpty())
					keywords_.append(v);
			}
		}
	}
}

KeyValueRecord::~KeyValueRecord() = default;

QString KeyValueRecord::value(const QString& key, const QString& defValue) const
{
	return values_.contains(key) ? values_[key] : defValue;
}

void KeyValueRecord::setKeyValue(const QString& key, const QString& value)
{
	values_.insert(key, value);
}

void KeyValueRecord::setKeyValue(const QString& key, qint32 value)
{
	values_.insert(key, QString::number(value));
}

void KeyValueRecord::setKeyValue(const QString &key, qint64 value)
{
	values_.insert(key, QString::number(value));
}

void KeyValueRecord::addKeyWord(const QString& keyword)
{
	keywords_.append(keyword);
}

QString KeyValueRecord::createStr() const
{
	QString result;
	for (auto it = values_.constBegin(); it != values_.constEnd(); ++it)
	{
		QString key = QString(it.key()).replace(Ramio::colonStr, Ramio::doubleColonStr).replace(Ramio::semicolonStr, Ramio::doubleSemicolonStr);
		QString value = QString(it.value()).replace(Ramio::colonStr, Ramio::doubleColonStr).replace(Ramio::semicolonStr, Ramio::doubleSemicolonStr);
		result.append(key % Ramio::colonStr % value % Ramio::semicolonStr);
	}
	for (const QString& str: keywords_)
	{
		QString key = QString(str).replace(Ramio::colonStr, Ramio::doubleColonStr).replace(Ramio::semicolonStr, Ramio::doubleSemicolonStr);
		result.append(key % Ramio::semicolonStr);
	}
	return result;
}

} // Smitto::
