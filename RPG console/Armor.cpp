#include "Armor.h"
#include "SpriteManager.h"

Armor::Armor(int _defense, int _durability, string _name, int _price, Effect _effect)
	: Item(_name, _price, _effect)
{
	Defense = _defense;
	Durability = _durability;
}

Armor::Armor(const Armor& _armor, Vector2f _position)
{
	*this = _armor;
	Position = _position;
}

void Armor::Display()
{
	getSprite(Name.substr(0, Name.find(" "))).setPosition(Position);
	App.Get_Window().draw(getSprite(Name.substr(0, Name.find(""))));
}