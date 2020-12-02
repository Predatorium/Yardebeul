#include "Effects_Container.h"

Effects_Container Effects;

Effects_Container::Effects_Container()
{
	Container.push_back(Effect("Embrassement", Element::Feu, Range_Effect::AOE, Affect_Stat::PV, 10, 2));
	Container.push_back(Effect("Volcan", Element::Lave, Range_Effect::AOE, Affect_Stat::PV, 20, 5));
	Container.push_back(Effect("Eclaboussure", Element::Eau, Range_Effect::Multicible, Affect_Stat::VITESSE, 5, 4));
	Container.push_back(Effect("Engelure", Element::Glace, Range_Effect::Multicible, Affect_Stat::VITESSE, 10, 8));
	Container.push_back(Effect("Rafale", Element::Air, Range_Effect::AOE, Affect_Stat::ENDURANCE, 10, 1));
	Container.push_back(Effect("Electrocution", Element::Foudre, Range_Effect::AOE, Affect_Stat::ENDURANCE, 20, 0.5));
	Container.push_back(Effect("Seisme", Element::Terre, Range_Effect::Monocible, Affect_Stat::SANTE_MENTAL, 5, 2));
	Container.push_back(Effect("Trou noir", Element::Gravité, Range_Effect::Monocible, Affect_Stat::SANTE_MENTAL, 10, 0.5));
	Container.push_back(Effect("Soin", Element::Neutre, Range_Effect::Monocible, Affect_Stat::PV, -20, 0));
}

Effect Effects_Container::Get_Effet(string _name)
{
	for (Effect& Actual_Effect : Container)
		if (Actual_Effect.Get_Name() == _name)
			return Actual_Effect;
}

void Effects_Container::Save()
{
	ofstream Save_Effect("../Ressources/Containers/Effect.txt");
	if (Save_Effect.is_open())
	{
		for (list<Effect>::iterator Current_Weapon = Container.begin(); Current_Weapon != Container.end(); Current_Weapon++)
		{
			Save_Effect << Current_Weapon->Get_Name() << " ";
			Save_Effect << Current_Weapon->Get_Durée() << " ";
			Save_Effect << static_cast<int>(Current_Weapon->Get_Affectation()) << " ";
			Save_Effect << static_cast<int>(Current_Weapon->Get_Range()) << " ";
			Save_Effect << static_cast<int>(Current_Weapon->Get_Element()) << " ";
			Save_Effect << Current_Weapon->Get_Puissance() << " ";
			Save_Effect << Current_Weapon->Get_Durée() << " ";

			if (Current_Weapon != Container.end())
				Save_Effect << endl;
		}
		Save_Effect.close();
	}

}

void Effects_Container::Load()
{
	ifstream Load_Effect("../Ressources/Containers/Effect.txt");
	if (Load_Effect.is_open())
	{
		string line = "0";
		while (getline(Load_Effect, line))
		{
			string tmpname;
			Element tmpelement;
			Range_Effect tmprange;
			Affect_Stat tmpstate;
			int tmppuissance;
			float tmpdurée;

			tmpname = line.substr(0, line.find(" "));
			line.erase(0, line.find(" ") + 1);

			tmpelement = static_cast<Element>(stoi(line.substr(0, line.find(" "))));
			line.erase(0, line.find(" ") + 1);

			tmprange = static_cast<Range_Effect>(stoi(line.substr(0, line.find(" "))));
			line.erase(0, line.find(" ") + 1);

			tmpstate = static_cast<Affect_Stat>(stoi(line.substr(0, line.find(" "))));
			line.erase(0, line.find(" ") + 1);

			tmppuissance = stoi(line.substr(0, line.find(" ")));
			line.erase(0, line.find(" ") + 1);

			tmpdurée = stof(line);
			line.erase(0, line.size());

			Container.push_back(Effect(tmpname, tmpelement, tmprange, tmpstate, tmppuissance, tmpdurée));
		}

		Load_Effect.close();
	}
}