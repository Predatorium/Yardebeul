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

		Encadré = RectangleShape(Vector2f(21, 30));
		Encadré.setFillColor(Color::Transparent);
		Encadré.setOutlineThickness(2);
		Encadré.setOutlineColor(Color::Black);
		Encadré.setOrigin(getMidle(Encadré));

		Title = Text("Inventory", getFont("Times"), 50);
		Title.setOrigin(getMidle(Title));
		Title.setPosition(Invent.getPosition().x, Invent.getPosition().y - 280);

		Current_MenuSub = 0;
		Sub_Menu.push_back(Button_Text("Weapon", "Times", 30, Vector2f(200, 30), 2, Vector2f(Invent.getPosition().x - 250, Invent.getPosition().y - 200), Color(50, 120, 255, 255)));
		Sub_Menu.push_back(Button_Text("Armor", "Times", 30, Vector2f(200, 30), 2, Vector2f(Invent.getPosition().x, Invent.getPosition().y - 200), Color(50, 120, 255, 255)));
		Sub_Menu.push_back(Button_Text("Consumable", "Times", 30, Vector2f(200, 30), 2, Vector2f(Invent.getPosition().x + 250, Invent.getPosition().y - 200), Color(50, 120, 255, 255)));
	}
}

void Inventory::Update(Hero& _player)
{
	timer += MainTime.GetTimeDeltaF();

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

	for (int x = 0; x < 10; x++)
		for (int y = 0; y < 10; y++)
		{
			Encadré.setPosition(Invent.getPosition().x - 250 + (x * 25), Invent.getPosition().y - 150 + (y * 34));
			App.Get_Window().draw(Encadré);
		}

	if (Current_MenuSub == 0)
	{
		int x = 0;
		int y = 0;
		for (Weapon* Current : weapon)
		{
			Current->Display(Vector2f(Invent.getPosition().x - 250 + (x * 25), Invent.getPosition().y - 150 + (y * 34)));
			x++;
			if (x == 10)
			{
				x = 0;
				y++;
			}
		}				
	}
}
