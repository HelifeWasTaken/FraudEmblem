/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Colorable
*/

#include "gui/widget/Colorable.hpp"

namespace emblem::gui {

    sf::Color Colorable::getColor() const {
        return __color;
    }

    Widget &Colorable::setColor(const sf::Color &color) {
        __color = color;
        return *this;
    }
}
