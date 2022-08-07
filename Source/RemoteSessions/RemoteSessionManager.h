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

#include "RemoteSession.h"
namespace Ramio {class ConnectionHandler; class Components; struct ConnectionInfo;
namespace Proto { struct QueryPacket; enum class Queries : quint8;
struct QPGetDataObject; struct APGetDataObject;
struct QPGetDataSet; struct APGetDataSet; struct QPCreateDataObject; struct APCreateDataObject;
struct QPSaveDataObject; struct APSaveDataObject; struct QPDeleteDataObject; struct APDeleteDataObject;
}}

namespace Smitto {

class MetaUserSet;

class SMITTO_LIB_EXPORT RemoteSessionManager : public QObject
{
public:
	RemoteSessionManager(Ramio::ConnectionHandler& server, Ramio::Components& components, MetaUserSet& users,
						 QObject* parent = Q_NULLPTR);
	~RemoteSessionManager() Q_DECL_OVERRIDE;

	RemoteSessionSet& sessions() {return sessions_;}

protected:
	virtual bool specialGetDataObject(const Ramio::Proto::QPGetDataObject& query, Ramio::Proto::APGetDataObject& answer,
							  Smitto::RemoteSession* session) {
				Q_UNUSED(query); Q_UNUSED(answer); Q_UNUSED(session); return false;}
	virtual bool specialGetDataSet(const Ramio::Proto::QPGetDataSet& query, Ramio::Proto::APGetDataSet& answer,
								   RemoteSession* session) {
				Q_UNUSED(query); Q_UNUSED(answer); Q_UNUSED(session); return false;}
	virtual bool specialCreateDataObjects(const Ramio::Proto::QPCreateDataObject& query, Ramio::Proto::APCreateDataObject& answer,
								   RemoteSession* session) {
				Q_UNUSED(query); Q_UNUSED(answer); Q_UNUSED(session); return false;}
	virtual bool specialSaveDataObject(const Ramio::Proto::QPSaveDataObject& query, Ramio::Proto::APSaveDataObject& answer,
								   RemoteSession* session) {
				Q_UNUSED(query); Q_UNUSED(answer); Q_UNUSED(session); return false;}
	virtual bool specialDeleteDataObject(const Ramio::Proto::QPDeleteDataObject& query, Ramio::Proto::APDeleteDataObject& answer,
								   RemoteSession* session) {
				Q_UNUSED(query); Q_UNUSED(answer); Q_UNUSED(session); return false;}



private:
	void onQueryReceived(Ramio::Proto::Queries query, const Ramio::Proto::QueryPacket& packet, const Ramio::ConnectionInfo& from);
	void onClientDisconnected(const Ramio::ConnectionInfo& client);

protected:
	void onItemCreated(const Ramio::AbstractMetaSet& set, const Ramio::Item& item);
	void onItemChanged(const Ramio::AbstractMetaSet& set, const Ramio::Item& item);
	void onItemDeleted(const Ramio::AbstractMetaSet& set, const Ramio::Item& item);

private:
	Ramio::ConnectionHandler& server_;
	Ramio::Components& components_;
	Smitto::MetaUserSet& users_;
	Smitto::RemoteSessionSet sessions_;
	qint64 epid_ = 0;
};

} // Smitto::
