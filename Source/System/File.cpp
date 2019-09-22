#include "File.h"
// Qt5
#include <QtCore/QByteArray>
#include <QtCore/QFile>

namespace Smitto {

QByteArray readAllFile(const QString& filepath)
{
	QByteArray result;
	QFile file(filepath);
	if (file.open(QIODevice::ReadOnly))
	{
		result = file.readAll();
		file.close();
	}
	return result;
}

void writeToFile(const QString& filepath, const QByteArray& data)
{
	QFile file(filepath);
	if (file.open(QIODevice::WriteOnly))
	{
		file.write(data);
		file.close();
	}
}

} // Smitto::
