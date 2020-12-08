#pragma once
#include "Tools.h"
#include "Niveau.h"
#include "Button.h"
#include "Views.h"
#include "HUD_Editor.h"

class Editeur : public Level
{
private :
	HUD_Editor Hud;

	list<Button_Text> Dispo_Map;
	Button_Text New_map;

	RectangleShape Grille;

	Vector2f Mouse_Position;

	bool Save_New_Map;
	bool App_Grille;
	bool PlayerIsPresent;
	float Timer;

public :
	Editeur();
	~Editeur() = default;

	void SaveNewMap();
	void LoadNewMap();

	void Set_MousePos(Vector2f _position);
	void Move_Map(int _coloulig, int _ajoures);
	void Resize_Map();
	void Interaction_Map();
	void Set_Map(vector<Maps> &_layer);
	void Erase_Map();
	void Update();

	void Display_SaveAndLoad();
	void Display_NewSave();
	void Display_HUD();
	void Display_Map();
	void display_Etage();
	void Display();
};