#include "Inventory.h"
#include "FontManager.h"
#include "SpriteManager.h"
#include "Hero.h"

Inventory::Inventory()
{
	if (FontList.size() > 0)
	{
		timer = 0;

		Invent = RectangleShape(Vector2f(800, 600));
		Invent.setFillColor(Color(200, 200, 200, 255));
		Invent.setOutlineThickness(5);
		Invent.setOutlineColor(Color::Black);
		Invent.setOrigin(getMidle(Invent));
		Invent.setPosition(960, 540);

		Encadré = RectangleShape(Vector2f(42, 60));
		Encadré.setFillColor(Color::Transparent);
		Encadré.setOutlineThickness(2);
		Encadré.setOutlineColor(Color::Black);
		Encadré.setOrigin(getMidle(Encadré));

		Title = Text("Inventory", getFont("Times"), 50);
		Title.setOrigin(getMidle(Title));
		Title.setPosition(Invent.getPosition().x, Invent.getPosition().y - 280);
		Title.setFillColor(Color(255, 120, 50, 255));

		Current_MenuSub = 0;
		Sub_Menu.push_back(Button_Text("Weapon", "Times", 30, Vector2f(200, 30), 2, Vector2f(Invent.getPosition().x - 250, Invent.getPosition().y - 200), Color(255, 120, 50, 255)));
		Sub_Menu.push_back(Button_Text("Armor", "Times", 30, Vector2f(200, 30), 2, Vector2f(Invent.getPosition().x, Invent.getPosition().y - 200), Color(50, 120, 255, 255)));
		Sub_Menu.push_back(Button_Text("Consumable", "Times", 30, Vector2f(200, 30), 2, Vector2f(Invent.getPosition().x + 250, Invent.getPosition().y - 200), Color(50, 120, 255, 255)));

		Item_Load();
	}
}

void Inventory::Item_Load()
{
	if (Current_MenuSub == 0)
	{
		int x = 0;
		int y = 0;
		for (Weapon* Current : weapon)
		{
			Current->Set_Position(Vector2f(Invent.getPosition().x - 350 + (x * 50), Invent.getPosition().y - 130 + (y * 68)));
			x++;
			if (x == 10)
			{
				x = 0;
				y++;
			}
		}
	}

	int i = 0;
	for (Button_Text& Current : Sub_Menu)
	{
		if (Current_MenuSub == i)
			Current.Set_Color(Color(255, 120, 50, 255));
		else
			Current.Set_Color(Color(50, 120, 255, 255));
		i++;
	}
}

void Inventory::Update(Hero& _player)
{
	timer += MainTime.GetTimeDeltaF();

	if (Keyboard::isKeyPressed(Keyboard::Tab) && timer > 0.2f)
	{
		Current_MenuSub++;
		if (Current_MenuSub >= 3)
			Current_MenuSub = 0;

		Item_Load();
		timer = 0;
	}

	if (Keyboard::isKeyPressed(Keyboard::I) && timer > 0.2f)
	{
		_player.Set_IsInventory(false);
		timer = 0;
	}
}

void Inventory::Display()
{
	App.Get_Window().draw(Invent);
	App.Get_Window().draw(Title);
	for (Button_Text& Current : Sub_Menu)
		Current.Display();

	for (int x = 0; x < 15; x++)
		for (int y = 0; y < 6; y++)
		{
			Encadré.setPosition(Invent.getPosition().x - 350 + (x * 50), Invent.getPosition().y - 130 + (y * 68));
			App.Get_Window().draw(Encadré);
		}
	if (Current_MenuSub == 0)
		for (Weapon* Current : weapon)
			Current->Display_Inventory(Vector2f(2, 2));
}
