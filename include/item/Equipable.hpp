/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Equipable
*/

#pragma once

#include "item/Item.hpp"

namespace emblem {

    class Equipable : public Item {
        bool __equipped = false;

        public:
            Equipable() = default;
            virtual ~Equipable() override = default;

            virtual void use(entt::entity &entity) override;

            virtual void equip(entt::entity &entity) = 0;
            virtual void unequip(entt::entity &entity) = 0;

            bool isEquipped() const;

    };
}
