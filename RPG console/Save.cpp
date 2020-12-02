#include "Save.h"
#include "Weapons_Container.h"
#include "Armors_Container.h"
#include "Consumables_Container.h"
#include "Effects_Container.h"

void Save::Save_World(int _party, World _world)
{
	string path;
	if (_party == 1)
		path = "../Ressources/Infos/World1.txt";
	if (_party == 2)
		path = "../Ressources/Infos/World2.txt";
	if (_party == 3)
		path = "../Ressources/Infos/World3.txt";

	ofstream Save_World(path);
	if (Save_World.is_open())
	{
		Save_World << _world.Get_Name() << endl;
		Save_World << _world.Get_Time() << endl;

		for (Dungeon& Current_Dugeon : _world.Get_Dungeon())
			Save_World << Current_Dugeon.Get_Finished() << endl;

		Save_World.close();
	}
}

void Save::Save_Player(int _party, Hero _joueur)
{
	string path;
	if (_party == 1)
		path = "../Ressources/Infos/Hero1.txt";
	if (_party == 2)
		path = "../Ressources/Infos/Hero2.txt";
	if (_party == 3)
		path = "../Ressources/Infos/Hero3.txt";

	ofstream Save_Hero(path);
	if (Save_Hero.is_open())
	{
		Save_Hero << _joueur.Get_Position().x << endl;
		Save_Hero << _joueur.Get_Position().y << endl;
		Save_Hero << _joueur.Get_Name() << endl;
		Save_Hero << _joueur.Get_Niveau() << endl;
		Save_Hero << _joueur.Get_Vie() << endl;
		Save_Hero << _joueur.Get_Mana() << endl;
		Save_Hero << _joueur.Get_SanteMental() << endl;
		Save_Hero << _joueur.Get_Vitesse() << endl;
		Save_Hero << _joueur.Get_Xptotal() << endl;
		Save_Hero << _joueur.Get_XpNiveau() << endl;
		Save_Hero << _joueur.Get_PointCapacity() << endl;
		Save_Hero << _joueur.Get_Argent();

		if (_joueur.Get_Weapon() != nullptr)
		{
			Save_Hero << endl;
			Save_Hero << _joueur.Get_Weapon()->Get_Name() << " ";
			Save_Hero << _joueur.Get_Weapon()->Get_Prix() << " ";
			Save_Hero << _joueur.Get_Weapon()->get_degat() << " ";
			Save_Hero << _joueur.Get_Weapon()->get_durabitlité() << " ";
			Save_Hero << _joueur.Get_Weapon()->Get_Effet().Get_Name();
		}

		if (_joueur.Get_Armor() != nullptr)
		{
			Save_Hero << endl;
			Save_Hero << _joueur.Get_Armor()->Get_Name() << " ";
			Save_Hero << _joueur.Get_Armor()->Get_Prix() << " ";
			Save_Hero << _joueur.Get_Armor()->Get_Defenses() << " ";
			Save_Hero << _joueur.Get_Armor()->Get_Durabilité() << " ";
			Save_Hero << _joueur.Get_Armor()->Get_Effet().Get_Name();
		}

		for (Consumable* Current_Consu : _joueur.Get_Consumable())
		{
			Save_Hero << endl;
			Save_Hero << Current_Consu->Get_Name() << " ";
			Save_Hero << Current_Consu->Get_Prix() << " ";
			Save_Hero << Current_Consu->Get_Effet().Get_Name() << "|";
		}

		Save_Hero.close();
	}
}

void Load::Load_World(int _party, World& _world)
{
	string path;
	if (_party == 1)
		path = "../Ressources/Infos/World1.txt";
	if (_party == 2)
		path = "../Ressources/Infos/World2.txt";
	if (_party == 3)
		path = "../Ressources/Infos/World3.txt";

	string tmpname;
	float tmptime;

	_world = World();

	ifstream Load_World(path);
	if (Load_World.is_open())
	{
		Load_World >> tmpname;
		_world.Set_Name(tmpname);
		Load_World >> tmptime;
		_world.Set_Time(tmptime);

		Load_World.close();
	}
}

void Load::Load_Player(int _party, Hero& _joueur)
{
	string path;
	if (_party == 1)
		path = "../Ressources/Infos/Hero1.txt";
	if (_party == 2)
		path = "../Ressources/Infos/Hero2.txt";
	if (_party == 3)
		path = "../Ressources/Infos/Hero3.txt";

	_joueur = Hero(Vector2f(100,100));

	Vector2f tmppos;
	string tmpname;
	int tmp;
	float tmpfloat;

	ifstream Load_Hero(path);
	if (Load_Hero.is_open())
	{
		Load_Hero >> tmppos.x;
		Load_Hero >> tmppos.y;
		_joueur.Set_Position(tmppos);
		Load_Hero >> tmpname;
		_joueur.Set_Name(tmpname);
		Load_Hero >> tmp;
		_joueur.Set_Niveau(tmp);
		Load_Hero >> tmp;
		_joueur.Set_PV(tmp);
		Load_Hero >> tmp;
		_joueur.Set_Mana(tmp);
		Load_Hero >> tmp;
		_joueur.Set_Mental(tmp);
		Load_Hero >> tmp;
		_joueur.Set_Vitesse(tmp);
		Load_Hero >> tmpfloat;
		_joueur.Set_XpTotal(tmpfloat);
		Load_Hero >> tmpfloat;
		_joueur.Set_XpNiveau(tmpfloat);
		Load_Hero >> tmp;
		_joueur.Set_Capa(tmp);
		Load_Hero >> tmp;
		_joueur.Set_Argent(tmp);

		string line = "0";
		int i = 0;
		while (getline(Load_Hero, line))
		{
			string tmpname = "0";
			int tmpprix = 0;
			string tmpname_effect = "0";

			if (i == 0)
			{
				int tmpdegat;
				int tmpdurabilite;

				tmpname = line.substr(0, line.find(" "));
				line.erase(0, line.find(" ") + 1);

				tmpprix = stoi(line.substr(0, line.find(" ")));
				line.erase(0, line.find(" ") + 1);

				tmpdegat = stoi(line.substr(0, line.find(" ")));
				line.erase(0, line.find(" ") + 1);

				tmpdurabilite = stoi(line.substr(0, line.find(" ")));
				line.erase(0, line.find(" ") + 1);

				tmpname_effect = line;
				line.erase(0, line.size());

				_joueur.Set_Arme(Weapon(tmpdegat, tmpdurabilite, tmpname, tmpprix, Effects.Get_Effet(tmpname_effect)));
			}
			if (i == 1)
			{
				int tmpdefense;
				int tmpdurabilite;

				tmpname = line.substr(0, line.find(" "));
				line.erase(0, line.find(" ") + 1);

				tmpprix = stoi(line.substr(0, line.find(" ")));
				line.erase(0, line.find(" ") + 1);

				tmpdefense = stoi(line.substr(0, line.find(" ")));
				line.erase(0, line.find(" ") + 1);

				tmpdurabilite = stoi(line.substr(0, line.find(" ")));
				line.erase(0, line.find(" ") + 1);

				tmpname_effect = line;
				line.erase(0, line.size());

				_joueur.Set_Armure(Armor(tmpdefense, tmpdurabilite, tmpname, tmpprix, Effects.Get_Effet(tmpname_effect)));
			}
			if (i > 1)
			{
				tmpname = line.substr(0, line.find(" "));
				line.erase(0, line.find(" ") + 1);

				tmpprix = stoi(line.substr(0, line.find(" ")));
				line.erase(0, line.find(" ") + 1);

				tmpname_effect = line;
				line.erase(0, line.size());

				_joueur.Set_Consommable(Consumable(tmpname, tmpprix, Effects.Get_Effet(tmpname_effect)));
			}
			i++;
		}
		Load_Hero.close();
	}
}