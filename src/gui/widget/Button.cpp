/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Button
*/

#include "gui/widget/Button.hpp"

namespace emblem::gui {

    void Button::onUpdate(const float &dt) {
        Movable::onUpdate(dt);
        Resizable::onUpdate(dt);
        Scalable::onUpdate(dt);
        Rotatable::onUpdate(dt);

        Hoverable::onUpdate(dt);
        Clickable::onUpdate(dt);

        if (isHovered()) {
            if (isPressed()) {
                __wasPressed = true;
            } else {
                if (__wasPressed)
                    __callback();
                __wasPressed = false;
            }
        } else {
            __wasPressed = false;
        }
    }

    void Button::onEvent(sf::Event &e) {
        Movable::onEvent(e);
        Resizable::onEvent(e);
        Scalable::onEvent(e);
        Rotatable::onEvent(e);

        Hoverable::onEvent(e);
        Clickable::onEvent(e);
    }

    void Button::setCallback(const std::function<void()> &callback) {
        __callback = callback;
    }
}
