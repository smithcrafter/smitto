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

#include <smitto.h>
#include <QtWidgets/QWidget>
#include <QtCore/QMap>
class QLabel; class QPushButton;

namespace Smitto {
namespace Ui {

enum class SubButtons : quint8
{
	None,
	Add = 1,
	Save = 2,
	Menu = 4,
	Refresh = 8,
	Clear = 16,
	Delete = 32,
	Edit = 64,
	Apply = 128,
	LastEnmnItem = Apply
};

inline SubButtons operator | (SubButtons b1, SubButtons b2) {return SubButtons(quint8(b1) | quint8(b2));}
inline SubButtons operator & (SubButtons b1, SubButtons b2) {return SubButtons(quint8(b1) & quint8(b2));}

enum class MainPanellButton : quint8
{
	None,
	Home,
	Back
};

class SMITTO_LIB_EXPORT ControlPanelWidget : public QWidget
{
	Q_OBJECT
public:
	ControlPanelWidget(const QString& basename, QWidget* parent = Q_NULLPTR);
	~ControlPanelWidget() Q_DECL_OVERRIDE;

	int section() const {return section_;}

	void home();
	void setSection(int sectionId, const QString& name, SubButtons button = SubButtons::None,
					MainPanellButton mbuttom = MainPanellButton::Home);

signals:
	void menuRequested();
	void backRequested();
	void labelClicked();
	void buttonClicked(Smitto::Ui::SubButtons button);

private:
	void paintEvent(QPaintEvent*) Q_DECL_OVERRIDE;
	bool eventFilter(QObject* watched, QEvent* event) Q_DECL_OVERRIDE;
	void keyPressEvent(QKeyEvent* event) Q_DECL_OVERRIDE;

private:
	const QString basename_;
	int section_ = -1;
	QLabel* label_;
	QPushButton *mainButton_, *backButton_;
	QMap<SubButtons, QPushButton*> subButtons_;
};

} // Ui ::
} // Smitto ::
