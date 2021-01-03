#pragma once
#include "Tools.h"
#include "Character.h"
#include "Weapon.h"
#include "Armor.h"
#include "Consumable.h"
#include "Effect.h"
#include "Inventory.h"

class Hero : public Character
{
private :
	Inventory inventory;
	int Tableau_Niveau[11];
	int Xp_Total;
	int Xp_Level;
	int Next_Niveau;
	int Capacity_Point;
	float Time;
	float timer;
	bool Interaction;
	bool IsInventory;

	Consumable* consumable;

public :
	Hero() = default;
	Hero(Vector2f _position);
	~Hero() = default;

	int Pourcentage_Niveau();
	void Gain_Xp(float _gainxp);
	void Passage_Niveau();
	void Amelioration_stat();

	inline int Get_Xptotal() { return Xp_Total; };
	inline int Get_XpLevel() { return Xp_Level; };
	inline int Get_PointCapacity() { return Capacity_Point; };

	inline float Get_Time() { return Time; };
	inline bool Get_Interact() { return Interaction; };
	inline Consumable* Get_Consumable() { return consumable; };
	inline bool Get_IsInventory() { return IsInventory; };
	inline Inventory& Get_Inventory() { return inventory; };

	void Set_Consumable(Consumable _consomable);
	inline void Set_XpTotal(float _xp) { Xp_Total = _xp; };
	inline void Set_XpLevel(float _xp) { Xp_Level = _xp; };
	inline void Set_CapacityPoint(int _capacité) { Capacity_Point = _capacité; };
	inline void Set_Time(float _time) { Time = _time; };
	inline void Set_IsInventory(bool _bool) { IsInventory = _bool; };

	virtual void Update();
	int Use_Consumable(Button_Text& _b);
	void Display_Fight(Vector2f _scale);
	void Display_HUD();
	virtual void Display();
};