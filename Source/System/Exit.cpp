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

#include "Exit.h"
#include <Log/Log.h>
#include <QtCore/QCoreApplication>
#include <signal.h>

namespace Smitto {

namespace Consts {

const int AppUpdateExitCode = 198;
const int AppRestartExitCode = 199;
const int AppNormalExitCode = 200;
const int AppSigIntExitCode = 201;
const int AppSigTermExitCode = 202;

} // Consts::

QString signalName(int sig)
{
	switch (sig) {
		case SIGINT: return "SIGINT";
		case SIGTERM: return "SIGTERM";
#ifdef Q_OS_LINUX
		case SIGUSR1: return "SIGUSR1";
#endif
		default: return "SIG-" % QString::number(sig);
	}
}

void signalHandler(int sig)
{
	int exitCode = 0;

	if (sig == SIGINT)
		exitCode = Consts::AppSigIntExitCode;
	else if (sig == SIGTERM)
		exitCode = Consts::AppSigTermExitCode;
#ifdef Q_OS_LINUX
	else if (sig == SIGUSR1)
		exitCode = Consts::AppUpdateExitCode;
#endif
	LOG("");
	PLOG(QString("signal[%1]=%2").arg(sig).arg(signalName(sig)));
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
