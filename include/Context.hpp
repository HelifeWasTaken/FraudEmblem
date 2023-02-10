/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Context
*/

#pragma once

#include <memory>
#include "entt/entt.hpp"

namespace emblem {
    class Context {
        entt::registry __registry;

        static Context *__instance;

        Context() = default;

        public:
            ~Context() = default;

            static Context &instance();

            static entt::registry &entt();

    };
}
