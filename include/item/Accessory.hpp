/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Accessory
*/

#pragma once

#include "item/Equipable.hpp"

namespace emblem {

    class Accessory : public Equipable {
        public:
            Accessory() = default;
            virtual ~Accessory() override = default;

            virtual void equip(entt::entity &entity) override;
            virtual void unequip(entt::entity &entity) override;

    };
}
