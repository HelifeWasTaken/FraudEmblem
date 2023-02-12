/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Stack
*/

#pragma once

#include <cstddef>
#include <memory>
#include <algorithm>

// #include "Item.hpp"

namespace emblem {
    class Item;

    class Stack {
        std::shared_ptr<Item> __item = nullptr;
        size_t __max = 5;
        size_t __amount = 1;

        public:
            Stack() = default;

            template<typename T>
            Stack(std::shared_ptr<T> &&item) {
                __item = std::move(item);
            }
            ~Stack() = default;

            Stack &setAmount(const size_t &amount);
            Stack &setMax(const size_t &max);

            Stack &give(const size_t &amount);
            Stack &take(const size_t &amount);
            Stack &drop();

            const size_t &amount() const;
            const size_t &max() const;

            bool isEmpty() const;
            bool isNull() const;

            template<typename T = Item>
            const T &item() const {
                if constexpr (std::is_same_v<T, Item>)
                    return *__item;
                return *dynamic_cast<T*>(__item.get());
            }

    };
}
