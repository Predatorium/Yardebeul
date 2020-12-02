#pragma once
#include "Item.h"

class Armor : public Item
{
private : 
	int Defenses;
	int DurabilitÚs;

public :
	Armor();
	Armor(int _defense, int _durabilitÚ, string _name, int _prix, Effect _effet);
	~Armor();

	inline int Get_Defenses() { return Defenses; };
	inline int Get_DurabilitÚ() { return DurabilitÚs; };

	virtual void Display_Stat();
};