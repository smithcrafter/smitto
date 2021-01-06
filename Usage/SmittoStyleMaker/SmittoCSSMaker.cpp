#include "SmittoCSSMaker.h"
#include <../Source/Gui/SmittoColors.h>
// Qt5
#include <QtCore/QCoreApplication>
#include <QtCore/QFile>
#include <QDebug>

void SmittoCSSMaker()
{
	QFile file(QCoreApplication::applicationDirPath().append("/gen/smitto-colors.css"));
	if (file.open(QIODevice::WriteOnly))
	{
		file.write(":root {\n");
		for (int i = int(Smitto::SmittoBaseColors::level01); i <= int(Smitto::SmittoBaseColors::level12); ++i)
			file.write(QString("--smitto-level-%1: %2;\n")
					   .arg(i + 1 - int(Smitto::SmittoBaseColors::level01))
					   .arg(Smitto::scolor(Smitto::SmittoBaseColors(i))).toLocal8Bit());
		file.write(QString("--smitto-red: %1;\n").arg(Smitto::scolor(Smitto::SmittoBaseColors::Red)).toLocal8Bit());
		file.write(QString("--smitto-bold-red: %1;\n").arg(Smitto::scolor(Smitto::SmittoBaseColors::BoldRed)).toLocal8Bit());
		file.write(QString("--smitto-green: %1;\n").arg(Smitto::scolor(Smitto::SmittoBaseColors::Green)).toLocal8Bit());
		file.write(QString("--smitto-bold-green: %1;\n").arg(Smitto::scolor(Smitto::SmittoBaseColors::BoldGreen)).toLocal8Bit());
		file.write(QString("--smitto-yellow: %1;\n").arg(Smitto::scolor(Smitto::SmittoBaseColors::Yellow)).toLocal8Bit());
		file.write(QString("--smitto-bold-yellow: %1;\n").arg(Smitto::scolor(Smitto::SmittoBaseColors::BoldYellow)).toLocal8Bit());
		file.write(QString("--smitto-blue: %1;\n").arg(Smitto::scolor(Smitto::SmittoBaseColors::Blue)).toLocal8Bit());
		file.write(QString("--smitto-bold-blue: %1;\n").arg(Smitto::scolor(Smitto::SmittoBaseColors::BoldBlue)).toLocal8Bit());
		file.write(QString("--smitto-purple: %1;\n").arg(Smitto::scolor(Smitto::SmittoBaseColors::Purple)).toLocal8Bit());
		file.write(QString("--smitto-bold-purple: %1;\n").arg(Smitto::scolor(Smitto::SmittoBaseColors::BoldPurple)).toLocal8Bit());
		file.write(QString("--smitto-cyan: %1;\n").arg(Smitto::scolor(Smitto::SmittoBaseColors::Cyan)).toLocal8Bit());
		file.write(QString("--smitto-bold-cyan: %1;\n").arg(Smitto::scolor(Smitto::SmittoBaseColors::BoldCyan)).toLocal8Bit());

		file.write("}\n\n");
		for (int i = int(Smitto::SmittoBaseColors::level01); i <= int(Smitto::SmittoBaseColors::level12); ++i)
			file.write(QString(".smitto-text-level-%1 {color: %2;}\n.smitto-background-level-%1 {background: %2;}\n")
					   .arg(i + 1 - int(Smitto::SmittoBaseColors::level01))
					   .arg(Smitto::scolor(Smitto::SmittoBaseColors(i))).toLocal8Bit());

		file.write("\n");
		file.close();
		qDebug()<<"/gen/smitto-colors.css";
	}
}
