/*
 * Copyright (C) 2016-2024 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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

#include "MaterialButtonsMenu.h"
#include "MaterialButton.h"
#include <Gui/PlatformSpecification.h>
#include <QtWidgets/QHBoxLayout>


namespace Smitto {
namespace Ui {

MaterialButtonsMenu::MaterialButtonsMenu(QWidget* parent)
	: QWidget(parent)
{
	auto hlayout = new QHBoxLayout(this);
	hlayout->setContentsMargins(0,0,0,0);
	hlayout->setSpacing(0);
	this->setFixedHeight(Smitto::Ui::panelSize()*1.3);
}

void MaterialButtonsMenu::setActiveButton(int index)
{
	for (auto it = buttons_.begin(); it != buttons_.end(); ++it)
		it.value()->setActive(it.key() == index);
}

MaterialButton* MaterialButtonsMenu::addButton(int buttonId, const QString& text, const QIcon& icon)
{
	auto button = new MaterialButton(text, icon);
	static_cast<QHBoxLayout*>(this->layout())->addWidget(button);
	buttons_.insert(buttonId, button);
	return button;
}

void MaterialButtonsMenu::updateFont()
{
	QFont font = this->font();
	if (font.pixelSize() > 10)
		font.setPixelSize(font.pixelSize()-6);
	else
		font.setPointSize(font.pointSize()-2);
	for (auto button: qAsConst(buttons_))
		button->setFont(font);

}

} // Ui ::
} // Smitto ::
