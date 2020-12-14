#include "Editeur.h"
#include "StateManager.h"
#include "SpriteManager.h"
#include "FontManager.h"
#include "Map_Manager.h"

Editeur::Editeur()
{
	if (FontList.size() > 0)
	{
		Range_Niveau = Vector2i(5, 5);
		Timer = 0;

		App_Grille = true;
		PlayerIsPresent = false;
		IsDialogue = false;

		Save = false;
		Save_New_Map = false;

		Grille.setSize(Vector2f(30, 30));
		Grille.setFillColor(Color::Transparent);
		Grille.setOutlineThickness(1);
		Grille.setOutlineColor(Color::Blue);

		Hud = HUD_Editor();

		if (Map_List.size() > 0)
		{
			Load = true;
			int i = 0;
			for (Map_Manager* Current_Map : Map_List)
			{
				Dispo_Map.push_back(Button_Text(Current_Map->Get_Name(), "Times", 50, Vector2f(200, 100), 5, Vector2f(960, 540 - (110 * (Map_List.size() / 2)) + ((i - 1) * 110)), Color::White));
				i++;
			}
		}
		else
			Load = false;

		New_map = Button_Text("New", "Times", 50, Vector2f(200, 100), 5, Vector2f(960, 1025), Color::White);

		Vue = Views(Vector2f(840, 420), Vector2f(1920, 1080), FloatRect(0.f, 0.f, 1.f, 1.f));
				
		Player = Hero(Vector2f(50, 50));
		Screen = Views();
	}
}

void Editeur::SaveNewMap()
{
	if (Mouse::isButtonPressed(Mouse::Left) && !(Keyboard::isKeyPressed(Keyboard::LControl)) && !Save_New_Map && Save)
	{
		for (Button_Text& Current_Button : Dispo_Map)
			if (Current_Button.Get_Shape().getGlobalBounds().contains(Mouse_Position))
			{
				Save_Map(Get_PathMap(Current_Button.Get_Name()));
				Save = false;
				break;
			}

		if (New_map.Get_Shape().getGlobalBounds().contains(Mouse_Position))
		{
			StateManager::Get_Singleton().Get_TextReceived().clear();
			Save_New_Map = true;
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Enter) && Save_New_Map && Save)
	{
		Map_List.push_back(new Map_Manager(StateManager::Get_Singleton().Get_TextReceived(), "../Ressources/Map/" + StateManager::Get_Singleton().Get_TextReceived() + ".txt"));
		SaveMap(Get_Map(StateManager::Get_Singleton().Get_TextReceived()));
		Save_Map(Get_PathMap(StateManager::Get_Singleton().Get_TextReceived()));
		Dispo_Map.clear();

		int i = 0;
		for (Map_Manager* Current_Map : Map_List)
		{
			Dispo_Map.push_back(Button_Text(Current_Map->Get_Name(), "Times", 50, Vector2f(200, 100), 5, Vector2f(960, 540 - (110 * (Map_List.size() / 2)) + ((i - 1) * 110)), Color::White));
			i++;
		}

		StateManager::Get_Singleton().Get_TextReceived().clear();
		Save_New_Map = false;
		Save = false;
	}
}

void Editeur::LoadNewMap()
{
	if (Mouse::isButtonPressed(Mouse::Left) && !(Keyboard::isKeyPressed(Keyboard::LControl)) && Load)
	{
		for (Button_Text& Current_Button : Dispo_Map)
			if (Current_Button.Get_Shape().getGlobalBounds().contains(Mouse_Position))
			{
				Load_Map(Get_PathMap(Current_Button.Get_Name()));
				Load = false;
				break;
			}

		if (New_map.Get_Shape().getGlobalBounds().contains(Mouse_Position))
		{
			Back_Layer.clear();
			Deco_Layer.clear();
			Player_Layer.clear();
			Front_Layer.clear();
			NpcList.clear();
			Load = false;
		}
	}
}

void Editeur::Set_MousePos(Vector2f _position)
{
	Mouse_Position = _position;
	if (_position.x < 0)
		Mouse_Position.x -= 32;
	if (_position.y < 0)
		Mouse_Position.y -= 32;
}

void Editeur::Move_Map(int _coloulig, int _ajoures)
{
	for (Maps& Current_Map : Back_Layer)
	{
		if (_ajoures == 0)
		{
			if (_coloulig == 0)
				Current_Map.Set_Position(Vector2f(Current_Map.Get_Position().x + Taille_tile, Current_Map.Get_Position().y));
			if (_coloulig == 1)
				Current_Map.Set_Position(Vector2f(Current_Map.Get_Position().x, Current_Map.Get_Position().y + Taille_tile));
		}
		if (_ajoures == 1)
		{
			if (_coloulig == 0)
				Current_Map.Set_Position(Vector2f(Current_Map.Get_Position().x - Taille_tile, Current_Map.Get_Position().y));
			if (_coloulig == 1)
				Current_Map.Set_Position(Vector2f(Current_Map.Get_Position().x, Current_Map.Get_Position().y - Taille_tile));
		}
	}
	for (Maps& Current_Map : Player_Layer)
	{
		if (_ajoures == 0)
		{
			if (_coloulig == 0)
				Current_Map.Set_Position(Vector2f(Current_Map.Get_Position().x + Taille_tile, Current_Map.Get_Position().y));
			if (_coloulig == 1)
				Current_Map.Set_Position(Vector2f(Current_Map.Get_Position().x, Current_Map.Get_Position().y + Taille_tile));
		}
		if (_ajoures == 1)
		{
			if (_coloulig == 0)
				Current_Map.Set_Position(Vector2f(Current_Map.Get_Position().x - Taille_tile, Current_Map.Get_Position().y));
			if (_coloulig == 1)
				Current_Map.Set_Position(Vector2f(Current_Map.Get_Position().x, Current_Map.Get_Position().y - Taille_tile));
		}
	}
	for (Maps& Current_Map : Front_Layer)
	{
		if (_ajoures == 0)
		{
			if (_coloulig == 0)
				Current_Map.Set_Position(Vector2f(Current_Map.Get_Position().x + Taille_tile, Current_Map.Get_Position().y));
			if (_coloulig == 1)
				Current_Map.Set_Position(Vector2f(Current_Map.Get_Position().x, Current_Map.Get_Position().y + Taille_tile));
		}
		if (_ajoures == 1)
		{
			if (_coloulig == 0)
				Current_Map.Set_Position(Vector2f(Current_Map.Get_Position().x - Taille_tile, Current_Map.Get_Position().y));
			if (_coloulig == 1)
				Current_Map.Set_Position(Vector2f(Current_Map.Get_Position().x, Current_Map.Get_Position().y - Taille_tile));
		}
	}
}

void Editeur::Resize_Map()
{
	Vector2i Max(0, 0);
	Vector2i Min(Range_Niveau);
	for (Maps& Current_Map : Back_Layer)
	{
		if ((int)Current_Map.Get_Position().x / Taille_tile < Min.x)
			Min.x = ((int)Current_Map.Get_Position().x / Taille_tile);

		if ((int)Current_Map.Get_Position().y / Taille_tile < Min.y)
			Min.y = ((int)Current_Map.Get_Position().y / Taille_tile);

		if ((int)Current_Map.Get_Position().x / Taille_tile >= Max.x)
			Max.x = ((int)Current_Map.Get_Position().x / Taille_tile) + 1;

		if ((int)Current_Map.Get_Position().y / Taille_tile >= Max.y)
			Max.y = ((int)Current_Map.Get_Position().y / Taille_tile) + 1;
	}
	for (Maps& Current_Map : Player_Layer)
	{
		if ((int)Current_Map.Get_Position().x / Taille_tile < Min.x)
			Min.x = ((int)Current_Map.Get_Position().x / Taille_tile);

		if ((int)Current_Map.Get_Position().y / Taille_tile < Min.y)
			Min.y = ((int)Current_Map.Get_Position().y / Taille_tile);

		if ((int)Current_Map.Get_Position().x / Taille_tile >= Max.x)
			Max.x = ((int)Current_Map.Get_Position().x / Taille_tile) + 1;

		if ((int)Current_Map.Get_Position().y / Taille_tile >= Max.y)
			Max.y = ((int)Current_Map.Get_Position().y / Taille_tile) + 1;
	}

	if (Min.x > 0)
		for (int i = 0; i < Min.x; i++)
			Move_Map(0, 1);
	if (Min.y > 0)
		for (int i = 0; i < Min.y; i++)
			Move_Map(1, 1);

	if (Min.x < 0)
		for (int i = Min.x; i < 0; i++)
			Move_Map(0, 0);
	if (Min.y < 0)
		for (int i = Min.y; i < 0; i++)
			Move_Map(1, 0);
	
	Range_Niveau = Max;

	if (Range_Niveau.x < 5)
		Range_Niveau.x = 5;
	if (Range_Niveau.y < 5)
		Range_Niveau.y = 5;
}

void Editeur::Interaction_Map()
{
	if (Mouse::isButtonPressed(Mouse::Left) && !(Keyboard::isKeyPressed(Keyboard::LControl)))
		if (!(Hud.Get_MenuShape().getGlobalBounds().contains(Vector2f(Mouse::getPosition(App.Get_Window())))))
		{
			if (Hud.Get_Layer() == 1)
				Set_Map(Back_Layer);
			if (Hud.Get_Layer() == 2)
				Set_Map(Deco_Layer);
			if (Hud.Get_Layer() == 3)
				Set_Map(Player_Layer);
			if (Hud.Get_Layer() == 4)
				Set_Map(Front_Layer);
		}

	if (Keyboard::isKeyPressed(Keyboard::G) && Timer > 0.2f)
	{
		App_Grille = !App_Grille;
		Timer = 0;
	}

	Resize_Map();
}

void Editeur::Set_Map(vector<Maps> &_layer)
{
	bool FindMap = false;
	for (Maps& Current_Map : _layer)
		if (FloatRect(Current_Map.Get_Position().x, Current_Map.Get_Position().y, Taille_tile, Taille_tile).contains(Mouse_Position))
		{
			if (Hud.Get_Selection().Get_Name() == "Rien")
			{
				Current_Map.Set_Actif(false);
				Erase_Map();
				FindMap = true;
			}
			else if (Hud.Get_Selection().Get_Name() != "NPC")
			{
				Current_Map.Set_Biome(Hud.Get_Selection().Get_Biome());
				Current_Map.Set_Name(Hud.Get_Selection().Get_Name());
				Current_Map.Set_Tile(Hud.Get_Selection().Get_Tile());
				FindMap = true;
			}
		}

	if (Hud.Get_Selection().Get_Name() != "Rien" && Mouse_Position.x <= (Range_Niveau.x + 1) * Taille_tile &&
		Mouse_Position.y <= (Range_Niveau.y + 1) * Taille_tile && Mouse_Position.x >= -64 && Mouse_Position.y >= -64)
		if (!FindMap && Hud.Get_Selection().Get_Name() != "NPC")
			_layer.push_back(Maps(Vector2f(static_cast<int>(Mouse_Position.x / Taille_tile) * Taille_tile, (static_cast<int>(Mouse_Position.y / Taille_tile) * Taille_tile)), Hud.Get_Selection().Get_Tile(), Hud.Get_Selection().Get_Name(), Hud.Get_Selection().Get_Biome()));

}

void Editeur::Erase_Map()
{
	for (int i = 0; i < Back_Layer.size(); i++)
		if (Back_Layer[i].Get_Actif() == false)
		{
			Back_Layer.erase(Back_Layer.begin() + i);
				i--;
		}

	for (int i = 0; i < Deco_Layer.size(); i++)
		if (Deco_Layer[i].Get_Actif() == false)
		{
			Deco_Layer.erase(Deco_Layer.begin() + i);
			i--;
		}

	for (int i = 0; i < Player_Layer.size(); i++)
		if (Player_Layer[i].Get_Actif() == false)
		{
			Player_Layer.erase(Player_Layer.begin() + i);
			i--;
		}

	for (int i = 0; i < Front_Layer.size(); i++)
		if (Front_Layer[i].Get_Actif() == false)
		{
			Front_Layer.erase(Front_Layer.begin() + i);
			i--;
		}
}

void Editeur::Update()
{
	Timer += MainTime.GetTimeDeltaF();
	Hud.Add_Timer(MainTime.GetTimeDeltaF());

	if (!PlayerIsPresent && !Save && !Load)
	{
		Set_MousePos(App.Get_Window().mapPixelToCoords(Mouse::getPosition(App.Get_Window()), Vue.Get_View()));

		Interaction_Map();
		Hud.Set_Npc(Mouse_Position, NpcList, Range_Niveau);

		Set_MousePos(Vector2f(Mouse::getPosition(App.Get_Window())));

		Hud.Interaction_Biome(Mouse_Position);
		Hud.Interaction_Tile(Mouse_Position);
		Hud.Interaction_NPC(Mouse_Position);
		Hud.Interaction_SaveAndLoad(Mouse_Position, Save, Load);
		Hud.Interaction_Layer(Mouse_Position);
		Hud.Interaction_MenuAndTest(Mouse_Position, PlayerIsPresent);
		
		Hud.Get_Selection().Set_Position(Vector2f(Mouse::getPosition(App.Get_Window())));
		Vue.Update(Range_Niveau, Hud.Get_Move(), Mouse_Position);
	}
	else if (Load)
	{
		Set_MousePos(Vector2f(Mouse::getPosition(App.Get_Window())));
		LoadNewMap();
	}
	else if (Save)
	{
		Set_MousePos(Vector2f(Mouse::getPosition(App.Get_Window())));
		SaveNewMap();
	}
	else
	{
		Mouse_Position = Vector2f(Mouse::getPosition(App.Get_Window()));

		Collision(Player);
		if (IsDialogue == false)
			Player.Update();

		Destroy_List();

		for (Npc& Current_Npc : NpcList)
		{
			Collision(Current_Npc);

			if (Current_Npc.Get_Attitude() == Comportement::Agressif && IsDialogue == false)
				Current_Npc.Update_Attack(Player);

			if (Current_Npc.Get_Attitude() == Comportement::Amical)
				Current_Npc.Update_Dialogue(IsDialogue, Player);
		}

		Hud.Interaction_MenuAndTest(Mouse_Position, PlayerIsPresent);
		Vue.Update(Range_Niveau, Player);
	}

	if(!Save && !Load)
		Hud.Interaction_MenuAndTest(Mouse_Position, PlayerIsPresent);
}

void Editeur::Display_SaveAndLoad()
{
	for (Button_Text& CurrentBouton : Dispo_Map)
		CurrentBouton.Display();

	New_map.Display();
}

void Editeur::Display_NewSave()
{
	static Text Name("",getFont("Times"),50);
	Name.setPosition(Vector2f(960, 540));
	Name.setFillColor(Color::Blue);
	Name.setOrigin(getMidle(Name));
	Name.setString(StateManager::Get_Singleton().Get_TextReceived());

	App.Get_Window().draw(Name);
}

void Editeur::Display_HUD()
{
	Screen.Display();

	if (!PlayerIsPresent)
	{
		Hud.Display_MenuShape();
		Hud.Display_ButtonRank();
		Hud.Display_LoadAndSave();
		Hud.Display_Move();
		Hud.Display_Tilemenu();
		Hud.Display_NpcModif();
	}

	Hud.Display_ButtonText(PlayerIsPresent);

	if (!PlayerIsPresent && !Load && !Save)
	{
		Hud.Display_Selection(Grille);
	}

	if (PlayerIsPresent)
		for (Npc& Current : NpcList)
			Current.Display_Dialogue();
}

void Editeur::Display_Map()
{
	if (!PlayerIsPresent)
	{
		Vue.Display();
		display_Etage();

		if (App_Grille)
			for (int y = 0; y < Range_Niveau.y; y++)
				for (int x = 0; x < Range_Niveau.x; x++)
				{
					Grille.setPosition(Vector2f(x * Taille_tile, y * Taille_tile));
					App.Get_Window().draw(Grille);
				}
	}
	else
		Display();
}

void Editeur::display_Etage()
{
	for (Maps& Current_Map : Back_Layer)
	{
		if (Hud.Get_Layer() != 1)
			getSprite(Current_Map.Get_Name()).setColor(Color(150, 150, 150, 160));
		else
			getSprite(Current_Map.Get_Name()).setColor(Color::White);

		Current_Map.Display();

		getSprite(Current_Map.Get_Name()).setColor(Color::White);
	}

	for (Maps& Current_Map : Deco_Layer)
	{
		if (Hud.Get_Layer() != 2)
			getSprite(Current_Map.Get_Name()).setColor(Color(150, 150, 150, 160));
		else
			getSprite(Current_Map.Get_Name()).setColor(Color::White);

		Current_Map.Display();

		getSprite(Current_Map.Get_Name()).setColor(Color::White);
	}

	for (Maps& Current_Map : Player_Layer)
	{
		if (Hud.Get_Layer() != 3)
			getSprite(Current_Map.Get_Name()).setColor(Color(150, 150, 150, 160));
		else
			getSprite(Current_Map.Get_Name()).setColor(Color::White);

		Current_Map.Display();

		getSprite(Current_Map.Get_Name()).setColor(Color::White);
	}

	for (Npc& Current : NpcList)
		Current.Display();

	for (Maps& Current_Map : Front_Layer)
	{
		if (Hud.Get_Layer() != 4)
			getSprite(Current_Map.Get_Name()).setColor(Color(150, 150, 150, 160));
		else
			getSprite(Current_Map.Get_Name()).setColor(Color::White);

		Current_Map.Display();

		getSprite(Current_Map.Get_Name()).setColor(Color::White);
	}
}

void Editeur::Display_editeur()
{
	Display_Map();

	Display_HUD();

	if ((Save && !Save_New_Map) || Load)
		Display_SaveAndLoad();

	if (Save_New_Map)
		Display_NewSave();
}