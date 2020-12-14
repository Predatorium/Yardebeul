#pragma once
#include "Effect.h"

class Effects_Container
{
private :
	list <Effect> Container;

public :
	Effects_Container();
	~Effects_Container() = default;

	void init();

	Effect Get_Effect(string _name);
	
	void Save();
	void Load();
};

extern Effects_Container Effects;