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
GNU Lesser General Public License for more details.

A copy of the GNU Affero General Public License should accompany
this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#ifndef ATLAS_H
#define ATLAS_H

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

#include "IdRegister.hpp"
#include "Logger.hpp"
#include "Parser.hpp"

using boost::property_tree::ptree;
using boost::property_tree::ptree_bad_data;
using boost::property_tree::ptree_bad_path;
using boost::property_tree::ptree_error;
using boost::property_tree::read_json;
using std::map;
using std::string;

// Class to encapsulate a large texture and divide it into smaller indexed
// rectangles Prevents the game from needing to bind multiple textures to the
// graphics card
class Atlas {
 public:
  // Initialize the atlas with a given atlas config file location
  Atlas(string file_location, const IdRegister &registry);

  // Returns a ref to the parser used for looking in the config file
  const Parser &GetParser() const;

  // Returns a ref to the Boost property tree that holds config information
  const ptree &GetParseTree() const;

  // Returns a ref to the texture loaded according to this Atlas' config file
  const sf::Texture &GetTexture() const;

  // Returns map of the specified Sprite's IntRects (specified by id).
  // If there's only one, its value will be mapped to "norm"
  const map<string, sf::IntRect> &GetRects(int id) const;

  // Returns map of the specified Sprite's IntRects (specified by name).
  // If there's only one, its value will be mapped to "norm"
  const map<string, sf::IntRect> &GetRects(const string &name) const;

  virtual ~Atlas();

 private:
  // Loads all the texture rects into the atlas_rects_map_ var
  void LoadTextureRects();

  const map<string, map<string, sf::IntRect>> ReadRectsByKey(
      string element_key) const;

  // String for that atlas' file location
  string atlas_file_location_;

  // Used for converting int IDs to their corresponding names
  const IdRegister &registry_;

  // Parser to be used for indexing the various parts of the atlas texture
  Parser atlas_coords_parser_;

  // Atlas texture usually obtained based on the config file from the parser
  sf::Texture atlas_texture_;

  // The first string key is the name of the object type (i.e. "player", "dirt",
  // etc.) The string key for the second map is the name of a specific
  // sf::IntRect subsection of the atlas for a specific texture for a given
  // object (i.e. "norm", "step4", etc.)
  map<string, map<string, sf::IntRect>> atlas_rects_map_;
};

#endif  // ATLAS_H