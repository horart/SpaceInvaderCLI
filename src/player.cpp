#include "player.h"

void Player::onInput(char c)  {
    switch (c) {
        case 'a':
            if(getPosition().x > 0)
                setPosition({getPosition().x - 1, getPosition().y});
            break;
        case 'd':
            if(getPosition().x < game.lock()->getGameSize().x - getSize().x - 1)
                setPosition({getPosition().x + 1, getPosition().y});
            break;
        default:
            break;
    }
}
