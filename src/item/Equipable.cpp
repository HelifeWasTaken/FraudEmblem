/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Equipable
*/

#include "item/Equipable.hpp"

namespace emblem {

    void Equipable::use(entt::entity &entity) {
        
    }

    bool Equipable::isEquipped() const {
        return __equipped;
    }
}
