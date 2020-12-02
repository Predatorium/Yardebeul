#pragma once
#include "Dungeon.h"

class Dungeon_Container
{
private :
	list <Dungeon> Container;

public :
	Dungeon_Container();
	~Dungeon_Container() = default;

	Dungeon Get_Dungeon(string _name);

	//void Save();
	//void Load();
};