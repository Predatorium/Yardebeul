#pragma once
#include "Weapon.h"

class Weapons_Container
{
private :
	list <Weapon> Container;

public :
	Weapons_Container();
	~Weapons_Container() = default;

	Weapon Get_Weapon(string _name);

	void Save();
	void Load();
};

extern Weapons_Container Weapons;