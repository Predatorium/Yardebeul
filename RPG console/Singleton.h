#pragma once
#include "Tools.h"

template <typename T>
class Singleton
{
public :
	static T& Get_Singleton()
	{
		static T Instance_Unique;
		return Instance_Unique;
	}

protected :
	Singleton() = default;
	~Singleton() = default;
};