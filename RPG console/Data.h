#pragma once
#include "Tools.h"
#include "Hero.h"

class Data
{
private :

public :
	Data() = default;
	~Data() = default;

	static void Save_Player(int _party, Hero _joueur);
	static void Load_Player(int _party, Hero& _joueur);
};