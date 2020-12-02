#include "Armor.h"

Armor::Armor()
{
	Defenses = 0;
	DurabilitÚs = 0;
}

Armor::Armor(int _defense, int _durabilitÚ, string _name, int _prix, Effect _effet)
{
	Name = _name;
	Prix = _prix;
	effet = _effet;
	Defenses = _defense;
	DurabilitÚs = _durabilitÚ;
}

Armor::~Armor()
{
}

void Armor::Display_Stat()
{
	cout << Name << endl;
	cout << Prix << endl;

	cout << Defenses << endl;
	cout << DurabilitÚs << endl;

	effet.Display_Stat();
}
