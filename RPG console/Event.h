#pragma once
#include "Tools.h"

class Events
{
private:
	State_Event Type;

public:
	Events() = default;
	Events(State_Event _type);
	~Events() = default;

	inline void Set_Type(State_Event _type) { Type = _type; };

	inline State_Event Get_Type() { return Type; };
};