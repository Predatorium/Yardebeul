#include "Armors_Container.h"
#include "Effects_Container.h"

Armors_Container Armors;

Armors_Container::Armors_Container()
{
}

void Armors_Container::init()
{
	Container.push_back(Armor(20, "Armor", Effects.Get_Effect("Pas d effet")));
	Container.push_back(Armor(20, "Armor fire", Effects.Get_Effect("Fire_Resist")));
	Container.push_back(Armor(20, "Armor water", Effects.Get_Effect("Water_Resist")));
	Container.push_back(Armor(20, "Armor air", Effects.Get_Effect("Air_Resist")));
	Container.push_back(Armor(20, "Armor earth", Effects.Get_Effect("Earth_Resist")));
}

Armor Armors_Container::Get_Armor(string _name)
{
	for (Armor& Actual_Armor : Container)
		if (Actual_Armor.Get_Name() == _name)
			return Actual_Armor;
}

void Armors_Container::Save()
{
	ofstream Save_Armor("../Ressources/Container/Armor.txt");
	if (Save_Armor.is_open())
	{
		for (list<Armor>::iterator Current = Container.begin(); Current != Container.end(); Current++)
		{
			Save_Armor << Current->Get_Name() << " ";
			Save_Armor << to_string(Current->Get_Defense()) << " ";
			Save_Armor << Current->Get_Effect().Get_Name();

			if (Current != Container.end())
				Save_Armor << endl;
		}
		Save_Armor.close();
	}
}

void Armors_Container::Load()
{
	ifstream Load_Armor("../Ressources/Container/Armor.txt");
	if (Load_Armor.is_open())
	{
		string line = "0";
		while (getline(Load_Armor, line))
		{
			string tmpname;
			int tmpdefense;
			string tmpname_effect;

			tmpname = line.substr(0, line.find(" "));
			line.erase(0, line.find(" ") + 1);

			tmpdefense = stoi(line.substr(0, line.find(" ")));
			line.erase(0, line.find(" ") + 1);

			tmpname_effect = line;
			line.erase(0, line.size());

			Container.push_back(Armor(tmpdefense, tmpname, Effects.Get_Effect(tmpname_effect)));
		}

		Load_Armor.close();
	}
}