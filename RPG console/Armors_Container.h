#pragma once
#include "Armor.h"

class Armors_Container
{
private :
	list <Armor> Container;

public :
	Armors_Container();
	~Armors_Container() = default;

	void init();

	Armor Get_Armor(string _name);
	
	void Save();
	void Load();
};

extern Armors_Container Armors;