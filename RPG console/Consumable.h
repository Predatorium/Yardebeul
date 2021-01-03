#pragma once
#include "Item.h"

class Hero;

class Consumable : public Item
{
private :
	int Number;

public :
	Consumable() = default;
	Consumable(string _name, int _number, Effect _effect);
	Consumable(const Consumable& _consumable, Vector2f _position);
	Consumable(const Consumable& _consumable, int number);
	~Consumable() = default;

	inline int Get_Number() { return Number; };
	inline void Set_Number(int _number) { Number = _number; };
	inline void Add_Number(int _number) { Number += _number; };

	bool operator == (const Consumable& _c) const { return Name == _c.Name; }
	bool operator != (const Consumable& _c) const { return !operator==(_c); }

	void Update();

	virtual void Take_Item(Hero& _player);
	virtual void Display(Vector2f _circlecol);
	virtual void Display_Inventory(Vector2f _scale);
	virtual void Display() {};
};