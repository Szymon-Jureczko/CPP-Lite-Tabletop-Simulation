#include <iostream>
#include "classes.h"
#include <time.h>
#include <cstdlib>

using std::cout;
using std::endl;
using std::to_string;
using std::string;
using std::vector;

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

Character::~Character() {}

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
    cout << "Health: " << health
         << " Armor: " << armorClass
         << " Magic resistance: " << magicResistance
         << " Damage type: " << dmgType << endl;
}

int Character::basicAttack() {
    int damage = rand() % attackPower + 1;
    cout << "[ " << name << " " << id << " " << attackMessage
         << " for " << damage << " damage ]" << endl;
    return damage;
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

Character* Character::operator-(Character* other) {
    if (health > 0 && other->health > 0) {
        int defense = (dmgType == "physical") ? other->armorClass : other->magicResistance;

        cout << ":::::: " << name << " " << id << " Attacks "
             << other->name << " " << other->id << " ::::::" << endl;

        int dmg = basicAttack();
        dmg = (dmg > defense) ? dmg - defense : 0;

        cout << " [ " << other->name << " " << other->id
             << " is dealt " << dmg << " damage ]" << endl;
        other->health -= dmg;
    }

    if (other->health <= 0) {
        other->health = 0;
    }

    return other;
}

int Goblin::idCount = 1;
int Skeleton::idCount = 1;

// Goblin
Goblin::Goblin() : Character(CharacterStats{25, 15, 3, 0, "physical", "stabs with dagger"}, "Goblin") {
    id = idCount++;
    cout << "Goblin " << id << " has appeared!" << endl;
}

// Skeleton
Skeleton::Skeleton() : Character(CharacterStats{50, 15, 8, 0, "physical", "hits with sword"}, "Skeleton") {
    id = idCount++;
    cout << "Skeleton " << id << " has appeared!" << endl;
}

int Wraith::idCount = 1;
int Dragon::idCount = 1;

// Wraith
Wraith::Wraith() : Character(CharacterStats{50, 25, 0, 3, "magical", "haunts"}, "Wraith") {
    id = idCount++;
    cout << "Wraith " << id << " has appeared!" << endl;
}

// Dragon
Dragon::Dragon() : Character(CharacterStats{60, 30, 9, 9, "magical", "breathes fire"}, "Dragon") {
    id = idCount++;
    cout << "Dragon " << id << " has appeared!" << endl;
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
