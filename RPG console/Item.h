#pragma once
#include "Tools.h"
#include "Effect.h"
#include "Animator.h"
#include "Entity.h"

class Hero;

class Item : public Entity
{
protected :
	Effect effect;
	Animator Anim;
	int Price;
	bool PickUp;

public :
	Item() = default;
	Item(string _name, int _price, Effect _effect);
	~Item() = default;
	
	inline Effect Get_Effect() { return effect; };
	inline int Get_Price() { return Price; };
	inline bool Get_PickUp() { return PickUp; };

	inline void Set_Effect(Effect _effect) { effect = _effect; };
	inline void Set_Price(int _price) { Price = _price; };

	virtual void Take_Item(Hero& _player) = 0;
	virtual void Display(Vector2f _circlecol) = 0;
	virtual void Display_Inventory(Vector2f _scale);

	virtual void Update() = 0;
	virtual void Display() = 0;
};