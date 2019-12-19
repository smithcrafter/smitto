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

#include "BaseUserItem.h"

namespace Smitto {

RMETA_OBJECT_IMPL(UserRecord)
RMETA_OBJECT_PROPERTY(login, String, "Login", "Пользователь", Field)
RMETA_OBJECT_PROPERTY(password, String, "Password", "Пароль", Field)
RMETA_OBJECT_PROPERTY(name, String, "Name", "Имя", Field)
RMETA_OBJECT_END

GENERATE_SOURCE_CLASS(User, UserRecord)

GENERATE_SOURCE_METASET(MetaUserSet, "Users", "User")

const User* MetaUserSet::findUser(const QString& login, const QString& password) const
{
	for (auto* user : *this)
		if (user->data().login == login && user->data().password == password)
			return user;
	return Q_NULLPTR;
}

} // Smitto::
