#include "inputmanager.h"


void InputManager::subscribe(int id, std::shared_ptr<InputManaged> inputManaged) {
    objectsById[id] = inputManaged;
}
void InputManager::unsubscribe(int id) {
    objectsById.erase(id);
}
void InputManager::notify() {
    char c = getInput();
    for(auto& [id, obj] : objectsById) {
        obj.lock()->onInput(c);
    }
}