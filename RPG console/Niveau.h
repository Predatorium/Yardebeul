#pragma once
#include "Tools.h"
#include "Hero.h"
#include "Npc_Container.h"
#include "Weapon.h"
#include "Armor.h"
#include "Consumable.h"
#include "Map.h"
#include "Views.h"

class Menu;

class Level
{
protected :
	vector<Maps> Back_Layer;
	vector<Maps> Deco_Layer;
	vector<Maps> Player_Layer;
	vector<Maps> Front_Layer;
	Vector2i Range_Niveau;
	Hero Player;

	list<Npc> NpcList;
	list<Weapon> WeaponList;
	list<Armor> ArmorList;
	list<Consumable> ConsumableList;

	Menu* Menu_Pause;

	Views Vue;
	Views Screen;

	bool Save;
	bool Load;
	bool Pause;
	bool IsDialogue;

public :
	Level() = default;
	~Level() = default;

	inline vector<Maps> Get_BaLayer() { return Back_Layer; };
	inline vector<Maps> Get_PlLayer() { return Player_Layer; };
	inline vector<Maps> Get_FrLayer() { return Front_Layer; };
	inline Vector2i Get_RangeNiveau() { return Range_Niveau; };
	inline bool Get_Save() { return Save; };
	inline bool Get_Load() { return Load; };
	inline Hero Get_Hero() { return Player; };

	inline void Set_Hero(Hero _hero) { Player = _hero; };

	bool Get_Void(Vector2i _position);
	bool Get_MapsPos(Vector2i _position);
	void Collision(Character& _Character);
	void Load_Map(string _file);
	void Save_Map(string _file);

	void ScreenShot(int _party);
	void Destroy_List();

	void Update();
	void Display();
};