#pragma once
#include "Tools.h"
#include "Menu.h"
#include "Editeur.h"
#include "Fight_System.h"

enum class State
{
	RTNULL,
	ALL,
	MENU,
	EDITOR,
	GAME,
	FIGHT,
	OPTION,
};

class StateManager
{
private:
	Menu Game_Menu;
	Editeur Edit_Niveau;
	World Monde;
	Fight_System Fight;
	State state;
	string Text_Received;

public:
	StateManager();
	~StateManager() = default;

	inline string& Get_TextReceived() { return Text_Received; };
	inline World Get_World() { return Monde; };

	void KeyboardEnter();
	void EventsManager();
	void UpdateManager();
	void DisplayManager();
	void ChangeState(State NextState);
	void State_Fight(Hero* _player, Npc* _enemy);
};
extern StateManager MState;

extern bool Pause;