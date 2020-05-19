#include "SmittoCSSMaker.h"
#include "SmittoTerminalTheme.h"
// Qt5
#include <QtCore/QCoreApplication>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	SmittoCSSMaker();
	SmittoXFCE4TermThemeMaker();

	return 0;
}
