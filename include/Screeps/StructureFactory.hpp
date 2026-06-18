#ifndef SCREEPS_STRUCTURE_FACTORY_HPP
#define SCREEPS_STRUCTURE_FACTORY_HPP

#include "OwnedStructure.hpp"
#include "JSON.hpp"

#include <string>

namespace Screeps {

class Store;

class StructureFactory : public OwnedStructure
{
public:
	explicit StructureFactory(JS::Value value);

	int cooldown() const;
	int level() const;
	Store store() const;
	int storeCapacity() const;

	int produce(const std::string& resourceType);
};

} // namespace Screeps

#endif // SCREEPS_STRUCTURE_FACTORY_HPP