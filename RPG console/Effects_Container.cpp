#include "Effects_Container.h"

Effects_Container Effects;

Effects_Container::Effects_Container()
{

}

void Effects_Container::init()
{
	Container.push_back(Effect("Pas d effet", Element::Neutre, Affect_Stat::NONE, 0, 0, 1));

	Container.push_back(Effect("Embrassement", Element::Feu, Affect_Stat::LIFE_POINT, 3, 1, 1));
	Container.push_back(Effect("Eclaboussure", Element::Eau, Affect_Stat::MANA, 5, 1, 1));
	Container.push_back(Effect("Rafale", Element::Air, Affect_Stat::ENDURANCE, 10, 1, 1));
	Container.push_back(Effect("Seisme", Element::Terre, Affect_Stat::SPEED, 5, 2, 1));
	Container.push_back(Effect("Legendaire", Element::Neutre , Affect_Stat::LIFE_POINT, 7, 1, 1));

	Container.push_back(Effect("Fire_Resist", Element::Feu, Affect_Stat::LIFE_POINT, 5, 1, 1));
	Container.push_back(Effect("Water_Resist", Element::Eau, Affect_Stat::MANA, 5, 1, 1));
	Container.push_back(Effect("Air_Resist", Element::Air, Affect_Stat::SPEED, 5, 1, 1));
	Container.push_back(Effect("Earth_Resist", Element::Terre, Affect_Stat::ENDURANCE, 5, 1, 1));

	Container.push_back(Effect("Soin", Element::Neutre, Affect_Stat::LIFE_POINT, 5, 0, 1));
	Container.push_back(Effect("Mana", Element::Neutre, Affect_Stat::MANA, 5, 0, 1));
	Container.push_back(Effect("Endurance", Element::Neutre, Affect_Stat::ENDURANCE, 5, 0, 1));

	Container.push_back(Effect("Feu 1", Element::Feu, Affect_Stat::LIFE_POINT, 2, 2, 1));
	Container.push_back(Effect("Feu 2", Element::Feu, Affect_Stat::LIFE_POINT, 2, 2, 2));
	Container.push_back(Effect("Feu 3", Element::Feu, Affect_Stat::LIFE_POINT, 2, 3, 3));
	Container.push_back(Effect("Feu 4", Element::Feu, Affect_Stat::LIFE_POINT, 2, 3, 4));

	Container.push_back(Effect("Eau 1", Element::Eau, Affect_Stat::MANA, 5, 0, 1));
	Container.push_back(Effect("Eau 2", Element::Eau, Affect_Stat::MANA, 5, 0, 2));
	Container.push_back(Effect("Eau 3", Element::Eau, Affect_Stat::MANA, 5, 0, 3));
	Container.push_back(Effect("Eau 4", Element::Eau, Affect_Stat::MANA, 5, 0, 4));

	Container.push_back(Effect("Air 1", Element::Air, Affect_Stat::SPEED, 5, 1, 1));
	Container.push_back(Effect("Air 2", Element::Air, Affect_Stat::SPEED, 5, 1, 2));
	Container.push_back(Effect("Air 3", Element::Air, Affect_Stat::SPEED, 5, 2, 3));
	Container.push_back(Effect("Air 4", Element::Air, Affect_Stat::SPEED, 5, 2, 4));

	Container.push_back(Effect("Terre 1", Element::Terre, Affect_Stat::ENDURANCE, 5, 0, 1));
	Container.push_back(Effect("Terre 2", Element::Terre, Affect_Stat::ENDURANCE, 5, 0, 2));
	Container.push_back(Effect("Terre 3", Element::Terre, Affect_Stat::ENDURANCE, 5, 0, 3));
	Container.push_back(Effect("Terre 4", Element::Terre, Affect_Stat::ENDURANCE, 5, 0, 4));

	Container.push_back(Effect("Soin 1", Element::Neutre, Affect_Stat::LIFE_POINT, 5, 0, 1));
	Container.push_back(Effect("Soin 2", Element::Neutre, Affect_Stat::LIFE_POINT, 3, 0, 2));
	Container.push_back(Effect("Soin 3", Element::Neutre, Affect_Stat::LIFE_POINT, 3, 0, 3));
	Container.push_back(Effect("Soin 4", Element::Neutre, Affect_Stat::LIFE_POINT, 3, 0, 4));
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
			Affect_Stat tmpstate;
			int tmppower;
			int tmpduration;
			int tmplevel;

			tmpname = line.substr(0, line.find(" "));
			line.erase(0, line.find(" ") + 1);

			tmpelement = static_cast<Element>(stoi(line.substr(0, line.find(" "))));
			line.erase(0, line.find(" ") + 1);

			tmpstate = static_cast<Affect_Stat>(stoi(line.substr(0, line.find(" "))));
			line.erase(0, line.find(" ") + 1);

			tmppower = stoi(line.substr(0, line.find(" ")));
			line.erase(0, line.find(" ") + 1);

			tmpduration = stoi(line.substr(0, line.find(" ")));
			line.erase(0, line.find(" ") + 1);

			tmplevel = stoi(line);
			line.erase(0, line.size());

			Container.push_back(Effect(tmpname, tmpelement, tmpstate, tmppower, tmpduration, tmplevel));
		}

		Load_Effect.close();
	}
}