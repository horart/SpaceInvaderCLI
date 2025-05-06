#include "inputmanager.h"

class CLIInputManager : public InputManager {
private:
    char getInput() override;
};