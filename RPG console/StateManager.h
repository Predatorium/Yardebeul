#pragma once
#include "Tools.h"
#include "Singleton.h"
#include "Menu.h"
#include "Editeur.h"
#include "Game_Manager.h"

enum class State
{
	RTNULL,
	ALL,
	MENU,
	EDITOR,
	GAME,
	OPTION,
};

class StateManager : public Singleton<StateManager>
{
	friend class Singleton<StateManager>;
public:
	inline string& Get_TextReceived() { return Text_Received; };

	State state;
	void KeyboardEnter();
	void EventsManager();
	void UpdateManager();
	void DisplayManager();

	void ChangeState(State NextState);

private:
	StateManager();
	~StateManager() = default;
	Menu Game_Menu;
	Editeur Edit_Niveau;
	string Text_Received;
};