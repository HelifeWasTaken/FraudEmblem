/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** MenuState
*/

#pragma once

#include <filesystem>

#include "AState.hpp"
#include "components/sprite.h"

namespace emblem {
    class MenuState : public AState {

        std::filesystem::path __assetsPath = "../assets";

        public:
            MenuState(const std::filesystem::path &path);
            virtual ~MenuState() override = default;
            virtual void onLoad() override;
            virtual void onRelease() override;
            virtual void onUpdate(const float &dt) override;
            //virtual void onEvent(sf::Event &e) override;
            virtual void onRender(Window &window) override;

    };
}
