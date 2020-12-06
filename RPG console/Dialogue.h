#pragma once
#include "Tools.h"
#include "Button.h"

class Dialogue;

class Dialogue_Button : public Button_Text
{
private:
	Dialogue* Next_Dialogue;

public:
	Dialogue_Button() = default;
	Dialogue_Button(string _name, Dialogue* _nextdialogue);
	Dialogue_Button(string _name);
	~Dialogue_Button() = default;

	inline Dialogue* Get_Dial() { return Next_Dialogue; };
	void Set_Position(Vector2f _position);
};

class Dialogue
{
private :
	string Id;
	Text text;
	list<Dialogue_Button> Answer;
	int Selection;
	float timer;

public :
	Dialogue() = default;
	Dialogue(string _id, string _dialogue, float _sizeTexte, list<Dialogue_Button> &_answer);
	~Dialogue() = default;

	inline string Get_Id() { return Id; };

	bool operator == (const Dialogue& _d) const { return Id == _d.Id; }
	bool operator != (const Dialogue& _d) const { return !operator==(_d); }

	void Update(bool& _dialogue);
	void Display();
};