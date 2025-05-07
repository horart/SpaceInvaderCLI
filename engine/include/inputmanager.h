#pragma once

#include <unordered_map>
#include <memory>

#include "gameobject.h"

class InputManaged;

class InputManager {
private:
    std::unordered_map<int, std::weak_ptr<InputManaged>> objectsById;
private:
    virtual char getInput() = 0;
public:
    void subscribe(int id, std::shared_ptr<InputManaged> inputManaged);
    void unsubscribe(int id);
    void notify();
    virtual ~InputManager() = default;
};

class InputManaged : virtual public GameObject {
private:
    std::weak_ptr<InputManager> im;
public:
    InputManaged(std::weak_ptr<InputManager> im): im(im) {}
    void initComponent(std::shared_ptr<InputManaged> self) {
        im.lock()->subscribe(id, self);
    }
    virtual void onInput(char c) {
        (void)c;
    }
    virtual ~InputManaged() {
        if(std::shared_ptr<InputManager> i = im.lock()) {
            i->unsubscribe(id);
        }
    }
};
