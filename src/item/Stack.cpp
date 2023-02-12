/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Stack
*/

#include "item/Stack.hpp"
#include "item/Item.hpp"

namespace emblem {

    Stack &Stack::setAmount(const size_t &amount) {
        __amount = amount;
        return *this;
    }

    Stack &Stack::setMax(const size_t &max) {
        __max = max;
        return *this;
    }

    Stack &Stack::give(const size_t &amount) {
        __amount = std::clamp<size_t>(__amount + amount, 0, __max);
        return *this;
    }

    Stack &Stack::take(const size_t &amount) {
        __amount = std::clamp<size_t>(__amount - amount, 0, __max);
        return *this;
    }

    Stack &Stack::drop() {
        __amount = 0;
        return *this;
    }

    const size_t &Stack::amount() const {
        return __amount;
    }

    const size_t &Stack::max() const {
        return __max;
    }

    bool Stack::isEmpty() const {
        return __amount == 0;
    }

    bool Stack::isNull() const {
        return __item == nullptr;
    }

}
