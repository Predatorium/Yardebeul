#pragma once
#include "Item.h"

class Hero;

class Consumable : public Item
{
private :

public :
	Consumable() = default;
	Consumable(string _name, int _price, Effect _effect);
	Consumable(const Consumable& _consumable, Vector2f _position);
	~Consumable() = default;

	bool operator == (const Consumable& _c) const { return Name == _c.Name; }
	bool operator != (const Consumable& _c) const { return !operator==(_c); }

	virtual void Take_Item(Hero& _player);
	virtual void Display(Vector2f _position);
};