#pragma once
#include "Tools.h"
#include "Niveau.h"
#include "Dungeon.h"
#include "Dialogue.h"
#include "Weapon.h"
#include "Armor.h"
#include "Consumable.h"

class World : public Level
{
private :
	list<Dungeon> dungeon;

public :
	World();
	World(int _load);
	~World() = default;

	inline list<Dungeon> Get_Dungeon() { return dungeon; };

	void ScreenShot(int _party);

	void Update();
	void Display();
};