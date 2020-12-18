#pragma once
#include "Tools.h"
#include "Niveau.h"
#include "HUD_Editor.h"

class Editeur : public Level
{
private :
	HUD_Editor Hud;
	list<Button_Text> Dispo_Map;
	Button_Text New_map;
	RectangleShape Grille;

	Vector2f Mouse_Position;
	Vector2i SizeMin;
	Vector2i SizeMax;
	int Position_Set;

	bool Save_New_Map;
	bool App_Grille;
	bool PlayerIsPresent;

public :
	Editeur();
	~Editeur() = default;

	void SaveNewMap();
	void LoadNewMap();

	void Set_MousePos(Vector2f _position);
	void Move_Map(int _coloulig, int _ajoures);
	void Resize_Map();
	void Interaction_Map();
	void Set_Map(list<Maps>& _layer);
	void Set_MapSize(list<Maps>& _layer, Vector2i _min, Vector2i _max);
	virtual void Update();

	void Display_SaveAndLoad();
	void Display_NewSave();
	void Display_HUD();
	void Display_Map();
	void Display_MiniMap();
	void display_EtageforMap();
	void display_EtageforMiniMap();
	void Display_editeur();
};