#pragma once
#include "Tools.h"
#include "Effect.h"
#include "Entity.h"

class Hero;

class Item : public Entity
{
protected :
	Effect effect;
	bool PickUp;

public :
	Item() = default;
	Item(string _name, Effect _effect);
	~Item() = default;
	
	inline Effect Get_Effect() { return effect; };
	inline bool Get_PickUp() { return PickUp; };

	inline void Set_Effect(Effect _effect) { effect = _effect; };

	virtual void Take_Item(Hero& _player) = 0;
	virtual void Display(Vector2f _circlecol) = 0;
	virtual void Display_Inventory(Vector2f _scale);

	void Update() {};
	void Display() {};
};