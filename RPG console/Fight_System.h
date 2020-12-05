#pragma once
#include "Tools.h"
#include "Hero.h"
#include "Npc.h"
#include "Bouton.h"
#include "Views.h"

class Fight_System
{
private :
	RectangleShape Menu;
	Box Pv_Joueur;
	Box Pv_Enemy;
	Hero* Player;
	Npc* Enemy;

	list<Button_Text> Button;
	float timer;
	Views FixView;
	Text Texte;

	bool Turn_Player;
	bool Turn_Enemy;
	int Selection;

public :
	Fight_System() = default;
	Fight_System(Hero* _player, Npc* _enemy);
	~Fight_System() = default;

	void Capacity_Select();
	void Hud_Update();
	void Hud_Display();

	void Update();
	void Display();
};