#include "Weapon.h"

Weapon::Weapon()
{
	D�gats = 0;
	Durabilit�s = 0;
}

Weapon::Weapon(int _d�gat, int _durabilit�, string _name, int _prix, Effect _effet)
{
	D�gats = _d�gat;
	Durabilit�s = _durabilit�;
	Name = _name;
	Prix = _prix;
	effet = _effet;
}

Weapon::~Weapon()
{

}

void Weapon::Display_Stat()
{
	cout << "Le nom de mon epee est " << Name << endl;
	cout << "Le prix de mon epee est " << Prix << endl;
	cout << "Les degats de mon epee sont de " << D�gats << endl;
	cout << "La durabilite de mon epee est de " << Durabilit�s << endl;
	cout << endl;

	effet.Display_Stat();
}