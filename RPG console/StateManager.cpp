#include "StateManager.h"
#include "SpriteManager.h"
#include "SoundManager.h"
#include "FontManager.h"
#include "Map_Manager.h"
#include "Dialogue_Container.h"
#include "Npc_Container.h"
#include "Effects_Container.h"
#include "Armors_Container.h"
#include "Weapons_Container.h"
#include "Consumables_Container.h"
#include "Sort_Container.h"
#include "Views.h"

StateManager::StateManager()
{
	RessourcesLoad("../Ressources/Infos/Ressources.load");
	LoadSprite();
	LoadFont();
	LoadMap();
	Dialogues.init();
	Effects.init();
	Armors.init();
	Weapons.init();
	Consumables.init();
	Npcs.init();
	Sorts.init();
	ChangeState(State::MENU);
}

void StateManager::KeyboardEnter()
{
	if (App.Get_Event().text.unicode > 64 && App.Get_Event().text.unicode < 91 || 
		App.Get_Event().text.unicode > 96 && App.Get_Event().text.unicode < 123)
		Text_Received += App.Get_Event().text.unicode;
	if (App.Get_Event().text.unicode > 47 && App.Get_Event().text.unicode < 58)
		Text_Received += App.Get_Event().text.unicode;
	else if (App.Get_Event().text.unicode == 8 && Text_Received.size() > 0)
		Text_Received.pop_back();
}

void StateManager::EventsManager()
{
	while (App.Get_Window().pollEvent(App.Get_Event()))
	{
		if (App.Get_Event().type == sf::Event::Closed)
			App.Get_Window().close();

		if (App.Get_Event().type == Event::TextEntered)
			KeyboardEnter();

		if (App.Get_Event().type == sf::Event::KeyPressed)
			;
		if (App.Get_Event().type == sf::Event::KeyReleased)
			;
		for (int i = 0; i < 8; i++)
			;
	}
}

void StateManager::UpdateManager()
{
	MainTime.RestartClock();

	static float timer = 0;
	static int count = 0;

	switch (state)
	{
	case State::MENU:
		Game_Menu.Update_Main();
		break;
	case State::EDITOR:
		Edit_Niveau.Update();
		break;
	case State::GAME:
		Game_Manager::Get_Singleton().Update();
		break;
	default:
		break;
	}

	timer += MainTime.GetTimeDeltaF();
	count++;
	if (timer > 1)
	{
		cout << count << endl;
		count = 0;
		timer = 0;
	}
}

void StateManager::DisplayManager()
{
	App.Get_Window().clear(Color::Black);

	switch (state)
	{
	case State::MENU:
		Game_Menu.Display_Main();
		break;
	case State::EDITOR:
		Edit_Niveau.Display_editeur();
		break;
	case State::GAME:
		Game_Manager::Get_Singleton().Display();
		break;
	default:
		break;
	}

	App.Get_Window().display();
}

void StateManager::ChangeState(State NextState)
{
	state = NextState;

	if (NextState == State::MENU)
		Game_Menu = Menu(0);

	if (NextState == State::EDITOR)
	{
		Edit_Niveau = Editeur();
		App.Get_Window().setMouseCursorVisible(true);
	}
	else
		App.Get_Window().setMouseCursorVisible(false);
}