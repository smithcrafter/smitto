#include <QCoreApplication>
#include <QElapsedTimer>
#include <QDateTime>
#include <QDebug>
#include <map>
#include <unordered_map>
#include <ramio/log/log.h>
#include <ramio/settings/arg.h>
#include <Algo/OrderedKeyMap.hpp>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	Ramio::initLogFromArguments();
	std::srand(QDateTime::currentDateTime().toSecsSinceEpoch());

	using Type = float;
	Smitto::OrderedKeyMap<quint32, Type, 1>  testmap;
	QMap<quint32, Type> qt_map;
	std::unordered_map<quint32, Type> std_umap;
	std::map<quint32, Type> std_map;
	Smitto::OrderedKeyMap<quint32, Type, 0> sokmap0;
	Smitto::OrderedKeyMap<quint32, Type, 1> sokmap1;

	auto end = QDateTime(QDate::currentDate().addDays(25*365), QTime(0,0,0)).toSecsSinceEpoch();
	for (qint64 i = QDateTime(QDate::currentDate(), QTime(0,0,0)).toSecsSinceEpoch(); i < end; i+=60)
		if (quint32 tod = i%(3600*24))
			if (tod > 7*3600 && tod < 20*3600)
				testmap.insert(i, std::rand());
	qDebug()<<"testmap "<<testmap.size();
	QElapsedTimer timer;

	qDebug()<<"---INSERT---";

	timer.start();
	for (auto it = testmap.constBegin(); it != testmap.constEnd(); ++it)
		qt_map.insert(it.key(), it.value());
	qDebug()<<"qt_map   insert count="<<qt_map.size()<<"time:"<<timer.nsecsElapsed()<<"ns";

	timer.restart();
	for (auto it = testmap.constBegin(); it != testmap.constEnd(); ++it)
		std_umap.insert(std::pair<quint32, Type>(it.key(), it.value()));
	qDebug()<<"std_umap insert count="<<std_umap.size()<<"time:"<<timer.nsecsElapsed()<<"ns";

	timer.restart();
	for (auto it = testmap.constBegin(); it != testmap.constEnd(); ++it)
		std_map.insert(std::pair<quint32, Type>(it.key(), it.value()));
	qDebug()<<"std_map  insert count="<<std_map.size()<<"time:"<<timer.nsecsElapsed()<<"ns";

	timer.restart();
	for (auto it = testmap.constBegin(); it != testmap.constEnd(); ++it)
		sokmap0.insert(it.key(), it.value());
	qDebug()<<"sokmap0  insert count="<<sokmap0.count()<<"time:"<<timer.nsecsElapsed()<<"ns";

	timer.restart();
	for (auto it = testmap.constBegin(); it != testmap.constEnd(); ++it)
		sokmap1.insert(it.key(), it.value());
	qDebug()<<"sokmap1  insert count="<<sokmap1.count()<<"time:"<<timer.nsecsElapsed()<<"ns";

/// --------------------------------------------------------------------
	qDebug()<<"---CIRCLE FOR BY ITERATOR---";
	double sum = 0; timer.restart();
	for (auto it = qt_map.constBegin(); it != qt_map.constEnd(); ++it)
		sum+= it.value();
	qDebug()<<"qt_map   for iterator sum="<<sum<<"time:"<<timer.nsecsElapsed()<<"ns";

	timer.restart(); sum = 0;
	for (auto it = std_umap.begin(); it != std_umap.end(); ++it)
		sum+= it->second;
	qDebug()<<"std_umap for iterator sum="<<sum<<"time:"<<timer.nsecsElapsed()<<"ns";

	timer.restart(); sum = 0;
	for (auto it = std_map.begin(); it != std_map.end(); ++it)
		sum+= it->second;
	qDebug()<<"std_map  for iterator sum="<<sum<<"time:"<<timer.nsecsElapsed()<<"ns";

	timer.restart(); sum = 0;
	for (auto it = sokmap0.constBegin(); it != sokmap0.constEnd(); ++it)
		sum += it.value();
	qDebug()<<"sokmap0  for iterator sum="<<sum<<"time:"<<timer.nsecsElapsed()<<"ns";

	timer.restart(); sum = 0;
	for (auto it = sokmap1.constBegin(); it != sokmap1.constEnd(); ++it)
		sum += it.value();
	qDebug()<<"sokmap1  for iterator sum="<<sum<<"time:"<<timer.nsecsElapsed()<<"ns";



	QList<qint64> randoms;
	auto tkeys = testmap.keys();
	for (int i = 0; i < 5000; i++)
		randoms.append(tkeys[std::rand()%testmap.size()]);

/// --------------------------------------------------------------------
	qDebug()<<"---CIRCLE FOR BY ORDERED TKEYS---";

	sum = 0; timer.restart();
	for(auto tkey : tkeys)
		sum += qt_map[tkey];
	qDebug()<<"qt_map   operator[] order_pass sum"<<sum<<"time:"<<timer.nsecsElapsed()<<"ns";

	sum = 0; timer.restart();
	for(auto tkey : tkeys)
		sum += std_umap[tkey];
	qDebug()<<"std_umap operator[] order_pass sum"<<sum<<"time:"<<timer.nsecsElapsed()<<"ns";

	sum = 0; timer.restart();
	for(auto tkey : tkeys)
		sum += std_map[tkey];
	qDebug()<<"std_map  operator[] order_pass sum"<<sum<<"time:"<<timer.nsecsElapsed()<<"ns";

	sum = 0; timer.restart();
	for(auto tkey : tkeys)
		sum += sokmap0[tkey];
	qDebug()<<"sokmap0  operator[] order_pass sum"<<sum<<"time:"<<timer.nsecsElapsed()<<"ns";

	sum = 0; timer.restart();
	for(auto tkey : tkeys)
		sum += sokmap1[tkey];
	qDebug()<<"sokmap1  operator[] order_pass sum"<<sum<<"time:"<<timer.nsecsElapsed()<<"ns";


/// --------------------------------------------------------------------
	qDebug()<<"--- FIND BY ORDERED TKEYS---";
	sum = 0; timer.restart();
	for(auto tkey : tkeys)
		sum += qt_map.find(tkey).value();
	qDebug()<<"qt_map   tkeys find sum"<<sum<<"time:"<<timer.nsecsElapsed()<<"ns";

	sum = 0; timer.restart();
	for(auto tkey : tkeys)
		sum += std_umap.find(tkey)->second;
	qDebug()<<"std_umap tkeys find sum"<<sum<<"time:"<<timer.nsecsElapsed()<<"ns";

	sum = 0; timer.restart();
	for(auto tkey : tkeys)
		sum += std_map.find(tkey)->second;
	qDebug()<<"std_map  tkeys find sum"<<sum<<"time:"<<timer.nsecsElapsed()<<"ns";

	sum = 0; timer.restart();
	for(auto tkey : tkeys)
		sum += sokmap0.find(tkey).value();
	qDebug()<<"sokmap0  tkeys find sum"<<sum<<"time:"<<timer.nsecsElapsed()<<"ns";

	sum = 0; timer.restart();
	for(auto tkey : tkeys)
		sum += sokmap1.find(tkey).value();
	qDebug()<<"sokmap1  tkeys find sum"<<sum<<"time:"<<timer.nsecsElapsed()<<"ns";

	sum = 0; timer.restart();
	for(auto tkey : tkeys)
		sum += sokmap0.findAlt(tkey).value();
	qDebug()<<"sokmap0  tkeys find sum"<<sum<<"time:"<<timer.nsecsElapsed()<<"ns Alt";

	sum = 0; timer.restart();
	for(auto tkey : tkeys)
		sum += sokmap1.findAlt(tkey).value();
	qDebug()<<"sokmap1  tkeys find sum"<<sum<<"time:"<<timer.nsecsElapsed()<<"ns Alt";


/// --------------------------------------------------------------------
	qDebug()<<"---FIND BY RANDOM KEYS---";
	sum = 0; timer.restart();
	for(auto tkey : randoms)
		sum += qt_map.find(tkey).value();
	qDebug()<<"qt_map   key randoms find sum"<<sum<<"time:"<<timer.nsecsElapsed()<<"ns";

	sum = 0; timer.restart();
	for(auto tkey : randoms)
		sum += std_umap.find(tkey)->second;
	qDebug()<<"std_umap key randoms find sum"<<sum<<"time:"<<timer.nsecsElapsed()<<"ns";

	sum = 0; timer.restart();
	for(auto tkey : randoms)
		sum += std_map.find(tkey)->second;
	qDebug()<<"std_map  key randoms find sum"<<sum<<"time:"<<timer.nsecsElapsed()<<"ns";

	sum = 0; timer.restart();
	for(auto tkey : randoms)
		sum += sokmap0.find(tkey).value();
	qDebug()<<"sokmap0  key randoms find sum"<<sum<<"time:"<<timer.nsecsElapsed()<<"ns";

	sum = 0; timer.restart();
	for(auto tkey : randoms)
		sum += sokmap1.find(tkey).value();
	qDebug()<<"sokmap1  key randoms find sum"<<sum<<"time:"<<timer.nsecsElapsed()<<"ns";

	sum = 0; timer.restart();
	for(auto tkey : randoms)
		sum += sokmap0.findAlt(tkey).value();
	qDebug()<<"sokmap0  key randoms find sum"<<sum<<"time:"<<timer.nsecsElapsed()<<"ns Alt";

	sum = 0; timer.restart();
	for(auto tkey : randoms)
		sum += sokmap1.findAlt(tkey).value();
	qDebug()<<"sokmap1  key randoms find sum"<<sum<<"time:"<<timer.nsecsElapsed()<<"ns Alt";


/// --------------------------------------------------------------------
	qDebug()<<"---OPERATOR[] BY RANDOM KEYS---";
	sum = 0; timer.restart();
	for(auto tkey : randoms)
		sum += qt_map[tkey];
	qDebug()<<"qt_map   operator[] random_pass sum"<<sum<<"time:"<<timer.nsecsElapsed()<<"ns";

	sum = 0;timer.restart();
	for(auto tkey : randoms)
		sum += std_umap[tkey];
	qDebug()<<"std_umap operator[] random_pass sum"<<sum<<"time:"<<timer.nsecsElapsed()<<"ns";

	sum = 0;timer.restart();
	for(auto tkey : randoms)
		sum += std_map[tkey];
	qDebug()<<"std_map  operator[] random_pass sum"<<sum<<"time:"<<timer.nsecsElapsed()<<"ns";

	sum = 0;timer.restart();
	for(auto tkey : randoms)
		sum += sokmap0[tkey];
	qDebug()<<"sokmap0  operator[] random_pass sum"<<sum<<"time:"<<timer.nsecsElapsed()<<"ns";

	sum = 0;timer.restart();
	for(auto tkey : randoms)
		sum += sokmap1[tkey];
	qDebug()<<"sokmap1  operator[] random_pass sum"<<sum<<"time:"<<timer.nsecsElapsed()<<"ns";


/// --------------------------------------------------------------------
	qDebug()<<"---CONTAINS BY BY RANDOM KEYS---";
	sum = 0; timer.restart();
	for(auto tkey : randoms)
		sum += qt_map.contains(tkey);
	qDebug()<<"qt_map   key randoms contains sum"<<sum<<"time:"<<timer.nsecsElapsed()<<"ns";

	sum = 0;timer.restart();
	for(auto tkey : randoms)
		sum += std_umap.contains(tkey);
	qDebug()<<"std_umap key randoms contains sum"<<sum<<"time:"<<timer.nsecsElapsed()<<"ns";

	sum = 0;timer.restart();
	for(auto tkey : randoms)
		sum += std_map.contains(tkey);
	qDebug()<<"std_map  key randoms contains sum"<<sum<<"time:"<<timer.nsecsElapsed()<<"ns";

	sum = 0;timer.restart();
	for(auto tkey : randoms)
		sum += sokmap0.contains(tkey);
	qDebug()<<"sokmap0  key randoms contains sum"<<sum<<"time:"<<timer.nsecsElapsed()<<"ns";

	sum = 0;timer.restart();
	for(auto tkey : randoms)
		sum += sokmap1.contains(tkey);
	qDebug()<<"sokmap1  key randoms contains sum"<<sum<<"time:"<<timer.nsecsElapsed()<<"ns";

	for (int i = 0; i < 200; i++)
	{
		auto time = end-std::rand();
		if (qt_map.contains(time) != sokmap0.contains(time))
			qDebug()<<"err contains";
	}

/// --------------------------------------------------------------------
	qDebug()<<"---LOWERBOUND BY RANDOM KEYS---";
	sum = 0; timer.restart();
	for(auto tkey : randoms)
		sum += qt_map.lowerBound(tkey).value();
	qDebug()<<"qt_map   key randoms lowerBound sum"<<sum<<"time:"<<timer.nsecsElapsed()<<"ns";

	sum = 0;timer.restart();
	for(auto tkey : randoms)
		sum += sokmap0.lowerBound(tkey).value();
	qDebug()<<"sokmap0  key randoms lowerBound sum"<<sum<<"time:"<<timer.nsecsElapsed()<<"ns";

	sum = 0;timer.restart();
	for(auto tkey : randoms)
		sum += sokmap1.lowerBound(tkey).value();
	qDebug()<<"sokmap1  key randoms lowerBound sum"<<sum<<"time:"<<timer.nsecsElapsed()<<"ns";


/// --------------------------------------------------------------------
	qDebug()<<"---UPPERBOUND BY RANDOM KEYS---";

	sum = 0;timer.restart();
	for(auto tkey : randoms)
	{
		auto it = sokmap0.lowerBound(tkey);
		if (sokmap0.constEnd() != it)
			++it;
		sum += it.value();
	}
	qDebug()<<"lmap key randoms upperBound over lowerBound sum"<<sum<<"time:"<<timer.nsecsElapsed()<<"ns";

	sum = 0; timer.restart();
	for(auto tkey : randoms)
		sum += qt_map.upperBound(tkey).value();
	qDebug()<<"qt_map   key randoms upperBound sum"<<sum<<"time:"<<timer.nsecsElapsed()<<"ns";

	sum = 0;timer.restart();
	for(auto tkey : randoms)
		sum += sokmap0.upperBound(tkey).value();
	qDebug()<<"sokmap0  key randoms upperBound sum"<<sum<<"time:"<<timer.nsecsElapsed()<<"ns";

	sum = 0;timer.restart();
	for(auto tkey : randoms)
		sum += sokmap1.upperBound(tkey).value();
	qDebug()<<"sokmap1  key randoms upperBound sum"<<sum<<"time:"<<timer.nsecsElapsed()<<"ns";

	sum = 0;timer.restart();
	for(auto tkey : randoms)
		sum += sokmap0.upperBoundAlt(tkey).value();
	qDebug()<<"sokmap0  key randoms upperBound sum"<<sum<<"time:"<<timer.nsecsElapsed()<<"ns Alt";

	sum = 0;timer.restart();
	for(auto tkey : randoms)
		sum += sokmap1.upperBoundAlt(tkey).value();
	qDebug()<<"sokmap1  key randoms upperBound sum"<<sum<<"time:"<<timer.nsecsElapsed()<<"ns Alt";

	return 0;
}
