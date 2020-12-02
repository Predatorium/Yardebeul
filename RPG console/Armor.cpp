#include "Armor.h"

Armor::Armor()
{
	Defenses = 0;
	Durabilit�s = 0;
}

Armor::Armor(int _defense, int _durabilit�, string _name, int _prix, Effect _effet)
{
	Name = _name;
	Prix = _prix;
	effet = _effet;
	Defenses = _defense;
	Durabilit�s = _durabilit�;
}

Armor::~Armor()
{
}

void Armor::Display_Stat()
{
	cout << Name << endl;
	cout << Prix << endl;

	cout << Defenses << endl;
	cout << Durabilit�s << endl;

	effet.Display_Stat();
}
