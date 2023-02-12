/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Scalable
*/

#include "gui/widget/Scalable.hpp"
#include "gui/widget/Movable.hpp"

namespace emblem::gui {

    sf::Vector2f Scalable::getScale() const {
        return __scale;
    }

    Widget &Scalable::setScale(const sf::Vector2f &scale) {
        Movable *movable = dynamic_cast<Movable *>(this);

        __rect.width = __rect.width * scale.x;
        __rect.height = __rect.height * scale.y;

        if (movable) {
            __rect.left = __rect.left * scale.x;
            __rect.top = __rect.top * scale.y;
        }
        __scale = scale;
        return *this;
    }
}
