#pragma once
#include "Sort.h"

class Sort_Container
{
private :
	list<Sort> Container;

public :
	Sort_Container() = default;
	~Sort_Container() = default;

	void init();

	Sort Get_Sort(string _name);
	inline list<Sort> Get_Container() { return Container; };
};
extern Sort_Container Sorts;