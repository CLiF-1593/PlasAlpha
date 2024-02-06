#include "CollectionGenerator.h"

CollectionGenerator::CollectionGenerator() {
	this->collection = new Collection();
}

CollectionGenerator::~CollectionGenerator() {
	delete this->collection;
}

Collection* CollectionGenerator::col() {
	return this->collection;
}
