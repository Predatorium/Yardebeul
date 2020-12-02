#pragma once
#include "Npc.h"

class Npcs_Container
{
private :
	list <Npc> Container;

public :
	Npcs_Container();
	~Npcs_Container() = default;

	Npc Get_Npc(string _name);
};

extern Npcs_Container Npcs;