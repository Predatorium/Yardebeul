#include "Dungeon.h"

Dungeon::Dungeon()
{
	Statut_Event = State_Event::Rien;
	Name = '0';
	Difficulté = 0;
	Rooms.push_back(Room());
}

Dungeon::Dungeon(State_Event _event, string _name, int _difficulte, list<Room> _room)
{
	Statut_Event = _event;
	Name = _name;
	Difficulté = _difficulte;
}