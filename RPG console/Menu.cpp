#include "Menu.h"
#include "StateManager.h"
#include "SpriteManager.h"
#include "FontManager.h"
#include "Controle.h"
#include "Data.h"

Menu::Menu(int _menutype)
{
	if (FontList.size() > 0)
	{
		Selection = 0;
		timer = 0;
		Option = false;
		Menu_Load = false;

		if (_menutype == 0)
		{
			for (int i = 0; i < 6; i++)
			{
				string name = "";
				if (i == 0)
					name = "New Game";
				if (i == 1)
					name = "Load Game";
				if (i == 2)
					name = "Editor";
				if (i == 3)
					name = "Options";
				if (i == 4)
					name = "Credit";
				if (i == 5)
					name = "Quit";

				Button.push_back(Button_Text(name, "Ethnocentric", 70, Vector2f(600, 70), 3, Vector2f(480, (1010 - (120 * 5)) + (i * 120)), Color(50, 120, 255, 255)));
			}
		}

		if (_menutype == 1)
		{
			for (int i = 0; i < 3; i++)
			{
				string name = "";
				if (i == 0)
					name = "Resume";
				if (i == 1)
					name = "Save Game";
				if (i == 2)
					name = "Quit";

				Button.push_back(Button_Text(name, "Ethnocentric", 70, Vector2f(600, 70), 3, Vector2f(480, (1010 - (120 * 5)) + (i * 120)), Color(50, 120, 255, 255)));
			}
		}

		Titre = Button_Text("Yardebeul Of Gardebeul", "Ethnocentric", 90, Vector2f(1910, 90), 5, Vector2f(960, 50), Color(50, 120, 255, 255));
		Vue = Views();
	}
}

void Menu::Update_Select()
{
	if (!Menu_Load && !Option)
	{
		int i = 0;
		for (Button_Text& Current_Button : Button)
		{
			if (Selection == i)
				Current_Button.Set_Color(Color::Blue);
			else
				Current_Button.Set_Color(Color(50, 120, 255, 255));

			i++;
		}

		if (Keyboard::isKeyPressed(Keyboard::Up) && timer > 0.2f)
		{
			Selection--;
			if (Selection < 0)
				Selection = Button.size() - 1;
			timer = 0;
		}
		if (Keyboard::isKeyPressed(Keyboard::Down) && timer > 0.2f)
		{
			Selection++;
			if (Selection >= Button.size())
				Selection = 0;
			timer = 0;
		}
	}
	else if (Menu_Load)
	{
		int i = 0;
		for (Bouton_Load& Current_Button : Emplacement)
		{
			if (Selection == i)
				Current_Button.Get_Shape().setOutlineColor(Color::Blue);
			else
				Current_Button.Get_Shape().setOutlineColor(Color(50, 120, 255, 255));

			i++;
		}

		if (Keyboard::isKeyPressed(Keyboard::Up) && timer > 0.2f)
		{
			Selection--;
			if (Selection < 0)
				Selection = Emplacement.size() - 1;
			timer = 0;
		}
		if (Keyboard::isKeyPressed(Keyboard::Down) && timer > 0.2f)
		{
			Selection++;
			if (Selection >= Emplacement.size())
				Selection = 0;
			timer = 0;
		}
	}
}

void Menu::Switch_Mode()
{
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		if (Menu_Load)
		{
			Menu_Load = false;
			Selection = 0;
			Emplacement.clear();
		}
		if (Option)
		{
			Option = false;
			Selection = 0;
		}
	}
}

void Menu::Update_Main(World& _world)
{
	timer += MainTime.GetTimeDeltaF();

	Update_Select();
	Switch_Mode();

	if (!Menu_Load && !Option)
	{
		if (Keyboard::isKeyPressed(Keyboard::Enter) && timer > 0.2f)
		{
			if (Selection == 0)
			{
				_world = World();
				MState.ChangeState(State::GAME);
			}
			if (Selection == 1)
			{
				Menu_Load = true;
				Selection = 0;
				Emplacement.clear();
				Emplacement.push_back(Bouton_Load(Vector2f(960, 300), "Load 1", 1));
				Emplacement.push_back(Bouton_Load(Vector2f(960, 540), "Load 2", 2));
				Emplacement.push_back(Bouton_Load(Vector2f(960, 780), "Load 3", 3));
			}
			if (Selection == 2)
				MState.ChangeState(State::EDITOR);
			if (Selection == 5)
				App.Get_Window().close();
		}
	}
	else if (Menu_Load)
	{
		for (Bouton_Load& Current_Button : Emplacement)
			if (Selection + 1 == Current_Button.Get_Num())
				if (Keyboard::isKeyPressed(Keyboard::Enter) && timer > 0.2f && Current_Button.Get_Name() != "Name : ----")
				{
					_world = World(Current_Button.Get_Num());
					MState.ChangeState(State::GAME);
				}
	}
}

void Menu::Update_Pause(World& _world, bool& _pause)
{
	timer += MainTime.GetTimeDeltaF();

	Update_Select();
	Switch_Mode();

	if (!Menu_Load && !Option)
	{
		if (Keyboard::isKeyPressed(Keyboard::Enter) && timer > 0.2f)
		{
			if (Selection == 0)
				_pause = false;
			if (Selection == 1)
			{
				Menu_Load = true;
				Selection = 0;
				Emplacement.clear();
				Emplacement.push_back(Bouton_Load(Vector2f(960, 300), "Save 1", 1));
				Emplacement.push_back(Bouton_Load(Vector2f(960, 540), "Save 2", 2));
				Emplacement.push_back(Bouton_Load(Vector2f(960, 780), "Save 3", 3));
			}
			if (Selection == 2)
				MState.ChangeState(State::MENU);

			timer = 0;
		}
	}
	else if (Menu_Load)
	{
		for (Bouton_Load& Current_Button : Emplacement)
			if (Selection + 1 == Current_Button.Get_Num())
				if (Keyboard::isKeyPressed(Keyboard::Enter) && timer > 0.2f)
				{
					Data::Save_Player(Selection + 1, MState.Get_World().Get_Hero());
					_world.ScreenShot(Selection + 1);
					Emplacement.clear();
					Emplacement.push_back(Bouton_Load(Vector2f(960, 300), "Save 1", 1));
					Emplacement.push_back(Bouton_Load(Vector2f(960, 540), "Save 2", 2));
					Emplacement.push_back(Bouton_Load(Vector2f(960, 780), "Save 3", 3));

					timer = 0;
				}
	}
}

void Menu::Display_Main()
{
	Vue.Display();

	App.Get_Window().draw(getSprite("Font"));

	for (Bouton_Load& Current_Button : Emplacement)
		Current_Button.Display();

	for (Button_Text& Current_Button : Button)
		Current_Button.Display();

	Titre.Display();
}

void Menu::Display_Pause()
{
	Vue.Display();

	for (Bouton_Load& Current_Button : Emplacement)
		Current_Button.Display();

	for (Button_Text& Current_Button : Button)
		Current_Button.Display();
}

Bouton_Load::Bouton_Load(Vector2f _position, string _name, int _num)
{
	if (FontList.size() > 0)
	{
		Numero = _num;
		Load();

		Shape = RectangleShape(Vector2f(800, 150));
		Shape.setPosition(_position);
		Shape.setFillColor(Color(150, 150, 150, 100));
		Shape.setOutlineThickness(3);
		Shape.setOutlineColor(Color(50, 120, 255, 255));

		if (texture.loadFromFile("../Ressources/Infos/Screen" + to_string(Numero) + ".png"))
		{
			sprite.setTexture(texture);
			sprite.setScale(0.139f, 0.139f);
			sprite.setPosition(_position);
		}
		else if (texture.loadFromFile("../Ressources/Infos/No_Screen.png"))
		{
			sprite.setTexture(texture);
			sprite.setPosition(_position);
		}

		texte.push_back(Text(Name, getFont("Times"), 30));
		texte.back().setPosition(Vector2f(_position.x + 350, _position.y + 10));

		texte.push_back(Text(Level, getFont("Times"), 30));
		texte.back().setPosition(Vector2f(_position.x + 600, _position.y + 10));

		texte.push_back(Text(Time, getFont("Times"), 30));
		texte.back().setPosition(Vector2f(_position.x + 600, _position.y + 75));
	}
}

void Bouton_Load::Load()
{
	string line = "0";

	Name = "Name : ----";
	Level = "Level : --";
	Time = "Time : --h --m";

	ifstream Load("../Ressources/Infos/Save" + to_string(Numero) + ".txt");
	if (Load.is_open())
	{
		while (getline(Load, line))
		{
			if (line.substr(0, line.find(" : ")) == "Name")
				Name = line;

			if (line.substr(0, line.find(" : ")) == "Level")
				Level = line;

			if (line.substr(0, line.find(" : ")) == "Time")
			{
				int Heure, minute = 0;
				int sec = stoi(line.substr(line.find(" : ") + 3));
				Heure = sec / 3600;
				minute = (sec - (Heure * 3600)) / 60;

				Time = "Time : " + to_string(Heure) + "h " + to_string(minute) + "m";
			}
		}

		Load.close();
	}

}

void Bouton_Load::Display()
{
	App.Get_Window().draw(Shape);

	if (sprite.getGlobalBounds().width != 0)
	{
		sprite.setTexture(texture);
		App.Get_Window().draw(sprite);
	}

	for (Text& Current_Text : texte)
		App.Get_Window().draw(Current_Text);
}