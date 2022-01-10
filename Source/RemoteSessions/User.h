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
#include <Items/MetaItems.h>
#include <QtCore/QDateTime>

namespace Smitto {

struct SMITTO_LIB_EXPORT UserRecord : Ramio::MetaStandardItemData
{
	RMString login;
	RMString password;
	RMString name;
    RMDateTime birthday;

	RMETA_DATA_DECL(Ramio::MetaStandardItemData)
};

class SMITTO_LIB_EXPORT User;
GENERATE_HEADER_METACLASS(User, UserRecord)

class SMITTO_LIB_EXPORT MetaUserSet;
GENERATE_HEADER_METASET_START(MetaUserSet, User, UserRecord)

	User* findUser(const QString& login, const QString* password = Q_NULLPTR);
	const User* findUser(const QString& login, const QString* password = Q_NULLPTR) const {
		return const_cast<MetaUserSet*>(this)->findUser(login, password);}
};

} // Smitto::
