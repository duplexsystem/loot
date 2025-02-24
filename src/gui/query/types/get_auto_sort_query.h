/*  LOOT

A load order optimisation tool for
Morrowind, Oblivion, Skyrim, Skyrim Special Edition, Skyrim VR,
Fallout 3, Fallout: New Vegas, Fallout 4 and Fallout 4 VR.

Copyright (C) 2014 WrinklyNinja

This file is part of LOOT.

LOOT is free software: you can redistribute
it and/or modify it under the terms of the GNU General Public License
as published by the Free Software Foundation, either version 3 of
the License, or (at your option) any later version.

LOOT is distributed in the hope that it will
be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with LOOT.  If not, see
<https://www.gnu.org/licenses/>.
*/

#ifndef LOOT_GUI_QUERY_GET_AUTO_SORT_QUERY
#define LOOT_GUI_QUERY_GET_AUTO_SORT_QUERY

#undef min

#include <json.hpp>

#include "gui/query/query.h"
#include "gui/state/loot_settings.h"

namespace loot {
class GetAutoSortQuery : public Query {
public:
  GetAutoSortQuery(const LootSettings& settings) : settings_(settings) {}

  std::string executeLogic() {
    auto logger = getLogger();
    if (logger) {
      logger->info("Getting whether or not LOOT was run to auto-sort.");
    }

    nlohmann::json json = {
        {"autoSort", settings_.shouldAutoSort()},
    };

    return json.dump();
  }

private:
  const LootSettings& settings_;
};
}

#endif
