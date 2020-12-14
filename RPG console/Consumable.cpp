#include "Consumable.h"
#include "SpriteManager.h"
#include "FontManager.h"
#include "Hero.h"

Consumable::Consumable(string _name, int _price, Effect _effect)
	: Item(_name, _price, _effect)
{
	PickUp = false;
}

Consumable::Consumable(const Consumable& _consumable, Vector2f _position)
{
	*this = _consumable;
	Position = _position;
}

void Consumable::Take_Item(Hero& _player)
{
	if (Circle_Collision(_player.Get_Position(), Position, 20, 20) && _player.Get_Interact())
	{
		_player.Get_Inventory().Add_Consumable(*this);
		PickUp = true;
	}
}

void Consumable::Display(Vector2f _position)
{
	getSprite(Name.substr(0, Name.find(" "))).setPosition(Position);
	getSprite(Name.substr(0, Name.find(" "))).setScale(Vector2f(1, 1));
	App.Get_Window().draw(getSprite(Name.substr(0, Name.find(" "))));
}