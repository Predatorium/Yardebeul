#include "Niveau.h"
#include "Menu.h"
#include "Npc_Container.h"

bool Level::Get_Void(Vector2f _position)
{
	for (Maps& Current_Map : Back_Layer)
		if (FloatRect(Current_Map.Get_Position().x, Current_Map.Get_Position().y, Taille_tile, Taille_tile).contains(_position))
			return false;

	return true;
}

bool Level::Get_MapsPos(Vector2f _position)
{
	for (Maps& Current_Map : Player_Layer)
		if (FloatRect(Current_Map.Get_Position().x, Current_Map.Get_Position().y,Taille_tile,Taille_tile).contains(_position))
			return true;

	if (Get_Void(_position) == false)
		return false;
	else
		return true;
}

void Level::Collision(Character& _Character)
{
	Vector2f NextPosOnMap;

	NextPosOnMap.x = _Character.Get_Position().x;
	NextPosOnMap.y = _Character.Get_Position().y;

	if (_Character.Get_Right() == true)
	{
		NextPosOnMap.x = ((_Character.Get_Position().x + (_Character.Get_Sprite().getGlobalBounds().width / 2) + 200 * MainTime.GetTimeDeltaF()));
		NextPosOnMap.y = (_Character.Get_Position().y);
		if (Get_MapsPos(NextPosOnMap) == true)
			_Character.Set_Right(false);

		NextPosOnMap.x = ((_Character.Get_Position().x + (_Character.Get_Sprite().getGlobalBounds().width / 2) + 200 * MainTime.GetTimeDeltaF()));
		NextPosOnMap.y = (_Character.Get_Position().y + (_Character.Get_Sprite().getGlobalBounds().height / 2));
		if (Get_MapsPos(NextPosOnMap) == true)
			_Character.Set_Right(false);
	}
	if (_Character.Get_Left() == true)
	{
		NextPosOnMap.x = ((_Character.Get_Position().x - (_Character.Get_Sprite().getGlobalBounds().width / 2) - 200 * MainTime.GetTimeDeltaF()));
		NextPosOnMap.y = (_Character.Get_Position().y);
		if ((_Character.Get_Position().x - (_Character.Get_Sprite().getGlobalBounds().width / 2) - 200 * MainTime.GetTimeDeltaF()) < 0)
			NextPosOnMap.x--;
		if (Get_MapsPos(NextPosOnMap) == true)
			_Character.Set_Left(false);

		NextPosOnMap.x = ((_Character.Get_Position().x - (_Character.Get_Sprite().getGlobalBounds().width / 2) - 200 * MainTime.GetTimeDeltaF()));
		NextPosOnMap.y = (_Character.Get_Position().y + (_Character.Get_Sprite().getGlobalBounds().height / 2));
		if ((_Character.Get_Position().x - (_Character.Get_Sprite().getGlobalBounds().width / 2) - 200 * MainTime.GetTimeDeltaF()) < 0)
			NextPosOnMap.x--;
		if (Get_MapsPos(NextPosOnMap) == true)
			_Character.Set_Left(false);
	}
	if (_Character.Get_Down() == true)
	{
		NextPosOnMap.x = (_Character.Get_Position().x - (_Character.Get_Sprite().getGlobalBounds().width / 4));
		NextPosOnMap.y = ((_Character.Get_Position().y + (_Character.Get_Sprite().getGlobalBounds().height / 1.75) + 200 * MainTime.GetTimeDeltaF()));
		if (Get_MapsPos(NextPosOnMap) == true)
			_Character.Set_Down(false);

		NextPosOnMap.x = (_Character.Get_Position().x + (_Character.Get_Sprite().getGlobalBounds().width / 4));
		NextPosOnMap.y = ((_Character.Get_Position().y + (_Character.Get_Sprite().getGlobalBounds().height / 1.75) + 200 * MainTime.GetTimeDeltaF()));
		if (Get_MapsPos(NextPosOnMap) == true)
			_Character.Set_Down(false);
	}
	if (_Character.Get_Up() == true)
	{
		NextPosOnMap.x = (_Character.Get_Position().x - (_Character.Get_Sprite().getGlobalBounds().width / 4));
		NextPosOnMap.y = ((_Character.Get_Position().y - 200 * MainTime.GetTimeDeltaF()));
		if ((_Character.Get_Position().y - 200 * MainTime.GetTimeDeltaF()) < 0)
			NextPosOnMap.y--;
		if (Get_MapsPos(NextPosOnMap) == true)
			_Character.Set_Up(false);

		NextPosOnMap.x = (_Character.Get_Position().x + (_Character.Get_Sprite().getGlobalBounds().width / 4));
		NextPosOnMap.y = ((_Character.Get_Position().y - 200 * MainTime.GetTimeDeltaF()));
		if ((_Character.Get_Position().y - 200 * MainTime.GetTimeDeltaF()) < 0)
			NextPosOnMap.y--;
		if (Get_MapsPos(NextPosOnMap) == true)
			_Character.Set_Up(false);
	}
}

void Level::Destroy_List()
{
	for (Npc& Current_Npc : NpcList)
		if (Current_Npc.Get_LifePoint() <= 0)
		{
			NpcList.remove(Current_Npc);
			break;
		}

	for (Weapon& Current : WeaponList)
		if (Current.Get_PickUp() == true)
		{
			WeaponList.remove(Current);
			break;
		}

	for (Armor& Current : ArmorList)
		if (Current.Get_PickUp() == true)
		{
			ArmorList.remove(Current);
			break;
		}

	for (Consumable& Current : ConsumableList)
		if (Current.Get_PickUp() == true)
		{
			ConsumableList.remove(Current);
			break;
		}
}

const Texture& Level::Get_TextureMap(function<bool(Views&, Vector2f)> f, Views _view)
{
	static RenderTexture texture;
	texture.create(1920, 1080);
	texture.setView(_view);

	CircleShape Info(30);
	Info.setOrigin(Info.getRadius(), Info.getRadius());

	texture.clear(Color::Black);

	for (Maps& Current : Back_Layer)
		if (f(_view,Current.Get_Position()))
			texture.draw(Current.Get_Sprite());

	for (Maps& Current : Player_Layer)
		if (f(_view, Current.Get_Position()))
			texture.draw(Current.Get_Sprite());

	for (Maps& Current : Deco_Layer)
		if (f(_view, Current.Get_Position()))
			texture.draw(Current.Get_Sprite());

	Info.setPointCount(3);
	for (Npc& Current : NpcList)
			if (f(_view, Current.Get_Position()))
			{
				if (Current.Get_Attitude() == Comportement::Agressif)
					Info.setFillColor(Color::Red);
				else
					Info.setFillColor(Color::Green);
				Info.setPosition(Current.Get_Position());
				texture.draw(Info);
			}
	Info.setPointCount(5);
	for (Weapon& Current : WeaponList)
			if (f(_view, Current.Get_Position()))
			{
				Info.setFillColor(Color::Yellow);
				Info.setPosition(Current.Get_Position());
				texture.draw(Info);
			}

	for (Armor& Current : ArmorList)
			if (f(_view, Current.Get_Position()))
			{
				Info.setFillColor(Color::Yellow);
				Info.setPosition(Current.Get_Position());
				texture.draw(Info);
			}

	for (Consumable& Current : ConsumableList)
			if (f(_view, Current.Get_Position()))
			{
				Info.setFillColor(Color::Yellow);
				Info.setPosition(Current.Get_Position());
				texture.draw(Info);
			}

	Info.setPointCount(30);
	for (Maps& Current : Front_Layer)
		if (f(_view, Current.Get_Position()))
			texture.draw(Current.Get_Sprite());

	Info.setFillColor(Color::Blue);
	Info.setPosition(Player.Get_Position());
	texture.draw(Info);
	
	texture.display();

	texture.getTexture().isSmooth();
	return texture.getTexture();
}

void Level::ScreenShot(int _party)
{
	RenderTexture texture;
	string path = "../Ressources/Infos/Screen" + to_string(_party) + ".png";
	View view(Player.Get_Position(), Vector2f(1920, 1080));
	texture.create(1920, 1080);

	texture.clear(Color::Black);
	view.setCenter(Player.Get_Position());
	texture.setView(view);

	for (Maps Current_Maps : Back_Layer)
	{
		Current_Maps.Get_Sprite().setTextureRect(IntRect(Current_Maps.Get_Tile().x * Taille_tile, Current_Maps.Get_Tile().y * Taille_tile, Taille_tile, Taille_tile));
		Current_Maps.Get_Sprite().setPosition(Current_Maps.Get_Position());
		texture.draw(Current_Maps.Get_Sprite());
	}
	for (Maps Current_Maps : Player_Layer)
	{
		Current_Maps.Get_Sprite().setTextureRect(IntRect(Current_Maps.Get_Tile().x * Taille_tile, Current_Maps.Get_Tile().y * Taille_tile, Taille_tile, Taille_tile));
		Current_Maps.Get_Sprite().setPosition(Current_Maps.Get_Position());
		texture.draw(Current_Maps.Get_Sprite());
	}
	for (Maps Current_Maps : Deco_Layer)
	{
		Current_Maps.Get_Sprite().setTextureRect(IntRect(Current_Maps.Get_Tile().x * Taille_tile, Current_Maps.Get_Tile().y * Taille_tile, Taille_tile, Taille_tile));
		Current_Maps.Get_Sprite().setPosition(Current_Maps.Get_Position());
		texture.draw(Current_Maps.Get_Sprite());
	}
	for (Maps Current_Maps : Front_Layer)
	{
		Current_Maps.Get_Sprite().setTextureRect(IntRect(Current_Maps.Get_Tile().x * Taille_tile, Current_Maps.Get_Tile().y * Taille_tile, Taille_tile, Taille_tile));
		Current_Maps.Get_Sprite().setPosition(Current_Maps.Get_Position());
		texture.draw(Current_Maps.Get_Sprite());
	}

	texture.display();

	texture.getTexture().copyToImage().saveToFile(path);
}

void Level::Update()
{
	Timer += MainTime.GetTimeDeltaF();

	if (Pause == false)
	{
		Collision(Player);
		if (!IsDialogue && !Player.Get_IsInventory())
			Player.Update();
		if (Player.Get_IsInventory())
			Player.Get_Inventory().Update(Player);

		Destroy_List();

		for (Npc& Current_Npc : NpcList)
		{
			Collision(Current_Npc);

			if (Current_Npc.Get_Attitude() == Comportement::Agressif && IsDialogue == false)
				Current_Npc.Update_Attack(Player);

			if (Current_Npc.Get_Attitude() == Comportement::Amical)
				Current_Npc.Update_Dialogue(IsDialogue, Player);
		}

		for (Weapon& Current : WeaponList)
			Current.Take_Item(Player);
		for (Armor& Current : ArmorList)
			Current.Take_Item(Player);
		for (Consumable& Current : ConsumableList)
			Current.Take_Item(Player);

		if (Keyboard::isKeyPressed(Keyboard::Escape))
			Pause = true;

		Vue.Update(Range_Niveau, Player.Get_Position());
		Screen.Update_MiniMap(Range_Niveau, Player.Get_Position()); 
	}

	if (Pause == true)
		Menu_Pause->Update_Pause(Pause);
}

void Level::Display()
{
	Vue.Display();

	for (Maps& Current : Back_Layer)
		if (Vue.Occlusion_CullingRectangle(Current.Get_Position()))
			Current.Display();

	for (Maps& Current : Player_Layer)
		if (Vue.Occlusion_CullingRectangle(Current.Get_Position()))
			Current.Display();

	for (Maps& Current : Deco_Layer)
		if (Vue.Occlusion_CullingRectangle(Current.Get_Position()))
			Current.Display();

	for (Npc& Current : NpcList)
		if (Current.Get_Position().y < Player.Get_Position().y)
			if (Vue.Occlusion_CullingRectangle(Current.Get_Position()))
				Current.Display();

	for (Weapon& Current : WeaponList)
		if (Current.Get_Position(). y < Player.Get_Position().y)
			if (Vue.Occlusion_CullingRectangle(Current.Get_Position()))
				Current.Display(Player.Get_Position());

	for (Armor& Current : ArmorList)
		if (Current.Get_Position().y < Player.Get_Position().y)
			if (Vue.Occlusion_CullingRectangle(Current.Get_Position()))
				Current.Display(Player.Get_Position());

	for (Consumable& Current : ConsumableList)
		if (Current.Get_Position().y < Player.Get_Position().y)
			if (Vue.Occlusion_CullingRectangle(Current.Get_Position()))
				Current.Display(Player.Get_Position());

	Player.Display();

	for (Npc& Current : NpcList)
		if (Current.Get_Position().y > Player.Get_Position().y)
			if (Vue.Occlusion_CullingRectangle(Current.Get_Position()))
				Current.Display();

	for (Weapon& Current : WeaponList)
		if (Current.Get_Position().y > Player.Get_Position().y)
			if (Vue.Occlusion_CullingRectangle(Current.Get_Position()))
				Current.Display(Player.Get_Position());

	for (Armor& Current : ArmorList)
		if (Current.Get_Position().y > Player.Get_Position().y)
			if (Vue.Occlusion_CullingRectangle(Current.Get_Position()))
				Current.Display(Player.Get_Position());

	for (Consumable& Current : ConsumableList)
		if (Current.Get_Position().y > Player.Get_Position().y)
			if (Vue.Occlusion_CullingRectangle(Current.Get_Position()))
				Current.Display(Player.Get_Position());

	for (Maps& Current : Front_Layer)
	{
		if (Vue.Occlusion_CullingRectangle(Current.Get_Position()))
		{
			if (Circle_Collision(Vector2f(Player.Get_Position().x, Player.Get_Position().y + Player.Get_Sprite().getGlobalBounds().height / 2.6f),
				Vector2f(Current.Get_Position().x + 16, Current.Get_Position().y + 16), 30, Player.Get_Sprite().getGlobalBounds().width))
				Current.Get_Sprite().setColor(Color(255, 255, 255, 100));
			else
				Current.Get_Sprite().setColor(Color::White);

			Current.Display();

			Current.Get_Sprite().setColor(Color::White);
		}
	}

	App.Get_Window().setView(App.Get_Window().getDefaultView());

	for (Npc& Current : NpcList)
		if (Vue.Occlusion_CullingRectangle(Current.Get_Position()))
			Current.Display_Dialogue();

	if (Player.Get_IsInventory() == true)
	{
		Player.Get_Inventory().Display();
		Player.Get_Inventory().Display_CurrentItem(Player);
	}

	if (Pause == true)
		Menu_Pause->Display_Pause();

	C_MiniMap.setTexture(&Get_TextureMap(&Views::Occlusion_CullingCircle, Screen));
	C_MiniMap.setTextureRect(IntRect(420, 0, 1080, 1080));
	App.Get_Window().draw(C_MiniMap);
}