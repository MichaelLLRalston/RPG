#pragma once
#include "Text.h"
#include "RPG.h"
#include <iostream>

using namespace std;

class Monster
{
public:
	int maxhp, hp;
	attributes atts;
	char *mname;
	char *attacktext;
	char *deathtext;
	char *wintext;
	int masteries;
	int copper;
	ARMOR armor;
	WEAPON weapon;
	Monster()
	{
		masteries = 0;
		switch (DiceRoll(1, 2))
		{
		case 1:
			mname = " A small Goblin ";
			hp = maxhp = DiceRoll(3, 6);
			atts.strength = DiceRoll(2, 6);
			atts.inspiration = DiceRoll(2, 6);
			atts.focus = DiceRoll(2, 6);
			atts.faith = DiceRoll(2, 6);
			atts.dexterity = DiceRoll(2, 6);
			atts.cleverness = DiceRoll(2, 6);
			copper = DiceRoll(10, 5);
			armor = LOINCLOTH;
			weapon = FISTS;
			attacktext = " a moldy stick ";
			deathtext = " the goblin cries out \" why yous hits me so hards? \" ";
			wintext = " the goblin celebrates its victory by dancing around with its moldy stick ";
			break;
		case 2:
			mname = " A large Rat ";
			hp = maxhp = DiceRoll(3, 6);
			atts.strength = DiceRoll(2, 6);
			atts.inspiration = DiceRoll(2, 6);
			atts.focus = DiceRoll(2, 6);
			atts.faith = DiceRoll(2, 6);
			atts.dexterity = DiceRoll(2, 6);
			atts.cleverness = DiceRoll(2, 6);
			copper = DiceRoll(5, 8);
			armor = LOINCLOTH;
			weapon = FISTS;
			attacktext = " sharp pointy teeth ";
			deathtext = "  it squels loudly. ";
			wintext = " the Rat begins gnawing on you're dead carcass. ";
			break;
		}
	}
	int Mitigate(int damage)
	{
		int dice = atts.dexterity + armor;
		damage -= DiceRoll(dice, 3) - dice;
		cout << " AFTER MIT:  " << damage;
		if (damage <= 0)
		{
			damage = 1;
		}
		hp -= damage;
		return damage;
	}
};