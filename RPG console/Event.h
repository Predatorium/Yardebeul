#pragma once
#include "Tools.h"
#include "Chest.h"

class Events
{
private:
	string Name;
	string Description;
	Biomes Biome;
	State_Event Type;
	int Difficulte;

	list <Chest> Coffre;

public:
	Events();
	~Events();

	inline string Get_Name() { return Name; };
	inline string Get_Description() { return Description; };
	inline Biomes Get_biome() { return Biome; };
	inline State_Event Get_Type() { return Type; };
	inline int Get_Difficulte() { return Difficulte; };
};