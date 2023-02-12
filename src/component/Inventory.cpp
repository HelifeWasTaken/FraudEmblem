/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Inventory
*/

#include "component/Inventory.hpp"

namespace emblem {

    void Inventory::addItemStack(Stack &&item) {
        __items.push_back(std::move(item));
    }

    Stack &Inventory::getItemStack(const size_t &index) {
        return __items.at(index);
    }

    const Stack &Inventory::getItemStack(const size_t &index) const {
        return __items.at(index);
    }

    void Inventory::removeItemStack(const size_t &index) {
        __items.at(index).drop();
    }

    Stack &&Inventory::extractItemStack(const size_t &index) {
        Stack &&ret = std::move(__items.at(index));
        __items.erase(__items.begin() + index);
        return std::move(ret);
    }

    size_t Inventory::size() const {
        return __items.size();
    }
}
