#include "Niveau.h"
#include "Menu.h"
#include "Npc_Container.h"

bool Level::Get_Void(Vector2i _position)
{
	for (Maps& Current_Map : Back_Layer)
	{
		if ((int)Current_Map.Get_Position().x / Taille_tile == _position.x &&
			(int)Current_Map.Get_Position().y / Taille_tile == _position.y)
			return false;
	}

	return true;
}

bool Level::Get_MapsPos(Vector2i _position)
{
	for (Maps& Current_Map : Player_Layer)
	{
		if ((int)Current_Map.Get_Position().x / Taille_tile == _position.x &&
			(int)Current_Map.Get_Position().y / Taille_tile == _position.y)
			return true;
	}

	if (Get_Void(_position) == false)
		return false;
	else
		return true;
}

void Level::Collision(Character& _Character)
{
	Vector2i NextPosOnMap;

	NextPosOnMap.x = (int)_Character.Get_Position().x / Taille_tile;
	NextPosOnMap.y = (int)_Character.Get_Position().y / Taille_tile;

	if (_Character.Get_Right() == true)
	{
		NextPosOnMap.x = (int)((_Character.Get_Position().x + (_Character.Get_Sprite().getGlobalBounds().width / 2) + 200 * MainTime.GetTimeDeltaF()) / Taille_tile);
		NextPosOnMap.y = (int)(_Character.Get_Position().y) / Taille_tile;
		if (Get_MapsPos(NextPosOnMap) == true)
			_Character.Set_Right(false);

		NextPosOnMap.x = (int)((_Character.Get_Position().x + (_Character.Get_Sprite().getGlobalBounds().width / 2) + 200 * MainTime.GetTimeDeltaF()) / Taille_tile);
		NextPosOnMap.y = (int)(_Character.Get_Position().y + (_Character.Get_Sprite().getGlobalBounds().height / 2)) / Taille_tile;
		if (Get_MapsPos(NextPosOnMap) == true)
			_Character.Set_Right(false);
	}
	if (_Character.Get_Left() == true)
	{
		NextPosOnMap.x = (int)((_Character.Get_Position().x - (_Character.Get_Sprite().getGlobalBounds().width / 2) - 200 * MainTime.GetTimeDeltaF()) / Taille_tile);
		NextPosOnMap.y = (int)(_Character.Get_Position().y) / Taille_tile;
		if ((_Character.Get_Position().x - (_Character.Get_Sprite().getGlobalBounds().width / 2) - 200 * MainTime.GetTimeDeltaF()) < 0)
			NextPosOnMap.x--;
		if (Get_MapsPos(NextPosOnMap) == true)
			_Character.Set_Left(false);

		NextPosOnMap.x = (int)((_Character.Get_Position().x - (_Character.Get_Sprite().getGlobalBounds().width / 2) - 200 * MainTime.GetTimeDeltaF()) / Taille_tile);
		NextPosOnMap.y = (int)(_Character.Get_Position().y + (_Character.Get_Sprite().getGlobalBounds().height / 2)) / Taille_tile;
		if ((_Character.Get_Position().x - (_Character.Get_Sprite().getGlobalBounds().width / 2) - 200 * MainTime.GetTimeDeltaF()) < 0)
			NextPosOnMap.x--;
		if (Get_MapsPos(NextPosOnMap) == true)
			_Character.Set_Left(false);
	}
	if (_Character.Get_Down() == true)
	{
		NextPosOnMap.x = (int)(_Character.Get_Position().x - (_Character.Get_Sprite().getGlobalBounds().width / 4)) / Taille_tile;
		NextPosOnMap.y = (int)((_Character.Get_Position().y + (_Character.Get_Sprite().getGlobalBounds().height / 1.75) + 200 * MainTime.GetTimeDeltaF()) / Taille_tile);
		if (Get_MapsPos(NextPosOnMap) == true)
			_Character.Set_Down(false);

		NextPosOnMap.x = (int)(_Character.Get_Position().x + (_Character.Get_Sprite().getGlobalBounds().width / 4)) / Taille_tile;
		NextPosOnMap.y = (int)((_Character.Get_Position().y + (_Character.Get_Sprite().getGlobalBounds().height / 1.75) + 200 * MainTime.GetTimeDeltaF()) / Taille_tile);
		if (Get_MapsPos(NextPosOnMap) == true)
			_Character.Set_Down(false);
	}
	if (_Character.Get_Up() == true)
	{
		NextPosOnMap.x = (int)(_Character.Get_Position().x - (_Character.Get_Sprite().getGlobalBounds().width / 4)) / Taille_tile;
		NextPosOnMap.y = (int)((_Character.Get_Position().y - 200 * MainTime.GetTimeDeltaF()) / Taille_tile);
		if ((_Character.Get_Position().y - 200 * MainTime.GetTimeDeltaF()) < 0)
			NextPosOnMap.y--;
		if (Get_MapsPos(NextPosOnMap) == true)
			_Character.Set_Up(false);

		NextPosOnMap.x = (int)(_Character.Get_Position().x + (_Character.Get_Sprite().getGlobalBounds().width / 4)) / Taille_tile;
		NextPosOnMap.y = (int)((_Character.Get_Position().y - 200 * MainTime.GetTimeDeltaF()) / Taille_tile);
		if ((_Character.Get_Position().y - 200 * MainTime.GetTimeDeltaF()) < 0)
			NextPosOnMap.y--;
		if (Get_MapsPos(NextPosOnMap) == true)
			_Character.Set_Up(false);
	}
}

void Level::Load_Map(string _file)
{
	Back_Layer.clear();
	Deco_Layer.clear();
	Player_Layer.clear();
 	Front_Layer.clear();
	NpcList.clear();

	ifstream Read_Map(_file);
	if (Read_Map.is_open())
	{
		string line;
		string layer;

		Read_Map >> Range_Niveau.x;
		Read_Map >> Range_Niveau.y;

		while (getline(Read_Map, line))
		{
			string name = "----";
			int tmpposX = 0;
			int tmpposY = 0;

			if (line == "Back_Layer")
				layer = "Back_Layer";
			else if (line == "Player_Layer")
				layer = "Player_Layer";
			else if (line == "Deco_Layer")
				layer = "Deco_Layer";
			else if (line == "Front_Layer")
				layer = "Front_Layer";
			else if (line == "Npc_List")
				layer = "Npc_List";
			else if (layer == "Back_Layer" || layer == "Player_Layer" || layer == "Front_Layer" || layer == "Deco_Layer")
			{
				int tmpX = 0;
				int tmpY = 0;
				Biomes tmpbiome;

				name = line.substr(0, line.find(" "));
				line.erase(0, line.find(" ") + 1);

				tmpposX = stoi(line.substr(0, line.find(" ")));
				line.erase(0, line.find(" ") + 1);

				tmpposY = stoi(line.substr(0, line.find(" ")));
				line.erase(0, line.find(" ") + 1);

				tmpX = stoi(line.substr(0, line.find(" ")));
				line.erase(0, line.find(" ") + 1);

				tmpY = stoi(line.substr(0, line.find(" ")));
				line.erase(0, line.find(" ") + 1);

				tmpbiome = static_cast<Biomes>(stoi(line));
				line.erase(0, line.size());

				if (layer == "Back_Layer")
					Back_Layer.push_back(Maps(Vector2f(tmpposX, tmpposY), Vector2i(tmpX, tmpY), name, tmpbiome));
				if (layer == "Player_Layer")
					Player_Layer.push_back(Maps(Vector2f(tmpposX, tmpposY), Vector2i(tmpX, tmpY), name, tmpbiome));
				if (layer == "Deco_Layer")
					Deco_Layer.push_back(Maps(Vector2f(tmpposX, tmpposY), Vector2i(tmpX, tmpY), name, tmpbiome));
				if (layer == "Front_Layer")
					Front_Layer.push_back(Maps(Vector2f(tmpposX, tmpposY), Vector2i(tmpX, tmpY), name, tmpbiome));
			}
			else if (layer == "Npc_List")
			{
				name = line.substr(0, line.find(" "));
				line.erase(0, line.find(" ") + 1);

				tmpposX = stoi(line.substr(0, line.find(" ")));
				line.erase(0, line.find(" ") + 1);

				tmpposY = stoi(line.substr(0, line.find(" ")));
				line.erase(0, line.size());

				NpcList.push_back(Npc(Npcs.Get_Npc(name), Vector2f(tmpposX, tmpposY)));
			}

			if (!Read_Map)
				Read_Map.close();
		}
		Read_Map.close();
	}
}

void Level::Save_Map(string _file)
{
	ofstream Write_Map(_file);
	if (Write_Map.is_open())
	{
		list<Maps> tmpMaps = Back_Layer;
		Write_Map << Range_Niveau.x << endl;
		Write_Map << Range_Niveau.y << endl;
		int i = 0;
		Write_Map << "Back_Layer";
		string tmp = "Back_Layer";
		bool done = true;
		while (done)
		{
			for (Maps& Actual_Map : tmpMaps)
			{
				i++;
				Write_Map << endl;
				Write_Map << Actual_Map.Get_Name() << " ";

				Write_Map << to_string(static_cast<int>(Actual_Map.Get_Position().x)) << " ";

				Write_Map << to_string(static_cast<int>(Actual_Map.Get_Position().y)) << " ";

				Write_Map << to_string(Actual_Map.Get_Tile().x) << " ";

				Write_Map << to_string(Actual_Map.Get_Tile().y) << " ";

				Write_Map << to_string(static_cast<int>(Actual_Map.Get_Biome()));
			}
			if (i == Back_Layer.size() && tmp == "Back_Layer")
			{
				Write_Map << endl;
				Write_Map << "Player_Layer";
				tmp = "Player_Layer";
				tmpMaps = Player_Layer;
			}
			if (i == Back_Layer.size() + Player_Layer.size() && tmp == "Player_Layer")
			{
				Write_Map << endl;
				Write_Map << "Deco_Layer";
				tmp = "Deco_Layer";
				tmpMaps = Deco_Layer;
			}
			if (i == Back_Layer.size() + Player_Layer.size() + Deco_Layer.size() && tmp == "Deco_Layer")
			{
				Write_Map << endl;
				Write_Map << "Front_Layer";
				tmp = "Front_Layer";
				tmpMaps = Front_Layer;
			}
			if (i == Back_Layer.size() + Deco_Layer.size() + Player_Layer.size() + Front_Layer.size() && tmp == "Front_Layer")
			{
				Write_Map << endl;
				Write_Map << "Npc_List";
				done = false;
			}
		}

		for (Npc& Current : NpcList)
		{
			Write_Map << endl;
			Write_Map << Current.Get_Name() << " ";
			Write_Map << to_string(static_cast<int>(Current.Get_Position().x)) << " ";
			Write_Map << to_string(static_cast<int>(Current.Get_Position().y));
		}
		Write_Map.close();
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

	for (Npc& Current : NpcList)
		if (Current.Get_Position().y < Player.Get_Position().y)
			if (f(_view, Current.Get_Position()))
			{
				if (Current.Get_Attitude() == Comportement::Agressif)
					Info.setFillColor(Color::Red);
				else
					Info.setFillColor(Color::Green);
				Info.setPosition(Current.Get_Position());
				texture.draw(Info);
			}

	for (Weapon& Current : WeaponList)
		if (Current.Get_Position().y < Player.Get_Position().y)
			if (f(_view, Current.Get_Position()))
			{
				Info.setFillColor(Color::Yellow);
				Info.setPosition(Current.Get_Position());
				texture.draw(Info);
			}
				

	for (Armor& Current : ArmorList)
		if (Current.Get_Position().y < Player.Get_Position().y)
			if (f(_view, Current.Get_Position()))
			{
				Info.setFillColor(Color::Yellow);
				Info.setPosition(Current.Get_Position());
				texture.draw(Info);
			}

	for (Consumable& Current : ConsumableList)
		if (Current.Get_Position().y < Player.Get_Position().y)
			if (f(_view, Current.Get_Position()))
			{
				Info.setFillColor(Color::Yellow);
				Info.setPosition(Current.Get_Position());
				texture.draw(Info);
			}

	Info.setFillColor(Color::Blue);
	Info.setPosition(Player.Get_Position());
	texture.draw(Info);

	for (Npc& Current : NpcList)
		if (Current.Get_Position().y > Player.Get_Position().y)
			if (f(_view, Current.Get_Position()))
			{
				if (Current.Get_Attitude() == Comportement::Agressif)
					Info.setFillColor(Color::Red);
				else
					Info.setFillColor(Color::Green);
				Info.setPosition(Current.Get_Position());
				texture.draw(Info);
			}
				
	for (Weapon& Current : WeaponList)
		if (Current.Get_Position().y > Player.Get_Position().y)
			if (f(_view, Current.Get_Position()))
			{
				Info.setFillColor(Color::Yellow);
				Info.setPosition(Current.Get_Position());
				texture.draw(Info);
			}

	for (Armor& Current : ArmorList)
		if (Current.Get_Position().y > Player.Get_Position().y)
			if (f(_view, Current.Get_Position()))
			{
				Info.setFillColor(Color::Yellow);
				Info.setPosition(Current.Get_Position());
				texture.draw(Info);
			}

	for (Consumable& Current : ConsumableList)
		if (Current.Get_Position().y > Player.Get_Position().y)
			if (f(_view, Current.Get_Position()))
			{
				Info.setFillColor(Color::Yellow);
				Info.setPosition(Current.Get_Position());
				texture.draw(Info);
			}

	for (Maps& Current : Front_Layer)
		if (f(_view, Current.Get_Position()))
			texture.draw(Current.Get_Sprite());

	
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
		Menu_Pause->Update_Pause(this, Pause);

	if (Keyboard::isKeyPressed(Keyboard::F4) && Timer > 0.2f)
	{
		Change_ShapeMap = !Change_ShapeMap;
		Timer = 0;
	}
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
			if (Circle_Collision(Vector2f(Player.Get_Position().x, Player.Get_Position().y + Player.Get_Sprite().getGlobalBounds().height / 2.1f),
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
		Player.Get_Inventory().Display();

	if (Pause == true)
		Menu_Pause->Display_Pause();

	if (Change_ShapeMap)
	{
		R_MiniMap.setTexture(&Get_TextureMap(&Views::Occlusion_CullingRectangle, Screen));

		App.Get_Window().draw(R_MiniMap);
	}
	if (!Change_ShapeMap)
	{
		C_MiniMap.setTexture(&Get_TextureMap(&Views::Occlusion_CullingCircle, Screen));
		
		C_MiniMap.setTextureRect(IntRect(420, 0, 1080, 1080));
		App.Get_Window().draw(C_MiniMap);
	}
}