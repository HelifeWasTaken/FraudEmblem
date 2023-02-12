/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Focusable
*/

#include "gui/widget/Focusable.hpp"

namespace emblem::gui {

    void Focusable::onUpdate(const float &dt) {}

    void Focusable::onEvent(sf::Event &e) {
        if (e.type == sf::Event::MouseButtonPressed) {
            if (e.mouseButton.button == sf::Mouse::Left) {
                if (__rect.contains(sf::Vector2f(e.mouseButton.x, e.mouseButton.y))) {
                    onFocus();
                } else {
                    onUnfocus();
                }
            }
        }
    }

    void Focusable::onFocus() {
        __focused = true;
    }

    void Focusable::onUnfocus() {
        __focused = false;
    }

    bool Focusable::isFocused() const {
        return __focused;
    }

}
