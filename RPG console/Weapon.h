#pragma once
#include "Item.h"

class Weapon : public Item
{
private : 
	int D�gats;
	int Durabilit�s;

public :
	Weapon();
	Weapon(int _d�gat, int _durabilit�, string _name, int _prix, Effect _effet);
	~Weapon();

	inline int get_degat() { return D�gats; };
	inline int get_durabitlit�() { return Durabilit�s; };

	inline void Set_Degat(int _degat) { D�gats = _degat; };
	inline void Set_Durabilit�(int _durabilit�) { Durabilit�s = _durabilit�; };

	bool operator == (const Weapon& _w) const { return Name == _w.Name; }
	bool operator != (const Weapon& _w) const { return !operator==(_w); }

	virtual void Display_Stat();
};