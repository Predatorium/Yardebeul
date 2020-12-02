#pragma once
#include "Tools.h"
#include "Weapons_Container.h"
#include "Armors_Container.h"
#include "Consumables_Container.h"
#include "Hero.h"

class Chest
{
private :
	int Probabilité;
	list<Item*> Objet;

public :
	Chest();
	~Chest() = default;

	void Take_Objet(Hero& _hero, int x);
	
	inline void Add_Arme(Weapon& _arme) { Objet.push_back(new Weapon(_arme)); };
	inline void Add_Armure(Armor& _armure) { Objet.push_back(new Armor(_armure)); };
	inline void Add_Consommable(Consumable& _consommable) { Objet.push_back(new Consumable(_consommable)); };

	void display_coffre();
};