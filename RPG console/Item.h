#pragma once
#include "Tools.h"
#include "Effect.h"

class Item
{
protected :
	Effect effect;
	Vector2f Position;
	string Name;
	int Price;

public :
	Item() = default;
	Item(string _name, int _price, Effect _effect);
	~Item() = default;
	
	inline Effect Get_Effect() { return effect; };
	inline Vector2f Get_Position() { return Position; };
	inline string Get_Name() { return Name; };
	inline int Get_Price() { return Price; };

	inline void Set_Effect(Effect _effect) { effect = _effect; };
	inline void Set_Position(Vector2f _position) { Position = _position; };
	inline void Set_Name(string _name) { Name = _name; };
	inline void Set_Price(int _price) { Price = _price; };

	virtual void Display() = 0;
};