#ifndef SPACEINVADERS_WEAPON_FIRE_H
#define SPACEINVADERS_WEAPON_FIRE_H

#include <iostream>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#define WEAPON_FIRE_IMG "../res/weapon-fire.png"

class WeaponFire
{
private:
    sf::Texture texture;

public:
    sf::Sprite sprite;
    sf::Vector2f dimensions;
    int moveOffset = 5;

    WeaponFire()
    {
        texture.loadFromFile(WEAPON_FIRE_IMG);
        sprite.setTexture(texture);
        sprite.setScale(0.6, 0.6);

        dimensions = {
                sprite.getTexture()->getSize().x * sprite.getScale().x,
                sprite.getTexture()->getSize().y * sprite.getScale().y
        };
    }

    void setStartPosition(SpaceCraft &spaceCraft) {
        sf::Vector2f shipDimensions = spaceCraft.dimensions;
        sf::Vector2f shipPosition = spaceCraft.sprite.getPosition();

        sprite.setPosition(shipPosition.x + shipDimensions.x / 2 - dimensions.x / 2,
                           shipPosition.y - dimensions.y);
    }

    bool isAvailable(sf::Vector2f windowSize) {
        sf::Vector2f position = sprite.getPosition();
        if (position.x - dimensions.x <= 0
            || position.y - dimensions.y <= 0
            || position.x + dimensions.x >= windowSize.x) {
            return false;
        } else {
            return true;
        }
    }

    void moveFireShot() {
        sf::Vector2f position = sprite.getPosition();
        sprite.setPosition(position.x, position.y - moveOffset);
    }
};

#endif //SPACEINVADERS_WEAPON_FIRE_H
