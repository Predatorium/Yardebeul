#pragma once
#include "Character.h"
#include "Hero.h"
#include "Dialogue.h"

enum class Comportement
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
	Dialogue dial;

public :
	Npc() = default;
	Npc(string _name, Vector2f _position, int _niveau, int _pv, int vitesse, Comportement _attitude);
	~Npc() = default;

	inline Comportement Get_Attitude() { return Attitude; };
	inline int Get_MinDamage() { return Damage_Min; };
	inline int Get_MaxDamage() { return Damage_Max; };
	inline int Get_Defense() { return Defense; };

	bool operator == (const Npc& n) const { return Name == n.Name && Point_de_vie == n.Point_de_vie; }

	void Update_Attack(Hero& _player);
	void Update_Dialogue(bool& _dial, Hero _player);
	void Display_Fight(Vector2f _scale);
	void Display_Dialogue();
	void Display();
};