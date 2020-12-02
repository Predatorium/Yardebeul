#pragma once
#include "Tools.h"
#include "StateManager.h"
#include "RessourcesManager.h"

class Map_Manager
{
private :
	string Name;
	State state;
	string Path;

public :
	Map_Manager() = default;
	Map_Manager(string _name, State _state, string _path);
	~Map_Manager() = default;

	inline string Get_Name() { return Name; };
	inline string Get_Path() { return Path; };
	inline State Get_State() { return state; };
};
extern list<Map_Manager*> Map_List;

void LoadMap(State _state);
void SaveMap(Map_Manager* _map);
Map_Manager* Get_Map(string _name);
string Get_PathMap(string _name);
void RemoveAllMap();
void RemoveStateMap(State _state);