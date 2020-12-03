#pragma once
#include "Tools.h"
#include "Hero.h"
#include "Npc.h"
#include "Bouton.h"
#include "Views.h"

class Fight_System
{
private :
	Hero Player;
	Npc Enemy;

	list<Bouton> Button;
	float timer;
	Views FixView;
	Text PvPerdu;

	bool Turn_Player;
	bool Turn_Enemy;
	int Selection;

public :
	Fight_System() = default;
	Fight_System(Hero _player, Npc _enemy);
	~Fight_System() = default;

	void Update();
	void Display();
};