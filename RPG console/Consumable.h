#pragma once
#include "Item.h"

class Consumable : public Item
{
protected :

public :
	Consumable();
	Consumable(string _name, int _prix, Effect _effet);
	~Consumable();

	virtual void Display_Stat();
};