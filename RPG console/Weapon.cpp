#include "Weapon.h"
#include "SpriteManager.h"
#include "FontManager.h"
#include "Hero.h"

Weapon::Weapon(int _damage, int _durability, string _name, int _price, Effect _effect)
	: Item(_name, _price, _effect)
{
	Damage = _damage;
	Durability = _durability;
	PickUp = false;

	if (Name == "Epee de feu")
	{
		Anim[Name] = Animator(IntRect(2, 18, 21, 30), 13, 0.15f);
	}
}

Weapon::Weapon(const Weapon& _weapon, Vector2f _position)
{
	*this = _weapon;
	Position = _position;
}

void Weapon::Take_Item(Hero& _player)
{
	if (Circle_Collision(_player.Get_Position(), Position, 20, 20) && _player.Get_Interact())
	{
		_player.Get_Inventory().Add_Weapon(*this);
		PickUp = true;
	}
}

void Weapon::Display(Vector2f _position)
{
	Anim[Name].Animation(sprite);
	sprite.setOrigin(Vector2f(10.5, 15));
	sprite.setPosition(Position);
	sprite.setScale(Vector2f(1, 1));
	App.Get_Window().draw(sprite);

	if (Circle_Collision(Position, _position, 20, 20))
	{
		Text My(Name, getFont("Times"), 20);
		My.setOrigin(getMidle(My));
		My.setFillColor(Color::Black);
		My.setPosition(Vector2f(Position.x, Position.y - 20));
		App.Get_Window().draw(My);
	}
}

void Weapon::Display_Inventory(Vector2f _scale)
{
	Anim[Name].Animation(sprite);
	sprite.setOrigin(Vector2f(10.5, 15));
	sprite.setPosition(Position);
	sprite.setScale(_scale);
	App.Get_Window().draw(sprite);
}