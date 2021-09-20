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

#include "RemoteSessionManager.h"
#include "User.h"
// Ramio
#include <Connection/TcpServerHandler.h>
#include <RamioProtocol>
#include <Log/Log.h>
#include <Items/Components.h>

namespace Smitto {

RemoteSessionManager::RemoteSessionManager(Ramio::ConnectionHandler& server, Ramio::Components& components,
										   MetaUserSet& users, QObject* parent)
	: QObject(parent),
	  server_(server),
	  components_(components),
	  users_(users)
{
	connect(&server_, &Ramio::ConnectionHandler::queryReceived, this, &RemoteSessionManager::onQueryReceived);
	connect(&server_, &Ramio::ConnectionHandler::clientDisconnected, this, &RemoteSessionManager::onClientDisconnected);
	connect(&components, &Ramio::Components::itemCreated, this, &RemoteSessionManager::onItemCreated);
	connect(&components, &Ramio::Components::itemChanged, this, &RemoteSessionManager::onItemChanged);
	connect(&components, &Ramio::Components::itemDeleted, this, &RemoteSessionManager::onItemDeleted);
}

RemoteSessionManager::~RemoteSessionManager()
{
}

void RemoteSessionManager::onQueryReceived(Ramio::Proto::Queries query, const Ramio::Proto::QueryPacket& packet,
										   const Ramio::ConnectionInfo& from)
{
	auto* session = static_cast<RemoteSession*>(sessions_.itemByUuid(QUuid(packet.sessionKey)));

	if (query == Ramio::Proto::Queries::Login)
	{
		auto& qlp = reinterpret_cast<const Ramio::Proto::QPLogin&>(packet);
		Ramio::Proto::APLogin answerPacket(packet.pid);
		if (session)
		{
			answerPacket.setResDesc(RD_WARNING, "Авторизация уже произведена");
			WLOG("Повторная авторизация");
		}
		else if (const User* user = users_.findUser(qlp.username, &qlp.password))
		{
			auto* sesion = new RemoteSession(RemoteSessionRecord(from));
			sesion->createUuidIfNull();
			sesion->data().loginTime = QDateTime::currentDateTime();
			sesion->data().queryTime = sesion->data().loginTime;
			sesion->data().login = qlp.username;
			sesion->data().userId = user->id();
			answerPacket.res = 0;
			answerPacket.userId = QString::number(user->id());
			answerPacket.name = user->data().name;
			answerPacket.uuid = user->uuidStr();
			answerPacket.sessionKey = sesion->uuidStr();
			sessions_.insertItem(sesion);
			PLOG("Авторизация " % answerPacket.name);
		}
		else
		{
			answerPacket.setResDesc(RD_AUTHORIZATION_ERROR, "Сбой авторизации");
			PLOG("Сбой авторизации");
		}

		server_.sendAnswer(query, answerPacket, from);
		return;
	}

	if (!session)
	{
		Ramio::Proto::AnswerPacket answerPacket(Ramio::Proto::PacketType::Query, int(query), packet.pid);
		answerPacket.setResDesc(RD_SESSION_ERROR, "Ошибка сессии");
		server_.sendAnswer(query, answerPacket, from);
		PLOG("Сессия не обнаружена");
		return;
	}

	session->changer().data().queryTime = QDateTime::currentDateTime();

	if (query == Ramio::Proto::Queries::GetDataObject)
	{
		auto& queryPacket = reinterpret_cast<const Ramio::Proto::QPGetDataObject&>(packet);
		Ramio::Proto::APGetDataObject answerPacket(packet.pid);
		if (specialGetDataObject(queryPacket, answerPacket, session))
		{
			// empty block
		}
		else
			answerPacket.setResDesc(RD_DATA_ERROR, tr("Данные не найдены"));
	}
	else if (query == Ramio::Proto::Queries::GetDataSet)
	{
		auto& queryPacket = reinterpret_cast<const Ramio::Proto::QPGetDataSet&>(packet);
		Ramio::Proto::APGetDataSet answerPacket(packet.pid);
		if (auto set = components_.findSet(queryPacket.dataSetName))
		{
			answerPacket.dataSetName = queryPacket.dataSetName;
			answerPacket.set = set;
			if (queryPacket.dataSetChangeNotification)
				session->notificationSets.append(set);
		}
		else if (specialGetDataSet(queryPacket, answerPacket, session))
		{
			// empty block
		}
		else
			answerPacket.setResDesc(RD_DATA_ERROR, tr("Данные не найдены"));
		server_.sendAnswer(query, answerPacket, from);
	}
	else if (query == Ramio::Proto::Queries::CreateDataObject)
	{
		auto& queryPacket = reinterpret_cast<const Ramio::Proto::QPCreateDataObject&>(packet);
		Ramio::Proto::APCreateDataObject answerPacket(packet.pid);
		if (specialCreateDataObjects(queryPacket, answerPacket, session))
		{
			// empty block
		}
		else
			answerPacket.setResDesc(RD_DATA_ERROR, tr("Обработчик не установлен"));
		server_.sendAnswer(query, answerPacket, from);
	}
	else if (query == Ramio::Proto::Queries::SaveDataObject)
	{
		auto& queryPacket = reinterpret_cast<const Ramio::Proto::QPSaveDataObject&>(packet);
		Ramio::Proto::APSaveDataObject answerPacket(packet.pid);
		if (specialSaveDataObject(queryPacket, answerPacket, session))
		{
			// empty block
		}
		else
			answerPacket.setResDesc(RD_DATA_ERROR, tr("Обработчик не установлен"));
		server_.sendAnswer(query, answerPacket, from);
	}
	else if (query == Ramio::Proto::Queries::DeleteDataObject)
	{
		auto& queryPacket = reinterpret_cast<const Ramio::Proto::QPDeleteDataObject&>(packet);
		Ramio::Proto::APDeleteDataObject answerPacket(packet.pid);
		if (specialDeleteDataObject(queryPacket, answerPacket, session))
		{
			// empty block
		}
		else
			answerPacket.setResDesc(RD_DATA_ERROR, tr("Обработчик не установлен"));
		server_.sendAnswer(query, answerPacket, from);
	}
	else
	{
		Ramio::Proto::AnswerPacket answerPacket(Ramio::Proto::PacketType::Query, int(query), packet.pid);
		answerPacket.setResDesc(RD_NOT_SUPPOT, "Команда не реализована");
		server_.sendAnswer(query, answerPacket, from);
		return;
	}
}

void RemoteSessionManager::onClientDisconnected(const Ramio::ConnectionInfo& client)
{
	if (const auto* session = sessions_.sessionByConnectionId(client.connectionId))
	{
		PLOG("Клиент отключился");
		sessions_.removeItem(*session);
		return;
	}
}

void RemoteSessionManager::onItemCreated(const Ramio::AbstractMetaSet& set, const Ramio::Item& item)
{
	if (sessions_.isEmpty())
		return;
	Ramio::Proto::EPDataObjectCreated eventPacket(set.meta().setName, set.meta().itemName, epid_++);
	eventPacket.createFromData(set.meta(), item.data());
	for (auto* session: sessions_.items())
		if (session->notificationSets.contains(&set))
			server_.sendEvent(Ramio::Proto::Events::DataObjectCreated, eventPacket, session->data().netInfo);
}

void RemoteSessionManager::onItemChanged(const Ramio::AbstractMetaSet& set, const Ramio::Item& item)
{
	if (sessions_.isEmpty())
		return;
	Ramio::Proto::EPDataObjectChanged eventPacket(set.meta().setName, set.meta().itemName, epid_++);
	eventPacket.createFromData(set.meta(), item.data());
	for (auto* session: sessions_.items())
		if (session->notificationSets.contains(&set))
			server_.sendEvent(Ramio::Proto::Events::DataObjectChanged, eventPacket, session->data().netInfo);
}

void RemoteSessionManager::onItemDeleted(const Ramio::AbstractMetaSet& set, const Ramio::Item& item)
{
	if (sessions_.isEmpty())
		return;
	QString itemUuid;
	if (auto uuiddiff = set.meta().fieldDiff("uuid", Ramio::Meta::Type::Uuid))
		itemUuid = item.data().field<RMUuid>(uuiddiff).toString();
	Ramio::Proto::EPDataObjectDeleted eventPacket(set.meta().setName, set.meta().itemName, QString::number(item.id()),
												  itemUuid, epid_++);
	for (auto* session: sessions_.items())
		if (session->notificationSets.contains(&set))
			server_.sendEvent(Ramio::Proto::Events::DataObjectDeleted, eventPacket, session->data().netInfo);
}

} // Smitto::
