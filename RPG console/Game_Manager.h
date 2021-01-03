#pragma once
#include "Tools.h"
#include "Fight_System.h"
#include "World.h"
#include "Singleton.h"

enum class Game_State
{
	WORLD,
	FIGHT,
	DUNGEON,
};

class Game_Manager : public Singleton<Game_Manager>
{
private :
	Fight_System Fight;
	World Monde;
	
public :
	Game_Manager();
	~Game_Manager() = default;
	inline World& Get_World() { return Monde; };

	Game_State state;
	void ChangeState(Game_State NextState);
	void State_Fight(Hero* _player, Npc* _enemy);

	void Update();
	void Display();
};