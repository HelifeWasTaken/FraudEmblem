/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Item
*/

#include "item/Item.hpp"

namespace emblem {

    void Item::setIcon(const std::string &icon) {
        __icon.create(
            Context::getResource<kat::Texture>("texture:icon/" + icon)
        );
    }
}
