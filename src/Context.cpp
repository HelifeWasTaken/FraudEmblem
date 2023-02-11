/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Context
*/

#include "Context.hpp"

emblem::Context::Context() : __window({800, 600}, "Fraud Emblem", kat::WindowStyle::Close) {}

emblem::Context &emblem::Context::instance() {
    if (!__instance)
        __instance = new emblem::Context();
    return *__instance;
}

entt::registry &emblem::Context::entt() {
    return instance().__registry;
}

kat::Window &emblem::Context::window() {
    return instance().__window;
}

emblem::Context *emblem::Context::__instance = nullptr;
