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

        std::unordered_map<Point, entt::entity> __characters;

        kat::Sprite __map;

        kat::Sprite __cursorCell;
        kat::Animator __cursorAnimator;
        std::vector<kat::shared_drawable_t> __emptyCell;
        std::vector<kat::shared_drawable_t> __wallCell;

        Map __mapData;

        std::filesystem::path __assetsPath = "../assets";

        Point __cursor;
        Area __path;

        bool __selected = false;
        Point __selectedStart;
        Point __selectedEnd;

        bool __action = false;

        entt::entity __selectedEntity;

        float __elapsed = 0;
        size_t __shading = 0;

        emblem::PathManager *__pathManager = nullptr;

        void __generateArea();

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
