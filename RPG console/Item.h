#pragma once
#include "Tools.h"
#include "Effect.h"

class Item
{
protected :
	Effect effet;
	string Name;
	int Prix;

public :
	Item();
	Item(string _name, int _prix, Effect _effet);
	~Item();
	
	inline string Get_Name() { return Name; };
	inline int Get_Prix() { return Prix; };
	inline Effect Get_Effet() { return effet; };

	inline void Set_Name(string _name) { Name = _name; };
	inline void Set_Prix(int _prix) { Prix = _prix; };
	inline void Set_Effet(Effect _effet) { effet = _effet; };

	virtual void Display_Stat() = 0;
};

void Display_StatFull(Item& _o);