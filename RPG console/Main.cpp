#include "Tools.h"
#include "StateManager.h"
#include "RessourcesManager.h"
#include "SoundManager.h"
#include "SpriteManager.h"
#include "FontManager.h"
#include "Controle.h"
#include "Hero.h"
#include "Weapon.h"
#include "Chest.h"

Global App;

void main()
{
#ifndef _DEBUG
	FreeConsole();
#endif //!DEBUG

	srand(time(NULL));
	MState.ChangeState(State::MENU);

	while (App.Get_Window().isOpen())
	{
		try
		{
			MState.EventsManager();
			if (App.Get_Window().hasFocus())
				MState.UpdateManager();
			MState.DisplayManager();
		}
		catch (exception const& e)
		{
			cerr << "ERREUR : " << e.what() << endl;
		}
	}
}