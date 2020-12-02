#include "Item.h"

Item::Item()
{
	Name = '0';
	Prix = 0;
}

Item::Item(string _name, int _prix, Effect _effet)
{
	Name = _name;
	Prix = _prix;
	effet = _effet;
}

Item::~Item()
{

}

void Display_StatFull(Item& _o)
{
	_o.Display_Stat();
}