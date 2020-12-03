#pragma once
#include "Tools.h"
#include "Hero.h"
#include "Npc.h"
#include "Weapon.h"
#include "Armor.h"
#include "Consumable.h"
#include "Map.h"
#include "Views.h"

class Niveau
{
protected :
	vector<Maps> Back_Layer;
	vector<Maps> Player_Layer;
	vector<Maps> Front_Layer;
	Vector2i Range_Niveau;
	Hero Player;

	list<Npc> NpcList;
	list<Weapon> WepaonList;
	list<Armor> ArmorList;
	list<Consumable> ConsumableList;

	Views Vue;
	Views Screen;

	int Nbr_Enemy;
	bool Save;
	bool Load;

public :
	Niveau() = default;
	~Niveau() = default;

	inline vector<Maps> Get_BaLayer() { return Back_Layer; };
	inline vector<Maps> Get_PlLayer() { return Player_Layer; };
	inline vector<Maps> Get_FrLayer() { return Front_Layer; };
	inline Vector2i Get_RangeNiveau() { return Range_Niveau; };
	inline bool Get_Save() { return Save; };
	inline bool Get_Load() { return Load; };

	bool Get_MapsPos(Vector2i _position);
	void Collision(Character& _Character);
	void Load_Map(string _file);
	void Save_Map(string _file);

	void display();
};