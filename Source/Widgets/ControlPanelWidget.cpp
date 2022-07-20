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


#include "ControlPanelWidget.h"
#include <Gui/Global.h>
#include <Gui/PlatformSpecification.h>
#include <Global/Text.h>
#include <QtWidgets/QPushButton>
#include <QPainter>
#include <QStyleOption>
#include <QKeyEvent>
#include <QEvent>

namespace Smitto {
namespace Ui {

ControlPanelWidget::ControlPanelWidget(const QString& basename, QWidget* parent)
	: QWidget(parent), basename_(basename)
{
	this->setObjectName("ControlPanelWidget");
	auto* layout = new QHBoxLayout(this);
	int m = Smitto::Ui::panelMargin();
	layout->setContentsMargins(m, m, m, m);
	layout->setSpacing(Smitto::Ui::panelSpacing());
	this->setFixedHeight(Smitto::Ui::panelSize());
	this->setMinimumWidth(100);

	layout->addWidget(mainButton_ = new QPushButton(QIcon(":/files/icons/menu-hamburger-button.png"), QString()));
	mainButton_->setStyleSheet("border:0px;");
	mainButton_->setIconSize(Smitto::Ui::iconSize());

	layout->addWidget(backButton_ = new QPushButton(QIcon(":/files/icons/menu-back-button.png"), QString()));
	backButton_->setStyleSheet("border:0px;");
	backButton_->setIconSize(Smitto::Ui::iconSize());

	layout->addWidget(label_ = new QLabel(this));
	label_->setStyleSheet("QLabel {font-weight: bold;font-size: 120%;}");
	label_->installEventFilter(this);
	layout->addStretch();

	layout->addWidget(addButton_ = new QPushButton(QIcon(":/files/icons/menu-add-button.png"), QString()));
	addButton_->setStyleSheet("border:0px;");
	addButton_->setIconSize(Smitto::Ui::iconSize());

	layout->addWidget(saveButton_ = new QPushButton(QIcon(":/files/icons/menu-save-button.png"), QString()));
	saveButton_->setStyleSheet("border:0px;");
	saveButton_->setIconSize(Smitto::Ui::iconSize());

	layout->addWidget(menuButton_ = new QPushButton(QIcon(":/files/icons/menu-more-button.png"), QString()));
	menuButton_->setStyleSheet("border:0px;");
	menuButton_->setIconSize(Smitto::Ui::iconSize());

	layout->addWidget(refreshButton_ = new QPushButton(QIcon(":/files/icons/menu-regresh-button.png"), QString()));
	refreshButton_->setStyleSheet("border:0px;");
	refreshButton_->setIconSize(Smitto::Ui::iconSize());

	connect(mainButton_, &QPushButton::clicked, this, &ControlPanelWidget::menuRequested);
	connect(backButton_, &QPushButton::clicked, this, &ControlPanelWidget::backRequested);

	connect(addButton_, &QPushButton::clicked, this, &ControlPanelWidget::addButtonClicked);
	connect(saveButton_, &QPushButton::clicked, this, &ControlPanelWidget::saveButtonClicked);
	connect(menuButton_, &QPushButton::clicked, this, &ControlPanelWidget::menuButtonClicked);
	connect(refreshButton_, &QPushButton::clicked, this, &ControlPanelWidget::refreshButtonClicked);

	home();
}

ControlPanelWidget::~ControlPanelWidget()
{
}

void ControlPanelWidget::home()
{
	label_->setText(H3(basename_));
	section_ = -1;
	addButton_->setHidden(true);
	mainButton_->setHidden(false);
	backButton_->setHidden(true);
	saveButton_->setHidden(true);
	menuButton_->setHidden(true);
	refreshButton_->setHidden(true);
}

void ControlPanelWidget::setSection(int sectionId, const QString& name, SubButtons button, MainPanellButton mbuttom)
{
	label_->setText(H3(name));
	section_ = sectionId;
	addButton_->setHidden(!(quint8(button) & quint8(SubButtons::Add)));
	saveButton_->setHidden(!(quint8(button) & quint8(SubButtons::Save)));
	menuButton_->setHidden(!(quint8(button) & quint8(SubButtons::Menu)));
	refreshButton_->setHidden(!(quint8(button) & quint8(SubButtons::Refresh)));
	mainButton_->setHidden(mbuttom != MainPanellButton::Home);
	backButton_->setHidden(mbuttom != MainPanellButton::Back);
}

void ControlPanelWidget::paintEvent(QPaintEvent*)
{
	QStyleOption opt;
	opt.initFrom(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

bool ControlPanelWidget::eventFilter(QObject* watched, QEvent* event)
{
	if (event->type() == QEvent::MouseButtonPress)
		emit labelClicked();
	else
		return QWidget::eventFilter(watched, event);
	event->accept();
	return true;
}

void ControlPanelWidget::keyPressEvent(QKeyEvent* event)
{
	if ((event->key() == Qt::Key_Back || event->key() == Qt::Key_Escape) && !backButton_->isHidden())
	{
		event->accept();
		emit backRequested();
	}
	else
		QWidget::keyPressEvent(event);
}

} // Ui ::
} // Smitto ::
