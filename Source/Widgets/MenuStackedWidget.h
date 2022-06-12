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

#include <Gui/SmittoStyleSheets.h>
#include <Gui/QtWidgetsDeclaration.h>
#include <QtCore/QMap>
class QBoxLayout;

namespace Smitto {

class SMITTO_LIB_EXPORT MenuStackedWidget : public QWidget
{
public:
	MenuStackedWidget(const QString& activeStyleSheet, const QString& backgroundStyleSheet, Qt::Orientation orientation,
					  QWidget* parent = Q_NULLPTR);
	~MenuStackedWidget() Q_DECL_OVERRIDE;

	void selectMenuItem(QWidget* watched);
	void selectWidgetItem(QWidget* watched);
	void selectFirstMenuItem();

	QWidget* insertMenuWidget(const QString& menutext, QWidget* content, int pos = -1);
	void insertMenuWidget(QWidget* menu, QWidget* content, int pos = -1);

	void insertMenuStretch();

	QWidget* baseMenuWidget() {return baseMenuWidget_;}

	QVBoxLayout* topStackedLayout() {return topStackedLayout_;}
	QVBoxLayout* rigthStackedLayout() {return rigthStackedLayout_;}
	QVBoxLayout* bottomStackedLayout() {return bottomStackedLayout_;}

	const QMap<QWidget*, QWidget*>& widgets() const {return widgets_;}

	QWidget* currentWidget() const;

protected:
	bool eventFilter(QObject* watched, QEvent* event) Q_DECL_OVERRIDE;

private:
	const QString& activeStyleSheet_;
	const QString& backgroundStyleSheet_;
	QMap<QWidget*, QWidget*> widgets_;
	QStackedWidget* stackedWidget_;
	QBoxLayout* menuLayout_;
	QVBoxLayout* topStackedLayout_;
	QVBoxLayout* rigthStackedLayout_;
	QVBoxLayout* bottomStackedLayout_;
	//Corner
	QWidget* baseMenuWidget_;
	QWidget* lastActiveMenu_ = Q_NULLPTR;
};

} // Smitto::
