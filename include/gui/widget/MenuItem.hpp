/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** MenuItem
*/

#pragma once

#include <functional>

#include "gui/widget/Movable.hpp"
#include "gui/widget/Resizable.hpp"
#include "gui/widget/Clickable.hpp"

namespace emblem::gui {
    class MenuItem : public Movable, public Clickable {
        kat::shared_drawable_t __text = std::make_shared<sf::Text>();

        std::function<void()> __callback;

        public:
            MenuItem();
            virtual ~MenuItem() override = default;

            virtual void onUpdate(const float &dt) override;
            virtual void onEvent(sf::Event &e) override;
            virtual void onRender(emblem::Window &window) override;

            virtual void onPress() override;
            virtual void onRelease() override;

            virtual Widget &setPosition(const sf::Vector2f &pos) override;

            MenuItem &setText(const std::string &text);

            void setCallback(const std::function<void()> &callback);

    };
}
