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

#include "DrawerMenuWidget.h"
#include <Gui/PlatformSpecification.h>
#include <Gui/SmittoColors.h>
#include <ramio/gui/global.h>
// Qt
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QStyleOption>
#include <QtGui/QPainter>
#include <QtCore/QPropertyAnimation>
#include <QtCore/QEvent>


namespace Smitto {
namespace Ui {

const int minValue = 1;

BlowWidget::BlowWidget(qreal opacity, QWidget* parent)
	: QWidget(parent), opacity_(opacity)
{
	this->setStyleSheet("QWidget{background-color: rgb(0, 0, 0);}");
	setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
	setAttribute(Qt::WA_TranslucentBackground);
	this->setWindowOpacity(0.1);
}

BlowWidget::~BlowWidget()
{
}

void BlowWidget::mousePressEvent(QMouseEvent* event)
{
	reinterpret_cast<QEvent*>(event)->accept();
	emit clicked();
}

void BlowWidget::paintEvent(QPaintEvent* event)
{
	QStyleOption o;
	o.initFrom(this);
	QPainter p(this);
	p.setOpacity(opacity_);
	style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
	reinterpret_cast<QEvent*>(event)->accept();
}


DrawerMenuWidget::DrawerMenuWidget(QWidget* parent)
	: QWidget(parent)
{
	UI_CREATE_HLAYOUT_ZERO_MARGINSPACING(layout)

	layout->addWidget(menuWidget_ = new QWidget(this), 3);
	layout->addWidget(blowWidget_ = new BlowWidget(1, this), 1);
	connect(blowWidget_, &BlowWidget::clicked, this, &DrawerMenuWidget::hideDrawlerMenu);

	menuWidget_->setStyleSheet(QString("QWidget{background: %1;}").arg(Smitto::scolor(Smitto::SmittoBaseColors::level04)));
	QVBoxLayout* menulayout = new QVBoxLayout(menuWidget_);
	menulayout->setMargin(0);
	QHBoxLayout* hlayout = new QHBoxLayout();
	hlayout->setMargin(5);
	hlayout->setSpacing(5);
	QPushButton* button;
	hlayout->addWidget(button = new QPushButton(QIcon(":/files/icons/go-back-left-arrow.png"), QString()));
	button->setIconSize(Smitto::Ui::iconSize());

	QLabel* label;
	hlayout->addWidget(label = new QLabel("<h3>LifeStreamer</h3>"));
	label->setStyleSheet("QLabel{margin: 5px; font-weight: bold;font-size: 160%; color:white;}");
	hlayout->addStretch();
	connect(button, &QPushButton::clicked, this, &DrawerMenuWidget::hideDrawlerMenu);
	menulayout->addLayout(hlayout);
	button->setStyleSheet("QPushButton{border:0px;}");


	menulayout->addLayout(buttonLayout_ = new QVBoxLayout);
	menulayout->addStretch(6);
	menulayout->addLayout(buttomLayout_ = new QVBoxLayout);

	menulayout->addSpacing(1);
	menulayout->addWidget(button = new QPushButton(tr("Выход")));
	button->setMinimumHeight(this->height()/12);
	connect(button, &QPushButton::clicked, this, &DrawerMenuWidget::logout);

	button->setStyleSheet(QString("QPushButton{background: %1; border: #666 1 px; padding: 10px; color:white;}")
			.arg(Smitto::scolor(Smitto::SmittoBaseColors::level03)));
	menuWidget_->setMinimumWidth(minValue);
	menuWidget_->setMaximumWidth(minValue);
}

DrawerMenuWidget::~DrawerMenuWidget()
{
}

void DrawerMenuWidget::addMenuButton(qint32 butId, const QString& text)
{
	QPushButton* button = new QPushButton(text, this);

	button->setMinimumHeight(this->height()/12);

	buttonLayout_->addWidget(button);
	button->setStyleSheet(QString("QPushButton{background: %1; border: #666 1 px; padding: 10px; color:white;}")
						  .arg(Smitto::scolor(Smitto::SmittoBaseColors::level08)));
	button->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Expanding);
	connect(button, &QPushButton::clicked, this, [this, butId](){emit buttonActivated(butId);});
}

void DrawerMenuWidget::addBottomMenu(qint32 butId, const QString &text)
{
	QPushButton* button = new QPushButton(text, this);

	button->setMinimumHeight(this->height()/12);

	buttomLayout_->addWidget(button);
	button->setStyleSheet(QString("QPushButton{background: %1; border: #666 1 px; padding: 10px; color:white;}")
						  .arg(Smitto::scolor(Smitto::SmittoBaseColors::level03)));
	button->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Expanding);
	connect(button, &QPushButton::clicked, this, [this, butId](){emit buttonActivated(butId);});
}

void DrawerMenuWidget::showDrawlerMenu()
{
	this->setFixedSize(parentWidget()->size());

	if (status != MenuStatus::Closed)
		return;
	status = MenuStatus::Opening;
	cliarAnimations();

	const int maxValue = this->width()*3/4;

	animation1_ = new QPropertyAnimation(menuWidget_, "minimumWidth", this);
	animation2_ = new QPropertyAnimation(menuWidget_, "maximumWidth", this);
	animation3_ = new QPropertyAnimation(blowWidget_, "op", this);

	animation1_->setDuration(180);
	animation1_->setStartValue(minValue);
	animation1_->setEndValue(maxValue);
	animation1_->setEasingCurve(QEasingCurve::OutQuad);

	animation2_->setDuration(180);
	animation2_->setStartValue(minValue);
	animation2_->setEndValue(maxValue);
	animation2_->setEasingCurve(QEasingCurve::OutQuad);

	animation3_->setDuration(180);
	animation3_->setStartValue(0.0);
	animation3_->setEndValue(0.8);
	animation3_->setEasingCurve(QEasingCurve::OutQuad);

	connect(animation2_,&QPropertyAnimation::finished, this, &DrawerMenuWidget::showDrawlerMenuFinished);

	animation3_->start();
	animation1_->start();
	animation2_->start();
}

void DrawerMenuWidget::hideDrawlerMenu()
{
	if (status != MenuStatus::Open)
		return;
	status = MenuStatus::Closing;
	cliarAnimations();

	const int maxValue = menuWidget_->width();

	animation1_ = new QPropertyAnimation(menuWidget_, "minimumWidth", this);
	animation2_ = new QPropertyAnimation(menuWidget_, "maximumWidth", this);
	animation3_ = new QPropertyAnimation(blowWidget_, "op", this);

	animation1_->setDuration(60);
	animation1_->setStartValue(maxValue);
	animation1_->setEndValue(minValue);
	animation1_->setEasingCurve(QEasingCurve::InQuad);

	animation2_->setDuration(60);
	animation2_->setStartValue(maxValue);
	animation2_->setEndValue(minValue);
	animation2_->setEasingCurve(QEasingCurve::InQuad);

	animation3_->setDuration(60);
	animation3_->setStartValue(0.8);
	animation3_->setEndValue(0.0);
	animation3_->setEasingCurve(QEasingCurve::InQuad);

	connect(animation2_,&QPropertyAnimation::finished, this, &DrawerMenuWidget::hideDrawlerMenuFinished);

	animation3_->start();
	animation1_->start();
	animation2_->start();
}

void DrawerMenuWidget::showDrawlerMenuFinished()
{
	cliarAnimations();
	status = MenuStatus::Open;
}

void DrawerMenuWidget::hideDrawlerMenuFinished()
{
	cliarAnimations();
	emit drawlerClosed();
	status = MenuStatus::Closed;
}

void DrawerMenuWidget::cliarAnimations()
{
	if (animation2_) animation1_->deleteLater();
	if (animation2_) animation2_->deleteLater();
	if (animation3_) animation3_->deleteLater();
}

void DrawerMenuWidget::showEvent(QShowEvent* event)
{
	QWidget::showEvent(event);

	for (int i = 0; i < buttonLayout_->count(); i++)
		if (auto* button = dynamic_cast<QPushButton*>(buttonLayout_->itemAt(i)->widget()))
			button->setMinimumHeight(this->height()/12);
}

} // Ui ::
} // Smitto ::
