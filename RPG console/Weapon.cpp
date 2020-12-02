#include "Weapon.h"

Weapon::Weapon()
{
	Dégats = 0;
	Durabilités = 0;
}

Weapon::Weapon(int _dégat, int _durabilité, string _name, int _prix, Effect _effet)
{
	Dégats = _dégat;
	Durabilités = _durabilité;
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
	cout << "Les degats de mon epee sont de " << Dégats << endl;
	cout << "La durabilite de mon epee est de " << Durabilités << endl;
	cout << endl;

	effet.Display_Stat();
}