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

public :
	Npc();
	Npc(string _name, int _niveau, int _pv, int vitesse, Comportement _attitude);
	~Npc();

	void Affichage_Type();
	void Affichage_Stat();
};