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
        size_t index = 0;
        emblem::Path path;

        static const float SPEED = 4;

    public:
        PathManager(const emblem::Path& path) : path(path) {}

        bool update(float dt) {
            if (index >= path.size()) {
                animator.play("idle");
                return false;
            }

            auto &registry = emblem::Context::entt();
            auto &sprite = registry.get<kat::Sprite>(path.entity);
            auto &animator = registry.get<kat::Animator>(path.entity);

            auto current = sprite.getPosition();
            auto &next = path[index];

            auto direction = { current.x - next.x, current.y - next.y };
            auto cspeed = SPEED * dt;

            if (abs(direction.x) < cspeed) {
                direction.x = 0;
                sprite.setPosition(next.x, sprite.getPosition().y);
            } else if (abs(direction.y) < cspeed) {
                sprite.setPosition(sprite.getPosition().x, next.y);
            } else if (direction.x == 0 && direction.y == 0) {
                index++;
                return true;
            } else if (direction.x >= cspeed) {
                animator.play("walk_left");
                sprite.move(-cspeed, 0);
            } else if (direction.y >= cspeed) {
                animator.play("walk_up");
                sprite.move(0, -cspeed);
            } else if (direction.x <= -cspeed) {
                animator.play("walk_right");
                sprite.move(cspeed, 0);
            } else if (direction.y <= -cspeed) {
                animator.play("walk_down");
                sprite.move(0, cspeed);
            }
            return true;
        }
    };

}
