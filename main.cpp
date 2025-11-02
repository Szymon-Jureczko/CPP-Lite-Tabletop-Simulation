#include <iostream>
#include "classes.h"
#include "classes.cpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using std::cout;
using std::endl;
using std::runtime_error;

int main() {
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Game Window", sf::Style::Fullscreen);
    sf::Font font;

    try {
        if (!font.loadFromFile("textures/font.ttf")) {
            throw runtime_error("Error loading font");
        }
    } catch (runtime_error& e) {
        cout << "Error: - " << e.what() << endl;
        return -1;
    }

    Character::seed();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear();
        window.display();
    }

    return 0;
}
