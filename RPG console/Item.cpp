#include "Item.h"
#include "SpriteManager.h"

Item::Item(string _name, int _price, Effect _effect)
{
	Name = _name;
	Price = _price;
	effect = _effect;
	PickUp = false;
}

void Item::Display_Inventory(Vector2f _scale)
{
	Anim.Animation(getSprite(Name.substr(0, Name.find(" "))));
	getSprite(Name.substr(0, Name.find(" "))).setOrigin(Vector2f(10.5, 15));
	getSprite(Name.substr(0, Name.find(" "))).setPosition(Position);
	getSprite(Name.substr(0, Name.find(" "))).setScale(_scale);
	App.Get_Window().draw(getSprite(Name.substr(0, Name.find(""))));
}
