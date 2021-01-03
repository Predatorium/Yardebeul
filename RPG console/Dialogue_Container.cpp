#include "Dialogue_Container.h"
#include "FontManager.h"

Dialogue_Container Dialogues;

void Dialogue_Container::init()
{
	list<Dialogue_Button> tmp;
	tmp.push_back(Dialogue_Button("Merci. *Partir*"));
	Container.push_back(Dialogue("1_2", "J'espere que ça va s'arranger.", 50, tmp));

	tmp.clear();
	tmp.push_back(Dialogue_Button("Merci. *Partir*"));
	Container.push_back(Dialogue("1_3", "Je vous laisse à vos aventures.", 50, tmp));

	tmp.clear();
	tmp.push_back(Dialogue_Button("Bien.", &Get_Dialogue("1_3")));
	tmp.push_back(Dialogue_Button("Mal.", &Get_Dialogue("1_2")));
	tmp.push_back(Dialogue_Button("*Partir*"));
	Container.push_back(Dialogue("1_1", "Comment allez-vous aujourd'hui ?", 50, tmp));

	tmp.clear();
	tmp.push_back(Dialogue_Button("Ok. *Partir*"));
	Container.push_back(Dialogue("2_2", "Si juvabien c'est juvamine", 50, tmp));

	tmp.clear();
	tmp.push_back(Dialogue_Button("De quoi?", &Get_Dialogue("2_2")));
	tmp.push_back(Dialogue_Button("*Partir*"));
	Container.push_back(Dialogue("2_1", "Les Refregirateurs sont moins cher chez But.", 50, tmp));
}

Dialogue& Dialogue_Container::Get_Dialogue(string _id)
{
	for (Dialogue& Current_Dialogue : Container)
		if (Current_Dialogue.Get_Id() == _id)
			return Current_Dialogue;
}

Dialogue& Dialogue_Container::Random_Dialogue()
{
	int number = 0;
	for (Dialogue& Current_Dialogue : Container)
		if (Current_Dialogue.Get_Id().substr(2, 1) == "1")
			number++;

	int rand = irandom(1, number);
	int i = 0;
	for (Dialogue& Current_Dialogue : Container)
		if (Current_Dialogue.Get_Id().substr(2, 1) == "1")
		{
			i++;
			if (i == rand)
				return Current_Dialogue;
		}

}