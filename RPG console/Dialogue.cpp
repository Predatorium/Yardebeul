#include "Dialogue.h"
#include "Dialogue_Container.h"
#include "FontManager.h"

Dialogue::Dialogue(string _id, string _dialogue, float _sizeTexte, list<Dialogue_Button> &_answer)
{
	Id = _id;
	text = Text(_dialogue, getFont("Times"), _sizeTexte);
	text.setOrigin(getMidle(text));
	text.setPosition(Vector2f(960,1080 - (60 * (_answer.size() + 1))));
	Answer = _answer;
	Selection = 0;
	timer = 0;

	int i = 1;
	for (Dialogue_Button& Current : Answer)
	{
		Current.Set_Position(Vector2f(text.getPosition().x, text.getPosition().y + (i * 40)));
		i++;
	}
}

Dialogue_Button::Dialogue_Button(string _name, Dialogue* _nextdialogue)
{
	Name = _name;

	Texte = Text(_name, getFont("Times"), 30);
	Texte.setOrigin(getMidle(Texte));
	Texte.setPosition(Vector2f(0,0));
	Texte.setFillColor(Color::White);

	shape = RectangleShape(Vector2f(Texte.getGlobalBounds().width + 5, Texte.getGlobalBounds().height + 5));
	shape.setOrigin(getMidle(shape));
	shape.setPosition(Vector2f(0,0));
	shape.setFillColor(Color::Transparent);
	shape.setOutlineThickness(3);
	shape.setOutlineColor(Color::White);

	Next_Dialogue = _nextdialogue;
}

Dialogue_Button::Dialogue_Button(string _name)
{
	Name = _name;

	Texte = Text(_name, getFont("Times"), 30);
	Texte.setOrigin(getMidle(Texte));
	Texte.setPosition(Vector2f(0, 0));
	Texte.setFillColor(Color::White);

	shape = RectangleShape(Vector2f(Texte.getGlobalBounds().width + 5, Texte.getGlobalBounds().height + 5));
	shape.setOrigin(getMidle(shape));
	shape.setPosition(Vector2f(0, 0));
	shape.setFillColor(Color::Transparent);
	shape.setOutlineThickness(3);
	shape.setOutlineColor(Color::White);

	Next_Dialogue = nullptr;
}

void Dialogue_Button::Set_Position(Vector2f _position)
{
	shape.setPosition(_position);
	Texte.setPosition(_position);
}

void Dialogue::Update(bool& _dialogue)
{
	timer += MainTime.GetTimeDeltaF();

	int i = 0;
	for (Dialogue_Button& Current_Button : Answer)
	{
		if (Selection == i)
		{
			Current_Button.Set_Color(Color(50, 120, 255, 255));
			if (Keyboard::isKeyPressed(Keyboard::Enter) && timer > 0.2f)
			{
				if (Current_Button.Get_Dial() == nullptr)
				{
					Id.pop_back();
					*this = Dialogues.Get_Dialogue(Id + to_string(1));
					_dialogue = false;
				}
				else
					*this = *Current_Button.Get_Dial();

				timer = 0;
				break;
			}
		}
		else
			Current_Button.Set_Color(Color::White);

		i++;
	}

	if (Keyboard::isKeyPressed(Keyboard::Up) && timer > 0.2f)
	{
		Selection--;
		if (Selection < 0)
			Selection = Answer.size() - 1;
		timer = 0;
	}
	if (Keyboard::isKeyPressed(Keyboard::Down) && timer > 0.2f)
	{
		Selection++;
		if (Selection >= Answer.size())
			Selection = 0;
		timer = 0;
	}
}

void Dialogue::Display()
{
	App.Get_Window().draw(text);

	for (Dialogue_Button Current_Button : Answer)
	{
		Current_Button.Display();
	}
}