#pragma once

#include <memory>

#include "game.h"
#include "clirenderer.h"
#include "cliinputmanager.h"
#include "collidermanager.h"
#include "spritemanager.h"

class SpaceInvaderGame : public Game {

public:
    std::shared_ptr<CLIInputManager> inputManager;
    std::shared_ptr<ColliderManager> colliderManager;
    std::shared_ptr<SpriteManager> spriteManager;
public:
    SpaceInvaderGame(std::unique_ptr<Renderer> renderer): 
        Game(std::move(renderer)),
        inputManager(std::make_shared<CLIInputManager>()),
        colliderManager(std::make_shared<ColliderManager>()),
        spriteManager(std::make_shared<SpriteManager>())
    {
        
    }

    void beforeUpdate() override {
        inputManager->notify();
        colliderManager->notify();
    }
};