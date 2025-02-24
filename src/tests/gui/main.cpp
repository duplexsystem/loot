/*  LOOT

    A load order optimisation tool for Oblivion, Skyrim, Fallout 3 and
    Fallout: New Vegas.

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
    along with LOOT. If not, see
    <https://www.gnu.org/licenses/>.
    */

#include <boost/locale.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/null_sink.h>

#include "tests/gui/query/json_test.h"
#include "tests/gui/query/types/close_settings_query_test.h"
#include "tests/gui/query/types/editor_closed_query_test.h"
#include "tests/gui/query/types/get_prelude_info_query_test.h"
#include "tests/gui/query/types/get_settings_query_test.h"
#include "tests/gui/query/types/get_themes_query_test.h"
#include "tests/gui/state/game/game_settings_test.h"
#include "tests/gui/state/game/game_test.h"
#include "tests/gui/state/game/games_manager_test.h"
#include "tests/gui/state/game/helpers_test.h"
#include "tests/gui/state/loot_paths_test.h"
#include "tests/gui/state/loot_settings_test.h"
#include "tests/gui/state/unapplied_change_counter_test.h"
#include "tests/gui/helpers_test.h"

int main(int argc, char **argv) {
  // Set the locale to get encoding conversions working correctly.
  std::locale::global(boost::locale::generator().generate(""));

  // Set the logger to use a null sink.
  spdlog::create<spdlog::sinks::null_sink_st>("loot_logger");

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
