#pragma once
#include "Npc.h"
#include "Weapons_Container.h"
#include "Armors_Container.h"

class Dialogue_Container;

class Npc_Containers
{
private:
	list<Npc> Container;
	Armors_Container Armors;
	Weapons_Container Weapons;
	Dialogue_Container Dialogues;

public :
	Npc_Containers();
	~Npc_Containers() = default;
	Npc Get_Npc(string _name);
	inline list<Npc> Get_List() { return Container; };
};