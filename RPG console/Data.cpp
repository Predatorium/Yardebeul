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
		Save_Hero << "Niveau : " << _joueur.Get_Niveau() << endl;
		Save_Hero << "Time : " << _joueur.Get_Time() << endl;
		Save_Hero << "Position : " << _joueur.Get_Position().x << "|" << _joueur.Get_Position().y << endl;
		Save_Hero << "Point de vie : " << _joueur.Get_Vie() << endl;
		Save_Hero << "Mana : " << _joueur.Get_Mana() << endl;
		Save_Hero << "Sante Mental : " << _joueur.Get_SanteMental() << endl;
		Save_Hero << "Vitesse : " << _joueur.Get_Vitesse() << endl;
		Save_Hero << "XpTotal : " << _joueur.Get_Xptotal() << endl;
		Save_Hero << "XpNiveau : " << _joueur.Get_XpNiveau() << endl;
		Save_Hero << "Capacité : " << _joueur.Get_PointCapacity() << endl;
		Save_Hero << "Argent : " << _joueur.Get_Argent();

		if (_joueur.Get_Weapon() != nullptr)
		{
			Save_Hero << endl;
			Save_Hero << "Weapon : " << _joueur.Get_Weapon()->Get_Name() << " ";
		}

		if (_joueur.Get_Armor() != nullptr)
		{
			Save_Hero << endl;
			Save_Hero << "Armor : " << _joueur.Get_Armor()->Get_Name() << " ";
		}

		for (Consumable* Current_Consu : _joueur.Get_Consumable())
		{
			Save_Hero << endl;
			Save_Hero << "Consumable : " << Current_Consu->Get_Name() << "|";
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

			if (line.substr(0, line.find(" : ")) == "Niveau")
				_joueur.Set_Niveau(stoi(line.substr(line.find(" : ") + 3)));

			if (line.substr(0, line.find(" : ")) == "Time")
				_joueur.Set_Time(stof(line.substr(line.find(" : ") + 3)));

			if (line.substr(0, line.find(" : ")) == "Position")
				_joueur.Set_Position(Vector2f(stof(line.substr(line.find(" : ") + 3)), stof(line.substr(line.find("|") + 1))));

			if (line.substr(0, line.find(" : ")) == "Point de vie")
				_joueur.Set_Vie(stoi(line.substr(line.find(" : ") + 3)));

			if (line.substr(0, line.find(" : ")) == "Mana")
				_joueur.Set_Mana(stoi(line.substr(line.find(" : ") + 3)));

			if (line.substr(0, line.find(" : ")) == "Sante Mental")
				_joueur.Set_SanteMental(stoi(line.substr(line.find(" : ") + 3)));

			if (line.substr(0, line.find(" : ")) == "Vitesse")
				_joueur.Set_Vitesse(stoi(line.substr(line.find(" : ") + 3)));

			if (line.substr(0, line.find(" : ")) == "XpTotal")
				_joueur.Set_XpTotal(stof(line.substr(line.find(" : ") + 3)));

			if (line.substr(0, line.find(" : ")) == "XpNiveau")
				_joueur.Set_XpNiveau(stof(line.substr(line.find(" : ") + 3)));

			if (line.substr(0, line.find(" : ")) == "Capacité")
				_joueur.Set_Capa(stoi(line.substr(line.find(" : ") + 3)));

			if (line.substr(0, line.find(" : ")) == "Argent")
				_joueur.Set_Argent(stoi(line.substr(line.find(" : ") + 3)));

			if (line.substr(0, line.find(" : ")) == "Weapon")
				_joueur.Set_Arme(Weapon(Weapons.Get_Weapon(line.substr(line.find(" : ") + 3))));

			if (line.substr(0, line.find(" : ")) == "Armor")
				_joueur.Set_Armure(Armor(Armors.Get_Armor(line.substr(line.find(" : ") + 3))));
			
			if (line.substr(0, line.find(" : ")) == "Consumable")
				_joueur.Set_Consommable(Consumable(Consumables.Get_Consumable(line.substr(line.find(" : ") + 3))));
			
		}
		Load_Hero.close();
	}
}