/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Equipment
*/

#include "component/Equipment.hpp"
#include "item/Weapon.hpp"
#include "item/Accessory.hpp"

namespace emblem {

    Equipment &Equipment::equipWeapon(const Stack &stack) {
        __weapon = stack;
        return *this;
    }

    Equipment &Equipment::equipAccessory(const Stack &stack) {
        __accessory = stack;
        return *this;
    }

    Equipment &Equipment::equipWeapon(Stack &&stack) {
        __weapon = std::move(stack);
        return *this;
    }

    Equipment &Equipment::equipAccessory(Stack &&stack) {
        __accessory = std::move(stack);
        return *this;
    }

    Equipment &Equipment::unequipWeapon() {
        __weapon.drop();
        return *this;
    }

    Equipment &Equipment::unequipAccessory() {
        __accessory.drop();
        return *this;
    }

    const Stack &Equipment::weapon() const {
        return __weapon;
    }

    const Stack &Equipment::accessory() const {
        return __accessory;
    }
}
