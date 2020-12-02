#pragma once
#include "Item.h"

class Armor : public Item
{
private : 
	int Defenses;
	int Durabilit�s;

public :
	Armor();
	Armor(int _defense, int _durabilit�, string _name, int _prix, Effect _effet);
	~Armor();

	inline int Get_Defenses() { return Defenses; };
	inline int Get_Durabilit�() { return Durabilit�s; };

	virtual void Display_Stat();
};