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
GENERATE_HEADER_CLASS_METASET(MetaUserSet, User, UserRecord)

} // Smitto::
