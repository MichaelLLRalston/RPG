#include "RPG.h"

#include "stdafx.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Text.h"
#include "Monster.h"
using namespace std;


int DiceRoll(int qty, int sides)
{
	int roll = 0;
	for(int i = 0; i < qty; i++)
	{
		roll += rand() % sides + 1;
	}
	return roll;
}
void DisplayStats(attributes atts)
{
	cout << "" << endl;
	cout << "+--------------------------+\n";
	cout << "|      	Attributes         |\n";
	cout << "+--------------------------+\n";
	cout << "" << endl;
	cout << "Strength:           " << atts.strength; 
	cout << "\n Faith:             " << atts.faith;
	cout << "\n Dexterity:         " << atts.dexterity; 
	cout << "\n Insperation:       " << atts.inspiration;
	cout << "\n cleverness:        " << atts.cleverness;
	cout << "\n Focus:             " << atts.focus << endl;
}
