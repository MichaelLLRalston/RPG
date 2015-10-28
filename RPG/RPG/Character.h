#pragma once

#include "Text.h"
#include "RPG.h"
#include "Monster.h"
#include <iostream>

using namespace std;

// 3 data types , public- anyone can look at it/ change it, private- only that class , protected - mine and child... 
// by default, it goes to private, SO MAKE SURE YOU HAVE THE RIGHT DATA TYPE
//function in general, a return type, name , and (parameters)
class Character
{
protected:
	attributes atts;
	int copper;
	OCC charClass;
	RACE charRace;
	int hp, hpmax;
	unsigned int mp, mpmax;
	LOCATION location;
	WEAPON Weapon;
	ARMOR Armor;
	int masteries;
public:
	// Constructors
	Character()
	{
		cout << "CHARACTER CREATED" << endl;
		copper = 50000;
		location = VIEWSTATS;
	}
	// Accesories
	void SetAtts(attributes tmpAtts)
	{
		atts = tmpAtts;
	}
	attributes GetAtts()
	{
		return atts;
	}
	LOCATION GetLocation()
	{
		return location;
	}
	virtual void Attack(Monster* monster) { }

	int Mitigate(int damage)
	{
		int dice = atts.dexterity + Armor;
		damage -= DiceRoll(dice, 3) - dice;
		cout << " AFTER MIT:  " << damage;
		if (damage <= 0)
		{
			damage = 1;
		}
		hp -= damage;
		return damage;
	}
	void MonsterAttack(Monster* monster1)
	{
		int damage = 0;
		int targetroll = 10 + (monster1->atts.strength + monster1->atts.dexterity) - (atts.strength + atts.dexterity);
		if (targetroll > 17)
		{
			targetroll = 17;
		}
		if (targetroll > 3)
		{
			targetroll = 3;
		}
		bool hit = targetroll >= DiceRoll(1, 20);
		if (!hit)
		{
			cout << monster1->mname << " misses! ";
		}
		else
		{
			int dice = monster1->atts.strength + monster1->weapon + monster1->masteries;
			damage = DiceRoll(dice, 3) - dice;
			cout << " monster damage " << damage;
			damage = Mitigate(damage);
			cout << "/n" << monster1->mname << " attacks you with " << monster1->attacktext << " for " << damage << " damage! ";
		}
	}
	int PawnItem(int item, int sell)
	{
		int tempgold = 0;
		switch (item)
		{
		case 7:
			tempgold += 1600;
		case 6:
			tempgold += 800;
		case 5:
			tempgold += 400;
		case 4:
			tempgold += 200;
		case 3:
			tempgold += 100;
		case 2:
			tempgold += 50;
		case 1:
			tempgold += 50;
		default:
			break;
		}
		if (sell == 1)
		{
			copper += tempgold;
		}
		return tempgold;
	}

	//Locations
	void LocStats()
	{
		bool reroll = true;
		char menuitem;
		while (reroll)
		{
			reroll = false;
			cout << "\nYou look yourself over.\n";
			DisplayStats(atts);
			cout << "HP: " << hp << " / " << hpmax;
			cout << "\nMP: " << mp << " / " << mpmax;
			cout << "\nCopper: " << copper;
			cout << "\nArmor: ";
			switch (Armor)
			{
			case 0:
				cout << "LoinCloth";
				break;
			case 1:
				cout << "Cloth";
				break;
			case 2:
				cout << "Leather";
				break;
			case 3:
				cout << "Chainmail";
				break;
			case 4:
				cout << "Platemail";
				break;
			case 5:
				cout << "Ancient Platemail";
				break;
			case 6:
				cout << "Magic Platemail";
				break;
			case 7:
				cout << "Arcane Platemail";
				break;
			}
			cout << "\n Weapon: ";
			switch (Weapon)
			{
			case 0:
				cout << "Fists";
				break;
			case 1:
				cout << "Dagger";
				break;
			case 2:
				cout << "Staff";
				break;
			case 3:
				cout << "Sword";
				break;
			case 4:
				cout << "Ancient Sword";
				break;
			case 5:
				cout << "Magic Sword";
				break;
			case 6:
				cout << "Arcane Sword";
				break;
			}

			cout << "\n[G]o back to town\n";
			cin >> menuitem;
			switch (menuitem)
			{
			case 'g':
			case 'G':
				location = TOWN;
				break;
			default:
				reroll = true;
				break;
			}
		}
	}
	void LocTown()
	{
		bool reroll = true;
		char menuitem;
		while (reroll)
		{
			reroll = false;
			cout << "\n You arrive in the far off lands of Yarnik. \n\n  As you search around you see; a weapon shop, an armorshop \n \n and the exit to the forest of bonelock : ";
			cout << "\n[1] The Forest \t\t [4] The Weaponsmith";
			cout << "\n[2] The Armorsmith \t\t [5] Quit\n ";
			cout << "\n[3] View your Stats\n ";
			cin >> menuitem;
			switch (menuitem)
			{
			case '1':
				location = FOREST;
				break;
			case '2':
				location = ARMORSMITH;
				break;
			case '3':
				location = VIEWSTATS;
				break;
			case '4':
				location = WEAPONSMITH;
			case '5':
				location = QUIT;
				break;
			default:
				cout << "invalid entry please try again" << endl;
				reroll = true;
				break;
			}
		}
	}
	void LocForest()
	{
		bool reroll = true;
		char menuitem;
		while (reroll)
		{
			reroll = false;
			cout << "\nAs you leave the town of yornik you see a few roads\n one is worn down and the sign is hard to read \n the next is lable alchemist hut  \n the final road wraps back to town...";
			cout << "\n[1] Look for Monsters\t\t [3] return to town  ";
			cout << "\n[2] Visit alchemist Hut ";
			cin >> menuitem;
			switch (menuitem)
			{
			case '1':
				location = MONSTER;
				break;
			case '2':
				location = ALCHEMIST;
				break;
			case '3':
				location = TOWN;
				break;
			default:
				cout << "Invalid entry please try again!" << endl;
				reroll = true;
				break;
			}
		}
	}
	void LocMonster()
	{
		Monster monster1;
		cout << "\nYou hear a rustle in the bushes. " << monster1.mname << " Jumps out at you!\n";
		while (hp > 0 && monster1.hp > 0)
		{
			cout << "\n\n" << monster1.mname << ": " << monster1.hp << "/" << monster1.maxhp;
			cout << "\nYou: " << hp << "/" << hpmax;
			cout << "\n\nAction?\n";
			Attack(&monster1);
			if (monster1.hp > 0)
			{
				MonsterAttack(&monster1);
			}
		}
		if (monster1.hp <= 0)
		{
			cout << " as it dies" << monster1.deathtext;
			location = FOREST;
			cout << "\n you collect" << monster1.copper << "copper from the corpse.";
			copper += monster1.copper;
		}
		if (hp <= 0)
		{
			cout << "\n" << monster1.wintext;
			cout << "\n you have died";
			location = QUIT;
		}
	}
	void LocArmorsmith()
	{
		bool reroll = true;
		char menuitem;
		while (reroll)
		{
			reroll = false;
			cout << "\n You enter a shop covered wall to wall in armors. \n the heat from the forge in the back cause sweat almost instantly. \n the shop owner looks at you and quarries at your intentions. ";

			cout << "\n[1] Buy Armor\t\t [3] Leave the shop";
			cout << "\n[2] Sell Armor\n";
			cin >> menuitem;
			switch (menuitem)
			{
			case '1':
				location = BUYARMOR;
				break;
			case '2':
				location = SELLARMOR;
				break;
			case '3':
				location = TOWN;
				break;

			default:
				cout << "Invalid entry please try again!" << endl;
				reroll = true;
				break;
			}
		}

	}

	void LocWeaponSmith()
	{
		bool reroll = true;
		char menuitem;
		while (reroll)
		{
			reroll = false;
			cout << "\n You enter a shop covered wall to wall in blades and staffs. \n the magic from some weapons is strong enough to feel as you walk towards the owner. \n the shop owner looks at you and quarries at your intentions. ";

			cout << "\n[1] Buy Weapon\t\t [3] Leave the shop";
			cout << "\n[2] Sell Weapon\n";
			cin >> menuitem;
			switch (menuitem)
			{
			case '1':
				location = BUYWEAPON;
				break;
			case '2':
				location = SELLWEAPON;
				break;
			case '3':
				location = TOWN;
				break;

			default:
				cout << "Invalid entry please try again!" << endl;
				reroll = true;
				break;
			}
		}

	}
	void LocBuyWeapon()
	{
		bool reroll = true;
		bool nosale = false;
		int menuitem;
		while (reroll)
		{
			reroll = false;
			cout << "\n amongst the masses of Swords and staffs hung on the wall you choose...";
			switch (Armor)
			{
			case FISTS:
				cout << "\n [1] Dagger \t 100 copper";
			case DAGGER:
				cout << "\n [2] Staff \t 200 copper";
			case STAFF:
				cout << "\n [3] Sword \t 400 copper";
			case SWORD:
				cout << "\n [4] Ancient Sword \t 800 copper";
			case ANCIENTBLADE:
				cout << "\n [5] Magic Sword \t 1600 copper";
			case MAGICBLADE:
				cout << "\n [6] Arcane sword \t 3200 copper";

			default:
				cout << "\n [8] Back to shop";
				break;
			}

			int LowMenu = Weapon + 1;
			cin >> menuitem;
			if (menuitem < LowMenu)
			{
				menuitem = 8;
			}

			switch (menuitem)
			{
			case 1:
				if (copper >= 100)
				{
					cout << "\n you buy Dagger for 100 copper \n you recieve." << PawnItem(Weapon, 1) << " copper for selling your old Weapon";
					copper -= 100;
					Weapon = DAGGER;
					cout << "you have" << copper << " copper";
				}
				else
				{
					nosale = true;
				}
				break;
			case 2:
				if (copper >= 200)
				{
					cout << "\n you buy Staff for 200 copper \n you recieve." << PawnItem(Weapon, 1) << " copper for selling your old Weapon";
					copper -= 200;
					Weapon = STAFF;
					cout << "you have" << copper << " copper";
				}
				else
				{
					nosale = true;
				}
				break;
			case 3:
				if (copper >= 400)
				{
					cout << "\n you buy Sword for 400 copper \n you recieve." << PawnItem(Weapon, 1) << " copper for selling your old Weapon";
					copper -= 400;
					Weapon = SWORD;
					cout << "you have" << copper << " copper";
				}
				else
				{
					nosale = true;
				}
				break;
			case 4:
				if (copper >= 800)
				{
					cout << "\n you buy Ancient Sword for 800 copper \n you recieve." << PawnItem(Weapon, 1) << " copper for selling your old Weapon";
					copper -= 800;
					Weapon = ANCIENTBLADE;
					cout << "you have" << copper << " copper";
				}
				else
				{
					nosale = true;
				}
				break;
			case 5:
				if (copper >= 1600)
				{
					cout << "\n you buy Magic Sword for 1600 copper \n you recieve." << PawnItem(Weapon, 1) << " copper for selling your old Weapon";
					copper -= 1600;
					Weapon = MAGICBLADE;
					cout << "you have" << copper << " copper";
				}
				else
				{
					nosale = true;
				}
				break;
			case 6:
				if (copper >= 3200)
				{
					cout << "\n you buy Arcane Sword for 3200 copper \n you recieve." << PawnItem(Weapon, 1) << " copper for selling your old Weapon";
					copper -= 3200;
					Weapon = ARCANEBLADE;
					cout << "you have" << copper << " copper";
				}
				else
				{
					nosale = true;
				}
				break;
			case 7:
				break;
			default:
				reroll = true;
				break;

			}
		}
		if (nosale)
		{
			cout << "You are too poor for that";
		}
		location = WEAPONSMITH;
	}
	void LocSellWeapon()
	{
		bool reroll = true;
		char menuitem;
		while (reroll)
		{
			reroll = false;
			cout << "\n the Weapon smith looks over your Weapon \" ill give you " << PawnItem(Weapon, 0) << "copper for it. If thats ok with you? [Y]es / [N]o";
			cin >> menuitem;
			switch (menuitem)
			{
			case 'y':
			case 'Y':
				cout << "\n you sell your Weapon for" << PawnItem(Weapon, 1) << " copper.";
				Weapon = FISTS;
				break;
			case 'n':
			case 'N':
				cout << "\n you take your Weapon back.";
				break;
			default:
				cout << "Invalid entry please try again!" << endl;
				reroll = true;
				break;
			}
		}
		location = WEAPONSMITH;
	}

	void LocBuyArmor()
	{
		bool reroll = true;
		bool nosale = false;
		int menuitem;
		while (reroll)
		{
			reroll = false;
			cout << "\n amongst the masses of armors hung on the wall you choose...";
			switch (Armor)
			{
			case LOINCLOTH:
				cout << "\n [1] Cloth Armor \t 100 copper";
			case CLOTH:
				cout << "\n [2] Leather Armor \t 200 copper";
			case LEATHER:
				cout << "\n [3] Chainmail Armor \t 400 copper";
			case CHAIN:
				cout << "\n [4] Platemail Armor \t 800 copper";
			case PLATE:
				cout << "\n [5] Ancient Platemail Armor \t 1600 copper";
			case ANCIENTPLATE:
				cout << "\n [6] Magic Platemail Armor \t 3200 copper";
			case MAGICPLATE:
				cout << "\n [7] Arcane Platemail Armor \t 6400 copper";
			default:
				cout << "\n [8] Back to shop";
				break;
			}

			int LowMenu = Armor + 1;
			cin >> menuitem;
			if (menuitem < LowMenu)
			{
				menuitem = 8;
			}

			switch (menuitem)
			{
			case 1:
				if (copper >= 100)
				{
					cout << "\n you buy Cloth armor for 100 copper \n you recieve." << PawnItem(Armor, 1) << " copper for selling your old armor";
					copper -= 100;
					Armor = CLOTH;
					cout << "you have" << copper << " copper";
				}
				else
				{
					nosale = true;
				}
				break;
			case 2:
				if (copper >= 200)
				{
					cout << "\n you buy leather armor for 200 copper \n you recieve." << PawnItem(Armor, 1) << " copper for selling your old armor";
					copper -= 200;
					Armor = LEATHER;
					cout << "you have" << copper << " copper";
				}
				else
				{
					nosale = true;
				}
				break;
			case 3:
				if (copper >= 400)
				{
					cout << "\n you buy Chainmail armor for 400 copper \n you recieve." << PawnItem(Armor, 1) << " copper for selling your old armor";
					copper -= 400;
					Armor = CHAIN;
					cout << "you have" << copper << " copper";
				}
				else
				{
					nosale = true;
				}
				break;
			case 4:
				if (copper >= 800)
				{
					cout << "\n you buy Platemail armor for 800 copper \n you recieve." << PawnItem(Armor, 1) << " copper for selling your old armor";
					copper -= 800;
					Armor = PLATE;
					cout << "you have" << copper << " copper";
				}
				else
				{
					nosale = true;
				}
				break;
			case 5:
				if (copper >= 1600)
				{
					cout << "\n you buy Ancient Platemail armor for 1600 copper \n you recieve." << PawnItem(Armor, 1) << " copper for selling your old armor";
					copper -= 1600;
					Armor = ANCIENTPLATE;
					cout << "you have" << copper << " copper";
				}
				else
				{
					nosale = true;
				}
				break;
			case 6:
				if (copper >= 3200)
				{
					cout << "\n you buy Magic Platemail armor for 3200 copper \n you recieve." << PawnItem(Armor, 1) << " copper for selling your old armor";
					copper -= 3200;
					Armor = MAGICPLATE;
					cout << "you have" << copper << " copper";
				}
				else
				{
					nosale = true;
				}
				break;
			case 7:
				if (copper >= 6400)
				{
					cout << "\n you buy Arcane Platemail armor for 6400 copper \n you recieve." << PawnItem(Armor, 1) << " copper for selling your old armor";
					copper -= 6400;
					Armor = ARCANEPLATE;
					cout << "you have" << copper << " copper";
				}
				else
				{
					nosale = true;
				}
				break;
			case 8:
				break;
			default:
				reroll = true;
				break;

			}
		}
		if (nosale)
		{
			cout << "You are too poor for that";
		}
		location = ARMORSMITH;
	}
	void LocSellArmor()
	{
		bool reroll = true;
		char menuitem;
		while (reroll)
		{
			reroll = false;
			cout << "\n the armor smith looks over your armor \" ill give ye " << PawnItem(Armor, 0) << "copper for it. Sound good to ye? [Y]es / [N]o";
			cin >> menuitem;
			switch (menuitem)
			{
			case 'y':
			case 'Y':
				cout << "\n you sell your armor for" << PawnItem(Armor, 1) << " copper.";
				Armor = LOINCLOTH;
				break;
			case 'n':
			case 'N':
				cout << "\n you take your armor back.";
				break;
			default:
				cout << "Invalid entry please try again!" << endl;
				reroll = true;
				break;
			}
		}
		location = ARMORSMITH;
	}
};
class Fighter : public Character
{
public:
	Fighter()
	{
		cout << "FIGHTER CREATED !!!" << endl;
		hp = DiceRoll(10, 6);
		hpmax = hp;
		mpmax = mp = 20;
		masteries = 1;
		Armor = LEATHER;
		Weapon = SWORD;
	}
	virtual void Attack(Monster* monster)
	{
		char inputs;
		bool reroll = true;
		int damage = 0;
		while (reroll)
		{
			reroll = false;
			cout << "\n[A]ttack";
			if (mp >= 1)
			{
				cout << "\t[F]renzy";
			}
			if (mp >= 5)
			{
				cout << "\t[D]eadly Strike \n";
			}
			cin >> inputs;
			int targetRoll = 10 + (atts.dexterity + atts.strength) - (monster->atts.dexterity + monster->atts.strength);
			if (targetRoll > 17)
			{
				targetRoll = 17;
			}
			if (targetRoll < 3)
			{
				targetRoll = 3;
			}
			bool hit = targetRoll >= DiceRoll(1, 20);

			if (!hit)
			{
				cout << "Miss!";
			}
			switch (inputs)
			{
			case 'a':
			case 'A':
				if (hit)
				{
					int dice = atts.strength + Weapon + masteries;
					damage = DiceRoll(dice, 3) - dice;
					cout << "Basic Attack (F): " << damage;
				}
				break;
			case 'f':
			case 'F':
				if (hit && mp >= 1)
				{
					int dice = 2 * (atts.strength + Weapon + masteries);
					damage = DiceRoll(dice, 3) - dice;
					cout << "Frenzy (F): " << damage;
					mp -= 1;
				}
				break;
			case 'd':
			case 'D':
				if (hit && mp >= 5)
				{
					int dice = 100 * (atts.strength + Weapon + masteries);
					damage = DiceRoll(dice, 6) - dice;
					cout << "Deadly Strike (F): " << damage;
					mp -= 5;
				}
				break;
			default:
				reroll = true;
				break;
			}
		}
		if (damage > 0)
		{
			damage = monster->Mitigate(damage);
		}
	}
};
class Cleric : public Character
{
public:
	Cleric()
	{
		cout << "CLERIC CREATED!!!" << endl;
		hp = DiceRoll(5, 6);
		hpmax = hp;
		mpmax = mp = 50;
		masteries = 1;
		Armor = CLOTH;
		Weapon = STAFF;
	}
	virtual void Attack(Monster* monster)
	{
		char inputs;
		bool reroll = true;
		int damage = 0;
		int heal = 0;
		while (reroll)
		{
			reroll = false;
			cout << "\n[A]ttack";
			if (mp >= 1)
			{
				cout << "\t[M]agic Missle";
			}
			if (mp >= 5)
			{
				cout << "\t[H]eal \n";
			}
			cin >> inputs;
			int targetRoll = 10 + (atts.focus) - (monster->atts.dexterity + monster->atts.faith);
			if (targetRoll > 17)
			{
				targetRoll = 17;
			}
			if (targetRoll < 3)
			{
				targetRoll = 3;
			}
			bool hit = targetRoll >= DiceRoll(1, 20);

			if (!hit)
			{
				cout << "Miss!";
			}
			switch (inputs)
			{
			case 'a':
			case 'A':
				if (hit)
				{
					int dice = atts.strength + Weapon + masteries;
					damage = DiceRoll(dice, 3) - dice;
					cout << "Basic Attack (C): " << damage;
				}
				break;
			case 'm':
			case 'M':
				if (hit && mp >= 1)
				{
					int dice = 2 * (atts.faith + Weapon + masteries);
					damage = DiceRoll(dice, 3) - dice;
					cout << "Magic Missile (C): " << damage;
					mp -= 1;
				}
				break;
			case 'h':
			case 'H':
				if (hit && mp >= 5)
				{
					int dice = (atts.inspiration + Weapon + masteries);
					heal = DiceRoll(dice, 1) - dice;
					cout << "Heal (C): " << heal;
					mp -= 5;
				}
				break;
			default:
				reroll = true;
				break;
			}
		}
		if (damage > 0)
		{
			damage = monster->Mitigate(damage);
		}
		if (heal > 0)
		{
			hp += heal;
			if (hp > hpmax)
				hp = hpmax;
		}
	}
};
class Rogue : public Character
{
public:
	Rogue()
	{
		cout << "ROGUE CREATED !!!" << endl;
		hp = DiceRoll(6, 6);
		hpmax = hp;
		mpmax = mp = 20;
		masteries = 1;
		Armor = LEATHER;
		Weapon = DAGGER;
	}
	virtual void Attack(Monster* monster)
	{
		char inputs;
		bool reroll = true;
		int damage = 0;
		while (reroll)
		{
			reroll = false;
			cout << "\n[A]ttack";
			if (mp >= 1)
			{
				cout << "\t[D]agger throw";
			}
			if (mp >= 5)
			{
				cout << "\t[B]ack Stab \n";
			}
			cin >> inputs;
			int targetRoll = 10 + (atts.dexterity) - (monster->atts.dexterity + monster->atts.strength);
			if (targetRoll > 17)
			{
				targetRoll = 17;
			}
			if (targetRoll < 3)
			{
				targetRoll = 3;
			}
			bool hit = targetRoll >= DiceRoll(1, 20);

			if (!hit)
			{
				cout << "Miss!";
			}
			switch (inputs)
			{
			case 'a':
			case 'A':
				if (hit)
				{
					int dice = atts.strength + Weapon + masteries;
					damage = DiceRoll(dice, 3) - dice;
					cout << "Basic Attack (R): " << damage;
				}
				break;
			case 'D':
			case 'd':
				if (hit && mp >= 1)
				{
					int dice = 1.5 * (atts.dexterity + Weapon + masteries);
					damage = DiceRoll(dice, 3) - dice;
					cout << "Dagger Throw (R): " << damage;
					mp -= 1;
				}
				break;
			case 'B':
			case 'b':
				if (hit && mp >= 5)
				{
					int dice = 25 * (atts.strength + Weapon + masteries);
					damage = DiceRoll(dice, 6) - dice;
					cout << "Backstab (R): " << damage;
					mp -= 5;
				}
				break;
			default:
				reroll = true;
				break;
			}
		}
		if (damage > 0)
		{
			damage = monster->Mitigate(damage);
		}
	}
};
class Bard : public Character
{
public:
	Bard()
	{
		cout << "BARD CREATED !!!" << endl;
		hp = DiceRoll(5, 6);
		hpmax = hp;
		mpmax = mp = 50;
		masteries = 1;
		Armor = CLOTH;
		Weapon = STAFF;
	}
	virtual void Attack(Monster* monster)
	{
		char inputs;
		bool reroll = true;
		int damage = 0;
		while (reroll)
		{
			reroll = false;
			cout << "\n[A]ttack";
			if (mp >= 1)
			{
				cout << "\t[D]ancing light";
			}
			if (mp >= 5)
			{
				cout << "\t[S]ong of flames \n";
			}
			cin >> inputs;
			int targetRoll = 10 + (atts.focus) - (monster->atts.dexterity + monster->atts.strength);
			if (targetRoll > 17)
			{
				targetRoll = 17;
			}
			if (targetRoll < 3)
			{
				targetRoll = 3;
			}
			bool hit = targetRoll >= DiceRoll(1, 20);

			if (!hit)
			{
				cout << "Miss!";
			}
			switch (inputs)
			{
			case 'a':
			case 'A':
				if (hit)
				{
					int dice = atts.strength + Weapon + masteries;
					damage = DiceRoll(dice, 3) - dice;
					cout << "Basic Attack (B):  " << damage;
				}
				break;
			case 'd':
			case 'D':
				if (hit && mp >= 1)
				{
					int dice = 2 * (atts.faith + Weapon + masteries);
					damage = DiceRoll(dice, 3) - dice;
					cout << "Dancing Light (B):  " << damage;
					mp -= 1;
					reroll = true;
				}
				break;
			case 's':
			case 'S':
				if (hit && mp >= 5)
				{
					int dice = 3 * (atts.inspiration + Weapon + masteries);
					damage = DiceRoll(dice, 6) - dice;
					cout << "Song of Flame (B): " << damage;
					mp -= 5;
				}
				break;
			default:
				reroll = true;
				break;
			}
		}
		if (damage > 0)
		{
			damage = monster->Mitigate(damage);
		}
	}
};
class Tinker : public Character
{
public:
	Tinker()
	{
		cout << "TINKER CREATED !!!" << endl;
		hp = DiceRoll(5, 6);
		hpmax = hp;
		mpmax = mp = 20;
		masteries = 1;
		Armor = CLOTH;
		Weapon = DAGGER;
	}
	virtual void Attack(Monster* monster)
	{
		char inputs;
		bool reroll = true;
		int damage = 0;
		while (reroll)
		{
			reroll = false;
			cout << "\n[A]ttack";
			if (mp >= 1)
			{
				cout << "\t[C]ogs";
			}
			if (mp >= 5)
			{
				cout << "\t[T]Raps \n";
			}
			cin >> inputs;
			int targetRoll = 10 + (atts.focus) - (monster->atts.dexterity + monster->atts.strength);
			if (targetRoll > 17)
			{
				targetRoll = 17;
			}
			if (targetRoll < 3)
			{
				targetRoll = 3;
			}
			bool hit = targetRoll >= DiceRoll(1, 20);

			if (!hit)
			{
				cout << "Miss!";
			}
			switch (inputs)
			{
			case 'a':
			case 'A':
				if (hit)
				{
					int dice = atts.strength + Weapon + masteries;
					damage = DiceRoll(dice, 3) - dice;
					cout << "Basic Attack (T):  " << damage;
				}
				break;
			case 'c':
			case 'C':
				if (hit && mp >= 1)
				{
					int dice = 3 * (atts.dexterity + Weapon + masteries);
					damage = DiceRoll(dice, 3) - dice;
					cout << "You throw your cogs (T):  " << damage;
					mp -= 1;
				}
				break;
			case 'd':
			case 'D':
				if (hit && mp >= 5)
				{
					int dice = 5 * (atts.cleverness + Weapon + masteries);
					damage = DiceRoll(dice, 6) - dice;
					cout << " Deploying trap (T): " << damage;
					mp -= 5;
				}
				break;
			default:
				reroll = true;
				break;
			}
		}
		if (damage > 0)
		{
			damage = monster->Mitigate(damage);
		}
	}
};
class Mage : public Character
{
public:
	Mage()
	{
		cout << "MAGE CREATED !!!" << endl;
		hp = DiceRoll(3, 6);
		hpmax = hp;
		mpmax = mp = 50;
		masteries = 1;
		Armor = CLOTH;
		Weapon = STAFF;
	}
	virtual void Attack(Monster* monster)
	{
		char inputs;
		bool reroll = true;
		int damage = 0;
		while (reroll)
		{
			reroll = false;
			cout << "\n[A]ttack";
			if (mp >= 1)
			{
				cout << "\t[F]ireball";
			}
			if (mp >= 5)
			{
				cout << "\t[H]oly Smite \n";
			}
			cin >> inputs;
			int targetRoll = 10 + (atts.focus) - (monster->atts.dexterity + monster->atts.faith);
			if (targetRoll > 17)
			{
				targetRoll = 17;
			}
			if (targetRoll < 3)
			{
				targetRoll = 3;
			}
			bool hit = targetRoll >= DiceRoll(1, 20);

			if (!hit)
			{
				cout << "Miss!";
			}
			switch (inputs)
			{
			case 'a':
			case 'A':
				if (hit)
				{
					int dice = atts.strength + Weapon + masteries;
					damage = DiceRoll(dice, 3) - dice;
					cout << "Basic Attack (M):  " << damage;
				}
				break;
			case 'f':
			case 'F':
				if (hit && mp >= 1)
				{
					int dice = 2 * (atts.inspiration + Weapon + masteries);
					damage = DiceRoll(dice, 4) - dice;
					cout << "Fireball (M):  " << damage;
					mp -= 1;
				}
				break;
			case 'h':
			case 'H':
				if (hit && mp >= 5)
				{
					int dice = atts.faith + Weapon + masteries;
					damage = DiceRoll(dice, 8) - dice;
					cout << "Holy Smite (M): " << damage;
					mp -= 5;
				}
				break;
			default:
				reroll = true;
				break;
			}
		}
		if (damage > 0)
		{
			damage = monster->Mitigate(damage);
		}
	}
};
class Vampire : public Character
{
public:
	Vampire()
	{
		cout << "VAMPIRE CREATED !!!" << endl;
		hp = DiceRoll(10, 5);
		hpmax = hp;
		mpmax = mp = 35;
		masteries = 1;
		Armor = PLATE;
		Weapon = SWORD;
	}
	virtual void Attack(Monster* monster)
	{
		char inputs;
		bool reroll = true;
		int damage = 0;
		int heal = 0;
		while (reroll)
		{
			reroll = false;
			cout << "\n[A]ttack";
			if (mp >= 1)
			{
				cout << "\t[B]ite";
			}
			if (mp >= 5)
			{
				cout << "\t[V]ampiric Strike \n";
			}
			cin >> inputs;
			int targetRoll = 10 + (atts.dexterity) - (monster->atts.dexterity + monster->atts.strength);
			if (targetRoll > 17)
			{
				targetRoll = 17;
			}
			if (targetRoll < 3)
			{
				targetRoll = 3;
			}
			bool hit = targetRoll >= DiceRoll(1, 20);

			if (!hit)
			{
				cout << "Miss!";
			}
			switch (inputs)
			{
			case 'a':
			case 'A':
				if (hit)
				{
					int dice = atts.strength + Weapon + masteries;
					damage = DiceRoll(dice, 3) - dice;
					cout << "Basic Attack (F): " << damage;
				}
				break;
			case 'b':
			case 'B':
				if (hit && mp >= 1)
				{
					int dice = 2 * (atts.strength + Weapon + masteries);
					damage = DiceRoll(dice, 3) - dice;
					heal = .5 * damage;
					cout << "Bite (V): " << damage;
					mp -= 1;
				}
				break;
			case 'v':
			case 'V':
				if (hit && mp >= 5)
				{
					int dice = 2 * (atts.faith + Weapon + masteries);
					damage = DiceRoll(dice, 6) - dice;
					heal = damage;
					cout << "Vampiric strike (V): " << damage;
					mp -= 5;
				}
				break;
			default:
				reroll = true;
				break;
			}
		}
		if (damage > 0)
		{
			damage = monster->Mitigate(damage);
		}
		if (heal > 0)
		{
			hp += heal;
			if (hp > hpmax)
				hp = hpmax;
		}
	}
};

void makeCharacter(Character *& player);