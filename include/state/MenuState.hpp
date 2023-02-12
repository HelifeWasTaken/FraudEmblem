/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Menu
*/

#pragma once
#include <iostream>
#include <string>

#include "AState.hpp"
#include "Kat.h"
#include "component/Button.hpp"

namespace emblem {
    class MenuState : public AState {
        public:
            MenuState() = default;
            virtual ~MenuState() = default;

            virtual void onLoad() override;
            virtual void onRelease() override;
            virtual void onUpdate(const float &dt) override;
            virtual void onEvent(sf::Event &e) override;
            virtual void onRender(emblem::Window &window);
        private:
            kat::shared_drawable_t __text = std::make_shared<sf::Text>();
            sf::Text *__title;
            sf::Font __font;
            emblem::Button __button;
    };
};
