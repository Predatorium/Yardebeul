#pragma once
#include "Tools.h"
#include "Room.h"

class Dungeon
{
private :
	State_Event Statut_Event;
	string Name;
	int Difficulté;
	bool DugeonIsFinished;

	list<Room> Rooms;

public :
	Dungeon();
	Dungeon(State_Event _event, string _name, int _difficulte, list<Room> _room);
	~Dungeon() = default;

	inline State_Event Get_Statut() { return Statut_Event; };
	inline string Get_Name() { return Name; };
	inline int Get_Difficulte() { return Difficulté; };
	inline list<Room> Get_Rooms() { return Rooms; };
	inline bool Get_Finished() { return DugeonIsFinished; };
};