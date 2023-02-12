/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Accessory
*/

#include "item/Accessory.hpp"

namespace emblem {

    void Accessory::equip(entt::entity &entity) {
        auto &equipment = getEquipment(entity);

        equipment.equipAccessory(std::move(Stack(std::make_shared<Accessory>(*this))));
    }

    void Accessory::unequip(entt::entity &entity) {
        auto &equipment = getEquipment(entity);

        equipment.unequipAccessory();
    }

}
