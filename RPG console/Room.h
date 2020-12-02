#pragma once
#include "Tools.h"
#include "Event.h"

class Room
{
private :
	int State_Machine;
	string Name;
	string Description;
	Biomes Biome;
	int Difficulte;
	bool isBoss;

	list <Event> Evenement;

public :
	Room();
	Room(string _name, string _description, Biomes _biome, int _difficulte, bool _isBoss, list<Event> _event);
	~Room();

	inline string Get_Name() { return Name; };
	inline string Get_Description() { return Description; };
	inline Biomes Get_biome() { return Biome; };
	inline bool Get_Boss() { return isBoss; };
	inline int Get_Difficulte() { return Difficulte; };
};