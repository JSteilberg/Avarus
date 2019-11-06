#ifndef ATLAS_H
#define ATLAS_H

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

#include "IdRegister.h"
#include "Logger.h"
#include "Parser.h"

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
  Atlas(const string &file_location, const IdRegister &registry);

  // Returns a ref to the parser used for looking in the config file
  const Parser &GetParser() const;

  // Returns a ref to the Boost property tree that holds config information
  const ptree &GetParseTree() const;

  // Returns a ref to the texture loaded according to this Atlas' config file
  const sf::Texture &GetTexture() const;

  // Returns map of the specified Sprite's IntRects (specified by id).
  // If there's only one, its value will be mapped to "norm"
  map<string, sf::IntRect> &GetRects(int id);

  // Returns map of the specified Sprite's IntRects (specified by name).
  // If there's only one, its value will be mapped to "norm"
  map<string, sf::IntRect> &GetRects(const string &name);

  virtual ~Atlas();

protected:
private:
  map<string, map<string, sf::IntRect>>
  ReadRectsByKey(string element_key) const;

  // Used for converting int IDs to their corresponding names
  const IdRegister &registry_;

  // Loads all the texture rects into the atlas_rects_map_ var
  void LoadTextureRects();

  // Parser to be used for indexing the various parts of the atlas texture
  Parser atlas_coords_parser_;

  // Parser to be used for translating object id's into names
  Parser id_key_parser_;

  // Atlas texture usually obtained based on the config file from the parser
  sf::Texture atlas_texture_;

  // String for that atlas' file location
  string atlas_file_location_;

  // The first string key is the name of the object type (i.e. "player", "dirt",
  // etc.) The string key for the second map is the name of a specific
  // sf::IntRect subsection of the atlas for a specific texture for a given
  // object (i.e. "norm", "step4", etc.)
  map<string, map<string, sf::IntRect>> atlas_rects_map_;
};

#endif // ATLAS_H
