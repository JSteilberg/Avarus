#include <SFML/Graphics.hpp>
#include "gamestate.cpp"

std::string version = "1.0";
GameState gamestate = MAIN_LOOP;
const bool DEBUG_MODE = true;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Avarus v" + version);
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
