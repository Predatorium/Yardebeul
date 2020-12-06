#pragma once
#include "Tools.h"
#include "Dialogue.h"

class Dialogue_Container
{
private :
	list<Dialogue> Containers;

public :
	Dialogue_Container();
	~Dialogue_Container() = default;

	Dialogue& Get_Dialogue(string _id);
};

extern Dialogue_Container Dialogues;