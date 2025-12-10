#include <iostream>
#include "classes.h"
#include <time.h>
#include <cstdlib>
#include <vector>
#include <windows.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::to_string;
using std::map;

// Static ID counters
int Knight::idCount = 1;
int Wizard::idCount = 1;
int Samurai::idCount = 1;
int Cleric::idCount = 1;
int Goblin::idCount = 1;
int Skeleton::idCount = 1;
int Wraith::idCount = 1;
int Dragon::idCount = 1;

// Global action log
vector<string> actionLogHistory;

void updateActionLog(const string& message) {
    actionLogHistory.push_back(message);
    if (actionLogHistory.size() > 15) {
        actionLogHistory.erase(actionLogHistory.begin());
    }
}

// Character base class implementation
Character::Character(const CharacterStats& stats, const string& characterName)
    : health(stats.health), attackPower(stats.attackPower), 
      armorClass(stats.armorClass), magicResistance(stats.magicResistance),
      dmgType(stats.damageType), name(characterName), attackMessage(stats.attackMessage) {}

Character::~Character() {
    updateActionLog(" !!!! " + name + " " + to_string(id) + " has died !!!!");
}

int Character::getHealth() const { return health; }
int Character::getAttackPower() const { return attackPower; }
int Character::getArmorClass() const { return armorClass; }
int Character::getMagicRes() const { return magicResistance; }
string Character::getName() const { return name; }
string Character::getDamageType() const { return dmgType; }
int Character::getId() const { return id; }

string Character::getStatsString() const {
    return name + " " + to_string(id) + "| HP: " + to_string(health) +
           " AP: " + to_string(attackPower) + " AC: " + to_string(armorClass) +
           " MR: " + to_string(magicResistance);
}

void Character::getInfo() {
    updateActionLog("Health: " + to_string(health) +
                    " Armor: " + to_string(armorClass) +
                    " Magic resistance: " + to_string(magicResistance) +
                    " Damage type: " + dmgType);
}

int Character::basicAttack() {
    int damage = rand() % attackPower + 1;
    updateActionLog("[ " + name + " " + to_string(id) + " " + attackMessage + 
                   " for " + to_string(damage) + " damage ]");
    return damage;
}

int Character::ability() {
    return 0;
}

void Character::seed() {
    srand(time(0));
}

Character* Character::partyTarget(Character** enemyArray, int n) {
    Character* target = nullptr;
    for (int i = 0; i < n; i++) {
        if (enemyArray[i] == nullptr) continue;
        
        if (target == nullptr || 
            (dmgType == "physical" && enemyArray[i]->armorClass > target->armorClass) ||
            (dmgType == "magical" && enemyArray[i]->magicResistance > target->magicResistance)) {
            target = enemyArray[i];
        }
    }
    return target;
}

Character* Character::operator-(Character* other) {
    if (health > 0 && other->health > 0) {
        int defense = (dmgType == "physical") ? other->armorClass : other->magicResistance;
        
        updateActionLog(":::::: " + name + " " + to_string(id) + " Attacks " + other->name + 
                       " " + to_string(other->id) + " ::::::");
        
        int dmg = basicAttack();
        dmg = (dmg > defense) ? dmg - defense : 0;
        
        updateActionLog(" [ " + other->name + " " + to_string(other->id) + " is dealt " + 
                       to_string(dmg) + " damage ]");
        other->health -= dmg;
    }

    if (other->health <= 0) {
        other->health = 0;
    }

    return other;
}

Character* Character::partyRecruiter(char choice) {
    switch (choice) {
        case '1': return new Knight();
        case '2': return new Wizard();
        case '3': return new Samurai();
        case '4': return new Cleric();
    }
    return nullptr;
}

Character* Character::enemyRecruiter() {
    int r = rand() % 100;
    if (r < 30) return new Skeleton();
    else if (r < 60) return new Wraith();
    else if (r < 80) return new Dragon();
    else return new Goblin();
}

// Knight
Knight::Knight() : Character(CharacterStats{50, 15, 8, 0, "physical", "hits with his sword"}, "Knight") {
    id = idCount++;
    updateActionLog("Knight " + to_string(id) + " has been recruited!");
}

// Wizard
Wizard::Wizard() : Character(CharacterStats{30, 30, 0, 3, "magical", "casts lightning"}, "Wizard") {
    id = idCount++;
    updateActionLog("Wizard " + to_string(id) + " has been recruited!");
}

// Samurai
Samurai::Samurai() : Character(CharacterStats{30, 30, 3, 0, "physical", "slashes with katana"}, "Samurai") {
    id = idCount++;
    updateActionLog("Samurai " + to_string(id) + " has been recruited!");
}

// Cleric
Cleric::Cleric() : Character(CharacterStats{50, 15, 0, 8, "magical", "casts holy ray"}, "Cleric") {
    id = idCount++;
    updateActionLog("Cleric " + to_string(id) + " has been recruited!");
}

// Goblin
Goblin::Goblin() : Character(CharacterStats{25, 15, 3, 0, "physical", "stabs with dagger"}, "Goblin") {
    id = idCount++;
    updateActionLog("Goblin " + to_string(id) + " has appeared!");
}

// Skeleton
Skeleton::Skeleton() : Character(CharacterStats{50, 15, 8, 0, "physical", "hits with sword"}, "Skeleton") {
    id = idCount++;
    updateActionLog("Skeleton " + to_string(id) + " has appeared!");
}

// Wraith
Wraith::Wraith() : Character(CharacterStats{50, 25, 0, 3, "magical", "haunts"}, "Wraith") {
    id = idCount++;
    updateActionLog("Wraith " + to_string(id) + " has appeared!");
}

// Dragon
Dragon::Dragon() : Character(CharacterStats{60, 30, 9, 9, "magical", "breathes fire"}, "Dragon") {
    id = idCount++;
    updateActionLog("Dragon " + to_string(id) + " has appeared!");
}
