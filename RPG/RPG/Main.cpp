#include "Text.h"
#include "State.h"
#include "RPG.h"
#include "Character.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

int main()
{
	srand(time(NULL));
	char inputs;
	RACE inputRace;
	OCC inputClass;
	attributes tmpStats;
	bool reroll = true;
	bool iQuit = false;
	Character *Player1 = nullptr;
	system("CLS");
	cout << "The lost lands of yarnik call out\nfor a hero to help stop the wrath\nof the ancient dragon Sonad\n\n";
	
	makeCharacter(Player1);

	while (!iQuit)
	{
		switch (Player1->GetLocation())
		{
		case QUIT:
			iQuit = true;
			break;
		case VIEWSTATS:
			Player1->LocStats();
			break;
		default:
		case TOWN:
			Player1->LocTown();
			break;
		case FOREST:
			Player1->LocForest();
			break;
		case MONSTER:
			Player1->LocMonster();
			break;
		case ARMORSMITH:
			Player1->LocArmorsmith();
			break;
		case BUYARMOR:
			Player1->LocBuyArmor();
			break;
		case SELLARMOR:
			Player1->LocSellArmor();
			break;
		case WEAPONSMITH:
			Player1->LocWeaponSmith();
			break;
		case BUYWEAPON:
			Player1->LocBuyWeapon();
			break;
		case SELLWEAPON:
			Player1->LocSellWeapon();
			break;
		case ALCHEMIST:
			Player1->LocAlchemist();
			break;
		case BUYPOTION:
			Player1->LocBuyPotion();
			break;
		case SELLPOTION:
			Player1->LocSellPotion();
			break;
		}
	}
	return 0;
}