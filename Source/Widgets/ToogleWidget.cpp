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

#include "ToogleWidget.h"
#include <Gui/SmittoTheme.h>
#include <QtWidgets/QStyleOption>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtGui/QPaintEvent>
#include <QtGui/QPainter>
#include <QtCore/QTimer>

namespace Smitto {

ToogleWidget::ToogleWidget(QWidget* parent)
 : QAbstractButton(parent),
   timer_(new QTimer(this))
{
	this->setCheckable(true);
	connect(timer_, &QTimer::timeout, this, [this] {
		if (isChecked())
		{
			if (pos >= 10)
				timer_->stop();
			else
				pos++;
		}
		else
		{
			if (pos == 0)
				timer_->stop();
			else
				pos--;
		}
		update();
	});
}

ToogleWidget::ToogleWidget(const QString& text, bool checked, QWidget* parent)
	: ToogleWidget (checked, parent)
{
	auto layout = new QHBoxLayout(this);
	layout->setContentsMargins(0, 0 , 0, 0);
	layout->addWidget(label_ = new QLabel(text));
}

void ToogleWidget::mousePressEvent(QMouseEvent* event)
{
	click();
	emit toggled(isChecked());
	update();
	timer_->start(100/10);
	event->accept();
}

void ToogleWidget::paintEvent(QPaintEvent* event)
{
	QStyleOption opt;
#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
	opt.initFrom(this);
#else
	opt.init(this);
#endif

	QPainter p(this);
	QPen pen;
	pen.setWidth(POINTSIZE);

	if (!timer_->isActive())
		pos = isChecked() ? 10 : 0;

	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

	int dx = label_ ? label_->sizeHint().width() : 0;
	if ((size().width()-dx) > 96)
		dx = size().width()-96;
	QRect rect(event->rect().x()+4+dx, event->rect().y()+4, size().width()-8-dx, size().height()-8);

	if (theme_ == Themes::Light)
	{
		pen.setColor(QColor(250*pos/10,250*pos/10,250*pos/10));
		p.setBrush(QBrush(QColor(127+127*(10-pos)/10,127+127*(10-pos)/10,127+127*(10-pos)/10)));
	}
	else
	{
		pen.setColor(QColor(127*(10-pos)/10,127*(10-pos)/10,127*(10-pos)/10));
		p.setBrush(QBrush(QColor(127*pos/10,127*pos/10,127*pos/10)));
	}

	p.setPen(pen);
	p.setRenderHint(QPainter::Antialiasing, true);

	p.drawRoundedRect(rect, rect.height()/2-1, rect.height()/2-1);

	if (theme_ == Themes::Light)
		p.setBrush(QBrush(QColor(127+127*pos/10,127+127*pos/10,127+127*pos/10)));
	else
		p.setBrush(QBrush(QColor(255*pos/10,255*pos/10,255*pos/10)));
	p.drawEllipse(QPoint(rect.x()+1+rect.height()/2+pos*(rect.width()-rect.height()-2)/10,
						 rect.y()+rect.height()/2), rect.height()/2-3, rect.height()/2-3);
	event->accept();
}

QSize ToogleWidget::sizeHint() const
{
	return QSize(48*POINTSIZE+(label_?label_->sizeHint().width():0), 24*POINTSIZE);
}

} // Smitto::
