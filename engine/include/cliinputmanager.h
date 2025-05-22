#include "inputmanager.h"

class CLIInputManager : public InputManager {
private:
    char getInput() override;
public:
    CLIInputManager(std::chrono::duration<int, std::milli> timeout);
    void setTimeout(std::chrono::duration<int, std::milli> timeout);
};