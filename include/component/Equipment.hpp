/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Hand
*/

#pragma once

#include "item/Stack.hpp"

namespace emblem {

    class Weapon;
    class Accessory;

    class Equipment {
        Stack __weapon;
        Stack __accessory;

        public:
            Equipment() = default;
            ~Equipment() = default;

            Equipment &equipWeapon(const Stack &stack);
            Equipment &equipAccessory(const Stack &stack);
            Equipment &equipWeapon(Stack &&stack);
            Equipment &equipAccessory(Stack &&stack);

            Equipment &unequipWeapon();
            Equipment &unequipAccessory();

            const Stack &weapon() const;
            const Stack &accessory() const;

    };
} // namespace
