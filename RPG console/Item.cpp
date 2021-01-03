 #include "Item.h"
#include "SpriteManager.h"

Item::Item(string _name, Effect _effect)
{
	Name = _name;
	effect = _effect;
	PickUp = false;
	sprite = Sprite(getTexture(Name.substr(0, Name.find(" "))));
}

void Item::Display_Inventory(Vector2f _scale)
{
	if (Anim[Name] != Animator())
		Anim[Name].Animation(sprite);
	sprite.setOrigin(Vector2f(10.5, 15));
	sprite.setPosition(Position);
	sprite.setScale(_scale);
	App.Get_Window().draw(sprite);
}