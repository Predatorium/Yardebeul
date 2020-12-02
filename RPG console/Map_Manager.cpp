#include "Map_Manager.h"

list<Map_Manager*> Map_List;

Map_Manager::Map_Manager(string _name, string _path)
{
	Name = _name;
	Path = _path;
}

void LoadMap()
{
	for (RessourcesManager& ActualRessource : RessourcesList)
		if (ActualRessource.Get_Type() == RessourceType::MAP)
			Map_List.push_back(new Map_Manager(ActualRessource.Get_Name(), ActualRessource.Get_Path()));
}

void SaveMap(Map_Manager* _map)
{
	ofstream save("../Ressources/Infos/Ressources.load", ios::app);
	if (save.is_open())
	{
		save.seekp(0 ,ios::end);
		save << endl;
		save << "Map ";

		save << _map->Get_Name() << " ";
		save << _map->Get_Path();
	}
}

Map_Manager* Get_Map(string _name)
{
	for (Map_Manager* Current_Map : Map_List)
		if (Current_Map->Get_Name() == _name)
			return Current_Map;
}

string Get_PathMap(string _name)
{
	for (Map_Manager* Current_Path : Map_List)
		if (Current_Path->Get_Name() == _name)
			return Current_Path->Get_Path();
}