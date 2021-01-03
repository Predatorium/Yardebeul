#pragma once
#include "Npc.h"

class Npc_Containers
{
private:
	list<Npc> Container;

public :
	Npc_Containers();
	~Npc_Containers() = default;

	void init();

	Npc Get_Npc(string _name);
	Npc Random_Npc(Comportement _attitude);
	Npc Random_Boss();

	inline list<Npc> Get_List() { return Container; };
};
extern Npc_Containers Npcs;