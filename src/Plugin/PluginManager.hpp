/******************************************************************************
 * PluginManager.hpp
 * Copyright (C) 2020  Mel McCalla <melmccalla@gmail.com>
 *
 * This file is part of GameEngine.
 *
 * GameEngine is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GameEngine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GameEngine.  If not, see <http://www.gnu.org/licenses/>.
 *****************************************************************************/
#ifndef SRC_PLUGIN_PLUGINMANAGER_HPP_
#define SRC_PLUGIN_PLUGINMANAGER_HPP_

namespace game_engine::plugin {

class PluginManager {
 public:
  PluginManager();

 private:
  std::shared_ptr<PluginLoader> plugin_loader;
};

}  // namespace game_engine::plugin

#endif /* SRC_PLUGIN_PLUGINMANAGER_HPP_ */
