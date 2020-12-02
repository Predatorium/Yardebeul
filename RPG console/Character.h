#pragma once
#include "Tools.h"

class Character
{
protected :
	Vector2f Position;
	enum class Direction
	{
		Haut,
		Bas,
		Gauche,
		Droite,
	};
	Direction Orientation;

	string Name;
	int Niveau;
	int Point_de_vie;
	int Mana;
	int Endurance;
	int Santé_mentale;
	int Vitesse;

public :
	Character();
	Character(string _name);
	~Character() = default;

	inline Vector2f Get_Position() { return Position; };
	inline Direction Get_Orientation() { return Orientation; };
	inline string Get_Name() { return Name; };
	inline int Get_Niveau() { return Niveau; };
	inline int Get_Vie() { return Point_de_vie; };
	inline int Get_Mana() { return Mana; };
	inline int Get_Endurance() { return Endurance; };
	inline int Get_SanteMental() { return Santé_mentale; };
	inline int Get_Vitesse() { return Vitesse; };

	inline void Set_Name(string _name) { Name = _name; };
	inline void Set_Niveau(int _niveau) { Niveau = _niveau; };
	inline void Set_Vie(int _vie) { Point_de_vie = _vie; };
	inline void Set_Mana(int _mana) { Mana = _mana; };
	inline void Set_Endurance(int _endurance) { Endurance = _endurance; };
	inline void Set_SanteMental(int _santémental) { Santé_mentale = _santémental; };
	inline void Set_Vitesse(int _vitesse) { Vitesse = _vitesse; };

	virtual void Affichage_Type() = 0;
	virtual void Affichage_Stat() = 0;
};

void Affichage_TypePerso(Character& p);
void Affichage_TypeStat(Character& p);