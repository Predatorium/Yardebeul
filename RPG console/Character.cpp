#include "Character.h"

Character::Character()
{
	Name = "0";
	Niveau = 0;
	Vitesse = 0;
	Point_de_vie = 0;
	Mana = 0;
	Endurance = 0;
	Santé_mentale = 0;
}

Character::Character(string _name)
{
	Name = _name;
	Niveau = 1;
	Vitesse = 1;
	Point_de_vie = 20;
	Mana = 50;
	Endurance = 50;
	Santé_mentale = 100;
}

void Affichage_TypePerso(Character& p)
{
	p.Affichage_Type();
}

void Affichage_TypeStat(Character& p)
{
	p.Affichage_Stat();
}