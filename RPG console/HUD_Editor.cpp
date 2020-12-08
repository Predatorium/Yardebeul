#include "HUD_Editor.h"
#include "StateManager.h"
#include "FontManager.h"
#include "SpriteManager.h"
#include "Dialogue_Container.h"

HUD_Editor::HUD_Editor()
{
	if (FontList.size() > 0)
	{
		Current_Layer = 1;
		IsSelect = false;
		NpcSelect = false;
		Current_Rank = 1;
		Timer = 0;
		Current_Biome = Biomes::Prairie;
		Modif = stat_modif::NONE;
		Current_Npc = 0;

		Tile_Select.setSize(Vector2f(28, 28));
		Tile_Select.setFillColor(Color::Transparent);
		Tile_Select.setOutlineThickness(2);
		Tile_Select.setOutlineColor(Color::Blue);

		Menu.setSize(Vector2f(1920, 64));
		Menu.setFillColor(Color(100, 100, 100, 255));

		Menu_Npc.setSize(Vector2f(130, 280));
		Menu_Npc.setFillColor(Color(100, 100, 100, 255));
		Menu_Npc.setOutlineThickness(2);
		Menu_Npc.setOutlineColor(Color(255, 150, 50, 255));
		Menu_Npc.setPosition(Vector2f(200, 200));

		Button.push_back(Button_Text("Back_Layer", "Times", 20, Vector2f(126, 26), 2, Vector2f(1556, 16), Color::White));
		Button.push_back(Button_Text("Deco_Layer", "Times", 20, Vector2f(126, 26), 2, Vector2f(1696, 16), Color::White));
		Button.push_back(Button_Text("Player_Layer", "Times", 20, Vector2f(126, 26), 2, Vector2f(1556, 49), Color::White));
		Button.push_back(Button_Text("Front_Layer", "Times", 20, Vector2f(126, 26), 2, Vector2f(1696, 49), Color::White));

		Button.push_back(Button_Text("NPC", "Times", 20, Vector2f(62, 26), 2, Vector2f(1426, 34), Color::White));

		Button.push_back(Button_Text("Test", "Times", 20, Vector2f(62, 26), 2, Vector2f(1887, 49), Color::White));
		Button.push_back(Button_Text("Menu", "Times", 20, Vector2f(62, 26), 2, Vector2f(1887, 16), Color::White));

		sButton.push_back(Button_Sprite("Save", 0, Vector2f(62, 26), 2, Vector2f(1820, 16), Color::White));
		sButton.push_back(Button_Sprite("Load", 0, Vector2f(62, 26), 2, Vector2f(1820, 49), Color::White));

		Button.push_back(Button_Text("Prev Biome", "Times", 20, Vector2f(126, 26), 2, Vector2f(1083, 16), Color::White));
		Button.push_back(Button_Text("Next Biome", "Times", 20, Vector2f(126, 26), 2, Vector2f(1083, 49), Color::White));

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
	IsSelect = false;

	Current_Rank = 1;

	Vector2i Max;
	string name;
	if (Current_Biome == Biomes::Prairie)
	{
		Max = Vector2i(3, 27);
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
			Tile_menu.push_back(Interface_Maps(j, Vector2f(56 + i * Taille_tile, (j - 1) * Taille_tile), Vector2i(x, y), name, Current_Biome));
		else if (j >= 3 && j < 5)
			Tile_menu.push_back(Interface_Maps(j, Vector2f(56 + i * Taille_tile, (j - 3) * Taille_tile), Vector2i(x, y), name, Current_Biome));
		else if (j >= 5 && j < 7)
			Tile_menu.push_back(Interface_Maps(j, Vector2f(56 + i * Taille_tile, (j - 5) * Taille_tile), Vector2i(x, y), name, Current_Biome));

		x++;
		i++;

		if (i == 30)
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

void HUD_Editor::Interaction_NPC(Vector2f _mouse)
{
	if (Mouse::isButtonPressed(Mouse::Left) && !(Keyboard::isKeyPressed(Keyboard::LControl)))
		if (Menu.getGlobalBounds().contains(Vector2f(_mouse)))
			for (Button_Text& Current_Button : Button)
				if (Current_Button.Get_Shape().getGlobalBounds().contains(_mouse))
				{
					if (Current_Button.Get_Name() == "NPC")
					{
						IsSelect = false;
						Selection.Set_Name("NPC");
						Modif = stat_modif::NONE;
						Current_Layer = 3;
					}
					else
					{
						NpcSelect = false;
						IsSelect = false;
						Modif = stat_modif::NONE;
						Selection.Set_Name("Rien");
					}
				}
}

void HUD_Editor::Set_Npc(Vector2f _mouse, list<Npc>& _npc, Vector2i _limit)
{
	bool findNpc = false;
	if (Mouse::isButtonPressed(Mouse::Left) && !(Keyboard::isKeyPressed(Keyboard::LControl)) && Selection.Get_Name() == "NPC")
	{
		if (!(Menu.getGlobalBounds().contains(Vector2f(Mouse::getPosition(App.Get_Window())))) && 
			!(Menu_Npc.getGlobalBounds().contains(Vector2f(Mouse::getPosition(App.Get_Window())))))
		{
			int i = 0;
			NpcSelect = false;
			for (Npc& Current : _npc)
			{
				if (FloatRect(Current.Get_Position().x - Current.Get_ColisionRect().width * 0.75, Current.Get_Position().y - Current.Get_ColisionRect().height * 1.5,
					Current.Get_ColisionRect().width * 1.5, Current.Get_ColisionRect().height * 3).contains(_mouse))
				{
					Current_Npc = i;
					Modif_Npc.clear();
					Select_Stat.clear();
					if (Menu_Npc.getSize().x == 265)
						Menu_Npc.setSize(Vector2f(130, 230));

					Modif_Npc.push_back(Button_Text("Name", "Times", 20, Vector2f(126, 26), 2, Vector2f(Menu_Npc.getPosition().x + 65, Menu_Npc.getPosition().y + 15), Color::White));
					Modif_Npc.push_back(Button_Text("Life", "Times", 20, Vector2f(126, 26), 2, Vector2f(Menu_Npc.getPosition().x + 65, Menu_Npc.getPosition().y + 65), Color::White));
					Modif_Npc.push_back(Button_Text("Level", "Times", 20, Vector2f(126, 26), 2, Vector2f(Menu_Npc.getPosition().x + 65, Menu_Npc.getPosition().y + 115), Color::White));
					Modif_Npc.push_back(Button_Text("Attitude", "Times", 20, Vector2f(126, 26), 2, Vector2f(Menu_Npc.getPosition().x + 65, Menu_Npc.getPosition().y + 165), Color::White));
					Modif_Npc.push_back(Button_Text("Dialogue", "Times", 20, Vector2f(126, 26), 2, Vector2f(Menu_Npc.getPosition().x + 65, Menu_Npc.getPosition().y + 215), Color::White));
					Modif_Npc.push_back(Button_Text("Remove", "Times", 20, Vector2f(126, 26), 2, Vector2f(Menu_Npc.getPosition().x + 65, Menu_Npc.getPosition().y + 265), Color::White));
					NpcSelect = true;
					findNpc = true;
				}
				i++;
			}

			if (!findNpc && Selection.Get_Name() == "NPC" && _mouse.x <= (_limit.x - 1) * Taille_tile &&
				_mouse.y <= (_limit.y - 2) * Taille_tile && _mouse.x >= 0 && _mouse.y >= 0)
				_npc.push_back(Npc("Fairy", _mouse, 1, 10, 20, Comportement::Neutre));
		}
	}

	if (Mouse::isButtonPressed(Mouse::Right))
	{
		Modif = stat_modif::NONE;
		Select_Stat.clear();
		Modif_Npc.clear();
		NpcSelect = false;
	}
	
	if (Mouse::isButtonPressed(Mouse::Left) && !(Keyboard::isKeyPressed(Keyboard::LControl)) && Timer > 0.2f && Selection.Get_Name() == "NPC")
	{
		bool find = false;
		for (Button_Text& Current : Modif_Npc)
			if (Current.Get_Shape().getGlobalBounds().contains(Vector2f(Mouse::getPosition(App.Get_Window()))))
			{
				if (Menu_Npc.getSize().x == 130 && Current.Get_Name() != "Remove")
					Menu_Npc.setSize(Vector2f(265, 280));

				if (Current.Get_Name() == "Name")
				{
					Select_Stat.clear();
					Modif = stat_modif::NAME;
					Select_Stat.push_back(Button_Text("Knucles", "Times", 20, Vector2f(126, 26), 2, Vector2f(Menu_Npc.getPosition().x + 200, Menu_Npc.getPosition().y + 15), Color::White));
					Select_Stat.push_back(Button_Text("Fairy", "Times", 20, Vector2f(126, 26), 2, Vector2f(Menu_Npc.getPosition().x + 200, Menu_Npc.getPosition().y + 45), Color::White));
					int i = 0;
					for (Npc& Current_npc : _npc)
					{
						if (Current_Npc == i)
							for (Button_Text& Current_text : Select_Stat)
								if (Current_npc.Get_Name() == Current_text.Get_Name())
									Current_text.Set_Color(Color::Red);

						i++;
					}
					Timer = 0;
				}
				if (Current.Get_Name() == "Attitude")
				{
					Select_Stat.clear();
					Modif = stat_modif::ATTITUDE;
					Select_Stat.push_back(Button_Text("Neutre", "Times", 20, Vector2f(126, 26), 2, Vector2f(Menu_Npc.getPosition().x + 200, Menu_Npc.getPosition().y + 15), Color::White));
					Select_Stat.push_back(Button_Text("Amical", "Times", 20, Vector2f(126, 26), 2, Vector2f(Menu_Npc.getPosition().x + 200, Menu_Npc.getPosition().y + 45), Color::White));
					Select_Stat.push_back(Button_Text("Agressif", "Times", 20, Vector2f(126, 26), 2, Vector2f(Menu_Npc.getPosition().x + 200, Menu_Npc.getPosition().y + 75), Color::White));
					int i = 0;
					for (Npc& Current_npc : _npc)
					{
						if (Current_Npc == i)
						{
							for (Button_Text& Current_text : Select_Stat)
							{
								if (Current_npc.Get_Attitude() == Comportement::Agressif)
									if (Current_text.Get_Name() == "Agressif")
										Current_text.Set_Color(Color::Red);
								if (Current_npc.Get_Attitude() == Comportement::Neutre)
									if (Current_text.Get_Name() == "Neutre")
										Current_text.Set_Color(Color::Red);
								if (Current_npc.Get_Attitude() == Comportement::Amical)
									if (Current_text.Get_Name() == "Amical")
										Current_text.Set_Color(Color::Red);
							}
						}

						i++;
					}
					Timer = 0;
				}
				if (Current.Get_Name() == "Dialogue")
				{
					Select_Stat.clear();
					Modif = stat_modif::DIALOGUE;
					Select_Stat.push_back(Button_Text("1_1", "Times", 20, Vector2f(126, 26), 2, Vector2f(Menu_Npc.getPosition().x + 200, Menu_Npc.getPosition().y + 15), Color::White));
					int i = 0;
					for (Npc& Current_npc : _npc)
					{
						if (Current_Npc == i)
							for (Button_Text& Current_text : Select_Stat)
								if (Current_npc.Get_Dialogue().Get_Id() == Current_text.Get_Name())
									Current_text.Set_Color(Color::Red);

						i++;
					}
					Timer = 0;
				}
				if (Current.Get_Name() == "Life")
				{
					Select_Stat.clear();
					MState.Get_TextReceived().clear();
					int i = 0;
					for (Npc& Current_npc : _npc)
					{
						if (Current_Npc == i)
							MState.Get_TextReceived() = to_string(Current_npc.Get_LifePoint());

						i++;
					}
					Modif = stat_modif::LIFE;
					Select_Stat.push_back(Button_Text("Life", "Times", 20, Vector2f(126, 26), 2, Vector2f(Menu_Npc.getPosition().x + 200, Menu_Npc.getPosition().y + 65), Color::White));
					Timer = 0;
				}
				if (Current.Get_Name() == "Level")
				{
					Select_Stat.clear();
					MState.Get_TextReceived().clear();
					int i = 0;
					for (Npc& Current_npc : _npc)
					{
						if (Current_Npc == i)
							MState.Get_TextReceived() = to_string(Current_npc.Get_Level());

						i++;
					}
					Modif = stat_modif::LEVEL;
					Select_Stat.push_back(Button_Text("Level", "Times", 20, Vector2f(126, 26), 2, Vector2f(Menu_Npc.getPosition().x + 200, Menu_Npc.getPosition().y + 115), Color::White));
					Timer = 0;
				}
				if (Current.Get_Name() == "Remove")
				{
					int i = 0;
					for (Npc& Current_npc : _npc)
					{
						if (Current_Npc == i)
						{
							_npc.remove(Current_npc);
							Modif_Npc.clear();
							Select_Stat.clear();
							NpcSelect = false;
							break;
						}

						i++;
					}
				}

				find = true;

				if (NpcSelect == false)
					break;
			}
		for (Button_Text& Current : Select_Stat)
			if (Current.Get_Shape().getGlobalBounds().contains(Vector2f(Mouse::getPosition(App.Get_Window()))))
				find = true;

		if (find == false)
		{
			Modif = stat_modif::NONE;
			Menu_Npc.setSize(Vector2f(130, 280));
			Select_Stat.clear();
		}
	}

	if ((Modif == stat_modif::NAME || Modif == stat_modif::ATTITUDE || Modif == stat_modif::DIALOGUE) && Selection.Get_Name() == "NPC")
		if (Mouse::isButtonPressed(Mouse::Left) && !(Keyboard::isKeyPressed(Keyboard::LControl)) && Timer > 0.2f)
			for (Button_Text& Current_Button : Select_Stat)
				if (Current_Button.Get_Shape().getGlobalBounds().contains(Vector2f(Mouse::getPosition(App.Get_Window()))))
				{
					Current_Button.Set_Color(Color::Red);
					if (Modif == stat_modif::NAME)
					{
						int i = 0;
						for (Npc& Current : _npc)
						{
							if (Current_Npc == i)
								Current.Set_Name(Current_Button.Get_Name());

							i++;
						}
					}
					if (Modif == stat_modif::ATTITUDE)
					{
						int i = 0;
						for (Npc& Current : _npc)
						{
							if (Current_Npc == i)
							{
								if (Current_Button.Get_Name() == "Amical")
									Current.Set_Attitude(Comportement::Amical);
								if (Current_Button.Get_Name() == "Neutre")
									Current.Set_Attitude(Comportement::Neutre);
								if (Current_Button.Get_Name() == "Agressif")
									Current.Set_Attitude(Comportement::Agressif);
							}

							i++;
						}
					}
					if (Modif == stat_modif::DIALOGUE)
					{
						int i = 0;
						for (Npc& Current : _npc)
						{
							if (Current_Npc == i)
								Current.Set_Dialogue(Dialogues.Get_Dialogue(Current_Button.Get_Name()));

							i++;
						}
					}
					Timer = 0;
				}
				else
					Current_Button.Set_Color(Color::White);

	if (Modif == stat_modif::LIFE || Modif == stat_modif::LEVEL && Selection.Get_Name() == "NPC")
	{
		if (Modif == stat_modif::LIFE)
		{
			Select_Stat.begin()->Set_String(Select_Stat.begin()->Get_Name() + " : " + MState.Get_TextReceived());
			if (Keyboard::isKeyPressed(Keyboard::Enter))
			{
				int i = 0;
				for (Npc& Current : _npc)
				{
					if (Current_Npc == i)
						Current.Set_Life(stoi(MState.Get_TextReceived()));

					i++;
				}
			}
		}
		if (Modif == stat_modif::LEVEL)
		{
			Select_Stat.begin()->Set_String(Select_Stat.begin()->Get_Name() + " : " + MState.Get_TextReceived());
			if (Keyboard::isKeyPressed(Keyboard::Enter))
			{
				int i = 0;
				for (Npc& Current : _npc)
				{
					if (Current_Npc == i)
						Current.Set_Level(stoi(MState.Get_TextReceived()));

					i++;
				}
			}
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
}

void HUD_Editor::Interaction_SaveAndLoad(Vector2f _mouse, bool& _save, bool& _load)
{
	if (Mouse::isButtonPressed(Mouse::Left) && !(Keyboard::isKeyPressed(Keyboard::LControl)))
		if (Menu.getGlobalBounds().contains(Vector2f(_mouse)))
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
		else if (Current_Button.Get_Name() == "Deco_Layer" && Current_Layer == 2)
			Current_Button.Set_Color(Color::Red);
		else if (Current_Button.Get_Name() == "Player_Layer" && Current_Layer == 3)
			Current_Button.Set_Color(Color::Red);
		else if (Current_Button.Get_Name() == "Front_Layer" && Current_Layer == 4)
			Current_Button.Set_Color(Color::Red);
		else
			Current_Button.Set_Color(Color::White);
	}

	if (Mouse::isButtonPressed(Mouse::Left) && !(Keyboard::isKeyPressed(Keyboard::LControl)))
		if (Menu.getGlobalBounds().contains(Vector2f(_mouse)))
			for (Button_Text& Current_Button : Button)
				if (Current_Button.Get_Shape().getGlobalBounds().contains(_mouse))
				{
					if (Current_Button.Get_Name() == "Back_Layer")
						Current_Layer = 1;
					if (Current_Button.Get_Name() == "Deco_Layer")
						Current_Layer = 2;
					if (Current_Button.Get_Name() == "Player_Layer")
						Current_Layer = 3;
					if (Current_Button.Get_Name() == "Front_Layer")
						Current_Layer = 4;
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
		if (Menu.getGlobalBounds().contains(Vector2f(_mouse)))
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

void HUD_Editor::Interaction_Tile(Vector2f _mouse)
{
	if (Mouse::isButtonPressed(Mouse::Left) && !(Keyboard::isKeyPressed(Keyboard::LControl)))
		if (Menu.getGlobalBounds().contains(Vector2f(_mouse)))
		{
			for (Interface_Maps& Actual_Select : Tile_menu)
				if (FloatRect(Actual_Select.Get_Position().x, Actual_Select.Get_Position().y, Taille_tile, Taille_tile).contains(_mouse) &&
					(Actual_Select.Get_Rank() == Current_Rank || Actual_Select.Get_Rank() == Current_Rank + 1))
				{
					if (Selection.Get_Name() == "NPC")
					{
						Modif_Npc.clear();
						Select_Stat.clear();
						NpcSelect = false;
					}

					Selection.Set_Biome(Actual_Select.Get_Biome());
					Selection.Set_Name(Actual_Select.Get_Name());
					Selection.Set_Tile(Actual_Select.Get_Tile());
					Tile_Select.setPosition(Vector2f(Actual_Select.Get_Position().x + 2, Actual_Select.Get_Position().y + 2));
					IsSelect = true;
				}

			for (Button_Sprite& Current_Shape : Change_Rank)
				if (Current_Shape.Get_Shape().getGlobalBounds().contains(_mouse) && Timer > 0.2f)
				{
					Selection.Set_Name("Rien");
					IsSelect = false;

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
		IsSelect = false;
	}
}

void HUD_Editor::Display_Tilemenu()
{
	for (Interface_Maps& Current_Tile : Tile_menu)
		if (Current_Tile.Get_Rank() == Current_Rank || Current_Tile.Get_Rank() == Current_Rank + 1)
			Current_Tile.display();
}

void HUD_Editor::Display_NpcModif()
{
	if (NpcSelect)
	{
		for (Button_Text& Current : Modif_Npc)
			Current.Display();
		for (Button_Text& Current : Select_Stat)
			Current.Display();
	}
}

void HUD_Editor::Display_MenuShape()
{
	App.Get_Window().draw(Menu);

	if (NpcSelect)
		App.Get_Window().draw(Menu_Npc);
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

void HUD_Editor::Display_ButtonText(bool _player)
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
	else if (Selection.Get_Name() != "NPC")
		Selection.display();

	if (IsSelect)
		App.Get_Window().draw(Tile_Select);
}