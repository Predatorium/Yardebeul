#pragma once
#include "Tools.h"
#include "Map.h"
#include "Button.h"
#include "Npc.h"

class HUD_Editor
{
private:
	enum class stat_modif
	{
		NONE,
		NAME,
		LIFE,
		LEVEL,
		ATTITUDE,
		DIALOGUE,
	};
	stat_modif Modif;

	RectangleShape Menu;
	RectangleShape Menu_Npc;

	list<Interface_Maps> Tile_menu;

	list<Button_Sprite> Move;
	list<Button_Sprite> Change_Rank;
	list<Button_Sprite> sButton;

	list<Button_Text> Button;
	list<Button_Text> Modif_Npc;
	list<Button_Text> Select_Stat;

	Maps Selection;
	RectangleShape Tile_Select;
	Biomes Current_Biome;

	bool IsSelect;
	bool NpcSelect;
	float Timer;
	int Current_Layer;
	int Current_Rank;
	int Current_Npc;
	int Max_Rank;

public:
	HUD_Editor();
	~HUD_Editor() = default;

	inline Maps& Get_Selection() { return Selection; };
	inline list<Button_Sprite>& Get_Move() { return Move; };
	inline RectangleShape Get_MenuShape() { return Menu; };
	inline int Get_Rank() { return Current_Rank; };
	inline int Get_Layer() { return Current_Layer; };
	inline bool Get_NpcIsSelect() { return NpcSelect; };

	inline void Add_Timer(float _timer) { Timer += _timer; };

	void Load_MenuBiome();
	void Interaction_NPC(Vector2f _mouse);
	void Set_Npc(Vector2f _mouse, list<Npc>& _npc, Vector2i _limit);
	void Interaction_Biome(Vector2f _mouse);
	void Interaction_SaveAndLoad(Vector2f _mouse, bool& _save, bool& _load);
	void Interaction_Layer(Vector2f _mouse);
	void Interaction_MenuAndTest(Vector2f _mouse, bool& _player);
	void Interaction_Tile(Vector2f _mouse);

	void Display_Tilemenu();
	void Display_NpcModif();
	void Display_MenuShape();
	void Display_Move();
	void Display_LoadAndSave();
	void Display_ButtonRank();
	void Display_ButtonText(bool _player);
	void Display_Selection(RectangleShape & _grille);
};