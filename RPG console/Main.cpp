#include "Tools.h"
#include "StateManager.h"

Global App;

void main()
{
#ifndef _DEBUG
	FreeConsole();
#endif //!DEBUG

	srand(time(NULL));

	while (App.Get_Window().isOpen())
	{
		try
		{
			StateManager::Get_Singleton().EventsManager();
			if (App.Get_Window().hasFocus())
				StateManager::Get_Singleton().UpdateManager();
			StateManager::Get_Singleton().DisplayManager();
		}
		catch (exception const& e)
		{
			cerr << "ERREUR : " << e.what() << endl;
		}
	}
}