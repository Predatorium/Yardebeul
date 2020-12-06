#include "Tools.h"
#include "StateManager.h"

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