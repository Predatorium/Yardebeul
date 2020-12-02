#pragma once
#include "Item.h"

class Armor : public Item
{
private : 
	int Defenses;
	int Durabilités;

public :
	Armor();
	Armor(int _defense, int _durabilité, string _name, int _prix, Effect _effet);
	~Armor();

	inline int Get_Defenses() { return Defenses; };
	inline int Get_Durabilité() { return Durabilités; };

	virtual void Display_Stat();
};