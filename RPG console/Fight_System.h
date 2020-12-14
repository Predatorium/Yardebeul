#pragma once
#include "Tools.h"
#include "Hero.h"
#include "Npc.h"
#include "Button.h"
#include "Views.h"

enum class State;

class Fight_System
{
private :
	RectangleShape Menu;
	Box Pv_Joueur;
	Box Pv_Enemy;
	Hero* Player;
	Npc* Enemy;
	State Previous_state;

	list<Button_Text> Button;
	float timer;
	Views FixView;
	Text Texte;

	bool Turn_Player;
	bool Turn_Enemy;
	int Selection;

public :
	Fight_System() = default;
	Fight_System(Hero* _player, Npc* _enemy, State _state);
	~Fight_System() = default;

	void Capacity_Select();
	void Hud_Update();
	void Hud_Display();

	void Update();
	void Display();
};