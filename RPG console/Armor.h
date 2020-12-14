#pragma once
#include "Item.h"

class Hero;

class Armor : public Item
{
private : 
	int Defense;
	int Durability;

public :
	Armor() = default;
	Armor(int _defense, int _durability, string _name, int _price, Effect _effect);
	Armor(const Armor& _armor, Vector2f _position);
	~Armor() = default;

	inline int Get_Defense() { return Defense; };
	inline int Get_Durability() { return Durability; };

	bool operator == (const Armor& _a) const { return Name == _a.Name; }
	bool operator != (const Armor& _a) const { return !operator==(_a); }

	virtual void Take_Item(Hero& _player);
	virtual void Display(Vector2f _position);
};