/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Movable
*/

#include "gui/widget/Movable.hpp"

namespace emblem::gui {

    Widget &Movable::setPosition(const sf::Vector2f &pos) {
        __rect.left = pos.x - __origin.x;
        __rect.top = pos.y - __origin.y;
        return *this;
    }

    sf::Vector2f Movable::getOrigin() const {
        return __origin;
    }

    Widget &Movable::setOrigin(const sf::Vector2f &origin) {
        __origin = origin;
        return *this;
    }
}
