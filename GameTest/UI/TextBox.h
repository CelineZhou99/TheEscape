#pragma once
#include "UI.h"

#define TEXT_START_X 64
#define TEXT_START_Y 80
#define DIALOGUE_CONTINUE "(Press space to continue)"
#define DIALOGUE_CONTINUE_X 768
#define DIALOGUE_CONTINUE_Y 16

using Dialogue = std::vector<std::string>;

class TextBox :
    public UI
{
public:
    TextBox(const char* file_name, unsigned int columns = 1, unsigned int rows = 1) : UI(file_name), 
        _dialogue(nullptr), _dialogue_index(0), _is_dialogue_finished(true) {}

    void SetDialogue(Dialogue* dialogue);
    void DisplayDialogue();
    void NextDialogue();

    bool GetIsDialogueFinished() const { return _is_dialogue_finished; }

private:
    Dialogue* _dialogue;
    unsigned short _dialogue_index;
    bool _is_dialogue_finished;
};

