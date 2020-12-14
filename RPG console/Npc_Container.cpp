#include "Npc_Container.h"
#include "Dialogue_Container.h"
#include "Weapons_Container.h"
#include "Armors_Container.h"

Npc_Containers Npcs;

Npc_Containers::Npc_Containers()
{

}

void Npc_Containers::init()
{
	Container.push_back(Npc("Knucles", Armor(), Weapons.Get_Weapon("Epee de feu"), 1, 20, 25));
	Container.push_back(Npc("Fairy", 1, 20, 25, Dialogues.Get_Dialogue("1_1")));
}

Npc Npc_Containers::Get_Npc(string _name)
{
	for (Npc& Current : Container)
		if (Current.Get_Name() == _name)
			return Current;
}