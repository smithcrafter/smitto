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

#pragma once

// #define USE_QLIB

#include <smitto.h>
#include <QtWidgets/QWidget>
class QLabel;
class QStackedWidget;
class QNetworkAccessManager;
#ifdef USE_QLIB
#include <QtCore/QLibrary>
#endif

namespace Smitto {

typedef QObject*   (*createEngineFPrt)();
typedef QWidget*   (*createWidgetFPtr)(QObject&);

class SMITTO_LIB_EXPORT LibLoaderWidget : public QWidget
{
	Q_OBJECT
public:
	LibLoaderWidget(const QString& libPath, const QString& libUrl, QWidget* parent = Q_NULLPTR);
	~LibLoaderWidget() Q_DECL_OVERRIDE;

	void loadSettings();
	void saveSettings();

	void check();

public slots:
	Q_SLOT void downoad();

private:
	void onFinished();
	void unload();
	void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;

private:
	QString libPath_;
	const QString libUrl_;
#ifdef USE_QLIB
	QLibrary library_;
#else
	void* handle = Q_NULLPTR;
#endif
	QNetworkAccessManager* manager_ = Q_NULLPTR;
	QStackedWidget* stackedWidget_;
	QWidget *checkWidget_, *donwloadWidget_, *updateWidget_, *errorWidget_;
	QLabel *checkLabel_, *donwloadLabel_, *errorLabel_;
	QObject* engine_;
	QWidget* widget_;
	int ver = 0;
};

} // Smitto::
