#include "StateManager.h"
#include "SpriteManager.h"
#include "SoundManager.h"
#include "FontManager.h"
#include "Map_Manager.h"
#include "Controle.h"
#include "Dialogue_Container.h"
#include "Views.h"

StateManager MState;

StateManager::StateManager()
{
	RessourcesLoad("../Ressources/Infos/Ressources.load");
	LoadSprite();
	LoadFont();
	LoadMap();
	Dialogues.init();
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

	switch (state)
	{
	case State::MENU:
		Game_Menu.Update_Main(Monde);
		break;
	case State::EDITOR:
		Edit_Niveau.Update();
		break;
	case State::GAME:
		Monde.Update();
		break;
	case State::FIGHT:
		Fight.Update();
		break;
	default:
		break;
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
		Edit_Niveau.Display();
		break;
	case State::GAME:
		Monde.Display();
		break;
	case State::FIGHT:
		Fight.Display();
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

void StateManager::State_Fight(Hero* _player, Npc *_enemy)
{
	Fight = Fight_System(_player, _enemy);
	state = State::FIGHT;
}