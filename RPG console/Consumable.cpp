#include "Consumable.h"

Consumable::Consumable()
{

}

Consumable::Consumable(string _name, int _prix, Effect _effet)
{
	Name = _name;
	Prix = _prix;
	effet = _effet;
}

Consumable::~Consumable()
{

}

void Consumable::Display_Stat()
{
	cout << Name << endl;
	cout << Prix << endl;

	effet.Display_Stat();
}