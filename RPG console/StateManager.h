#pragma once
#include "Tools.h"
#include "Menu.h"
#include "Editeur.h"

enum class State
{
	RTNULL,
	ALL,
	MENU,
	EDITEUR,
	GAME,
	OPTION,
};

class StateManager
{
private:
	Menu Game_Menu;
	Editeur Edit_Niveau;
	World Monde;
	State state;
	string Text_Received;

public:
	StateManager();
	~StateManager() = default;

	inline string Get_TextReceived() { return Text_Received; };
	inline World Get_World() { return Monde; };

	void KeyboardEnter();
	void EventsManager();
	void UpdateManager();
	void DisplayManager();
	void ChangeState(State NextState);
};
extern StateManager MState;

extern bool Pause;