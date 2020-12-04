#pragma once
#include "Tools.h"
#include "Animator.h"

enum class Direction
{
	Haut,
	Bas,
	Gauche,
	Droite,
};

class Character
{
protected :
	Vector2f Position;
	Direction Orientation;

	bool Droite;
	bool Gauche;
	bool Bas;
	bool Haut;

	Animator Walk_Right;
	Animator Walk_Top;
	Animator Walk_Down;

	Animator Beat_Right;
	Animator Beat_Top;
	Animator Beat_Down;

	IntRect Colision_Rect;

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

	inline IntRect Get_ColisionRect() { return Colision_Rect; };
	inline Vector2f Get_Position() { return Position; };
	inline Direction Get_Orientation() { return Orientation; };
	inline string Get_Name() { return Name; };
	inline int Get_Niveau() { return Niveau; };
	inline int& Get_HP() { return Point_de_vie; };
	inline int Get_Mana() { return Mana; };
	inline int Get_Endurance() { return Endurance; };
	inline int Get_SanteMental() { return Santé_mentale; };
	inline int Get_Vitesse() { return Vitesse; };
	inline bool Get_Gauche() { return Gauche; };
	inline bool Get_Droite() { return Droite; };
	inline bool Get_Haut() { return Haut; };
	inline bool Get_Bas() { return Bas; };
	inline Animator& Get_BeatRight() { return Beat_Right; };
	inline Animator& Get_BeatDown() { return Beat_Down; };

	inline void Set_Gauche(bool _bool) { Gauche = _bool; };
	inline void Set_Droite(bool _bool) { Droite = _bool; };
	inline void Set_Haut(bool _bool) { Haut = _bool; };
	inline void Set_Bas(bool _bool) { Bas = _bool; };
	inline void Set_Orientation(Direction _orientation) { Orientation = _orientation; };
	inline void Set_Position(Vector2f _position) { Position = _position; };
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