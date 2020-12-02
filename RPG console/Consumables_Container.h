#pragma once
#include "Consumable.h"

class Consumables_Container
{
private :
	list <Consumable> Container;

public :
	Consumables_Container();
	~Consumables_Container() = default;

	Consumable Get_Consumable(string _name);
	
	void Save();
	void Load();
};

extern Consumables_Container Consumables;