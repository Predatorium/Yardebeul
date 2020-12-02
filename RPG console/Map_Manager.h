#pragma once
#include "Tools.h"
#include "RessourcesManager.h"

class Map_Manager
{
private :
	string Name;
	string Path;

public :
	Map_Manager() = default;
	Map_Manager(string _name, string _path);
	~Map_Manager() = default;

	inline string Get_Name() { return Name; };
	inline string Get_Path() { return Path; };
};
extern list<Map_Manager*> Map_List;

void LoadMap();
void SaveMap(Map_Manager* _map);
Map_Manager* Get_Map(string _name);
string Get_PathMap(string _name);