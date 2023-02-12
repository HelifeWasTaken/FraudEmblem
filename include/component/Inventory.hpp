/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Inventory
*/

#pragma once

#include <vector>

#include "item/Stack.hpp"

namespace emblem {

    class Inventory {
        std::vector<Stack> __items;

        public:
            Inventory() = default;
            ~Inventory() = default;

            void addItemStack(Stack &&item);

            Stack &getItemStack(const size_t &index);
            const Stack &getItemStack(const size_t &index) const;

            void removeItemStack(const size_t &index);

            Stack &&extractItemStack(const size_t &index);

            size_t size() const;

    };
}
