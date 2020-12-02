#pragma once
#include "Tools.h"
#include "World.h"
#include "Hero.h"
#include "Dungeon.h"

class Save
{
private :

public :
	Save() = default;
	~Save() = default;

	static void Save_World(int _party, World _world);
	static void Save_Player(int _party, Hero _joueur);
}; 

class Load
{
private:

public:
	Load() = default;
	~Load() = default;

	static void Load_World(int _party, World& _world);
	static void Load_Player(int _party, Hero& _joueur);
};