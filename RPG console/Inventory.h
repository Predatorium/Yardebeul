#pragma once
#include "Tools.h"
#include "Armor.h"
#include "Weapon.h"
#include "Consumable.h"
#include "Sort.h"
#include "Button.h"

class Hero;

class Inventory
{
private :
	RectangleShape Invent;
	RectangleShape Encadré;

	Text Title;
	Text Item_Player;

	list<Button_Text> Sub_Menu;

	list<Weapon*> weapon;
	list<Armor*> armor;
	list<Consumable*> consumable;
	list<Sort*> Spell;

	int Current_MenuSub;
	int Current_Item;
	float timer;

public :
	Inventory() = default;
	~Inventory() = default;
	void init();

	inline list<Weapon*> Get_Weapon() { return weapon; };
	inline list<Armor*> Get_Armor() { return armor; };
	inline list<Consumable*> Get_Consumable() { return consumable; };

	inline void Add_Weapon(Weapon _arme) { weapon.push_back(new Weapon(_arme)); };
	inline void Add_Armor(Armor _armure) { armor.push_back(new Armor(_armure)); };
	void Add_Consumable(Consumable _consomable);
	
	void Item_Load();
	void Update(Hero& _player);
	void Display_stat();
	void Display_CurrentItem(Hero _player);
	void Display();
};