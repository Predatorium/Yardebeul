#include "Effect.h"

Effect::Effect(string _name, Element _element, Affect_Stat _state, int _puissance, int _durée, int _level)
{
	Name = _name;
	Type_Element = _element;
	Stat = _state;
	Power = _puissance;
	Duration = _durée;
	Level = _level;
}