#include "Npc.h"

Npc::Npc()
{
	Name = "Thierry";
	Niveau = 7;
	Point_de_vie = 15;
	Mana = 40;
	Endurance = 25;
	Santé_mentale = 100;
	Vitesse = 15;
	Attitude = Comportement::Amical;
}

Npc::Npc(string _name, int _niveau, int _pv, int vitesse, Comportement _attitude)
{
	Name = _name;
	Niveau = _niveau;
	Point_de_vie = _pv;
	Mana = 50;
	Endurance = 25;
	Santé_mentale = 100;
	Vitesse = vitesse;
	Attitude = _attitude;
}

Npc::~Npc()
{

}

void Npc::Affichage_Type()
{
	cout << "Je suis un Pnj." << endl;
}

void Npc::Affichage_Stat()
{
	cout << "Mon nom est : " << Name << endl;
	cout << "Mon niveau est : " << Niveau << endl;
	cout << "Mes pv sont a : " << Point_de_vie << endl;
	cout << "Mon mana est a : " << Mana << endl;
	cout << "Mon endurance est a : " << Endurance << endl;
	cout << "Ma sante mental est  a : " << Santé_mentale << endl;
	cout << "Ma vitesse est  de : " << Vitesse << endl << endl;
}