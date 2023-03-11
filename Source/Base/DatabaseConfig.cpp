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

#include "DatabaseConfig.h"
#include <ramio/database/options.h>
#include <ramio/settings/config.h>

namespace Smitto {

Ramio::DatabaseConfig dbconfig(const QString& groupname, const QString& targetName)
{
	Ramio::DatabaseConfig res;
	const Ramio::Config& config = Ramio::config(targetName);
	res.dbname = config.value(groupname + "/Name");
	res.username = config.value(groupname + "/User");
	res.password = config.value(groupname + "/Password");
	res.host = config.value(groupname + "/Host");
	res.port = config.value(groupname + "/Port").toUShort();
	return res;
}

} // Smitto::
