#include "Consumable.h"
#include "FontManager.h"
#include "Hero.h"

Consumable::Consumable(string _name, int _number, Effect _effect)
	: Item(_name, _effect)
{
	Number = _number;
	PickUp = false;
	if (Name == "Potion Soin")
		Anim[Name] = Animator(IntRect(0, 0, 19, 20), 10, 0.15f);
	if (Name == "Potion Mana")
		Anim[Name] = Animator(IntRect(0, 20, 19, 20), 10, 0.15f);
	if (Name == "Potion Endu")
		Anim[Name] = Animator(IntRect(0, 40, 19, 20), 10, 0.15f);
}

Consumable::Consumable(const Consumable& _consumable, Vector2f _position)
{
	*this = _consumable;
	Position = _position;
}

Consumable::Consumable(const Consumable& _consumable, int number)
{
	*this = _consumable;
	Number = number;
}

void Consumable::Update()
{

}

void Consumable::Take_Item(Hero& _player)
{
	if (Circle_Collision(_player.Get_Position(), Position, 20, 20) && _player.Get_Interact())
	{
		if (_player.Get_Consumable()->Get_Name() == Name)
			_player.Get_Consumable()->Add_Number(Number);
		else
			_player.Get_Inventory().Add_Consumable(*this);
		PickUp = true;
	}
}

void Consumable::Display(Vector2f _circlecol)
{
	Text number = Text(to_string(Number), getFont("Times"), 15);
	number.setFillColor(Color::Black);
	Anim[Name].Animation(sprite);
	sprite.setPosition(Position);
	number.setPosition(Vector2f(Position.x - sprite.getGlobalBounds().width / 2, Position.y - sprite.getGlobalBounds().height));
	sprite.setScale(Vector2f(1, 1));

	App.Get_Window().draw(sprite);
	App.Get_Window().draw(number);

	if (Circle_Collision(Position, _circlecol, 20, 20))
	{
		Text My(Name, getFont("Times"), 20);
		My.setOrigin(getMidle(My));
		My.setFillColor(Color::Black);
		My.setPosition(Vector2f(Position.x, Position.y - 20));
		App.Get_Window().draw(My);
	}
}

void Consumable::Display_Inventory(Vector2f _scale)
{
	Text number = Text(to_string(Number), getFont("Times"), 30);
	number.setFillColor(Color::Black);
	Anim[Name].Animation(sprite);
	sprite.setPosition(Position);
	number.setPosition(Vector2f(Position.x - sprite.getGlobalBounds().width / 2, Position.y - sprite.getGlobalBounds().height));
	sprite.setScale(_scale);
	App.Get_Window().draw(sprite);
	App.Get_Window().draw(number);
}