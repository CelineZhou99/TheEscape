#pragma once
#include "UI.h"

#define TEXT_START_X 64
#define TEXT_START_Y 80
#define DIALOGUE_CONTINUE "(Press space to continue)"
#define DIALOGUE_CONTINUE_X 768
#define DIALOGUE_CONTINUE_Y 16

class TextBox :
    public UI
{
public:
    TextBox(const char* file_name, unsigned int columns = 1, unsigned int rows = 1) : UI(file_name), 
        _dialogue(nullptr), _is_dialogue_finished(true), _dialogue_index(0) {}

    void SetDialogue(std::vector<const char*>* dialogue);
    void DisplayDialogue();
    void NextDialogue();

    bool GetIsDialogueFinished() { return _is_dialogue_finished; }

private:
    std::vector<const char*>* _dialogue;
    bool _is_dialogue_finished;
    int _dialogue_index;
};

