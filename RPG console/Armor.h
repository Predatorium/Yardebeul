#pragma once
#include "Item.h"

class Hero;

class Armor : public Item
{
private : 
	int Defense;

public :
	Armor() = default;
	Armor(int _defense, string _name, Effect _effect);
	Armor(const Armor& _armor, Vector2f _position);
	~Armor() = default;

	inline int Get_Defense() { return Defense; };

	bool operator == (const Armor& _a) const { return Name == _a.Name; }
	bool operator != (const Armor& _a) const { return !operator==(_a); }

	virtual void Update() {};

	virtual void Take_Item(Hero& _player);
	virtual void Display(Vector2f _circlecol);
	virtual void Display_Inventory(Vector2f _scale);
	virtual void Display() {};
};