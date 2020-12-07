#include "Character.h"

Character::Character(string _name)
{
	Name = _name;
	Level = 1;
	Speed = 1;
	Life_Point = 20;
	Mana = 50;
	Endurance = 50;
	Mental_Health = 100;
}

void Character::Add_Life(int _life)
{
	Life_Point = _life;
	if (Life_Point > Life_Max)
		Life_Point = Life_Max;
}