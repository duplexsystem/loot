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

#ifndef LOOT_GUI_QUERY_APPLY_SORT_QUERY
#define LOOT_GUI_QUERY_APPLY_SORT_QUERY

#include "gui/query/query.h"

namespace loot {
template<typename G = gui::Game>
class ApplySortQuery : public Query {
public:
  ApplySortQuery(G& game,
                 UnappliedChangeCounter& counter,
                 const std::vector<std::string>& plugins) :
      game_(game),
      counter_(counter),
      plugins_(plugins) {}

  std::string executeLogic() {
    auto logger = getLogger();
    if (logger) {
      logger->trace("User has accepted sorted load order, applying it.");
    }
    try {
      game_.SetLoadOrder(plugins_);
      counter_.DecrementUnappliedChangeCounter();
    } catch (...) {
      errorMessage = getSortingErrorMessage(game_);
      throw;
    }

    return "";
  }

  std::optional<std::string> getErrorMessage() override { return errorMessage; }

private:
  G& game_;
  UnappliedChangeCounter& counter_;
  const std::vector<std::string> plugins_;
  std::optional<std::string> errorMessage;
};
}

#endif
