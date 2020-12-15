#pragma once
#include "Tools.h"
#include "Niveau.h"
#include "Button.h"
#include "Views.h"

class Bouton_Load
{
private:
	RectangleShape Shape;
	list<Text> texte;
	Texture texture;
	Sprite sprite;
	string Name;
	string Time;
	string Level;
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
	list<Button_Text> Button;
	list<Bouton_Load> Emplacement;
	Button_Text Titre;
	int Selection;
	float timer;
	bool Option;
	bool Menu_Load;
	Views Vue;

public :
	Menu() = default;
	Menu(int _menutype);
	~Menu() = default;

	void Update_Select();
	void Switch_Mode();
	void Update_Main(Level* _level);
	void Update_Pause(Level* _level, bool& _pause);
	void Display_Main();
	void Display_Pause();
};