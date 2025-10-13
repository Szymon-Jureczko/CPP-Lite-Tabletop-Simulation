#include <iostream>
#include "classes.h"
#include <time.h>
#include <cstdlib>

using std::cout;
using std::endl;
using std::to_string;

// Character base class implementation
Character::Character(const CharacterStats& stats, const string& characterName)
    : health(stats.health), attackPower(stats.attackPower),
      armorClass(stats.armorClass), magicResistance(stats.magicResistance),
      dmgType(stats.damageType), name(characterName), attackMessage(stats.attackMessage) {}

Character::~Character() {}

int Character::getHealth() const { return health; }
int Character::getAttackPower() const { return attackPower; }
int Character::getArmorClass() const { return armorClass; }
int Character::getMagicRes() const { return magicResistance; }
string Character::getName() const { return name; }
string Character::getDamageType() const { return dmgType; }
int Character::getId() const { return id; }

void Character::getInfo() {
    cout << "Health: " << health
         << " Armor: " << armorClass
         << " Magic resistance: " << magicResistance
         << " Damage type: " << dmgType << endl;
}

int Character::basicAttack() {
    return rand() % attackPower + 1;
}

void Character::seed() {
    srand(time(0));
}

int Knight::idCount = 1;

// Knight
Knight::Knight() : Character(CharacterStats{50, 15, 8, 0, "physical", "hits with his sword"}, "Knight") {
    id = idCount++;
    cout << "Knight " << id << " has been recruited!" << endl;
}

int Wizard::idCount = 1;
int Samurai::idCount = 1;
int Cleric::idCount = 1;

// Wizard
Wizard::Wizard() : Character(CharacterStats{30, 30, 0, 3, "magical", "casts lightning"}, "Wizard") {
    id = idCount++;
    cout << "Wizard " << id << " has been recruited!" << endl;
}

// Samurai
Samurai::Samurai() : Character(CharacterStats{30, 30, 3, 0, "physical", "slashes with katana"}, "Samurai") {
    id = idCount++;
    cout << "Samurai " << id << " has been recruited!" << endl;
}

// Cleric
Cleric::Cleric() : Character(CharacterStats{50, 15, 0, 8, "magical", "casts holy ray"}, "Cleric") {
    id = idCount++;
    cout << "Cleric " << id << " has been recruited!" << endl;
}
