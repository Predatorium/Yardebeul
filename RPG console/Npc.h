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
	bool IsDialogue;
	Dialogue dialogue;

public :
	Npc() = default;
	Npc(string _name, Armor _armor, Weapon _weapon, int _level, int _hp, int _speed);
	Npc(string _name, int _level, int _hp, int _speed, Dialogue &_dial);
	Npc(const Npc& _npc, Vector2f _position);
	~Npc() = default;

	inline Comportement Get_Attitude() { return Attitude; };
	inline Dialogue Get_Dialogue() { return dialogue; };

	inline void Set_Dialogue(Dialogue _dial) { dialogue = _dial; };
	inline void Set_Attitude(Comportement _attitude) { Attitude = _attitude; };

	bool operator == (const Npc& n) const { return Name == n.Name && Life_Point == n.Life_Point && Position.x == n.Position.x && Position.y == n.Position.y; }

	void Update_Attack(Hero& _player);
	void Update_Dialogue(bool& _dial, Hero _player);
	void Display_Fight(Vector2f _scale);
	void Display_Dialogue();
	void Display();
};