/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Clickable
*/

#pragma once

#include "gui/widget/Static.hpp"

namespace emblem::gui {

    class Clickable : public virtual Static {
        bool __pressed = false;

        public:
            Clickable() = default;
            virtual ~Clickable() override = default;

            virtual void onUpdate(const float &dt) override;
            virtual void onEvent(sf::Event &e) override;

            virtual void onPress() override = 0;
            virtual void onRelease() override = 0;

            virtual bool isPressed() const override;

    };
}
