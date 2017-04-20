#ifndef ATLAS_H
#define ATLAS_H

#include <SFML/Graphics.hpp>
#include <string>

#include "Parser.h"

using boost::property_tree::ptree;
using boost::property_tree::read_json;
using std::string;

// Class to encapsulate a large texture and divide it into smaller indexed rectangles
// Prevents the game from needing to bind multiple textures to the graphics card
class Atlas
{
  public:

    // do not
    Atlas();

    // Initialize the atlas with a given atlas config file location
    Atlas(string file_location);

    // Returns a ref to the parser used for looking in the config file
    const Parser& GetParser();

    // Returns a ref to the Boost property tree that holds config information
    const ptree& GetPTree();

    // Returns a ref to the texture loaded according to this Atlas' config file
    const sf::Texture& GetTexture();

    // Returns an sf::IntRect to the "norm" rectangle of the
    sf::IntRect[] GetRect(int id);

    sf::

    // Returns an sf::IntRect to the
    sf::IntRect GetRect(const string& id);



    virtual ~Atlas();

  protected:

  private:
    // Parser to be used for indexing the various parts of the atlas texture
    Parser atlas_coords_parser_;

    // Atlas texture usually obtained based on the config file from the parser
    sf::Texture atlas_texture_;

    //
    string file_location_;
};

#endif // ATLAS_H
