#include "Npcs_Container.h"

Npcs_Container::Npcs_Container()
{
	Container.push_back(Npc());
}

Npc Npcs_Container::Get_Npc(string _name)
{
	for (Npc Actual_Npc : Container)
		if (Actual_Npc.Get_Name() == _name)
			return Actual_Npc;
}