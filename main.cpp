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

void executeAttackRound(vector<Character*>& attackers, vector<Character*>& defenders) {
    for (int i = 0; i < 4; i++) {
        if (attackers[i] == nullptr) continue;

        Character* target = attackers[i]->partyTarget(defenders.data(), 4);
        if (target == nullptr) continue;

        *attackers[i] - target;

        if (target->getHealth() == 0) {
            for (int j = 0; j < 4; j++) {
                if (defenders[j] == target) {
                    delete target;
                    defenders[j] = nullptr;
                    break;
                }
            }
        }
    }
}

void renderLog(sf::RenderWindow& window, const sf::Font& font, float yPos = 50.0f) {
    for (const auto& line : actionLogHistory) {
        sf::Text logLine(line, font, 22);
        logLine.setFillColor(sf::Color::White);
        logLine.setPosition(960.0f - (logLine.getGlobalBounds().width / 2), yPos);
        window.draw(logLine);
        yPos += 25.0f;
    }
}

void assignSpritePosition(vector<sf::Sprite>& sprites, bool isParty) {
    for (int i = 0; i < 4; i++) {
        if (isParty) {
            sprites[i].setPosition(150, 200 + i * 200);
        } else {
            sprites[i].setPosition(1500, 250 + i * 200);
        }
    }
}

void initializeStatsText(vector<sf::Text>& statsTexts, const sf::Font& font) {
    for (int i = 0; i < 4; i++) {
        statsTexts[i].setFont(font);
        statsTexts[i].setCharacterSize(17);
        statsTexts[i].setFillColor(sf::Color::White);
    }
}

void updateCharacterStats(vector<sf::Text>& statsTexts, const vector<Character*>& characters) {
    for (int i = 0; i < 4; i++) {
        if (characters[i] != nullptr) {
            statsTexts[i].setString(characters[i]->getStatsString());
        }
    }
}

void updateStatsPositions(vector<sf::Text>& statsTexts, const vector<sf::Sprite>& sprites, bool isParty) {
    for (int i = 0; i < 4; i++) {
        if (isParty) {
            statsTexts[i].setPosition(sprites[i].getPosition().x - 140, sprites[i].getPosition().y);
        } else {
            statsTexts[i].setPosition(sprites[i].getPosition().x - 140, sprites[i].getPosition().y - 20);
        }
    }
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
        updateActionLog("Recruitment - Press 1 for Knight, 2 for Wizard, 3 for Samurai, 4 for Cleric");

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
            renderLog(window, font);
            window.display();
        }

        partySprites[i].setPosition(150, 200 + i * 200);
    }

    // Enemy Initialization
    vector<sf::Sprite> enemySprites(4);
    vector<Character*> enemy(4, nullptr);
    for (int i = 0; i < 4; i++) {
        enemy[i] = Character::enemyRecruiter();
        enemySprites[i].setTexture(*getCharacterTexture(enemy[i], textureMap));
    }

    assignSpritePosition(partySprites, true);
    assignSpritePosition(enemySprites, false);

    vector<sf::Text> partyStatsText(4), enemyStatsText(4);
    initializeStatsText(partyStatsText, font);
    initializeStatsText(enemyStatsText, font);
    updateCharacterStats(partyStatsText, party);
    updateCharacterStats(enemyStatsText, enemy);
    updateStatsPositions(partyStatsText, partySprites, true);
    updateStatsPositions(enemyStatsText, enemySprites, false);

    // Game Loop
    int turn = 1;
    bool partyTurn = true;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        if (partyTurn) {
            updateActionLog("|TURN " + std::to_string(turn) + " - PARTY TURN|");
            executeAttackRound(party, enemy);
        } else {
            updateActionLog("|TURN " + std::to_string(turn) + " - ENEMY TURN|");
            executeAttackRound(enemy, party);
        }

        updateCharacterStats(partyStatsText, party);
        updateCharacterStats(enemyStatsText, enemy);

        window.clear();
        window.draw(bgSprite);
        for (auto& sp : partySprites) window.draw(sp);
        for (auto& sp : enemySprites) window.draw(sp);
        for (auto& t : partyStatsText) window.draw(t);
        for (auto& t : enemyStatsText) window.draw(t);
        renderLog(window, font);
        window.display();

        partyTurn = !partyTurn;
        turn++;
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
