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

#include <QtWidgets/QWidget>
#include <QtCore/QMap>
class QHBoxLayout;
class QLabel;
class QToolButton;

namespace Smitto {
namespace Ui {

enum class TiltleButton
{
	NoButton,
	Close = 1,
	NormMax = 2,
	Min = 4,
	Collapce = 8,

	Snandard = Close | NormMax | Min
};

Q_DECLARE_FLAGS(TiltleButtons, TiltleButton)
Q_DECLARE_OPERATORS_FOR_FLAGS(TiltleButtons)

class CustomTitleWidget : public QWidget
{
public:
	CustomTitleWidget(QWidget* parent = Q_NULLPTR) : QWidget(parent) {}
	CustomTitleWidget(const QString& title, TiltleButtons butons = TiltleButton::Close, QWidget* parent = Q_NULLPTR);
	~CustomTitleWidget() Q_DECL_OVERRIDE;

	QLabel* titleLabel() {return titleLabel_;}
	const QMap<TiltleButton, QToolButton*>& buttons() const {return buttons_;}
	QHBoxLayout* cornLayout() {return cornLayout_;}

	QToolButton* addButtonToCornLayout(const QString& text);

protected:
	QWidget* maxParent();
	void mousePressEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
	void mouseDoubleClickEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
	void mouseMoveEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
	void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;

	bool eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;

private:
	QLabel* titleLabel_;
	QMap<TiltleButton, QToolButton*> buttons_;
	QHBoxLayout* cornLayout_ = Q_NULLPTR;
	QPoint mouseClickPos_;
	QPoint parentPos_;
	bool move_ = false;
};

} // Ui ::
} // Smitto ::
