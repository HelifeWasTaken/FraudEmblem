/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Character
*/

#pragma once

#include <string>

#include "Kat/components/animator.h"
#include "Kat/components/sprite.h"
#include "Kat/components/texture.h"

#include "entt/entt.hpp"
#include "nlohmann/json.hpp"
#include "Context.hpp"

namespace emblem {

    entt::entity createCharacter(const std::string &filename, const nlohmann::json &json);
}
