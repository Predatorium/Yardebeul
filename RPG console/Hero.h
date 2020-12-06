#pragma once
#include "Tools.h"
#include "Character.h"
#include "Weapon.h"
#include "Armor.h"
#include "Consumable.h"
#include "Effect.h"

class Hero : public Character
{
private :
	int Tableau_Niveau[11];
	int Xp_Total;
	int Xp_Level;
	int Next_Niveau;
	int Capacity_Point;
	int Gold;
	float Time;
	bool Interaction;

	Weapon* weapon;
	Armor* armor;
	list<Consumable*> consumable;

public :
	Hero() = default;
	Hero(Vector2f _position);
	~Hero() = default;

	int Pourcentage_Niveau();
	void Gain_Xp(float _gainxp);
	void Passage_Niveau();
	void Affectation_Stat(Effect _effet);
	void Amelioration_stat();

	inline int Get_Xptotal() { return Xp_Total; };
	inline int Get_XpLevel() { return Xp_Level; };
	inline int Get_PointCapacity() { return Capacity_Point; };
	inline int Get_Gold() { return Gold; };
	inline float Get_Time() { return Time; };
	inline bool Get_Interact() { return Interaction; };
	inline Weapon* Get_Weapon() { return weapon; };
	inline Armor* Get_Armor() { return armor; };
	inline list<Consumable*> Get_Consumable() { return consumable; };

	inline void Set_Weapon(Weapon _arme) { weapon = new Weapon(_arme); };
	inline void Set_Armor(Armor _armure) { armor = new Armor(_armure); };
	inline void Set_Consumable(Consumable _consomable) { consumable.push_back(new Consumable(_consomable)); };
	inline void Set_XpTotal(float _xp) { Xp_Total = _xp; };
	inline void Set_XpLevel(float _xp) { Xp_Level = _xp; };
	inline void Set_CapacityPoint(int _capacité) { Capacity_Point = _capacité; };
	inline void Set_Gold(int _argent) { Gold = _argent; };
	inline void Set_Time(float _time) { Time = _time; };

	void Update(Vector2i _limitMap);
	void Display_Fight(Vector2f _scale);
	void Display();
};