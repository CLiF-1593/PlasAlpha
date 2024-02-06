#pragma once
#include <qstring.h>
#include <qstringlist.h>
#include <vector>
#include "Collection.h"

class CollectionGenerator {
private:
	QString vector_path;
	std::vector<QStringList> datas_path;
	Collection *collection;

public:
	CollectionGenerator();
	~CollectionGenerator();
	CollectionGenerator* SetVectorPath(const QString &vector_path) { this->vector_path = vector_path; return this; }
	CollectionGenerator* SetDatasPath(const std::vector<QStringList> &datas) { this->datas_path = datas; return this; }
	Collection* col();
};

