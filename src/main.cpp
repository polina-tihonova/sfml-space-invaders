#include <iostream>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "includes/space-craft.h"
#include "includes/weapon-fire.h"

constexpr unsigned WINDOW_WIDTH = 1280;
constexpr unsigned WINDOW_HEIGHT = 720;

void handleEvent(sf::RenderWindow &window, SpaceCraft &spaceCraft, std::vector<WeaponFire*> &weaponShots);
void handleKeyEvent(SpaceCraft &spaceCraft, std::vector<WeaponFire*> &weaponShots);
void continueEvents(std::vector<WeaponFire*> &weaponShots);
void drawWeaponShots(sf::RenderWindow &window, std::vector<WeaponFire*> &weaponShots);

int main() {
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Space Invaders");

    sf::Clock clock;

    SpaceCraft spaceCraft;
    std::vector<WeaponFire*> weaponShots;

    while (window.isOpen()) {
        // Event Handler
        handleEvent(window, spaceCraft, weaponShots);
        continueEvents(weaponShots);

        // Render
        window.clear();
        window.draw(spaceCraft.sprite);
        drawWeaponShots(window, weaponShots);
        window.display();
    }
}

void handleEvent(sf::RenderWindow &window, SpaceCraft &spaceCraft, std::vector<WeaponFire*> &weaponShots) {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                handleKeyEvent(spaceCraft, weaponShots);
                break;
            default:
                break;
        }
    }
}

void handleKeyEvent(SpaceCraft &spaceCraft, std::vector<WeaponFire*> &weaponShots) {
    sf::Vector2f windowSize = {WINDOW_WIDTH, WINDOW_HEIGHT};

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        spaceCraft.moveLeft();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        spaceCraft.moveRight(windowSize);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        WeaponFire *newPod = new WeaponFire();
        newPod->setStartPosition(spaceCraft);
        weaponShots.push_back(newPod);
    }
}

void continueEvents(std::vector<WeaponFire*> &weaponShots) {
    sf::Vector2f windowSize = {WINDOW_WIDTH, WINDOW_HEIGHT};

    for (size_t i = 0; i < weaponShots.size(); ++i) {
        if (weaponShots[i]->isAvailable(windowSize)) {
            weaponShots[i]->moveFireShot();
        } else {
            delete weaponShots[i];
            weaponShots.erase(weaponShots.begin() + i);
        }
    }
}

void drawWeaponShots(sf::RenderWindow &window, std::vector<WeaponFire*> &weaponShots) {
    for (size_t i = 0; i < weaponShots.size(); ++i) {
        window.draw(weaponShots[i]->sprite);
    }
}