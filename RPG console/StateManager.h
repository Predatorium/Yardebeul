#pragma once
#include "Tools.h"
#include "Singleton.h"
#include "Menu.h"
#include "Editeur.h"
#include "Fight_System.h"
#include "World.h"

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

class StateManager : public Singleton<StateManager>
{
	friend class Singleton<StateManager>;
public:
	inline string& Get_TextReceived() { return Text_Received; };
	inline World Get_World() { return Monde; };

	State state;
	void KeyboardEnter();
	void EventsManager();
	void UpdateManager();
	void DisplayManager();
	void ChangeState(State NextState);
	void State_Fight(Hero * _player, Npc * _enemy);

private:
	StateManager();
	~StateManager() = default;
	Menu Game_Menu;
	Editeur Edit_Niveau;
	World Monde;
	Fight_System Fight;
	string Text_Received;
};