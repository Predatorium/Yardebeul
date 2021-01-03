#pragma once
#include "Tools.h"

class Hero;
class World;

class Data
{
private :

public :
	Data() = default;
	~Data() = default;

	static void Save_Player(int _party, Hero _joueur, World _w);
	static void Load_Player(int _party, Hero& _joueur, World &_w);
};