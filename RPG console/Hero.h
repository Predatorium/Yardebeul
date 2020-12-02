#pragma once
#include "Tools.h"
#include "Character.h"
#include "Weapon.h"
#include "Armor.h"
#include "Consumable.h"
#include "Effect.h"
#include "Animator.h"

class Hero : public Character
{
private :
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

	int Tableau_Niveau[11];
	int Xp_Total;
	int Xp_Niveau;
	int Next_Niveau;
	int Point_Capacité;
	int Argent;
	float Time;

	IntRect Colision_Rect;

	Weapon* Arme;
	Armor* Armure;
	list<Consumable*> consommables;

public :
	Hero() = default;
	Hero(Vector2f _position);
	~Hero() = default;

	int Pourcentage_Niveau();
	void Gain_Xp(float _gainxp);
	void Passage_Niveau();
	void Affectation_Stat(Effect _effet);
	void Amelioration_stat();
	void Update(Vector2i _limitMap);

	inline bool Get_Gauche() { return Gauche; };
	inline bool Get_Droite() { return Droite; };
	inline bool Get_Haut() { return Haut; };
	inline bool Get_Bas() { return Bas; };
	inline IntRect Get_ColisionRect() { return Colision_Rect; };
	inline int Get_Xptotal() { return Xp_Total; };
	inline int Get_XpNiveau() { return Xp_Niveau; };
	inline int Get_PointCapacity() { return Point_Capacité; };
	inline int Get_Argent() { return Argent; };
	inline float Get_Time() { return Time; };
	inline Weapon* Get_Weapon() { return Arme; };
	inline Armor* Get_Armor() { return Armure; };
	inline list<Consumable*> Get_Consumable() { return consommables; };

	inline void Set_Arme(Weapon _arme) { Arme = new Weapon(_arme); };
	inline void Set_Armure(Armor _armure) { Armure = new Armor(_armure); };
	inline void Set_Consommable(Consumable _consomable) { consommables.push_back(new Consumable(_consomable)); };
	inline void Set_Gauche(bool _bool) { Gauche = _bool; };
	inline void Set_Droite(bool _bool) { Droite = _bool; };
	inline void Set_Haut(bool _bool) { Haut = _bool; };
	inline void Set_Bas(bool _bool) { Bas = _bool; };
	inline void Set_Position(Vector2f _position) { Position = _position; };
	inline void Set_Name(string _name) { Name = _name; };
	inline void Set_Niveau(int _niveau) { Niveau = _niveau; };
	inline void Set_PV(int _pv) { Point_de_vie = _pv; };
	inline void Set_Mana(int _mana) { Mana = _mana; };
	inline void Set_Mental(int _mental) { Santé_mentale = _mental; };
	inline void Set_Vitesse(int _vitesse) { Vitesse = _vitesse; };
	inline void Set_XpTotal(float _xp) { Xp_Total = _xp; };
	inline void Set_XpNiveau(float _xp) { Xp_Niveau = _xp; };
	inline void Set_Capa(int _capacité) { Point_Capacité = _capacité; };
	inline void Set_Argent(int _argent) { Argent = _argent; };
	inline void Set_Time(float _time) { Time = _time; };

	virtual void Affichage_Type();
	virtual void Affichage_Stat();

	void Display();
};