#include "SmittoTerminalTheme.h"
#include <../Source/Gui/SmittoColors.h>
// Qt5
#include <QtCore/QCoreApplication>
#include <QtCore/QFile>
#include <QStringBuilder>
#include <QDebug>

void SmittoXFCE4TermThemeMaker()
{
	QFile file(QCoreApplication::applicationDirPath().append("/gen/smitto.theme"));
	if (file.open(QIODevice::WriteOnly))
	{
		QString allcolors, allcolorsb;
		for (int i = int(Smitto::ConsoleColors::Black); i <= int(Smitto::ConsoleColors::White); ++i)
		{
			allcolors.append(Smitto::ccolor(Smitto::ConsoleColors(i), false) % ";");
			allcolorsb.append(Smitto::ccolor(Smitto::ConsoleColors(i), true) % ";");
		}
		file.write(QString("[Scheme]\nName=Smitto\nColorPalette=%1%2\nColorForeground=%3\nColorBackground=%4")
				   .arg(allcolors, allcolorsb, Smitto::scolor(Smitto::SmittoBaseColors::level11),
						Smitto::scolor(Smitto::SmittoBaseColors::level02)).toLocal8Bit());
		file.close();
		qDebug()<<file.fileName()<<"move to"<<"	/usr/share/xfce4/terminal/colorschemes";
	}

}



