#pragma once
#include "Tools.h"
#include "Niveau.h"
#include "Dungeon.h"
#include "Dialogue.h"

class World : public Level
{
protected :
	list<Dungeon> dungeon;
	string Current_Dungeon;

public :
	World();
	World(int _load);
	~World() = default;

	void Load_Map(string _file);
	void Save_Map(string _file);

	inline list<Dungeon> &Get_Dungeon() { return dungeon; };
	inline string Get_CurrentDungeon() { return Current_Dungeon; };

	void Update();
	void Display();
};