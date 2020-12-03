#pragma once
#include "Character.h"

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
	bool IsDead;
	int Damage_Min;
	int Damage_Max;
	int Defense;
	int Numero;

public :
	Npc() = default;
	Npc(string _name, Vector2f _position, int& _numero, int _niveau, int _pv, int vitesse, Comportement _attitude);
	~Npc() = default;

	inline Comportement Get_Attitude() { return Attitude; };
	inline int Get_Numero() { return Numero; };
	inline bool Get_IsDead() { return IsDead; };
	inline int Get_MinDamage() { return Damage_Min; };
	inline int Get_MaxDamage() { return Damage_Max; };
	inline int Get_Defense() { return Defense; };

	void Affichage_Type();
	void Affichage_Stat();

	void Update_Attack(Vector2f _playerpos);
	void Display_Fight(Vector2f _scale);
	void Display();
};