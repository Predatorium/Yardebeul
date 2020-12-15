#pragma once
#include "Item.h"

class Hero;

class Weapon : public Item
{
private : 
	int Damage;
	int Durability;

public :
	Weapon() = default;
	Weapon(int _damage, int _durability, string _name, int _price, Effect _effect);
	Weapon(const Weapon& _weapon, Vector2f _position);
	~Weapon() = default;

	inline int Get_Damage() { return Damage; };
	inline int Get_Durability() { return Durability; };

	inline void Set_Damage(int _damage) { Damage = _damage; };
	inline void Set_Durability(int _durability) { Durability = _durability; };

	bool operator == (const Weapon& _w) const { return Name == _w.Name; }
	bool operator != (const Weapon& _w) const { return !operator==(_w); }

	virtual void Update() {};

	virtual void Take_Item(Hero& _player);
	virtual void Display(Vector2f _circlecol);
	virtual void Display_Inventory(Vector2f _scale);
	virtual void Display() {};
};