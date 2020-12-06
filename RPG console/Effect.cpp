#include "Effect.h"

Effect::Effect(string _name, Element _element, Range_Effect _range, Affect_Stat _state, int _puissance, float _durée)
{
	Name = _name;
	Type_Element = _element;
	Range = _range;
	Stat = _state;
	Power = _puissance;
	Duration = _durée;
}