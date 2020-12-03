#pragma once
#include "Tools.h"
#include "Character.h"
#include "Weapon.h"
#include "Armor.h"
#include "Consumable.h"
#include "Effect.h"

class Hero : public Character
{
private :
	int Tableau_Niveau[11];
	int Xp_Total;
	int Xp_Niveau;
	int Next_Niveau;
	int Point_Capacité;
	int Argent;
	float Time;

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
	inline void Set_XpTotal(float _xp) { Xp_Total = _xp; };
	inline void Set_XpNiveau(float _xp) { Xp_Niveau = _xp; };
	inline void Set_Capa(int _capacité) { Point_Capacité = _capacité; };
	inline void Set_Argent(int _argent) { Argent = _argent; };
	inline void Set_Time(float _time) { Time = _time; };

	virtual void Affichage_Type();
	virtual void Affichage_Stat();

	void Display();
};