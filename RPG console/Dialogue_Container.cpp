#include "Dialogue_Container.h"
#include "FontManager.h"

Dialogue_Container Dialogues;

Dialogue_Container::Dialogue_Container()
{
	if (FontList.size() > 0)
	{
		list<Dialogue_Button> tmp;
		tmp.push_back(Dialogue_Button("Merci. *Partir*"));
		Containers.push_back(Dialogue("1_2", "J'espere que ça va s'arranger.", 50, tmp));

		tmp.clear();
		tmp.push_back(Dialogue_Button("Merci. *Partir*"));
		Containers.push_back(Dialogue("1_3", "Je vous laisse à vos aventure.", 50, tmp));

		tmp.clear();
		tmp.push_back(Dialogue_Button("Bien.", &Get_Dialogue("1_3")));
		tmp.push_back(Dialogue_Button("Mal.", &Get_Dialogue("1_2")));
		tmp.push_back(Dialogue_Button("*Partir*"));
		Containers.push_back(Dialogue("1_1", "Comment allez-vous aujourd'hui ?", 50, tmp));
	}
}

Dialogue& Dialogue_Container::Get_Dialogue(string _id)
{
	for (Dialogue& Current_Dialogue : Containers)
		if (Current_Dialogue.Get_Id() == _id)
			return Current_Dialogue;
}