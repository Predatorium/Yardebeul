#include "Character.h"

Character::Character(string _name, Armor _armor, Weapon _weapon)
	: Entity(_name)
{
	Name = _name;
	Level = 1;
	Speed = 1;
	Life_Point = 20;
	Mana = 50;
	Endurance = 50;
	Mental_Health = 100;
	armor = new Armor(_armor);
	weapon = new Weapon(_weapon);
}

void Character::Add_Life(int _life)
{
	Life_Point += _life;
	if (Life_Point > Life_Max)
		Life_Point = Life_Max;
}

void Character::Set_Life(int _life)
{
	Life_Point = _life;
	Life_Max = _life;
}