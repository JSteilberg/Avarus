#include "Atlas.h"
#include <iostream>

Atlas::Atlas(const string& file_location, const IdRegister& registry) :
  registry_(registry),
  atlas_coords_parser_(file_location.c_str()) {

  Logger::Log("Parsing atlas file", INFO);
  atlas_coords_parser_.Parse();
  atlas_file_location_ = file_location;
  if (!atlas_texture_.loadFromFile(atlas_coords_parser_.GetParseTree().get<string>("atlas.file"))) {
    throw new std::runtime_error("Failed to load atlas "
                                 + file_location
                                 + " texture from "
                                 + atlas_coords_parser_.GetParseTree().get<string>("atlas.file"));
  }

  Logger::Log("Loading texture rects", INFO);

  LoadTextureRects();
}

const Parser& Atlas::GetParser() const {
  return atlas_coords_parser_;
}

const sf::Texture& Atlas::GetTexture() const {
  return atlas_texture_;
}

const ptree& Atlas::GetParseTree() const {
  return atlas_coords_parser_.GetParseTree();
}

map<string, sf::IntRect>& Atlas::GetRects(int id) {
  try {
    return atlas_rects_map_[registry_.IdToName(id)];
  } catch(std::out_of_range e) {
    Logger::Log("Failed to get texture rect for " + registry_.IdToName(id), MED);
    return atlas_rects_map_["error"];
  }
}

map<string, sf::IntRect>& Atlas::GetRects(const string& name) {
  return atlas_rects_map_[name];
}

void Atlas::LoadTextureRects() {

  Logger::Log("Loading objects", INFO);

  // Loop through all the objects in the atlas
  BOOST_FOREACH(ptree::value_type v, atlas_coords_parser_.GetParseTree().get_child("atlas.objects")) {
    Logger::Log("Object name=" + string(v.first.data()), INFO);

    // Loop through the different sf::IntRects within each object
    BOOST_FOREACH(ptree::value_type rects, v.second.get_child("rects")) {
      // Create the rect
      sf::IntRect rect(rects.second.get<int>("x"),
                       rects.second.get<int>("y"),
                       rects.second.get<int>("l"),
                       rects.second.get<int>("w"));

      // Add the rect to the rects map
      atlas_rects_map_[string(v.first.data())][rects.second.get<string>("name")] = rect;
      Logger::RawLog("Rect " + rects.second.get<string>("name") +
                     ": x=" + rects.second.get<string>("x") +
                     ", y=" + rects.second.get<string>("y") +
                     ", l=" + rects.second.get<string>("l") +
                     ", w=" + rects.second.get<string>("w"), INFO);
    }
  }

  Logger::Log("Loading entities", INFO);

  // Loop through all the entities in the atlas
  BOOST_FOREACH(ptree::value_type v, atlas_coords_parser_.GetParseTree().get_child("atlas.entities")) {
    Logger::Log("Entity name=" + string(v.first.data()), INFO);

    // Loop through the different sf::IntRects within each object
    BOOST_FOREACH(ptree::value_type rects, v.second.get_child("rects")) {
      // Create the rect
      sf::IntRect rect(rects.second.get<int>("x"),
                       rects.second.get<int>("y"),
                       rects.second.get<int>("l"),
                       rects.second.get<int>("w"));

      // Add the rect to the rects map
      atlas_rects_map_[v.first.data()][rects.second.get<string>("name")] = rect;

      Logger::RawLog("Rect " + rects.second.get<string>("name") +
                     ": x=" + rects.second.get<string>("x") +
                     ", y=" + rects.second.get<string>("y") +
                     ", l=" + rects.second.get<string>("l") +
                     ", w=" + rects.second.get<string>("w"), INFO);
    }
  }

  Logger::Log("Loading others", INFO);

  // Loop through all the misc textures in the atlas
  // Loop through all the entities in the atlas
  BOOST_FOREACH(ptree::value_type v, atlas_coords_parser_.GetParseTree().get_child("atlas.other")) {
    Logger::Log("Other name=" + string(v.first.data()), INFO);

    // Loop through the different sf::IntRects within each object
    BOOST_FOREACH(ptree::value_type rects, v.second.get_child("rects")) {
      // Create the rect
      sf::IntRect rect(rects.second.get<int>("x"),
                       rects.second.get<int>("y"),
                       rects.second.get<int>("l"),
                       rects.second.get<int>("w"));

      // Add the rect to the rects map
      atlas_rects_map_[v.first.data()][rects.second.get<string>("name")] = rect;

      Logger::RawLog("Rect " + rects.second.get<string>("name") +
                     ": x=" + rects.second.get<string>("x") +
                     ", y=" + rects.second.get<string>("y") +
                     ", l=" + rects.second.get<string>("l") +
                     ", w=" + rects.second.get<string>("w"), INFO);
    }
  }
}

Atlas::~Atlas() {
  //dtor
}
