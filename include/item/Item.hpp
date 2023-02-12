/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Item
*/

#pragma once

#include <string>

#include "components/sprite.h"
#include "entt/entt.hpp"

#include "Context.hpp"

namespace emblem {
    class Item {
        kat::Sprite __icon;

        public:
            Item() = default;
            virtual ~Item() = default;

            virtual void use(entt::entity &entity) = 0;

            void setIcon(const std::string &icon);

    };
}
