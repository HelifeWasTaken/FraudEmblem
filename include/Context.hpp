/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Context
*/

#pragma once

#include "entt/entt.hpp"
#include "window.h"

namespace emblem {
    class Context {
        entt::registry __registry;
        kat::Window __window;

        static Context *__instance;

        Context();

        public:
            ~Context() = default;

            static Context &instance();

            static entt::registry &entt();
            static kat::Window &window();

    };
}
