#pragma once
#include "Tools.h"

enum class Affect_Stat : int
{
	LIFE_POINT,
	MANA,
	SPEED,
	ENDURANCE,
	NONE
};

class Effect
{
private:
	Element Type_Element;
	Affect_Stat Stat;
	string Name;
	int Power;
	int Level;
	int Duration;

public :
	Effect() = default;
	Effect(string _name, Element _element, Affect_Stat _state, int _puissance, int _durée, int _level);
	~Effect() = default;

	inline Element Get_Element() { return Type_Element; };
	inline Affect_Stat Get_Affectation() { return Stat; };
	inline string Get_Name() { return Name; };
	inline int Get_Power() { return Power; };
	inline int Get_Duration() { return Duration; };
	inline int Get_Level() { return Level; };

	inline void Set_Duration(int _duration) { Duration = _duration; };

	bool operator==(Effect _e) { return Name == _e.Name; };
	bool operator!=(Effect _e) { return !operator==(_e); };
	bool operator()(const Effect& e) { return e.Duration <= 0; };
};