#include "Chest.h"
#include "Consumables_Container.h"
#include "Room.h"

Chest::Chest(Vector2f _position)
	: Entity("Chest")
{
	Position = _position;
	Probabilité = irandom(1, 3);

	string object;
	if (Probabilité == 1)
		object = "Potion Soin";
	if (Probabilité == 2)
		object = "Potion Mana";
	if (Probabilité == 3)
		object = "Potion Endu";

	int rand = irandom(3, 3);

	Objet = new Consumable(Consumables.Get_Consumable(object), rand);

	sprite.setPosition(Position);
}

void Chest::Take_Objet(Room& _room, Vector2f _player)
{
	if (Keyboard::isKeyPressed(Keyboard::E) && Circle_Collision(Position, _player, 30, 30) && Objet != nullptr)
	{
		_room.Add_Consumable(*Objet, Position);
		Objet = nullptr;
	}
}

void Chest::Display()
{
	App.Get_Window().draw(sprite);
}