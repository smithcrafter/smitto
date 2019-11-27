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

#pragma once

#include <Items/MetaItems.h>

namespace Smitto {

struct UserRecord : Ramio::MetaItemData
{
	QString login;
	QString password;
	QString name;

	RMETA_OBJECT_DECL(Ramio::MetaItemData)
};

GENERATE_HEADER_CLASS(User, UserRecord)

GENERATE_HEADER_CLASS_METASET_START(MetaUserSet, User, UserRecord)

	const User* findUser(const QString& login, const QString& password) const;
};

} // Smitto::
