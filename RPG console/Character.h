#pragma once
#include "Tools.h"
#include "Armor.h"
#include "Weapon.h"
#include "Animator.h"
#include "Entity.h"

enum class Direction
{
	Up,
	Down,
	Left,
	Right,
};

class Character : public Entity
{
protected :
	Direction Orientation;

	bool Right;
	bool Left;
	bool Down;
	bool Up;

	Weapon* weapon;
	Armor* armor;

	Animator Walk_Right;
	Animator Walk_Top;
	Animator Walk_Down;

	Animator Beat_Right;
	Animator Beat_Top;
	Animator Beat_Down;

	IntRect Colision_Rect;

	int Level;
	int Life_Point;
	int Life_Max;
	int Mana;
	int Endurance;
	int Mental_Health;
	int Speed;

public :
	Character() = default;
	Character(string _name, Armor _armor, Weapon _weapon);
	~Character() = default;

	inline IntRect Get_ColisionRect() { return Colision_Rect; };
	inline Direction Get_Orientation() { return Orientation; };
	inline int Get_Level() { return Level; };
	inline int Get_LifePoint() { return Life_Point; };
	inline int Get_LifeMax() { return Life_Max; };
	inline int Get_Mana() { return Mana; };
	inline int Get_Endurance() { return Endurance; };
	inline int Get_MentalHealth() { return Mental_Health; };
	inline int Get_Speed() { return Speed; };
	inline bool Get_Left() { return Left; };
	inline bool Get_Right() { return Right; };
	inline bool Get_Up() { return Up; };
	inline bool Get_Down() { return Down; };
	inline Animator& Get_BeatRight() { return Beat_Right; };
	inline Animator& Get_BeatDown() { return Beat_Down; };
	inline Weapon* Get_Weapon() { return weapon; };
	inline Armor* Get_Armor() { return armor; };

	inline void Set_Left(bool _bool) { Left = _bool; };
	inline void Set_Right(bool _bool) { Right = _bool; };
	inline void Set_Up(bool _bool) { Up = _bool; };
	inline void Set_Down(bool _bool) { Down = _bool; };
	inline void Set_Orientation(Direction _orientation) { Orientation = _orientation; };
	inline void Set_Level(int _level) { Level = _level; };
	void Add_Life(int _life);
	void Set_Life(int _life);
	inline void Set_LifeMax(int _lifemax) { Life_Max = _lifemax; };
	inline void Set_Mana(int _mana) { Mana = _mana; };
	inline void Set_Endurance(int _endurance) { Endurance = _endurance; };
	inline void Set_MentalHealth(int _mentalhealth) { Mental_Health = _mentalhealth; };
	inline void Set_Speed(int _speed) { Speed = _speed; };

	virtual void Update() = 0;
	virtual void Display() = 0;
};