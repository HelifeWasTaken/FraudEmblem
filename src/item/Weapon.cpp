/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Weapon
*/

#include "item/Weapon.hpp"

namespace emblem {

    Weapon::Weapon(const size_t &atk, const size_t &range) : __atk(atk), __range(range) {}

    void Weapon::equip(entt::entity &entity) {
        auto &equipment = getEquipment(entity);

        equipment.equipWeapon(std::move(Stack(std::make_shared<Weapon>(*this))));
    }

    void Weapon::unequip(entt::entity &entity) {
        auto &equipment = getEquipment(entity);

        equipment.unequipWeapon();
    }

    const size_t &Weapon::atk() const {
        return __atk;
    }

    const size_t &Weapon::range() const {
        return __range;
    }

}
