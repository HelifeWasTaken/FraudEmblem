/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Weapon
*/

#pragma once

#include <cstddef>

#include "item/Equipable.hpp"

namespace emblem {

    class Weapon : public Equipable {
        size_t __atk;
        size_t __range;

        public:
            Weapon(const size_t &atk, const size_t &range);
            virtual ~Weapon() override = default;

            virtual void equip(entt::entity &entity) override;
            virtual void unequip(entt::entity &entity) override;

            const size_t &atk() const;
            const size_t &range() const;

    };
}
