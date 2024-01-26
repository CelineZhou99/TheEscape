#include "stdafx.h"
#include "TextBox.h"

void TextBox::SetDialogue(Dialogue* dialogue)
{
	_dialogue = dialogue; 
	_is_dialogue_finished = false; 
	_dialogue_index = 0;
}

void TextBox::DisplayDialogue()
{
	if (_dialogue_index < _dialogue->size())
	{
		const char* message = _dialogue->at(_dialogue_index).c_str();
		App::Print(TEXT_START_X, TEXT_START_Y, message);
		App::Print(DIALOGUE_CONTINUE_X, DIALOGUE_CONTINUE_Y, DIALOGUE_CONTINUE);
	}
	else 
	{
		_is_dialogue_finished = true;
	}
}

void TextBox::NextDialogue()
{
	++_dialogue_index;
}
