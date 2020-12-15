#pragma once
#include "Tools.h"
#include "Niveau.h"
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
	Vector2f SizeMin;
	Vector2f SizeMax;
	int Position_Set;

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
	void Set_MapSize(vector<Maps>& _layer, Vector2f _min, Vector2f _max);
	void Erase_Map();
	virtual void Update();

	void Display_SaveAndLoad();
	void Display_NewSave();
	void Display_HUD();
	void Display_Map();
	void display_Etage();
	void Display_editeur();
};