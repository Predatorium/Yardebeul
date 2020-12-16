#pragma once
#include "Tools.h"

class Entity
{
protected :
	Sprite sprite;
	Vector2f Position;
	string Name;

public :
	Entity() = default;
	Entity(string _name);
	~Entity() = default;

	inline Vector2f Get_Position() { return Position; };
	inline string Get_Name() { return Name; };
	inline Sprite& Get_Sprite() { return sprite; };

	inline void Set_Position(Vector2f _position) { Position = _position; sprite.setPosition(Position); };
	inline void Set_Name(string _name) { Name = _name; };

	virtual void Update() = 0;
	virtual void Display() = 0;
};