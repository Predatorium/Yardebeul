#pragma once
#include "Tools.h"
#include "Niveau.h"
#include "Dungeon.h"
#include "Dialogue.h"

class World : public Niveau
{
private :
	list<Dungeon> Donjon;

public :
	World();
	World(int _load);
	~World() = default;

	inline list<Dungeon> Get_Dungeon() { return Donjon; };

	void ScreenShot(int _party);

	void Destroy_Npc();

	void Update();
	void Display();
};