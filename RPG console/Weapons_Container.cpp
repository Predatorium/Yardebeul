#include "Weapons_Container.h"
#include "Effects_Container.h"

Weapons_Container Weapons;

Weapons_Container::Weapons_Container()
{
	Container.push_back(Weapon(2, 10, "Epee de feu", 100, Effects.Get_Effet("Embrassement")));
	Container.push_back(Weapon(4, 20, "Epee de lave", 200, Effects.Get_Effet("Volcan")));
	Container.push_back(Weapon(2, 10, "Epee d eau", 100, Effects.Get_Effet("Eclaboussure")));
	Container.push_back(Weapon(4, 20, "Epee de glace", 200, Effects.Get_Effet("Engelure")));
	Container.push_back(Weapon(2, 10, "Epee d air", 100, Effects.Get_Effet("Rafale")));
	Container.push_back(Weapon(4, 20, "Epee de foudre", 200, Effects.Get_Effet("Electrocution")));
	Container.push_back(Weapon(2, 10, "Epee de terre", 100, Effects.Get_Effet("Seisme")));
	Container.push_back(Weapon(4, 20, "Epee de gravité", 200, Effects.Get_Effet("Trou noir")));
}

Weapon Weapons_Container::Get_Weapon(string _name)
{
	for (Weapon& Actual_Weapon : Container)
		if (Actual_Weapon.Get_Name() == _name)
			return Actual_Weapon;
}

void Weapons_Container::Save()
{
	ofstream Save_Weapon("../Ressources/Containers/Weapon.txt");
	if (Save_Weapon.is_open())
	{
		for (list<Weapon>::iterator Current_Weapon=Container.begin(); Current_Weapon != Container.end(); Current_Weapon++)
		{
			Save_Weapon << Current_Weapon->Get_Name() << " ";
			Save_Weapon << to_string(Current_Weapon->Get_Prix()) << " ";
			Save_Weapon << to_string(Current_Weapon->get_degat()) << " ";
			Save_Weapon << to_string(Current_Weapon->get_durabitlité()) << " ";
			Save_Weapon << Current_Weapon->Get_Effet().Get_Name();

			if (Current_Weapon != Container.end())
				Save_Weapon << endl;
		}
		Save_Weapon.close();
	}

}

void Weapons_Container::Load()
{
	ifstream Load_Weapon("../Ressources/Containers/Weapon.txt");
	if (Load_Weapon.is_open())
	{
		string line = "0";
		while (getline(Load_Weapon, line))
		{
			string tmpname;
			int tmpprix;
			int tmpdegat;
			int tmpdurabilite;
			string tmpname_effect;

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

			Container.push_back(Weapon(tmpdegat, tmpdurabilite, tmpname, tmpprix, Effects.Get_Effet(tmpname_effect)));
		}

		Load_Weapon.close();
	}
}