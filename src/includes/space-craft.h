#ifndef SPACEINVADERS_SPACE_CRAFT_H
#define SPACEINVADERS_SPACE_CRAFT_H

#include <iostream>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#define SPACE_CRAFT_IMG "../res/space-craft.png"

class SpaceCraft
{
private:
    sf::Texture texture;

public:
    sf::Sprite sprite;
    sf::Vector2f dimensions;
    int moveOffset = 5;

    SpaceCraft()
    {
        texture.loadFromFile(SPACE_CRAFT_IMG);
        sprite.setTexture(texture);
        sprite.setScale(0.08, 0.08);
        sprite.setPosition(588.8, 610);

        dimensions = {
                sprite.getTexture()->getSize().x * sprite.getScale().x,
                sprite.getTexture()->getSize().y * sprite.getScale().y
        };
    };

    void moveLeft() {
        sf::Vector2f position = sprite.getPosition();
        if (position.x > 0) {
            sprite.setPosition(position.x - moveOffset, position.y);
        }
    }

    void moveRight(sf::Vector2f windowSize) {
        sf::Vector2f position = sprite.getPosition();
        if (position.x + dimensions.x < windowSize.x) {
            sprite.setPosition(position.x + moveOffset, position.y);
        }
    }
};

#endif //SPACEINVADERS_SPACE_CRAFT_H