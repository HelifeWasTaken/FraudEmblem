/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Resizable
*/

#include "gui/widget/Resizable.hpp"

namespace emblem::gui {

    Widget &Resizable::setSize(const sf::Vector2f &size) {
        __rect.width = size.x;
        __rect.height = size.y;
        return *this;
    }
}
