#include "Dungeon_Container.h"

Dungeon_Container::Dungeon_Container()
{
	list<Room> rooms;
	Container.push_back(Dungeon(State_Event::Rien, "Tellurique", 2, rooms));
}

Dungeon Dungeon_Container::Get_Dungeon(string _name)
{
    for (Dungeon& Actual_Dugeon : Container)
        if (Actual_Dugeon.Get_Name() == _name)
            return Actual_Dugeon;
}

//void Dungeon_Container::Save()
//{
//	ofstream Save_Weapon("../Ressources/Containers/Dungeon.txt");
//	if (Save_Weapon.is_open())
//	{
//		for (list<Dungeon>::iterator Current_Container = Container.begin(); Current_Container != Container.end(); Current_Container++)
//		{
//			Save_Weapon << Current_Container->Get_Name() << " ";
//			Save_Weapon << static_cast<int>(Current_Container->Get_Statut()) << " ";
//			
//			for (list<Room>::iterator Current_Room = Current_Container->Get_Rooms().begin(); Current_Room != Current_Container->Get_Rooms().end(); Current_Room++)
//			{
//				Save_Weapon << static_cast<int>(Current_Room->Get_biome()) << " ";
//				Save_Weapon << Current_Room->Get_Description() << " ";
//				Save_Weapon << Current_Room->Get_Difficulte() << " ";
//				Save_Weapon << Current_Room->Get_Boss() << " ";
//				Save_Weapon << Current_Room->Get_Name() << "|";
//			}
//
//			Save_Weapon << Current_Container->Get_Difficulte();
//
//			if (Current_Container != Container.end())
//				Save_Weapon << endl;
//		}
//		Save_Weapon.close();
//	}
//
//}

//void Weapons_Container::Load()
//{
//	ifstream Load_Weapon("../Ressources/Containers/Weapon.txt");
//	if (Load_Weapon.is_open())
//	{
//		string line = "0";
//		while (getline(Load_Weapon, line))
//		{
//			list<Room> tmprooms;
//			Biomes tmpBiome;
//			string tmpdescript;
//			int tmpdif_room;
//			bool tmpboss;
//			string tmpname_room;
//
//			string tmpname;
//			State_Event tmpstate;
//			int tmpdif;
//
//			tmpname = line.substr(0, line.find(" "));
//			line.erase(0, line.find(" ") + 1);
//
//			tmpstate = static_cast<State_Event>(stoi(line.substr(0, line.find(" "))));
//			line.erase(0, line.find(" ") + 1);
//
//			while (line.find("|"))
//			{
//				tmpBiome = static_cast<Biomes>(stoi(line.substr(0, line.find(" "))));
//				tmpdescript = line.substr(0, line.find(" "));
//				tmpdif_room = stoi(line.substr(0, line.find(" ")));
//				tmpboss = stoi(line.substr(0, line.find(" ")));
//				tmpname_room = line.substr(0, line.find(" "));
//
//				tmprooms.push_back(Room(tmpname_room,tmpdescript,tmpBiome,tmpdif_room,tmpboss,))
//			}
//
//			Container.push_back(Weapon(tmpdegat, tmpdurabilite, tmpname, tmpprix, Effects.Get_Effet(tmpname_effect)));
//		}
//
//		Load_Weapon.close();
//	}
//}