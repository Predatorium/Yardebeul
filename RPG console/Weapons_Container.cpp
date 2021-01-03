#include "Weapons_Container.h"
#include "Effects_Container.h"

Weapons_Container Weapons;

Weapons_Container::Weapons_Container()
{

}

void Weapons_Container::init()
{
	Container.push_back(Weapon(5, "Epee", Effects.Get_Effect("Pas d effet")));
	Container.push_back(Weapon(10, "Epee de feu", Effects.Get_Effect("Embrassement")));
	Container.push_back(Weapon(10, "Epee d eau", Effects.Get_Effect("Eclaboussure")));
	Container.push_back(Weapon(10, "Epee d air", Effects.Get_Effect("Rafale")));
	Container.push_back(Weapon(10, "Epee de terre", Effects.Get_Effect("Seisme")));
	Container.push_back(Weapon(15, "Epee legendaire", Effects.Get_Effect("Legendaire")));
}

Weapon Weapons_Container::Get_Weapon(string _name)
{
	for (Weapon& Actual_Weapon : Container)
		if (Actual_Weapon.Get_Name() == _name)
			return Actual_Weapon;
}

void Weapons_Container::Save()
{
	ofstream Save_Weapon("../Ressources/Container/Weapon.txt");
	if (Save_Weapon.is_open())
	{
		for (list<Weapon>::iterator Current = Container.begin(); Current != Container.end(); Current++)
		{
			Save_Weapon << Current->Get_Name() << " ";
			Save_Weapon << to_string(Current->Damage()) << " ";
			Save_Weapon << Current->Get_Effect().Get_Name();

			if (Current != Container.end())
				Save_Weapon << endl;
		}
		Save_Weapon.close();
	}

}

void Weapons_Container::Load()
{
	ifstream Load_Weapon("../Ressources/Container/Weapon.txt");
	if (Load_Weapon.is_open())
	{
		string line = "0";
		while (getline(Load_Weapon, line))
		{
			string tmpname;
			int tmpdegat;
			int tmpdurabilite;
			string tmpname_effect;

			tmpname = line.substr(0, line.find(" "));
			line.erase(0, line.find(" ") + 1);

			tmpdegat = stoi(line.substr(0, line.find(" ")));
			line.erase(0, line.find(" ") + 1);

			tmpname_effect = line;
			line.erase(0, line.size());

			Container.push_back(Weapon(tmpdegat, tmpname, Effects.Get_Effect(tmpname_effect)));
		}

		Load_Weapon.close();
	}
}