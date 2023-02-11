/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Character
*/

#pragma once

#include <string>
#include <unordered_map>
#include <filesystem>
#include <fstream>

#include "components/animator.h"
#include "components/sprite.h"
#include "components/texture.h"

#include "entt/entt.hpp"
#include "nlohmann/json.hpp"
#include "Context.hpp"
#include "component/Stats.hpp"
#include "component/Transform.hpp"

#include "Map.hpp"

namespace emblem {

    entt::entity createCharacter(const nlohmann::json &json);

    class CharacterFactory {
        std::unordered_map<std::string, nlohmann::json> __characters;

        static CharacterFactory *__instance;

        CharacterFactory() = default;

        static CharacterFactory &instance();

        public:
            ~CharacterFactory() = default;


            static void loadCharacters(const std::string &path);
            static void registerCharacter(const std::string &name, const nlohmann::json &json);
            static entt::entity createCharacter(const std::string &name);
    };

    class PathManager {
        size_t index;
        emblem::Path path;

        static constexpr float SPEED = 4;

    public:
        PathManager(const emblem::Path& path) : path(path)
         , index(path.size() - 1) {}

        bool update(entt::entity &entity, float dt);
    };
}
