#ifndef CONSOLE_H
#define CONSOLE_H

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <vector>
#include <queue>
#include <map>

#include "Logger.h"

using std::string;
using std::map;

class Console : public sf::Drawable {
 public:
    Console();

    virtual void draw(sf::RenderTarget &target,
                      sf::RenderStates states) const override;

    void clear();

    void Update();

    
    
 private:
    //std::queue<string> history;

    // Translucent background to make info stand out
    sf::RectangleShape background_;

    // Text object that is used to draw the console to screen
    sf::Text info_;

    // Font to draw the debug overlay with
    sf::Font font_;

    string msg_;
};


#endif // CONSOLE_H
