/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Button
*/

#pragma once

#include <functional>

#include "gui/widget/Movable.hpp"
#include "gui/widget/Resizable.hpp"
#include "gui/widget/Scalable.hpp"
#include "gui/widget/Rotatable.hpp"

#include "gui/widget/Hoverable.hpp"
#include "gui/widget/Clickable.hpp"

namespace emblem::gui {
    class Button : public Movable, public Resizable, public Scalable, public Rotatable, public Hoverable, public Clickable {
        bool __wasPressed = false;

        std::function<void()> __callback;

        public:
            Button() = default;
            virtual ~Button() override = default;

            virtual void onUpdate(const float &dt) override;
            virtual void onEvent(sf::Event &e) override;

            void setCallback(const std::function<void()> &callback);
    };
}
