#pragma once
#include "Tools.h"
#include "Effect.h"
#include "Entity.h"

enum class Target : int
{
	Passif,
	Actif
};

class Sort : public Entity
{
private :
	Target target;
	int Damage;
	Effect effect;

public :
	Sort() = default;
	Sort(string _name, int _damage, Target _target, Effect _effect);
	~Sort() = default;

	inline Effect Get_Effect() { return effect; };
	inline Target Get_Affectation() { return target; };
	inline string Get_Name() { return Name; };
	inline int Get_Damage() { return Damage; };

	bool operator==(Sort _e) { return Name == _e.Name; };
	bool operator!=(Sort _e) { return !operator==(_e); };

	void Update() {};
	void Display() {};
	void Display(Vector2f _position);
};