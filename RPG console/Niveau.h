#pragma once
#include "Tools.h"
#include "Hero.h"
#include "Map.h"
#include "Views.h"
#include "Weapons_Container.h"
#include "Armors_Container.h"
#include "Consumables_Container.h"
#include "Npc_Container.h"

class Menu;

class Level
{
protected :
	list<Maps> Back_Layer;
	list<Maps> Player_Layer;
	list<Maps> Deco_Layer;
	list<Maps> Front_Layer;
	Vector2i Range_Niveau;
	Hero Player;

	list<Npc> NpcList;
	list<Weapon> WeaponList;
	list<Armor> ArmorList;
	list<Consumable> ConsumableList;

	Menu* Menu_Pause;

	CircleShape C_MiniMap;
	RectangleShape R_MiniMap;

	Views Vue;
	Views Screen;

	bool Save;
	bool Load;
	bool Pause;
	bool IsDialogue;
	float Timer;

public :
	Level() = default;
	~Level() = default;

	inline list<Maps> Get_BaLayer() { return Back_Layer; };
	inline list<Maps> Get_PlLayer() { return Player_Layer; };
	inline list<Maps> Get_DcLayer() { return Deco_Layer; };
	inline list<Maps> Get_FrLayer() { return Front_Layer; };
	inline Vector2i Get_RangeNiveau() { return Range_Niveau; };
	inline bool Get_Save() { return Save; };
	inline bool Get_Load() { return Load; };
	inline Hero& Get_Hero() { return Player; };

	inline void Set_Hero(Hero _hero) { Player = _hero; };

	bool Get_Void(Vector2f _position);
	bool Get_MapsPos(Vector2f _position);
	void Collision(Character& _Character);

	const Texture& Get_TextureMap(function<bool(Views&, Vector2f)> f, Views _view);
	void ScreenShot(int _party);
	void Destroy_List();

	void Update();
	virtual void Display() = 0;
};