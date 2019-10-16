/*
 * Copyright (C) 2016-2019 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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

#include "RichTextDelegate.h"
// Qt5
#include <QtGui/QPainter>
#include <QtGui/QTextDocument>

namespace Smitto {

void RichTextDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	QStyleOptionViewItem optionCopy = option;
	initStyleOption(&optionCopy, index);
	painter->save();
	QTextDocument doc;
	doc.setHtml(optionCopy.text);
	doc.setDocumentMargin(1);
	optionCopy.text.clear();
	optionCopy.widget->style()->drawControl(QStyle::CE_ItemViewItem, &optionCopy, painter);
	painter->translate(optionCopy.rect.left(), optionCopy.rect.top());
	QRect rect(0, 0, optionCopy.rect.width(), optionCopy.rect.height());
	doc.drawContents(painter, rect);
	painter->restore();
}

QSize RichTextDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	QStyleOptionViewItem optionCopy = option;
	initStyleOption(&optionCopy, index);
	QTextDocument doc;
	doc.setHtml(QString());
	doc.setDocumentMargin(1);
	doc.setTextWidth(optionCopy.rect.width());
	return QSize(optionCopy.rect.width(), doc.size().height());
}

} // Smitto::
