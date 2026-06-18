/**
 * @file StructureExtractor.hpp
 * @brief StructureExtractor class definition for Screeps game API wrapper.
 * @see https://docs.screeps.com/api/#StructureExtractor
 */
#ifndef SCREEPS_STRUCTURE_EXTRACTOR_HPP
#define SCREEPS_STRUCTURE_EXTRACTOR_HPP

#include "OwnedStructure.hpp"

namespace Screeps {

/**
 * @class StructureExtractor
 * @brief A structure that extracts minerals from deposits.
 *
 * Extractors are structures that allow harvesting of mineral deposits. They
 * have a cooldown period after each extraction and must be placed adjacent
 * to a mineral deposit.
 *
 * @see https://docs.screeps.com/api/#StructureExtractor
 * @see OwnedStructure
 */
class StructureExtractor : public OwnedStructure
{
public:
	/**
	 * @brief Construct a StructureExtractor from a JavaScript value.
	 * @param value The JavaScript value representing the extractor.
	 */
	explicit StructureExtractor(JS::Value value);

	/**
	 * @brief Get the current cooldown of this extractor.
	 * @return The remaining cooldown ticks.
	 * @see https://docs.screeps.com/api/#StructureExtractor.cooldown
	 */
	int cooldown() const;
};

} // namespace Screeps

#endif // SCREEPS_STRUCTURE_EXTRACTOR_HPP
