#include "Data.h"
#include "Weapons_Container.h"
#include "Armors_Container.h"
#include "Consumables_Container.h"
#include "Effects_Container.h"

void Data::Save_Player(int _party, Hero _joueur)
{
	string path;
	if (_party == 1)
		path = "../Ressources/Infos/Save1.txt";
	if (_party == 2)
		path = "../Ressources/Infos/Save2.txt";
	if (_party == 3)
		path = "../Ressources/Infos/Save3.txt";

	ofstream Save_Hero(path);
	if (Save_Hero.is_open())
	{
		Save_Hero << "Name : " << _joueur.Get_Name() << endl;
		Save_Hero << "Level : " << _joueur.Get_Level() << endl;
		Save_Hero << "Time : " << _joueur.Get_Time() << endl;
		Save_Hero << "Position : " << _joueur.Get_Position().x << "|" << _joueur.Get_Position().y << endl;
		Save_Hero << "Life Point : " << _joueur.Get_LifePoint() << endl;
		Save_Hero << "Mana : " << _joueur.Get_Mana() << endl;
		Save_Hero << "Mental Health : " << _joueur.Get_MentalHealth() << endl;
		Save_Hero << "Speed : " << _joueur.Get_Speed() << endl;
		Save_Hero << "XpTotal : " << _joueur.Get_Xptotal() << endl;
		Save_Hero << "XpLevel : " << _joueur.Get_XpLevel() << endl;
		Save_Hero << "Capacity : " << _joueur.Get_PointCapacity() << endl;
		Save_Hero << "Gold : " << _joueur.Get_Gold();

		for (Weapon* Current : _joueur.Get_Weapon())
		{
			Save_Hero << endl;
			Save_Hero << "Weapon : " << Current->Get_Name();
		}

		for (Armor* Current : _joueur.Get_Armor())
		{
			Save_Hero << endl;
			Save_Hero << "Armor : " << Current->Get_Name();
		}

		for (Consumable* Current_Consu : _joueur.Get_Consumable())
		{
			Save_Hero << endl;
			Save_Hero << "Consumable : " << Current_Consu->Get_Name();
		}

		Save_Hero.close();
	}
}

void Data::Load_Player(int _party, Hero& _joueur)
{
	string path;
	if (_party == 1)
		path = "../Ressources/Infos/Save1.txt";
	if (_party == 2)
		path = "../Ressources/Infos/Save2.txt";
	if (_party == 3)
		path = "../Ressources/Infos/Save3.txt";

	_joueur = Hero(Vector2f(100,100));

	string line = "0";

	ifstream Load_Hero(path);
	if (Load_Hero.is_open())
	{
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

			if (line.substr(0, line.find(" : ")) == "Mental Health")
				_joueur.Set_MentalHealth(stoi(line.substr(line.find(" : ") + 3)));

			if (line.substr(0, line.find(" : ")) == "Speed")
				_joueur.Set_Speed(stoi(line.substr(line.find(" : ") + 3)));

			if (line.substr(0, line.find(" : ")) == "XpTotal")
				_joueur.Set_XpTotal(stof(line.substr(line.find(" : ") + 3)));

			if (line.substr(0, line.find(" : ")) == "XpLevel")
				_joueur.Set_XpLevel(stof(line.substr(line.find(" : ") + 3)));

			if (line.substr(0, line.find(" : ")) == "Capacity")
				_joueur.Set_CapacityPoint(stoi(line.substr(line.find(" : ") + 3)));

			if (line.substr(0, line.find(" : ")) == "Gold")
				_joueur.Set_Gold(stoi(line.substr(line.find(" : ") + 3)));

			if (line.substr(0, line.find(" : ")) == "Weapon")
				_joueur.Add_Weapon(Weapon(Weapons.Get_Weapon(line.substr(line.find(" : ") + 3))));

			if (line.substr(0, line.find(" : ")) == "Armor")
				_joueur.Add_Armor(Armor(Armors.Get_Armor(line.substr(line.find(" : ") + 3))));
			
			if (line.substr(0, line.find(" : ")) == "Consumable")
				_joueur.Add_Consumable(Consumable(Consumables.Get_Consumable(line.substr(line.find(" : ") + 3))));
			
		}
		Load_Hero.close();
	}
}