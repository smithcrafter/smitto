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
#include <Protocol/ProtocolEnums.h>
#include <Network/NetGlobal.h>
#include <QtCore/QDateTime>

namespace Smitto {

struct SMITTO_LIB_EXPORT RemoteSessionRecord : Ramio::MetaStandardItemData
{
	Ramio::ConnectionInfo netInfo;
	RMDateTime loginTime;
	RMDateTime queryTime;
	RMString login;
	RMPKey userId;

	RemoteSessionRecord() = default;
	RemoteSessionRecord(const RemoteSessionRecord& other) = default;
	RemoteSessionRecord(const Ramio::ConnectionInfo& from) : netInfo(from) {}
};

class SMITTO_LIB_EXPORT RemoteSession;
GENERATE_HEADER_METACLASS_START(RemoteSession, RemoteSessionRecord)
public:
	QMap<const Ramio::AbstractMetaSet*, Ramio::Proto::DataSetChangeNotifications> notificationSets;
};

class SMITTO_LIB_EXPORT RemoteSessionSet;
GENERATE_ITEMSET_START(RemoteSessionSet, RemoteSession, RemoteSessionRecord)

	RemoteSession* sessionByConnectionId(quint16 connectionId);
};

} // Smitto::
