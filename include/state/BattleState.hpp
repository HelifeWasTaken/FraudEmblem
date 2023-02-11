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

        kat::Sprite __map;

        kat::Sprite __cursorCell;
        std::vector<kat::shared_drawable_t> __emptyCell;
        std::vector<kat::shared_drawable_t> __wallCell;

        Map __mapData;

        std::filesystem::path __assetsPath = "../assets";

        Point __cursor;
        Area __path;

        public:
            BattleState(const std::filesystem::path &path);
            virtual ~BattleState() override = default;

            virtual void onLoad() override;
            virtual void onRelease() override;
            virtual void onUpdate(const float &dt) override;
            virtual void onEvent(sf::Event &e) override;
            virtual void onRender(Window &window) override;

    };
}
