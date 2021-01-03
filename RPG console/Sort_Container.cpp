#include "Sort_Container.h"
#include "Effects_Container.h"

Sort_Container Sorts;

void Sort_Container::init()
{
	Container.push_back(Sort("Immolation 1", 5, Target::Actif, Effects.Get_Effect("Feu 1")));
	Container.push_back(Sort("Immolation 2", 7, Target::Actif, Effects.Get_Effect("Feu 2")));
	Container.push_back(Sort("Immolation 3", 9, Target::Actif, Effects.Get_Effect("Feu 3")));
	Container.push_back(Sort("Immolation 4", 11, Target::Actif, Effects.Get_Effect("Feu 4")));

	Container.push_back(Sort("Gel 1", 5, Target::Actif, Effects.Get_Effect("Eau 1")));
	Container.push_back(Sort("Gel 2", 7, Target::Actif, Effects.Get_Effect("Eau 2")));
	Container.push_back(Sort("Gel 3", 9, Target::Actif, Effects.Get_Effect("Eau 3")));
	Container.push_back(Sort("Gel 4", 11, Target::Actif, Effects.Get_Effect("Eau 4")));

	Container.push_back(Sort("Rafale 1", 5, Target::Actif, Effects.Get_Effect("Air 1")));
	Container.push_back(Sort("Rafale 2", 7, Target::Actif, Effects.Get_Effect("Air 2")));
	Container.push_back(Sort("Rafale 3", 9, Target::Actif, Effects.Get_Effect("Air 3")));
	Container.push_back(Sort("Rafale 4", 11, Target::Actif, Effects.Get_Effect("Air 4")));

	Container.push_back(Sort("Choc 1", 5, Target::Actif, Effects.Get_Effect("Terre 1")));
	Container.push_back(Sort("Choc 2", 7, Target::Actif, Effects.Get_Effect("Terre 2")));
	Container.push_back(Sort("Choc 3", 9, Target::Actif, Effects.Get_Effect("Terre 3")));
	Container.push_back(Sort("Choc 4", 11, Target::Actif, Effects.Get_Effect("Terre 4")));

	Container.push_back(Sort("Soin 1", 0, Target::Passif, Effects.Get_Effect("Soin 1")));
	Container.push_back(Sort("Soin 2", 0, Target::Passif, Effects.Get_Effect("Soin 2")));
	Container.push_back(Sort("Soin 3", 0, Target::Passif, Effects.Get_Effect("Soin 3")));
	Container.push_back(Sort("Soin 4", 0, Target::Passif, Effects.Get_Effect("Soin 4")));
}

Sort Sort_Container::Get_Sort(string _name)
{
	for (Sort& Current : Container)
		if (Current.Get_Name() == _name)
			return Current;
}
