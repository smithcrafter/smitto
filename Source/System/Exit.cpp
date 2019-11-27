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

#include "Exit.h"
#include <signal.h>
#include <QtCore/QCoreApplication>

namespace Smitto {

namespace Consts {

const int AppRestartExitCode = 199;
const int AppNormalExitCode = 200;
const int AppSigIntExitCode = 202;
const int AppSigTermExitCode = 215;
const int AppUpdateExitCode = 210;
} // Consts::

void signalHandler(int sig)
{
	int exitCode = 0;
#ifdef Q_OS_LINUX
	if (sig == SIGINT)
		exitCode = Consts::AppSigIntExitCode;
	if (sig == SIGTERM)
		exitCode = Consts::AppSigTermExitCode;
	else if (sig == SIGUSR1)
		exitCode = Consts::AppUpdateExitCode;
#endif
	qApp->exit(exitCode);
}


ExitHelper::ExitHelper(QCoreApplication& app)
	: QObject(&app)
{
#ifdef Q_OS_LINUX
	signal(SIGINT, signalHandler);
	signal(SIGTERM, signalHandler);
	signal(SIGUSR1, signalHandler);
#endif
}

} // Smitto::
