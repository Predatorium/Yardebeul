#include "Consumables_Container.h"
#include "Effects_Container.h"

Consumables_Container Consumables;

Consumables_Container::Consumables_Container()
{
	Container.push_back(Consumable());
}

Consumable Consumables_Container::Get_Consumable(string _name)
{
	for (Consumable Actual_Consumable : Container)
		if (Actual_Consumable.Get_Name() == _name)
			return Actual_Consumable;
}

void Consumables_Container::Save()
{
	ofstream Save_Consumable("../Ressources/Containers/Consumable.txt");
	if (Save_Consumable.is_open())
	{
		for (list<Consumable>::iterator Current_Weapon = Container.begin(); Current_Weapon != Container.end(); Current_Weapon++)
		{
			Save_Consumable << Current_Weapon->Get_Name() << " ";
			Save_Consumable << to_string(Current_Weapon->Get_Prix()) << " ";
			Save_Consumable << Current_Weapon->Get_Effet().Get_Name();

			if (Current_Weapon != Container.end())
				Save_Consumable << endl;
		}
		Save_Consumable.close();
	}

}

void Consumables_Container::Load()
{
	ifstream Load_Consumable("../Ressources/Containers/Consumable.txt");
	if (Load_Consumable.is_open())
	{
		string line = "0";
		while (getline(Load_Consumable, line))
		{
			string tmpname;
			int tmpprix;
			string tmpname_effect;

			tmpname = line.substr(0, line.find(" "));
			line.erase(0, line.find(" ") + 1);

			tmpprix = stoi(line.substr(0, line.find(" ")));
			line.erase(0, line.find(" ") + 1);

			tmpname_effect = line;
			line.erase(0, line.size());

			Container.push_back(Consumable(tmpname, tmpprix, Effects.Get_Effet(tmpname_effect)));
		}

		Load_Consumable.close();
	}
}