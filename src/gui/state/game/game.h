/*  LOOT

    A load order optimisation tool for
    Morrowind, Oblivion, Skyrim, Skyrim Special Edition, Skyrim VR,
    Fallout 3, Fallout: New Vegas, Fallout 4 and Fallout 4 VR.

    Copyright (C) 2012 WrinklyNinja

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

#ifndef LOOT_GUI_STATE_GAME_GAME
#define LOOT_GUI_STATE_GAME_GAME

#include <filesystem>
#include <mutex>
#include <optional>
#include <string>
#include <unordered_set>

#include "gui/state/game/game_settings.h"
#include "loot/api.h"

namespace loot {
namespace gui {
class Game : public GameSettings {
public:
  Game(const GameSettings& gameSettings,
       const std::filesystem::path& lootDataPath,
       const std::filesystem::path& preludePath);
  Game(const Game& game);

  Game& operator=(const Game& game);

  using GameSettings::Type;

  void Init();

  std::shared_ptr<const PluginInterface> GetPlugin(
      const std::string& name) const;
  std::vector<std::shared_ptr<const PluginInterface>> GetPlugins() const;
  std::vector<Message> CheckInstallValidity(
      const std::shared_ptr<const PluginInterface>& plugin,
      const PluginMetadata& metadata,
      const std::string& language);

  void RedatePlugins();  // Change timestamps to match load order (Skyrim only).

  void LoadAllInstalledPlugins(
      bool headersOnly);  // Loads all installed plugins.
  bool ArePluginsFullyLoaded()
      const;  // Checks if the game's plugins have already been loaded.

  std::filesystem::path MasterlistPath() const;
  std::filesystem::path UserlistPath() const;
  std::filesystem::path PluginsTxtPath() const;

  std::vector<std::string> GetLoadOrder() const;
  void SetLoadOrder(const std::vector<std::string>& loadOrder);

  bool IsPluginActive(const std::string& pluginName) const;
  std::optional<short> GetActiveLoadOrderIndex(
      const std::shared_ptr<const PluginInterface>& plugin,
      const std::vector<std::string>& loadOrder) const;

  std::vector<std::string> SortPlugins();
  void IncrementLoadOrderSortCount();
  void DecrementLoadOrderSortCount();

  std::vector<Message> GetMessages() const;
  void AppendMessage(const Message& message);
  void ClearMessages();

  bool UpdateMasterlist() const;
  FileRevision GetMasterlistInfo() const;

  void LoadMetadata();
  std::vector<std::string> GetKnownBashTags() const;

  std::vector<Group> GetMasterlistGroups() const;
  std::vector<Group> GetUserGroups() const;

  std::optional<PluginMetadata> GetMasterlistMetadata(
      const std::string& pluginName,
      bool evaluateConditions = false) const;
  std::optional<PluginMetadata> GetUserMetadata(
      const std::string& pluginName,
      bool evaluateConditions = false) const;

  void SetUserGroups(const std::vector<Group>& groups);
  void AddUserMetadata(const PluginMetadata& metadata);
  void ClearUserMetadata(const std::string& pluginName);
  void ClearAllUserMetadata();
  void SaveUserMetadata();

private:
  std::vector<std::string> GetInstalledPluginNames();
  void AppendMessages(std::vector<Message> messages);

  std::shared_ptr<GameInterface> gameHandle_;
  std::vector<Message> messages_;
  std::filesystem::path lootDataPath_;
  std::filesystem::path preludePath_;
  unsigned short loadOrderSortCount_;
  bool pluginsFullyLoaded_;

  mutable std::mutex mutex_;
};
}
}

#endif
