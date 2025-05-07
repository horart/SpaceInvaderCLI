#include "player.h"

void Player::onInput(char c)  {
    switch (c) {
        case 'w':
            setPosition({getPosition().x, getPosition().y - 1});
            break;
        case 's':
            setPosition({getPosition().x, getPosition().y + 1});
            break;
        case 'a':
            setPosition({getPosition().x - 1, getPosition().y});
            break;
        case 'd':
            setPosition({getPosition().x + 1, getPosition().y});
            break;
        default:
            break;
    }
}
