#pragma once
#include "Tools.h"
#include "Map.h"
#include "Bouton.h"
#include "Views.h"

class HUD_Editor
{
private :
	RectangleShape Menu;

	list<Interface_Maps> Tile_menu;
	list<Button_Sprite> Move;
	list<Button_Sprite> Change_Rank;
	Maps Selection;
	RectangleShape Tile_Select;
	list<Button_Text> Button;
	list<Button_Sprite> sButton;
	Biomes Current_Biome;

	bool TileIsSelect;
	float Timer;
	int Current_Layer;
	int Current_Rank;
	int Max_Rank;

public :
	HUD_Editor();
	~HUD_Editor() = default;

	inline Maps& Get_Selection() { return Selection; };
	inline list<Button_Sprite>& Get_Move() { return Move; };
	inline RectangleShape Get_MenuShape() { return Menu; };
	inline int Get_Rank() { return Current_Rank; };
	inline int Get_Layer() { return Current_Layer; };

	inline void Add_Timer(float _timer) { Timer += _timer; };

	void Load_MenuBiome();
	void Interaction_Biome(Vector2f _mouse);
	void Interaction_SaveAndLoad(Vector2f _mouse, bool& _save, bool& _load);
	void Interaction_Layer(Vector2f _mouse);
	void Interaction_MenuAndTest(Vector2f _mouse, bool& _player);
	void Interaction_Tile(Vector2f _mouse, bool& _grille);
	void Update_TileSelect();

	void Display_Tilemenu();
	void Display_MenuShape();
	void Display_Move();
	void Display_LoadAndSave();
	void Display_ButtonRank();
	void Display_ButtonMenuAndTest(bool _player);
	void Display_Selection(RectangleShape& _grille);
};