#pragma once
#include "Item.h"

class Weapon : public Item
{
private : 
	int Dégats;
	int Durabilités;

public :
	Weapon();
	Weapon(int _dégat, int _durabilité, string _name, int _prix, Effect _effet);
	~Weapon();

	inline int get_degat() { return Dégats; };
	inline int get_durabitlité() { return Durabilités; };

	inline void Set_Degat(int _degat) { Dégats = _degat; };
	inline void Set_Durabilité(int _durabilité) { Durabilités = _durabilité; };

	bool operator == (const Weapon& _w) const { return Name == _w.Name; }
	bool operator != (const Weapon& _w) const { return !operator==(_w); }

	virtual void Display_Stat();
};