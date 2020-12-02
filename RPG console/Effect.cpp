#include "Effect.h"

Effect::Effect()
{
	Name = "Soin";
	Type_Element = Element::Neutre;
	Range = Range_Effect::AOE;
	Stat = Affect_Stat::PV;
	Puissance = 10;
	Durée = 1;
}

Effect::Effect(string _name, Element _element, Range_Effect _range, Affect_Stat _state, int _puissance, float _durée)
{
	Name = _name;
	Type_Element = _element;
	Range = _range;
	Stat = _state;
	Puissance = _puissance;
	Durée = _durée;
}

Effect::~Effect()
{
}

void Effect::Display_Stat()
{
	cout << "Le nom de mon effet est " << Get_Name() << endl;

	if (Get_Element() == Element::Feu)
		cout << "L element de mon effet est le feu." << endl;
	if (Get_Element() == Element::Lave)
		cout << "L element de mon effet est le lave." << endl;
	if (Get_Element() == Element::Eau)
		cout << "L element de mon effet est le eau." << endl;
	if (Get_Element() == Element::Glace)
		cout << "L element de mon effet est le glace." << endl;
	if (Get_Element() == Element::Air)
		cout << "L element de mon effet est le air." << endl;
	if (Get_Element() == Element::Foudre)
		cout << "L element de mon effet est le foudre." << endl;
	if (Get_Element() == Element::Terre)
		cout << "L element de mon effet est le terre." << endl;
	if (Get_Element() == Element::Gravité)
		cout << "L element de mon effet est le gravité." << endl;
	if (Get_Element() == Element::Neutre)
		cout << "L element de mon effet est le neutre." << endl;

	if (Get_Affectation() == Affect_Stat::PV)
		cout << "Mon effet affecte les PV."<< endl;
	if (Get_Affectation() == Affect_Stat::MANA)
		cout << "Mon effet affecte la mana." << endl;
	if (Get_Affectation() == Affect_Stat::SANTE_MENTAL)
		cout << "Mon effet affecte la sante mental." << endl;
	if (Get_Affectation() == Affect_Stat::VITESSE)
		cout << "Mon effet affecte la vitesse." << endl;
	if (Get_Affectation() == Affect_Stat::ENDURANCE)
		cout << "Mon effet affecte l endurance." << endl;

	if (Get_Range() == Range_Effect::AOE)
		cout << "Mon effet a une etendu de zone." << endl;
	if (Get_Range() == Range_Effect::Multicible)
		cout << "Mon effet a une etendu multicible." << endl;
	if (Get_Range() == Range_Effect::Monocible)
		cout << "Mon effet a une etendu monocible." << endl;

	cout << "Mon effet a une puissance de " << Get_Puissance() << endl;
	cout << "Mon effet a une duree de " << Get_Durée() << endl;
}