#pragma once
#include "Tools.h"
#include "Armor.h"
#include "Weapon.h"
#include "Entity.h"
#include "Sort.h"

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

	list<Sort*> Spell;

	bool Right;
	bool Left;
	bool Down;
	bool Up;

	Weapon* weapon;
	Armor* armor;

	list<Effect> Current_Effect;

	int Level;
	int Life_Point;
	int Life_Max;
	int Mana;
	int Mana_Max;
	int Endurance;
	int Endurance_Max;
	int Speed;
	int Speed_Max;

public :
	Character() = default;
	Character(string _name, int _life, int _mana, int _endurance, int _speed, Armor _armor, Weapon _weapon);
	~Character() = default;

	inline Direction Get_Orientation() { return Orientation; };
	inline int Get_Level() { return Level; };
	inline int Get_LifePoint() { return Life_Point; };
	inline int Get_LifeMax() { return Life_Max; };
	inline int Get_Mana() { return Mana; };
	inline int Get_Endurance() { return Endurance; };
	inline int Get_Speed() { return Speed; };
	inline bool Get_Left() { return Left; };
	inline bool Get_Right() { return Right; };
	inline bool Get_Up() { return Up; };
	inline bool Get_Down() { return Down; };
	inline Weapon* Get_Weapon() { return weapon; };
	inline Armor* Get_Armor() { return armor; };
	Sort* Get_OneSpell(string _name);
	Sort* Get_OneSpell(int _it);
	list<Sort*> Get_Spell() { return Spell; };

	inline void Set_Weapon(Weapon _arme) { weapon = new Weapon(_arme); };
	inline void Set_Armor(Armor _armure) { armor = new Armor(_armure); };
	inline void Set_Left(bool _bool) { Left = _bool; };
	inline void Set_Right(bool _bool) { Right = _bool; };
	inline void Set_Up(bool _bool) { Up = _bool; };
	inline void Set_Down(bool _bool) { Down = _bool; };
	inline void Set_Orientation(Direction _orientation) { Orientation = _orientation; };
	inline void Set_Level(int _level) { Level = _level; };
	void Add_Life(int _life);
	void Set_Life(int _life);
	inline void Set_LifeMax(int _lifemax) { Life_Max = _lifemax; };
	void Add_Mana(int _mana);
	inline void Set_Mana(int _mana) { Mana = _mana; Mana_Max = _mana; };
	void Add_Endurance(int _endurance);
	inline void Set_Endurance(int _endurance) { Endurance = _endurance; Endurance_Max = _endurance; };
	void Add_Speed(int _speed);
	inline void Set_Speed(int _speed) { Speed = _speed; Speed_Max = _speed; };

	inline void Reset_Speed() { Speed = Speed_Max; };

	void Add_Effect(Effect _effect) { Current_Effect.push_back(_effect); };
	int Attack(Character* _c);
	pair<string, int> Use_Spell(Character* _c, Sort _s);

	map<string, int> Effect_Update();
	void Effect_Received(Effect _effect);

	virtual void Update() = 0;
	virtual void Display() = 0;
};