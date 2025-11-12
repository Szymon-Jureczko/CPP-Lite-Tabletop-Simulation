#include <iostream>
#include <vector>
#include <map>
#include "classes.h"
#include "classes.cpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using std::cout;
using std::endl;
using std::runtime_error;
using std::map;
using std::string;
using std::vector;

struct TextureMap {
    map<string, sf::Texture*> textures;
};

sf::Texture* getCharacterTexture(Character* character, TextureMap& textureMap) {
    return textureMap.textures[character->getName()];
}

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

    TextureMap textureMap;
    textureMap.textures["Knight"] = new sf::Texture();
    textureMap.textures["Wizard"] = new sf::Texture();
    textureMap.textures["Samurai"] = new sf::Texture();
    textureMap.textures["Cleric"] = new sf::Texture();
    textureMap.textures["Goblin"] = new sf::Texture();
    textureMap.textures["Skeleton"] = new sf::Texture();
    textureMap.textures["Wraith"] = new sf::Texture();
    textureMap.textures["Dragon"] = new sf::Texture();

    textureMap.textures["Knight"]->loadFromFile("textures/knight.png");
    textureMap.textures["Wizard"]->loadFromFile("textures/wizard.png");
    textureMap.textures["Samurai"]->loadFromFile("textures/samurai.png");
    textureMap.textures["Cleric"]->loadFromFile("textures/cleric.png");
    textureMap.textures["Goblin"]->loadFromFile("textures/goblin.png");
    textureMap.textures["Skeleton"]->loadFromFile("textures/skeleton.png");
    textureMap.textures["Wraith"]->loadFromFile("textures/wraith.png");
    textureMap.textures["Dragon"]->loadFromFile("textures/dragon.png");

    sf::Texture bgTexture, graveTexture;
    bgTexture.loadFromFile("textures/background.png");
    graveTexture.loadFromFile("textures/grave.png");
    sf::Sprite bgSprite(bgTexture);

    Character::seed();

    // Recruitment Phase
    vector<sf::Sprite> partySprites(4);
    vector<Character*> party(4, nullptr);
    vector<char> classChoices = {'1', '2', '3', '4'};

    for (int i = 0; i < 4; i++) {
        bool recruited = false;
        cout << "Recruitment - Press 1=Knight 2=Wizard 3=Samurai 4=Cleric" << endl;

        while (window.isOpen() && !recruited) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    return 0;
                }
                if (event.type == sf::Event::KeyPressed) {
                    for (char choice : classChoices) {
                        if (event.key.code == sf::Keyboard::Num1 + (choice - '1')) {
                            party[i] = Character::partyRecruiter(choice);
                            partySprites[i].setTexture(*getCharacterTexture(party[i], textureMap));
                            recruited = true;
                            break;
                        }
                    }
                }
            }
            window.clear();
            window.draw(bgSprite);
            window.display();
        }
    }

    // Enemy Initialization
    vector<sf::Sprite> enemySprites(4);
    vector<Character*> enemy(4, nullptr);
    for (int i = 0; i < 4; i++) {
        enemy[i] = Character::enemyRecruiter();
        enemySprites[i].setTexture(*getCharacterTexture(enemy[i], textureMap));
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }
        window.clear();
        window.draw(bgSprite);
        window.display();
    }

    for (int i = 0; i < 4; i++) {
        if (party[i] != nullptr) delete party[i];
        if (enemy[i] != nullptr) delete enemy[i];
    }
    for (auto& pair : textureMap.textures) {
        delete pair.second;
    }
    return 0;
}
