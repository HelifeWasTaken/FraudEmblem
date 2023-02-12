/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** BattleState
*/

#pragma once

#include <filesystem>

#include "AState.hpp"
#include "components/sprite.h"
#include "component/Character.hpp"
#include "Map.hpp"

namespace emblem {

    class BattleState : public AState {

        enum State {
            SELECT,
            MOVE,
            ACTION,
            ATTACK
        };

        enum Turn {
            PLAYER,
            ENEMY
        };

        State __state = SELECT;
        Turn __turn = PLAYER;

        std::unordered_map<Point, entt::entity> __characters;

        kat::Sprite __map;

        kat::Sprite __cursorCell;
        kat::Animator __cursorAnimator;
        Point __cursorPos;

        Map __mapData;

        std::vector<kat::shared_drawable_t> __cells;

        std::filesystem::path __assetsPath = "../assets";

        Area __area;

        Point __selectedStart;
        Point __selectedEnd;

        entt::entity __selectedEntity;

        float __elapsed = 0;
        size_t __shading = 0;

        emblem::PathManager *__pathManager = nullptr;

        void __generateMoveArea();
        void __generateAttackArea();

        public:
            BattleState(const std::filesystem::path &path);
            virtual ~BattleState() override = default;

            virtual void onLoad() override;
            virtual void onRelease() override;
            virtual void onUpdate(const float &dt) override;
            virtual void onEvent(sf::Event &e) override;
            virtual void onRender(Window &window) override;

            void createCharacter(const std::string &name, const Point &pos, const emblem::EntityType &type);

    };
}
