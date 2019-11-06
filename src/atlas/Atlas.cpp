#include "Atlas.h"
#include <iostream>

Atlas::Atlas(const string &file_location, const IdRegister &registry)
    : registry_(registry), atlas_coords_parser_(file_location.c_str()) {

  Logger::Log("Parsing atlas file", INFO);
  atlas_coords_parser_.Parse();
  atlas_file_location_ = file_location;
  if (!atlas_texture_.loadFromFile(
          atlas_coords_parser_.GetParseTree().get<string>("atlas.file"))) {
    throw new std::runtime_error(
        "Failed to load atlas " + file_location + " texture from " +
        atlas_coords_parser_.GetParseTree().get<string>("atlas.file"));
  }

  Logger::Log("Loading texture rects", INFO);

  LoadTextureRects();
}

const Parser &Atlas::GetParser() const { return atlas_coords_parser_; }

const sf::Texture &Atlas::GetTexture() const { return atlas_texture_; }

const ptree &Atlas::GetParseTree() const {
  return atlas_coords_parser_.GetParseTree();
}

map<string, sf::IntRect> &Atlas::GetRects(int id) {
  try {
    return atlas_rects_map_[registry_.IdToName(id)];
  } catch (std::out_of_range e) {
    Logger::Log("Failed to get texture rect for " + registry_.IdToName(id),
                MED);
    return atlas_rects_map_["error"];
  }
}

map<string, sf::IntRect> &Atlas::GetRects(const string &name) {
  return atlas_rects_map_[name];
}

map<string, map<string, sf::IntRect>>
Atlas::ReadRectsByKey(string element_key) const {

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
}

Atlas::~Atlas() {
  // dtor
}
