#pragma once
#include "Tools.h"
#include "World.h"
#include "Bouton.h"
#include "Views.h"

class Bouton_Load
{
private:
	RectangleShape Shape;
	list<Text> texte;
	string Name;
	string Time;
	string Niveau;
	int Numero;

public:
	Bouton_Load() = default;
	Bouton_Load(Vector2f _position, string _name, int _num);
	~Bouton_Load() = default;

	inline string Get_Name() { return Name; };
	inline RectangleShape& Get_Shape() { return Shape; };
	inline int Get_Num() { return Numero; };

	void Load();

	void Display();
};

class Menu
{
private :
	list<Bouton> Button;
	list<Bouton_Load> Emplacement;
	Bouton Titre;
	int Selection;
	float timer;
	Views Vue;

public :
	Menu() = default;
	Menu(int _menutype);
	~Menu() = default;

	void Update_Select();
	void Update_Main(World& _world);
	void Update_Pause(World& _world, bool& _pause);
	void Display_Main();
	void Display_Pause();
};