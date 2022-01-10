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
#include <QtCore/QObject>
class QTimer;

namespace Smitto {

class SMITTO_LIB_EXPORT Service: public QObject
{
	Q_OBJECT
public:
	Service(const QString& name, int timer = 1000, QObject* parent = Q_NULLPTR);
	~Service() Q_DECL_OVERRIDE;

	void setNotyfyTimeout(qint64 value) {notyfyTimeout_ = value;}

	const QString& name() const {return name_;}

	bool started() const;

	void start();
	void stop();
	void toogle() {started() ? stop() : start();}

	void work();

	bool dlog() {return dlog_;}
	void setDlog(bool value) {dlog_ = value;}

signals:
	void activeChanged(bool started);

protected:
	virtual bool prepareStart() {return true;}
	virtual void processWork() = 0;
	virtual void processStop() {}

protected:
	QString name_;
	bool dlog_ = false;

private:
	QTimer* timer_;
	qint64 notyfyTimeout_ = 200000;
};

} // Smitto::
