#include "BaseUserItem.h"

namespace Smitto {

RMETA_OBJECT_IMPL(UserRecord)
RMETA_OBJECT_PROPERTY(login, String, "Login", "Пользователь", Field)
RMETA_OBJECT_PROPERTY(password, String, "Password", "Пароль", Field)
RMETA_OBJECT_PROPERTY(name, String, "Name", "Имя", Field)
RMETA_OBJECT_END

GENERATE_SOURCE_CLASS(User, UserRecord)

GENERATE_SOURCE_CLASS_METASET(MetaUserSet, "Users", "User")

} // Smitto::
