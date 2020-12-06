#include "Consumable.h"
#include "SpriteManager.h"

Consumable::Consumable(string _name, int _price, Effect _effect)
	: Item(_name, _price, _effect){}

Consumable::Consumable(const Consumable& _consumable, Vector2f _position)
{
	*this = _consumable;
	Position = _position;
}

void Consumable::Display()
{
	getSprite(Name.substr(0, Name.find(" "))).setPosition(Position);
	App.Get_Window().draw(getSprite(Name.substr(0, Name.find(" "))));
}