#ifndef CLASSES_H_INCLUDED
#define CLASSES_H_INCLUDED
#include <vector>
#include <string>

using std::vector;
using std::string;

// Character stats configuration
struct CharacterStats {
    int health;
    int attackPower;
    int armorClass;
    int magicResistance;
    string damageType;
    string attackMessage;
};

// Base character class
class Character {
protected:
    int health;
    int attackPower;
    int armorClass;
    int magicResistance;
    string dmgType;
    string name;
    int id;
    string attackMessage;

public:
    Character(const CharacterStats& stats, const string& characterName);
    virtual ~Character();

    int getHealth() const;
    int getArmorClass() const;
    int getMagicRes() const;
    int getAttackPower() const;
    int getId() const;
    string getName() const;
    string getDamageType() const;

    static void seed();
    virtual int basicAttack();
    void getInfo();
};


class Knight : public Character {
private:
    static int idCount;
public:
    Knight();
};

#endif // CLASSES_H_INCLUDED
