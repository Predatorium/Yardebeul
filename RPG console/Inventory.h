#pragma once
#include "Tools.h"
#include "Armor.h"
#include "Weapon.h"
#include "Consumable.h"
#include "Button.h"

class Hero;

class Inventory
{
private :
	RectangleShape Invent;
	RectangleShape Encadré;
	Text Title;
	list<Button_Text> Sub_Menu;
	list<Weapon*> weapon;
	list<Armor*> armor;
	list<Consumable*> consumable;
	int Current_MenuSub;
	float timer;
	int Gold;

public :
	Inventory();
	~Inventory() = default;

	inline int Get_Gold() { return Gold; };

	inline list<Weapon*> Get_Weapon() { return weapon; };
	inline list<Armor*> Get_Armor() { return armor; };
	inline list<Consumable*> Get_Consumable() { return consumable; };

	inline void Add_Weapon(Weapon _arme) { weapon.push_back(new Weapon(_arme)); };
	inline void Add_Armor(Armor _armure) { armor.push_back(new Armor(_armure)); };
	inline void Add_Consumable(Consumable _consomable) { consumable.push_back(new Consumable(_consomable)); };
	inline void Add_Gold(int _gold) { Gold += _gold; };

	void Update(Hero& _player);
	void Display();
};