#include "Event.h"
#include "Room.h"

Room::Room()
{
	Name = '0';
	Description = '0';
	State_Machine = 0;
	Biome = Biomes::Prairie;
	Difficulte = 0;
	isBoss = false;
}

Room::Room(string _name, string _description, Biomes _biome, int _difficulte, bool _isBoss, list<Event> _event)
{
	Name = _name;
	Description = _description;
	State_Machine = 0;
	Biome = _biome;
	Difficulte = _difficulte;
	isBoss = _isBoss;
	Evenement = _event;
}

Room::~Room()
{
}