#include "Data.h"
#include "Hero.h"
#include "World.h"
#include "Weapons_Container.h"
#include "Armors_Container.h"
#include "Consumables_Container.h"

void Data::Save_Player(int _party, Hero _joueur, World _w)
{
	ofstream Save_Hero("../Ressources/Infos/Save" + to_string(_party) + ".txt");
	if (Save_Hero.is_open())
	{
		Save_Hero << "Name : " << _joueur.Get_Name() << endl;
		Save_Hero << "Level : " << _joueur.Get_Level() << endl;
		Save_Hero << "Time : " << _joueur.Get_Time() << endl;
		Save_Hero << "Position : " << _joueur.Get_Position().x << "|" << _joueur.Get_Position().y << endl;
		Save_Hero << "Life Point : " << _joueur.Get_LifePoint() << endl;
		Save_Hero << "Mana : " << _joueur.Get_Mana() << endl;
		Save_Hero << "Speed : " << _joueur.Get_Speed() << endl;
		Save_Hero << "XpTotal : " << _joueur.Get_Xptotal() << endl;
		Save_Hero << "XpLevel : " << _joueur.Get_XpLevel() << endl;
		Save_Hero << "Capacity : " << _joueur.Get_PointCapacity();

		if (_joueur.Get_Weapon() != nullptr)
			Save_Hero << "Current Weapon : " << _joueur.Get_Weapon()->Get_Name();
		if (_joueur.Get_Armor() != nullptr)
			Save_Hero << "Current Armor : " << _joueur.Get_Armor()->Get_Name();
		if (_joueur.Get_Consumable() != nullptr)
			Save_Hero << "Current Consumable : " << _joueur.Get_Consumable()->Get_Name();

		for (Weapon* Current : _joueur.Get_Inventory().Get_Weapon())
		{
			Save_Hero << endl;
			Save_Hero << "Weapon : " << Current->Get_Name();
		}

		for (Armor* Current : _joueur.Get_Inventory().Get_Armor())
		{
			Save_Hero << endl;
			Save_Hero << "Armor : " << Current->Get_Name();
		}

		for (Consumable* Current_Consu : _joueur.Get_Inventory().Get_Consumable())
		{
			Save_Hero << endl;
			Save_Hero << "Consumable : " << Current_Consu->Get_Name();
		}

		for (Dungeon& Current : _w.Get_Dungeon())
		{
			Save_Hero << endl;
			if (Current.Get_Finished() == true)
				Save_Hero << "Dungeon : " << Current.Get_Name() << " " << 1;
			else
				Save_Hero << "Dungeon : " << Current.Get_Name() << " " << 0;
		}

		Save_Hero.close();
	}
}

void Data::Load_Player(int _party, Hero& _joueur, World& _w)
{
	_joueur = Hero(Vector2f(100, 100));

	ifstream Load_Hero("../Ressources/Infos/Save" + to_string(_party) + ".txt");
	if (Load_Hero.is_open())
	{
		string line = "0";
		while (getline(Load_Hero, line))
		{
			if (line.substr(0,line.find(" : ")) == "Name")
				_joueur.Set_Name(line.substr(line.find(" : ") + 3));

			if (line.substr(0, line.find(" : ")) == "Level")
				_joueur.Set_Level(stoi(line.substr(line.find(" : ") + 3)));

			if (line.substr(0, line.find(" : ")) == "Time")
				_joueur.Set_Time(stof(line.substr(line.find(" : ") + 3)));

			if (line.substr(0, line.find(" : ")) == "Position")
				_joueur.Set_Position(Vector2f(stof(line.substr(line.find(" : ") + 3)), stof(line.substr(line.find("|") + 1))));

			if (line.substr(0, line.find(" : ")) == "Life Point")
				_joueur.Set_Life(stoi(line.substr(line.find(" : ") + 3)));

			if (line.substr(0, line.find(" : ")) == "Mana")
				_joueur.Set_Mana(stoi(line.substr(line.find(" : ") + 3)));

			if (line.substr(0, line.find(" : ")) == "Speed")
				_joueur.Set_Speed(stoi(line.substr(line.find(" : ") + 3)));

			if (line.substr(0, line.find(" : ")) == "XpTotal")
				_joueur.Set_XpTotal(stof(line.substr(line.find(" : ") + 3)));

			if (line.substr(0, line.find(" : ")) == "XpLevel")
				_joueur.Set_XpLevel(stof(line.substr(line.find(" : ") + 3)));

			if (line.substr(0, line.find(" : ")) == "Capacity")
				_joueur.Set_CapacityPoint(stoi(line.substr(line.find(" : ") + 3)));

			if (line.substr(0, line.find(" : ")) == "Current Weapon")
				_joueur.Set_Weapon(Weapon(Weapons.Get_Weapon(line.substr(line.find(" : ") + 3))));

			if (line.substr(0, line.find(" : ")) == "Current Armor")
				_joueur.Set_Armor(Armor(Armors.Get_Armor(line.substr(line.find(" : ") + 3))));

			if (line.substr(0, line.find(" : ")) == "Current Consumable")
				_joueur.Set_Consumable(Consumable(Consumables.Get_Consumable(line.substr(line.find(" : ") + 3))));

			if (line.substr(0, line.find(" : ")) == "Weapon")
				_joueur.Get_Inventory().Add_Weapon(Weapon(Weapons.Get_Weapon(line.substr(line.find(" : ") + 3))));

			if (line.substr(0, line.find(" : ")) == "Armor")
				_joueur.Get_Inventory().Add_Armor(Armor(Armors.Get_Armor(line.substr(line.find(" : ") + 3))));
			
			if (line.substr(0, line.find(" : ")) == "Consumable")
				_joueur.Get_Inventory().Add_Consumable(Consumable(Consumables.Get_Consumable(line.substr(line.find(" : ") + 3))));

			if (line.substr(0, line.find(" : ")) == "Dungeon")
				for (Dungeon& Current : _w.Get_Dungeon())
				{
					if (Current.Get_Name() == line.substr(line.find(" : ") + line.find(" ")))
					{
						if (line.find("0"))
							Current.Set_Finish(false);
						else if (line.find("1"))
							Current.Set_Finish(true);
					}
				}
		}
		Load_Hero.close();
	}
}