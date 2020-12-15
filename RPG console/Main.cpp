#include "Tools.h"
#include "StateManager.h"

Global App;

void main()
{
#ifndef _DEBUG
	FreeConsole();
#endif //!DEBUG

	srand(time(NULL));
	float timer = 0;
	int count = 0;

	while (App.Get_Window().isOpen())
	{
		try
		{
			StateManager::Get_Singleton().EventsManager();
			if (App.Get_Window().hasFocus())
				StateManager::Get_Singleton().UpdateManager();
			timer += MainTime.GetTimeDeltaF();
			count++;
			if (timer > 1)
			{
				cout << count << endl;
				count = 0;
				timer = 0;
			}

			StateManager::Get_Singleton().DisplayManager();
		}
		catch (exception const& e)
		{
			cerr << "ERREUR : " << e.what() << endl;
		}
	}
}