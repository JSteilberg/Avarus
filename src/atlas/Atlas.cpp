/*             ___
              / | |_   _ ___ _ __ __  __ _____
             / /| | | / /   |  __/ / / /_____/
            / / | | |/ / /| | | / /_/ /__\ \
           /_/  |_|___/_/ |_|_| \____/_____/

Copyright (C) 2019 Jack Steilberg <jsteil123@gmail.com>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Affero General Public
License as published by the Free Software Foundation; either
version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

A copy of the GNU Affero General Public License should accompany
this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include "Atlas.hpp"

Atlas::Atlas(string file_location, const IdRegister &registry)
    : atlas_file_location_(file_location),
      atlas_coords_parser_(atlas_file_location_),
      registry_(registry),
      atlas_texture_(),
      atlas_rects_map_(),
      err_tex_() {
  // Attempt to parse the atlas file. If it isn't found then create an
  // error texture so that we don't have to crash
  Logger::Log("Parsing atlas file '" + atlas_file_location_ + "'", INFO);
  string atlas_texture_file = "";
  try {
    atlas_coords_parser_.Parse();
    atlas_texture_file =
        atlas_coords_parser_.GetParseTree().get<string>("atlas.file");

    // If we got here, we loaded the atlas coordinate file successfully, so go
    // ahead and load the texture rects
    Logger::Log("Loading texture rects", INFO);
    LoadTextureRects();

    if (!atlas_texture_.loadFromFile(atlas_texture_file)) {
      Logger::Log("Failed to load atlas " + atlas_file_location_ +
                      " texture from " + atlas_texture_file,
                  HIGH);
      atlas_texture_ = CreateErrorTexture();
    }
  } catch (const json_parser_error &ex) {
    Logger::Log("Creating default atlas coordinate map", INFO);
    atlas_rects_map_["error"]["norm"] = sf::IntRect(0, 0, 1, 1);
    atlas_texture_ = CreateErrorTexture();
  }
}

const Parser &Atlas::GetParser() const { return atlas_coords_parser_; }

const sf::Texture &Atlas::GetTexture() const { return atlas_texture_; }

const ptree &Atlas::GetParseTree() const {
  return atlas_coords_parser_.GetParseTree();
}

const map<string, sf::IntRect> &Atlas::GetRects(int id) const {
  try {
    return atlas_rects_map_.at(registry_.IdToName(id));
  } catch (std::out_of_range e) {
    Logger::Log("Failed to get texture rect for " + registry_.IdToName(id),
                MED);
    return atlas_rects_map_.at("error");
  }
}

const map<string, sf::IntRect> &Atlas::GetRects(const string &name) const {
  return atlas_rects_map_.at(name);
}

const map<string, map<string, sf::IntRect>> Atlas::ReadRectsByKey(
    string element_key) const {
  // Get the name of the object and make a pretty singular version
  string entity_type_pl = element_key.substr(element_key.rfind(".") + 1);
  string entity_type;
  if (entity_type_pl.substr(entity_type_pl.length() - 3) == "ies") {
    entity_type = entity_type_pl.substr(0, entity_type_pl.length() - 3) + "y";
  } else if (entity_type_pl.substr(entity_type_pl.length() - 1, 1) == "s") {
    entity_type = entity_type_pl.substr(0, entity_type_pl.length() - 1);
  } else {
    entity_type = entity_type_pl;
  }

  Logger::Log("Loading " + entity_type_pl, INFO);

  map<string, map<string, sf::IntRect>> read_rects_map;

  // Loop through all the objects found in the given key
  for (auto &name_rects :
       atlas_coords_parser_.GetParseTree().get_child(element_key)) {
    Logger::Log(entity_type + " name=" + string(name_rects.first.data()), INFO);

    // Loop through the different sf::IntRects within each object
    for (auto &rects : name_rects.second.get_child("rects")) {
      // Create the rect
      sf::IntRect rect(rects.second.get<int>("x"), rects.second.get<int>("y"),
                       rects.second.get<int>("w"), rects.second.get<int>("l"));

      // Add the rect to the rects map
      read_rects_map[name_rects.first.data()]
                    [rects.second.get<string>("name")] = rect;

      Logger::RawLog("Rect " + rects.second.get<string>("name") +
                         ": x=" + rects.second.get<string>("x") +
                         ", y=" + rects.second.get<string>("y") +
                         ", w=" + rects.second.get<string>("w") +
                         ", l=" + rects.second.get<string>("l"),
                     INFO);
    }
  }
  return read_rects_map;
}

void Atlas::LoadTextureRects() {
  auto rects = ReadRectsByKey("atlas.objects");
  atlas_rects_map_.insert(rects.begin(), rects.end());

  rects = ReadRectsByKey("atlas.entities");
  atlas_rects_map_.insert(rects.begin(), rects.end());

  rects = ReadRectsByKey("atlas.other");
  atlas_rects_map_.insert(rects.begin(), rects.end());

  try {
    auto a = atlas_rects_map_.at("error");
  } catch (std::out_of_range e) {
    Logger::Log("Failed to find error texture", HIGH);
    throw e;
  }
}

const sf::Texture Atlas::CreateErrorTexture() {
  if (!err_tex_.create(1, 1)) {
    string err_msg = "Failed to create backup error texture";
    Logger::Log(err_msg, HIGH);
    throw std::runtime_error(err_msg);
  } else {
    err_tex_.clear(sf::Color::Cyan);
  }
  return err_tex_.getTexture();
}

Atlas::~Atlas() {
  // dtor
}
