/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Hoverable
*/

#include "gui/widget/Hoverable.hpp"

namespace emblem::gui {

    void Hoverable::onUpdate(const float &dt) {
        if (__hovered) {
            onHover();
        } else {
            onUnhover();
        }
    }

    void Hoverable::onEvent(sf::Event &e) {
        if (e.type == sf::Event::MouseMoved) {
            if (__rect.contains(e.mouseMove.x, e.mouseMove.y)) {
                if (!__hovered) {
                    __hovered = true;
                    onHover();
                }
            } else {
                if (__hovered) {
                    __hovered = false;
                    onUnhover();
                }
            }
        }
    }

    bool Hoverable::isHovered() const {
        return __hovered;
    }
}