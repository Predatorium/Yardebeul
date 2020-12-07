#pragma once
#include "Character.h"
#include "Hero.h"
#include "Dialogue.h"

enum class Comportement : int
{
	Amical,
	Neutre,
	Agressif,
};

class Npc : public Character
{
private :
	Comportement Attitude;
	Vector2f Delta;
	int Damage_Min;
	int Damage_Max;
	int Defense;
	bool IsDialogue;
	Dialogue dialogue;

public :
	Npc() = default;
	Npc(string _name, Vector2f _position, int _level, int _hp, int _speed, Comportement _attitude);
	~Npc() = default;

	inline Comportement Get_Attitude() { return Attitude; };
	inline int Get_MinDamage() { return Damage_Min; };
	inline int Get_MaxDamage() { return Damage_Max; };
	inline int Get_Defense() { return Defense; };

	inline void Set_Dialogue(Dialogue _dial) { dialogue = _dial; };
	inline void Set_Attitude(Comportement _attitude) { Attitude = _attitude; };
	void Set_Name(string _name);

	bool operator == (const Npc& n) const { return Name == n.Name && Life_Point == n.Life_Point; }

	void Update_Attack(Hero& _player);
	void Update_Dialogue(bool& _dial, Hero _player);
	void Display_Fight(Vector2f _scale);
	void Display_Dialogue();
	void Display();
};