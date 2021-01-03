#include "Weapon.h"
#include "SpriteManager.h"
#include "FontManager.h"
#include "Hero.h"

Weapon::Weapon(int _damage, string _name, Effect _effect)
	: Item(_name, _effect)
{
	MaxDamage = _damage * 1.2;
	MinDamage = _damage * 0.8;
	PickUp = false;

	if (Name == "Epee")
		Anim[Name] = Animator(IntRect(2, 18, 21, 30), 13, 0.15f);

	if (Name == "Epee de feu")
		Anim[Name] = Animator(IntRect(2, 60 , 21, 30), 13, 0.15f);

	if (Name == "Epee d air")
		Anim[Name] = Animator(IntRect(296, 18, 21, 30), 13, 0.15f);

	if (Name == "Epee d eau")
		Anim[Name] = Animator(IntRect(296, 142, 21, 30), 13, 0.15f);
	
	if (Name == "Epee de terre") 
		Anim[Name] = Animator(IntRect(2, 102, 21, 30), 13, 0.15f);

	if (Name == "Epee legendaire")
		Anim[Name] = Animator(IntRect(2, 142, 21, 30), 13, 0.15f);
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

void Weapon::Display(Vector2f _circlecol)
{
	Anim[Name].Animation(sprite);
	sprite.setPosition(Position);
	sprite.setScale(Vector2f(1, 1));
	App.Get_Window().draw(sprite);

	if (Circle_Collision(Position, _circlecol, 20, 20))
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
	if (Anim[Name] != Animator())
		Anim[Name].Animation(sprite);
	sprite.setPosition(Position);
	sprite.setScale(_scale);
	App.Get_Window().draw(sprite);
}