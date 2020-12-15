#include "Item.h"
#include "SpriteManager.h"

Item::Item(string _name, int _price, Effect _effect)
{
	Name = _name;
	Price = _price;
	effect = _effect;
	PickUp = false;
	sprite = getSprite(Name.substr(0, Name.find(" ")));
}

void Item::Display_Inventory(Vector2f _scale)
{
	Anim.Animation(sprite);
	sprite.setOrigin(Vector2f(10.5, 15));
	sprite.setPosition(Position);
	sprite.setScale(_scale);
	App.Get_Window().draw(sprite);
}
