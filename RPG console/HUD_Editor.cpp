#include "HUD_Editor.h"
#include "StateManager.h"
#include "FontManager.h"

HUD_Editor::HUD_Editor()
{
	if (FontList.size() > 0)
	{
		Current_Layer = 1;
		TileIsSelect = false;
		Current_Rank = 1;
		Timer = 0;
		Current_Biome = Biomes::Prairie;

		Tile_Select.setSize(Vector2f(28, 28));
		Tile_Select.setFillColor(Color::Transparent);
		Tile_Select.setOutlineThickness(2);
		Tile_Select.setOutlineColor(Color::Blue);

		Menu.setSize(Vector2f(1920, 64));
		Menu.setFillColor(Color::Color(100, 100, 100, 255));

		Button.push_back(Button_Text("Back_Layer", "Times", 20, Vector2f(126, 26), 2, Vector2f(1416, 34), Color::White));
		Button.push_back(Button_Text("Player_Layer", "Times", 20, Vector2f(126, 26), 2, Vector2f(1556, 34), Color::White));
		Button.push_back(Button_Text("Front_Layer", "Times", 20, Vector2f(126, 26), 2, Vector2f(1696, 34), Color::White));
		Button.push_back(Button_Text("Prev Biome", "Times", 20, Vector2f(126, 26), 2, Vector2f(1260, 16), Color::White));
		Button.push_back(Button_Text("Next Biome", "Times", 20, Vector2f(126, 26), 2, Vector2f(1260, 49), Color::White));
		Button.push_back(Button_Text("Test", "Times", 20, Vector2f(62, 26), 2, Vector2f(1887, 49), Color::White));
		Button.push_back(Button_Text("Menu", "Times", 20, Vector2f(62, 26), 2, Vector2f(1887, 16), Color::White));
		sButton.push_back(Button_Sprite("Save", 0, Vector2f(62, 26), 2, Vector2f(1820, 16), Color::White));
		sButton.push_back(Button_Sprite("Load", 0, Vector2f(62, 26), 2, Vector2f(1820, 49), Color::White));

		Change_Rank.push_back(Button_Sprite("Fleche", 0, Vector2f(50, 26), 2, Vector2f(27, 16), Color::White));
		Change_Rank.push_back(Button_Sprite("Fleche", 180, Vector2f(50, 26), 2, Vector2f(27, 49), Color::White));

		Move.push_back(Button_Sprite("Fleche", 0, Vector2f(1916, 36), 2, Vector2f(960, 84), Color::White));
		Move.push_back(Button_Sprite("Fleche", 270, Vector2f(36, 1012), 2, Vector2f(20, 572), Color::White));
		Move.push_back(Button_Sprite("Fleche", 180, Vector2f(1916, 36), 2, Vector2f(960, 1060), Color::White));
		Move.push_back(Button_Sprite("Fleche", 90, Vector2f(36, 1012), 2, Vector2f(1900, 572), Color::White));

		Selection = Maps(Vector2f(Mouse::getPosition(App.Get_Window())), Vector2i(0, 0), "Rien", Current_Biome);
		Load_MenuBiome();
	}
}

void HUD_Editor::Load_MenuBiome()
{
	Tile_menu.clear();

	Selection.Set_Name("Rien");
	TileIsSelect = false;

	Current_Rank = 1;

	Vector2i Max;
	string name;
	if (Current_Biome == Biomes::Prairie)
	{
		Max = Vector2i(4, 27);
		name = "Grass_lands";
	}
	else if (Current_Biome == Biomes::Caverne)
	{
		Max = Vector2i(5, 14);
		name = "Caverne";
	}
	else if (Current_Biome == Biomes::Desert)
	{
		Max = Vector2i(5, 14);
		name = "Desert";
	}
	else if (Current_Biome == Biomes::Montagne)
	{
		Max = Vector2i(1, 27);
		name = "Montagne";
	}

	int i = 0;
	int j = 1;
	int y = 0;
	int x = 0;
	bool done = true;
	while (done)
	{
		done = false;

		if (j < 3)
			Tile_menu.push_back(Interface_Maps(j, Vector2f(64 + i * Taille_tile, (j - 1) * Taille_tile), Vector2i(x, y), name, Current_Biome));
		else if (j >= 3 && j < 5)
			Tile_menu.push_back(Interface_Maps(j, Vector2f(64 + i * Taille_tile, (j - 3) * Taille_tile), Vector2i(x, y), name, Current_Biome));
		else if (j >= 5 && j < 7)
			Tile_menu.push_back(Interface_Maps(j, Vector2f(64 + i * Taille_tile, (j - 5) * Taille_tile), Vector2i(x, y), name, Current_Biome));

		x++;
		i++;

		if (i == 35)
		{
			i = 0;
			j++;
		}

		if (y == Max.y && x == Max.x)
		{
			Max_Rank = j;
			done = false;
		}
		else
			done = true;

		if (x == 5)
		{
			if (y < Max.y)
				x = 0;
			y++;
		}
	}
}

void HUD_Editor::Interaction_Biome(Vector2f _mouse)
{
	if (Mouse::isButtonPressed(Mouse::Left) && !(Keyboard::isKeyPressed(Keyboard::LControl)))
		if (Menu.getGlobalBounds().contains(Vector2f(Mouse::getPosition(App.Get_Window()))))
			for (Button_Text& Current_Button : Button)
				if (Current_Button.Get_Shape().getGlobalBounds().contains(_mouse))
				{
					if (Current_Button.Get_Name() == "Next Biome" && Timer > 0.2f)
					{
						Current_Biome = Biomes((int)Current_Biome + 1);
						if ((int)Current_Biome > 3)
							Current_Biome = Biomes(0);
						Load_MenuBiome();
						Timer = 0;
					}
					if (Current_Button.Get_Name() == "Prev Biome" && Timer > 0.2f)
					{
						Current_Biome = Biomes((int)Current_Biome - 1);
						if ((int)Current_Biome < 0)
							Current_Biome = Biomes(3);
						Load_MenuBiome();
						Timer = 0;
					}
				}

	if (Keyboard::isKeyPressed(Keyboard::Add) && Timer > 0.2f)
	{
		Current_Biome = Biomes((int)Current_Biome + 1);
		if ((int)Current_Biome > 3)
			Current_Biome = Biomes(0);
		Load_MenuBiome();
		Timer = 0;
	}
	if (Keyboard::isKeyPressed(Keyboard::Subtract) && Timer > 0.2f)
	{
		Current_Biome = Biomes((int)Current_Biome - 1);
		if ((int)Current_Biome < 0)
			Current_Biome = Biomes(3);
		Load_MenuBiome();
		Timer = 0;
	}
}

void HUD_Editor::Interaction_SaveAndLoad(Vector2f _mouse, bool& _save, bool& _load)
{
	if (Mouse::isButtonPressed(Mouse::Left) && !(Keyboard::isKeyPressed(Keyboard::LControl)))
		if (Menu.getGlobalBounds().contains(Vector2f(Mouse::getPosition(App.Get_Window()))))
			for (Button_Sprite& Current_Button : sButton)
				if (Current_Button.Get_Shape().getGlobalBounds().contains(_mouse))
				{
					if (Current_Button.Get_Name() == "Save" && Timer > 0.2f)
						_save = true;
					if (Current_Button.Get_Name() == "Load" && Timer > 0.2f)
						_load = true;
				}
}

void HUD_Editor::Interaction_Layer(Vector2f _mouse)
{
	for (Button_Text& Current_Button : Button)
	{
		if (Current_Button.Get_Name() == "Back_Layer" && Current_Layer == 1)
			Current_Button.Set_Color(Color::Red);
		else if (Current_Button.Get_Name() == "Player_Layer" && Current_Layer == 2)
			Current_Button.Set_Color(Color::Red);
		else if (Current_Button.Get_Name() == "Front_Layer" && Current_Layer == 3)
			Current_Button.Set_Color(Color::Red);
		else
			Current_Button.Set_Color(Color::White);
	}

	if (Mouse::isButtonPressed(Mouse::Left) && !(Keyboard::isKeyPressed(Keyboard::LControl)))
		if (Menu.getGlobalBounds().contains(Vector2f(Mouse::getPosition(App.Get_Window()))))
			for (Button_Text& Current_Button : Button)
				if (Current_Button.Get_Shape().getGlobalBounds().contains(_mouse))
				{
					if (Current_Button.Get_Name() == "Back_Layer")
						Current_Layer = 1;
					if (Current_Button.Get_Name() == "Player_Layer")
						Current_Layer = 2;
					if (Current_Button.Get_Name() == "Front_Layer")
						Current_Layer = 3;
				}

	if (Keyboard::isKeyPressed(Keyboard::Num1) && Timer > 0.2f)
	{
		Current_Layer = 1;
		Timer = 0;
	}
	if (Keyboard::isKeyPressed(Keyboard::Num2) && Timer > 0.2f)
	{
		Current_Layer = 2;
		Timer = 0;
	}
	if (Keyboard::isKeyPressed(Keyboard::Num3) && Timer > 0.2f)
	{
		Current_Layer = 3;
		Timer = 0;
	}
}

void HUD_Editor::Interaction_MenuAndTest(Vector2f _mouse, bool& _player)
{
	if (Mouse::isButtonPressed(Mouse::Left) && !(Keyboard::isKeyPressed(Keyboard::LControl)))
		if (Menu.getGlobalBounds().contains(Vector2f(Mouse::getPosition(App.Get_Window()))))
			for (Button_Text& Current_Button : Button)
				if (Current_Button.Get_Shape().getGlobalBounds().contains(_mouse))
				{
					if (Current_Button.Get_Name() == "Menu" && Timer > 0.2f && !_player)
					{
						MState.ChangeState(State::MENU);
						Timer = 0;
					}
					if (Current_Button.Get_Name() == "Test" && Timer > 0.2f)
					{
						_player = !_player;
						Timer = 0;
					}
				}

	if (Keyboard::isKeyPressed(Keyboard::Escape) && Timer > 0.2f && !_player)
	{
		MState.ChangeState(State::MENU);
		Timer = 0;
	}
	if (Keyboard::isKeyPressed(Keyboard::T) && Timer > 0.2f)
	{
		_player = !_player;
		Timer = 0;
	}
}

void HUD_Editor::Interaction_Tile(Vector2f _mouse, bool& _grille)
{
	if (Mouse::isButtonPressed(Mouse::Left) && !(Keyboard::isKeyPressed(Keyboard::LControl)))
		if (Menu.getGlobalBounds().contains(Vector2f(Mouse::getPosition(App.Get_Window()))))
		{
			for (Interface_Maps& Actual_Select : Tile_menu)
				if (FloatRect(Actual_Select.Get_Position().x, Actual_Select.Get_Position().y, Taille_tile, Taille_tile).contains(_mouse) &&
					(Actual_Select.Get_Rank() == Current_Rank || Actual_Select.Get_Rank() == Current_Rank + 1))
				{
					Selection.Set_Biome(Actual_Select.Get_Biome());
					Selection.Set_Name(Actual_Select.Get_Name());
					Selection.Set_Tile(Actual_Select.Get_Tile());
					TileIsSelect = true;
				}

			for (Button_Sprite& Current_Shape : Change_Rank)
				if (Current_Shape.Get_Shape().getGlobalBounds().contains(_mouse) && Timer > 0.2f)
				{
					Selection.Set_Name("Rien");
					TileIsSelect = false;

					if (Current_Shape.Get_Rotate() == 0)
					{
						Current_Rank -= 2;
						if (Current_Rank < 1)
						{
							if (Max_Rank == 2)
								Current_Rank = 1;
							else if (Max_Rank == 4)
								Current_Rank = 3;
							else if (Max_Rank == 6)
								Current_Rank = 5;
							else
								Current_Rank = Max_Rank;
						}
					}
					if (Current_Shape.Get_Rotate() == 180)
					{
						Current_Rank += 2;
						if (Current_Rank > Max_Rank)
							Current_Rank = 1;
					}
					Timer = 0;
				}
		}

	if (Mouse::isButtonPressed(Mouse::Right))
	{
		Selection.Set_Name("Rien");
		TileIsSelect = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::G) && Timer > 0.2f)
	{
		if (_grille == false)
			_grille = true;
		else if (_grille == true)
			_grille = false;

		Timer = 0;
	}
}

void HUD_Editor::Update_TileSelect()
{
	for (Interface_Maps& Current_Tile : Tile_menu)
		if (Current_Tile.Get_Tile() == Selection.Get_Tile() && Current_Tile.Get_Biome() == Selection.Get_Biome())
			Tile_Select.setPosition(Vector2f(Current_Tile.Get_Position().x + 2, Current_Tile.Get_Position().y + 2));
}

void HUD_Editor::Display_Tilemenu()
{
	for (Interface_Maps& Current_Tile : Tile_menu)
		if (Current_Tile.Get_Rank() == Current_Rank || Current_Tile.Get_Rank() == Current_Rank + 1)
			Current_Tile.display();
}

void HUD_Editor::Display_MenuShape()
{
	App.Get_Window().draw(Menu);
}

void HUD_Editor::Display_Move()
{
	for (Button_Sprite& Current_Shape : Move)
		if (Current_Shape.Get_Color() == Color::Red)
			Current_Shape.Display();
}

void HUD_Editor::Display_LoadAndSave()
{
	for (Button_Sprite& Current_Button : sButton)
		Current_Button.Display();
}

void HUD_Editor::Display_ButtonRank()
{
	for (Button_Sprite& Current_Button : Change_Rank)
		Current_Button.Display();
}

void HUD_Editor::Display_ButtonMenuAndTest(bool _player)
{
	for (Button_Text& Current_Button : Button)
	{
		if (!_player)
			Current_Button.Display();
		else
			if (Current_Button.Get_Name() == "Test")
				Current_Button.Display();
	}
}

void HUD_Editor::Display_Selection(RectangleShape& _grille)
{
	if (Selection.Get_Name() == "Rien")
	{
		_grille.setPosition(Selection.Get_Position());
		App.Get_Window().draw(_grille);
	}
	else
		Selection.display();

	if (TileIsSelect)
		App.Get_Window().draw(Tile_Select);
}