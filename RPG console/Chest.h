#pragma once
#include "Tools.h"
#include "Weapons_Container.h"
#include "Armors_Container.h"
#include "Consumables_Container.h"

class Room;

class Chest : public Entity
{
private :
	int Probabilité;
	Consumable* Objet;

public :
	Chest() = default;
	Chest(Vector2f _position);
	~Chest() = default;

	void Take_Objet(Room& _room, Vector2f _player);

	virtual void Update() {};
	void Display();
};