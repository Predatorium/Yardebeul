#include "Consumables_Container.h"
#include "Effects_Container.h"

Consumables_Container Consumables;

Consumables_Container::Consumables_Container()
{
}

void Consumables_Container::init()
{
	Container.push_back(Consumable("Potion Soin", 1, Effects.Get_Effect("Soin")));
	Container.push_back(Consumable("Potion Mana", 1, Effects.Get_Effect("Mana")));
	Container.push_back(Consumable("Potion Endu", 1, Effects.Get_Effect("Endurance")));
}

Consumable Consumables_Container::Get_Consumable(string _name)
{
	for (Consumable Actual_Consumable : Container)
		if (Actual_Consumable.Get_Name() == _name)
			return Actual_Consumable;
}

void Consumables_Container::Save()
{
	ofstream Save_Consumable("../Ressources/Container/Consumable.txt");
	if (Save_Consumable.is_open())
	{
		for (list<Consumable>::iterator Current = Container.begin(); Current != Container.end(); Current++)
		{
			Save_Consumable << Current->Get_Name() << " ";
			Save_Consumable << Current->Get_Number() << " ";
			Save_Consumable << Current->Get_Effect().Get_Name();

			if (Current != Container.end())
				Save_Consumable << endl;
		}
		Save_Consumable.close();
	}

}

void Consumables_Container::Load()
{
	ifstream Load_Consumable("../Ressources/Container/Consumable.txt");
	if (Load_Consumable.is_open())
	{
		string line = "0";
		while (getline(Load_Consumable, line))
		{
			string tmpname;
			int tmpnumber;
			string tmpname_effect;

			tmpname = line.substr(0, line.find(" "));
			line.erase(0, line.find(" ") + 1);

			tmpnumber = stoi(line.substr(0, line.find(" ")));
			line.erase(0, line.find(" ") + 1);

			tmpname_effect = line;
			line.erase(0, line.size());

			Container.push_back(Consumable(tmpname, tmpnumber, Effects.Get_Effect(tmpname_effect)));
		}

		Load_Consumable.close();
	}
}