/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Rotatable
*/

#include "gui/widget/Rotatable.hpp"

namespace emblem::gui {

        float Rotatable::getRotation() const {
            return __angle;
        }

        Widget &Rotatable::setRotation(const float &rotation) {
            __angle = rotation;
            return *this;
        }
}
