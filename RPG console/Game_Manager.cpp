#include "Game_Manager.h"

Game_Manager::Game_Manager()
{
	ChangeState(Game_State::WORLD);
}

void Game_Manager::ChangeState(Game_State NextState)
{
	this->state = NextState;
}

void Game_Manager::State_Fight(Hero* _player, Npc* _enemy)
{
	Fight = Fight_System(_player, _enemy, this->state);
	this->state = Game_State::FIGHT;
}

void Game_Manager::Update()
{
	switch (this->state)
	{
	case Game_State::WORLD:
		Monde.Update();
		break;
	case Game_State::FIGHT:
		Fight.Update();
		break;
	case Game_State::DUNGEON:
		for (Dungeon& Current : Monde.Get_Dungeon())
			if (Current.Get_Name() == Monde.Get_CurrentDungeon())
			{
				Current.Update(Monde.Get_Hero());
				break;
			}
		break;
	default:
		break;
	}
}

void Game_Manager::Display()
{
	switch (this->state)
	{
	case Game_State::WORLD:
		Monde.Display();
		break;
	case Game_State::FIGHT:
		Fight.Display();
		break;
	case Game_State::DUNGEON:
		for (Dungeon& Current : Monde.Get_Dungeon())
			if (Current.Get_Name() == Monde.Get_CurrentDungeon())
			{
				Current.Display();
				break;
			}
		break;
	default:
		break;
	}
}
