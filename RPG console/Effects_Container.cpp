#include "Effects_Container.h"

Effects_Container Effects;

Effects_Container::Effects_Container()
{

}

void Effects_Container::init()
{
	Container.push_back(Effect("Embrassement", Element::Feu, Range_Effect::AOE, Affect_Stat::LIFE_POINT, 10, 2));
	Container.push_back(Effect("Eclaboussure", Element::Eau, Range_Effect::Multicible, Affect_Stat::SPEED, 5, 4));
	Container.push_back(Effect("Rafale", Element::Air, Range_Effect::AOE, Affect_Stat::ENDURANCE, 10, 1));
	Container.push_back(Effect("Seisme", Element::Terre, Range_Effect::Monocible, Affect_Stat::MENTAL_HEALTH, 5, 2));
	Container.push_back(Effect("Soin", Element::Neutre, Range_Effect::Monocible, Affect_Stat::LIFE_POINT, -20, 0));
}

Effect Effects_Container::Get_Effect(string _name)
{
	for (Effect& Current_Effect : Container)
		if (Current_Effect.Get_Name() == _name)
			return Current_Effect;
}

void Effects_Container::Save()
{
	ofstream Save_Effect("../Ressources/Container/Effect.txt");
	if (Save_Effect.is_open())
	{
		for (list<Effect>::iterator Current = Container.begin(); Current != Container.end(); Current++)
		{
			Save_Effect << Current->Get_Name() << " ";
			Save_Effect << Current->Get_Duration() << " ";
			Save_Effect << static_cast<int>(Current->Get_Affectation()) << " ";
			Save_Effect << static_cast<int>(Current->Get_Range()) << " ";
			Save_Effect << static_cast<int>(Current->Get_Element()) << " ";
			Save_Effect << Current->Get_Power();

			if (Current != Container.end())
				Save_Effect << endl;
		}
		Save_Effect.close();
	}

}

void Effects_Container::Load()
{
	ifstream Load_Effect("../Ressources/Container/Effect.txt");
	if (Load_Effect.is_open())
	{
		string line = "0";
		while (getline(Load_Effect, line))
		{
			string tmpname;
			Element tmpelement;
			Range_Effect tmprange;
			Affect_Stat tmpstate;
			int tmppower;
			int tmpduration;

			tmpname = line.substr(0, line.find(" "));
			line.erase(0, line.find(" ") + 1);

			tmpelement = static_cast<Element>(stoi(line.substr(0, line.find(" "))));
			line.erase(0, line.find(" ") + 1);

			tmprange = static_cast<Range_Effect>(stoi(line.substr(0, line.find(" "))));
			line.erase(0, line.find(" ") + 1);

			tmpstate = static_cast<Affect_Stat>(stoi(line.substr(0, line.find(" "))));
			line.erase(0, line.find(" ") + 1);

			tmppower = stoi(line.substr(0, line.find(" ")));
			line.erase(0, line.find(" ") + 1);

			tmpduration = stoi(line);
			line.erase(0, line.size());

			Container.push_back(Effect(tmpname, tmpelement, tmprange, tmpstate, tmppower, tmpduration));
		}

		Load_Effect.close();
	}
}