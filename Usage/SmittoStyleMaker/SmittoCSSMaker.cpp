#include "SmittoCSSMaker.h"
#include <../Source/Gui/SmittoColors.h>
// Qt5
#include <QtCore/QCoreApplication>
#include <QtCore/QFile>

void SmittoCSSMaker()
{
	QFile file(QCoreApplication::applicationDirPath() + "/gen/smitto.css");
	if (file.open(QIODevice::WriteOnly))
	{
		for ( int i = int(Smitto::SmittoBaseColors::level01); i <= int(Smitto::SmittoBaseColors::level12); ++i)
			file.write(QString("sm_t%1{color:%2};\nsm_bg%1{background:%2};\n")
					   .arg(i +1 - int(Smitto::SmittoBaseColors::level01))
					   .arg(Smitto::scolor(Smitto::SmittoBaseColors(i))).toLocal8Bit());
		file.close();
	}
}
