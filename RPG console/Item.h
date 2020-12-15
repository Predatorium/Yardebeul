#pragma once
#include "Tools.h"
#include "Effect.h"
#include "Animator.h"

class Hero;

class Item
{
protected :
	Effect effect;
	Vector2f Position;
	string Name;
	Animator Anim;
	int Price;
	bool PickUp;

public :
	Item() = default;
	Item(string _name, int _price, Effect _effect);
	~Item() = default;
	
	inline Effect Get_Effect() { return effect; };
	inline Vector2f Get_Position() { return Position; };
	inline string Get_Name() { return Name; };
	inline int Get_Price() { return Price; };
	inline bool Get_PickUp() { return PickUp; };

	inline void Set_Effect(Effect _effect) { effect = _effect; };
	inline void Set_Position(Vector2f _position) { Position = _position; };
	inline void Set_Name(string _name) { Name = _name; };
	inline void Set_Price(int _price) { Price = _price; };

	virtual void Take_Item(Hero& _player) = 0;
	virtual void Display(Vector2f _circlecol) = 0;
	virtual void Display_Inventory(Vector2f _scale);
};