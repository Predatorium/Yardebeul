#include "Item.h"

Item::Item(string _name, int _price, Effect _effect)
{
	Name = _name;
	Price = _price;
	effect = _effect;
	PickUp = false;
}