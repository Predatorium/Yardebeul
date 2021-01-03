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
	Container.push_back(Npc("Knucles", Armor(), Weapons.Get_Weapon("Epee"), 1, 25, 20, 0));
	Container.push_back(Npc("Knucles", Armor(), Weapons.Get_Weapon("Epee"), 1, 25, 20, 1));
	Container.push_back(Npc("Knucles", Armor(), Weapons.Get_Weapon("Epee"), 1, 25, 20, 2));

	Container.push_back(Npc("Yves", Armors.Get_Armor("Armor"), Weapons.Get_Weapon("Epee"), 2, 20, 25, 0));
	Container.push_back(Npc("Yves", Armors.Get_Armor("Armor"), Weapons.Get_Weapon("Epee"), 2, 20, 25, 1));

	Container.push_back(Npc("Boss", Armors.Get_Armor("Armor"), Weapons.Get_Weapon("Epee de feu"), 3, 20, 30, 0));
	Container.push_back(Npc("Boss", Armors.Get_Armor("Armor"), Weapons.Get_Weapon("Epee d eau"), 3, 20, 30, 1));
	Container.push_back(Npc("Boss", Armors.Get_Armor("Armor"), Weapons.Get_Weapon("Epee d air"), 3, 20, 30, 2));

	Container.push_back(Npc("Fairy", 1, 20, 25, 0));
	Container.push_back(Npc("Fairy", 1, 20, 25, 1));
	Container.push_back(Npc("Fairy", 1, 20, 25, 2));
}

Npc Npc_Containers::Get_Npc(string _name)
{
	for (Npc& Current : Container)
		if (Current.Get_Name() == _name)
			return Current;
}

Npc Npc_Containers::Random_Npc(Comportement _attitude)
{
	int number = 0;
	for (auto Current = Container.begin(); Current != Container.end(); Current++)
		if (Current->Get_Attitude() == _attitude && Current->Get_Name().substr(0, 4) != "Boss")
			number++;

	int random = irandom(1, number);

	int i = 0;
	for (auto Current : Container)
		if (Current.Get_Attitude() == _attitude && Current.Get_Name().substr(0, 4) != "Boss")
		{
			i++;
			if (i == random)
				return Current;
		}
}

Npc Npc_Containers::Random_Boss()
{
	int number = 0;
	for (auto Current = Container.begin(); Current != Container.end(); Current++)
		if (Current->Get_Name().substr(0, 4) == "Boss")
			number++;

	int random = irandom(1, number);

	int i = 0;
	for (auto Current : Container)
		if (Current.Get_Name().substr(0, 4) == "Boss")
		{
			i++;
			if (i == random)
				return Current;
		}
}
