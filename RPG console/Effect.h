#pragma once
#include "Tools.h"

enum class Range_Effect : int
{
	AOE,
	Multicible,
	Monocible
};

enum class Affect_Stat : int
{
	PV,
	MANA,
	SANTE_MENTAL,
	VITESSE,
	ENDURANCE
};

class Effect
{
private:
	Element Type_Element;
	Range_Effect Range;
	Affect_Stat Stat;
	string Name;
	int Puissance;
	float Durée;

public :
	Effect();
	Effect(string _name, Element _element, Range_Effect _range, Affect_Stat _state, int _puissance, float _durée);
	~Effect();

	inline Element Get_Element() { return Type_Element; };
	inline Range_Effect Get_Range() { return Range; };
	inline Affect_Stat Get_Affectation() { return Stat; };
	inline string Get_Name() { return Name; };
	inline int Get_Puissance() { return Puissance; };
	inline float Get_Durée() { return Durée; };

	inline void Set_Element(Element _element) { Type_Element = _element; };
	inline void Set_Range(Range_Effect _range) { Range = _range; };
	inline void Set_Affectation(Affect_Stat _affectation) { Stat = _affectation; };
	inline void Set_Name(string _name) { Name = _name; };
	inline void Set_Puissance(int _puissance) { Puissance = _puissance; };
	inline void Set_Durée(float _durée) { Durée = _durée; };

	void Display_Stat();
};