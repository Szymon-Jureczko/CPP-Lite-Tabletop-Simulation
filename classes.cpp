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
