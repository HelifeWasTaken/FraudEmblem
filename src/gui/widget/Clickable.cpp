/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Clickable
*/

#include "gui/widget/Clickable.hpp"

namespace emblem::gui {

    void Clickable::onUpdate(const float &dt) {}

    void Clickable::onEvent(sf::Event &e) {
        if (e.type == sf::Event::MouseButtonPressed) {
            if (e.mouseButton.button == sf::Mouse::Left) {
                if (__rect.contains(e.mouseButton.x, e.mouseButton.y)) {
                    __pressed = true;
                    onPress();
                }
            }
        }
        if (e.type == sf::Event::MouseButtonReleased) {
            if (e.mouseButton.button == sf::Mouse::Left) {
                if (__rect.contains(e.mouseButton.x, e.mouseButton.y)) {
                    __pressed = false;
                    onRelease();
                }
            }
        }
    }

    bool Clickable::isPressed() const {
        return __pressed;
    }
}
