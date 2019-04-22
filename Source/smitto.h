#pragma once

#include <qcompilerdetection.h>

#ifdef SMITTO_LIB
	# define SMITTO_LIB_EXPORT Q_DECL_EXPORT
#elif defined(SMITTO_DIRECT)
	# define SMITTO_LIB_EXPORT
#else
	# define SMITTO_LIB_EXPORT Q_DECL_IMPORT
#endif

