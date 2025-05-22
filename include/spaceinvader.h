#pragma once

#include <memory>

#include "game.h"
#include "clirenderer.h"
#include "cliinputmanager.h"
#include "collidermanager.h"
#include "spritemanager.h"
#include "enemymanager.h"
#include "renderingprimitives.h"
#include "point.h"


class GameOver : public GameObject {
public:
    using GameObject::GameObject;
    Point getPosition() const override {
        return {0, 0};
    }
    std::unique_ptr<RenderRange> getPrimitives() const override;
};

class Score : public GameObject {
private:
    std::vector<std::shared_ptr<RenderingPrimitive>> score_primitives
    {
        std::make_shared<RenderingText>(Point{0, 0}, Colors::WHITE, Colors::BLACK, "Score: 0"),
    };
    int score = 0;
public:
    using GameObject::GameObject;
    Point getPosition() const override {
        return {0, game.lock()->getGameSize().y - 1};
    }
    std::unique_ptr<RenderRange> getPrimitives() const override {
        static_cast<RenderingText*>(score_primitives[0].get())->text = "Score: " + std::to_string(score);
        return std::make_unique<PrimitivesRange>(
            score_primitives
        );
    }
    void addScore(int inc) {
        score += inc;
    }
};

class SpaceInvaderGame : public Game {
private:
    bool stop = false;
    Score* scoreObject = nullptr;
public:
    std::shared_ptr<CLIInputManager> inputManager;
    std::shared_ptr<ColliderManager> colliderManager;
    std::shared_ptr<SpriteManager> spriteManager;
    std::shared_ptr<EnemyManager> enemyManager;
public:
    SpaceInvaderGame(std::unique_ptr<Renderer> renderer, 
        std::chrono::duration<int, std::milli> frameDuration = std::chrono::milliseconds(1000 / 20)) : 
            Game(std::move(renderer), frameDuration),
            inputManager(std::make_shared<CLIInputManager>(frameDuration)),
            colliderManager(std::make_shared<ColliderManager>()),
            spriteManager(std::make_shared<SpriteManager>()),
            enemyManager(std::make_shared<EnemyManager>(this)) {}

    void beforeUpdate() override {
        if(stop) return;
        inputManager->notify();
        colliderManager->notify();
        enemyManager->notify();
    }

    void init() override;

    void gameOver() {
        for(auto& [id, obj] : objectsById) {
            obj->destroy();
        }
        createObject<GameOver>(Point{getGameSize().x / 2, getGameSize().y / 2});
        stop = true;
    }

    void addScore(int inc) {
        scoreObject->addScore(inc);
    }
};