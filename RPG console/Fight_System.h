#pragma once
#include "Tools.h"
#include "Hero.h"
#include "Npc.h"
#include "Button.h"
#include "Views.h"

enum class Game_State;

enum class Etat
{
	IsMyTurn,
	WaitMyTurn,
	Finish,
};

class Fight_System
{
private :
	RectangleShape Menu;
	Box Pv_Joueur;
	Box Pv_Enemy;
	Hero* Player;
	Npc* Enemy;
	Game_State Previous_state;
	Sprite sprite;
	list<Button_Text> Button;
	float timer;
	Text Texte;
	enum class Etape
	{
		Attack,
		AfDamage,
		AfEffect,
	};
	Etape etape;

	Etat Turn_Player;
	Etat Turn_Enemy;
	int Selection;

public :
	Fight_System() = default;
	Fight_System(Hero* _player, Npc* _enemy, Game_State _state);
	~Fight_System() = default;

	void Capacity_Select();
	void Hud_Update();
	void Hud_Display();

	void Update();
	void Display();
};