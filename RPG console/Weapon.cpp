#include "Weapon.h"
#include "SpriteManager.h"

Weapon::Weapon(int _damage, int _durability, string _name, int _price, Effect _effect)
	: Item(_name, _price, _effect)
{
	Damage = _damage;
	Durability = _durability;
}

Weapon::Weapon(const Weapon& _weapon, Vector2f _position)
{
	*this = _weapon;
	Position = _position;
}

void Weapon::Display()
{
	getSprite(Name.substr(0, Name.find(" "))).setPosition(Position);
	App.Get_Window().draw(getSprite(Name.substr(0, Name.find(" "))));
}