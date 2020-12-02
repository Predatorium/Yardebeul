#include "Armor.h"

Armor::Armor()
{
	Defenses = 0;
	Durabilités = 0;
}

Armor::Armor(int _defense, int _durabilité, string _name, int _prix, Effect _effet)
{
	Name = _name;
	Prix = _prix;
	effet = _effet;
	Defenses = _defense;
	Durabilités = _durabilité;
}

Armor::~Armor()
{
}

void Armor::Display_Stat()
{
	cout << Name << endl;
	cout << Prix << endl;

	cout << Defenses << endl;
	cout << Durabilités << endl;

	effet.Display_Stat();
}
