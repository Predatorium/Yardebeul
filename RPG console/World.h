#pragma once
#include "Tools.h"
#include "Niveau.h"
#include "Dungeon.h"

class Menu;

class World : public Niveau
{
private :
	list<Dungeon> Donjon;
	Menu* Menu_Pause;
	bool Pause;

public :
	World();
	World(int _load);
	~World() = default;

	inline Hero Get_Hero() { return Player; };

	inline void Set_Hero(Hero _hero) { Player = _hero; };
	inline list<Dungeon> Get_Dungeon() { return Donjon; };

	void ScreenShot(int _party);

	void Destroy_Npc();

	void Update();
	void Display();
};