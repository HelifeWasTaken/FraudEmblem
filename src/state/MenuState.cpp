/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Menu
*/

#include "state/MenuState.hpp"
#include <iostream>
#include <string>
#include "Window.hpp"
#include "Context.hpp"
#include "component/Button.hpp"
#include "component/Character.hpp"
#include "component/Stats.hpp"

#include "Context.hpp"

namespace emblem {
    void MenuState::onLoad() {
        if (!__font.loadFromFile("../assets/OldLondon.ttf")) {
            std::cerr << "Error while loading font" << std::endl;
            return;
        }
        __title = dynamic_cast<sf::Text *>(this->__text.get());
        
        __title->setString("FRAUD EMBLEM");
        __title->setFont(__font);
        __title->setPosition(-100, 300);
        __title->setCharacterSize(60);
        __title->setOrigin(__title->getLocalBounds().width / 2, (__title->getLocalBounds().height / 2) + 100);
        std::cout << "[*] Load Title" << std::endl;
        // set the origin at the center
        // __title->setOrigin(__title->getLocalBounds().width / 2, (__title->getLocalBounds().height / 2) + 100);
       

    }
    void MenuState::onRelease() {
    }
    void MenuState::onUpdate(const float &dt) {
        sf::Vector2f pos = __title->getPosition();
        // if the pos.x is lower than the center of the screen, move it to the right by inc by 0.02
        // else, move it to the right by inc by 0.5
        if (pos.x < 500) {
            __title->move(0.02, 0);
        } else {
            __title->move(0.5, 0);
        }
    }
    void MenuState::onEvent(sf::Event &e) {
        if (e.type == sf::Event::KeyPressed) {
            if (e.key.code == sf::Keyboard::Return) {
                emblem::Context::load("battle");
                std::cout << "Enter pressed" << std::endl;
            }
        }
    }

    void MenuState::onRender(emblem::Window &window) {
        window.draw(this->__text, "mainmenu", 0);
        this->__button.render(window);
    }
};