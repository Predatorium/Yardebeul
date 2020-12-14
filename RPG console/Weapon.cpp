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
		Anim = Animator(IntRect(2, 18, 21, 30), 13, 0.2f);
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
		_player.Add_Weapon(*this);
		PickUp = true;
	}
}

void Weapon::Display(Vector2f _position)
{
	Anim.Animation(getSprite(Name.substr(0, Name.find(" "))));
	getSprite(Name.substr(0, Name.find(" "))).setOrigin(Vector2f(10.5, 15));
	getSprite(Name.substr(0, Name.find(" "))).setPosition(Position);
	App.Get_Window().draw(getSprite(Name.substr(0, Name.find(" "))));

	if (Circle_Collision(Position, _position, 20, 20))
	{
		Text My(Name, getFont("Times"), 20);
		My.setOrigin(getMidle(My));
		My.setFillColor(Color::Black);
		My.setPosition(Vector2f (Position.x, Position.y - 20));
		App.Get_Window().draw(My);
	}
}