#include "Character.h"

#include <iostream>

using namespace std;


void makeCharacter(Character *& player)
{
	bool reroll = true;
	char inputs;
	RACE inputRace;
	OCC inputClass;
	attributes tmpStats;

	while (reroll == true)
	{
		cout << "Please select a race";
		cout << "[H]uman [E]lf [D]ark Elf [A]ngel/Demon\n[M]ongrel [S]hamani [N]ibelung [U]ndead\n";
		cin >> inputs;
		switch (inputs)
		{
		case 'h':
		case 'H':
			cout << "You have chosen the human class";
			inputRace = HUMAN;
			tmpStats.strength = DiceRoll(3, 6);
			tmpStats.faith = DiceRoll(3, 6);
			tmpStats.dexterity = DiceRoll(3, 6);
			tmpStats.inspiration = DiceRoll(3, 6);
			tmpStats.cleverness = DiceRoll(3, 6);
			tmpStats.focus = DiceRoll(3, 6);
			break;
		case 'e':
		case 'E':
			cout << "You have chosen the elf class";
			inputRace = ELF;
			tmpStats.strength = DiceRoll(3, 6);
			tmpStats.faith = DiceRoll(3, 6);
			tmpStats.dexterity = DiceRoll(3, 6);
			tmpStats.inspiration = DiceRoll(3, 6);
			tmpStats.cleverness = DiceRoll(2, 6);
			tmpStats.focus = DiceRoll(4, 6);
			break;
		case 'd':
		case 'D':
			cout << "You have chosen the dark elf class";
			inputRace = DARKELF;
			tmpStats.strength = DiceRoll(3, 6);
			tmpStats.faith = DiceRoll(3, 6);
			tmpStats.dexterity = DiceRoll(4, 6);
			tmpStats.inspiration = DiceRoll(2, 6);
			tmpStats.cleverness = DiceRoll(3, 6);
			tmpStats.focus = DiceRoll(3, 6);
			break;
		case 'a':
		case 'A':
			cout << "You have chosen the angel/demon class";
			inputRace = ANGEL;
			tmpStats.strength = DiceRoll(3, 6);
			tmpStats.faith = DiceRoll(4, 6);
			tmpStats.dexterity = DiceRoll(3, 6);
			tmpStats.inspiration = DiceRoll(3, 6);
			tmpStats.cleverness = DiceRoll(3, 6);
			tmpStats.focus = DiceRoll(3, 6);
			break;
		case 'm':
		case 'M':
			cout << "You have chosen the mongrel class";
			inputRace = MONGREL;
			tmpStats.strength = DiceRoll(4, 6);
			tmpStats.faith = DiceRoll(3, 6);
			tmpStats.dexterity = DiceRoll(3, 6);
			tmpStats.inspiration = DiceRoll(3, 6);
			tmpStats.cleverness = DiceRoll(3, 6);
			tmpStats.focus = DiceRoll(2, 6);
			break;
		case 's':
		case 'S':
			cout << "You have chosen the shamani class";
			inputRace = SHAMANI;
			tmpStats.strength = DiceRoll(2, 6);
			tmpStats.faith = DiceRoll(4, 6);
			tmpStats.dexterity = DiceRoll(3, 6);
			tmpStats.inspiration = DiceRoll(3, 6);
			tmpStats.cleverness = DiceRoll(3, 6);
			tmpStats.focus = DiceRoll(3, 6);
			break;
		case 'n':
		case 'N':
			cout << "You have chosen the nibelung class";
			inputRace = NIBELUNG;
			tmpStats.strength = DiceRoll(3, 6);
			tmpStats.faith = DiceRoll(3, 6);
			tmpStats.dexterity = DiceRoll(2, 6);
			tmpStats.inspiration = DiceRoll(3, 6);
			tmpStats.cleverness = DiceRoll(4, 6);
			tmpStats.focus = DiceRoll(3, 6);
			break;
		case 'u':
		case 'U':
			cout << "You have chosen the undead class";
			inputRace = UNDEAD;
			tmpStats.strength = DiceRoll(3, 6);
			tmpStats.faith = DiceRoll(3, 6);
			tmpStats.dexterity = DiceRoll(3, 6);
			tmpStats.inspiration = DiceRoll(3, 6);
			tmpStats.cleverness = DiceRoll(2, 6);
			tmpStats.focus = DiceRoll(3, 6);
			break;
		default:
			cout << "Please enter a correct value";
			break;
		}
		DisplayStats(tmpStats);
		bool validEntry = false;
		while (!validEntry)
		{
			cout << "Reroll? [Y]es [N]o" << endl;
			cin >> inputs;

			if (inputs == 'y' || inputs == 'Y')
			{
				reroll = true;
				validEntry = true;
			}
			else if (inputs == 'n' || inputs == 'N')
			{
				reroll = false;
				validEntry = true;
			}
		}
	}
	reroll = true;
	while (reroll)
	{
		reroll = false;
		cout << "Please select a Class" << endl;
		cout << "[F]ighter [C]leric [R]ogue [B]ard [T]inker [M]age [V]ampire" << endl;
		cin >> inputs;
		switch (inputs)
		{
		case 'F':
		case 'f':
			inputClass = FIGHTER;
			player = new Fighter;
			cout << "\n FIGHTER!" << endl;
			break;
		case 'C':
		case 'c':
			inputClass = CLERIC;
			player = new Cleric;
			cout << "\n CLERIC!" << endl;
			break;
		case 'R':
		case 'r':
			inputClass = ROGUE;
			player = new Rogue;
			cout << "\n ROGUE!" << endl;
			break;
		case 'B':
		case 'b':
			inputClass = BARD;
			player = new Bard;
			cout << "\n BARD!" << endl;
			break;
		case 'T':
		case 't':
			inputClass = TINKER;
			player = new Tinker;
			cout << "\n TINKER!" << endl;
			break;
		case 'M':
		case 'm':
			inputClass = MAGE;
			player = new Mage;
			cout << "\n MAGE!" << endl;
			break;
		case 'v':
		case 'V':
			inputClass = VAMPIRE;
			player = new Vampire;
			cout << "\n VAMPIRE!" << endl;
			break;
		default:
			cout << "Please input a valid Class." << endl;
			reroll = true;
			break;
		}
	}
	player->SetAtts(tmpStats);
}