/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Context
*/

#include "Context.hpp"

emblem::Context &emblem::Context::instance() {
    if (!__instance)
        __instance = new emblem::Context();
    return *__instance;
}

entt::registry &emblem::Context::entt() {
    return instance().__registry;
}

emblem::Context *emblem::Context::__instance = nullptr;
