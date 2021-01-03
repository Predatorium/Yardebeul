#pragma once
#include "Tools.h"
#include "Dialogue.h"

class Dialogue_Container
{
private :
	list<Dialogue> Container;

public :
	Dialogue_Container() = default;
	~Dialogue_Container() = default;

	void init();

	Dialogue& Get_Dialogue(string _id);
	Dialogue& Random_Dialogue();
};

extern Dialogue_Container Dialogues;