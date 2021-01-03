#pragma once
#include "Item.h"

class Hero;

class Weapon : public Item
{
private : 
	int MaxDamage;
	int MinDamage;

public :
	Weapon() = default;
	Weapon(int _damage, string _name, Effect _effect);
	Weapon(const Weapon& _weapon, Vector2f _position);
	~Weapon() = default;

	inline int Damage() { return irandom(MinDamage, MaxDamage - MinDamage + 1); };
	inline int Get_MaxDamage() { return MaxDamage; };
	inline int Get_Mindamage() { return MinDamage; };

	inline void Set_Damage(int _damage) { MaxDamage = _damage * 1.2; MinDamage = _damage * 0.8; };

	bool operator == (const Weapon& _w) const { return Name == _w.Name; }
	bool operator != (const Weapon& _w) const { return !operator==(_w); }

	virtual void Update() {};

	virtual void Take_Item(Hero& _player);
	virtual void Display(Vector2f _circlecol);
	virtual void Display_Inventory(Vector2f _scale);
	virtual void Display() {};
};