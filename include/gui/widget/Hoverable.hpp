/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Hoverable
*/

#pragma once

#include "gui/widget/Static.hpp"

namespace emblem::gui {

    class Hoverable : public virtual Static {
        bool __hovered = false;

        public:
            Hoverable() = default;
            virtual ~Hoverable() override = default;

            virtual void onUpdate(const float &dt) override;
            virtual void onEvent(sf::Event &e) override;

            virtual void onHover() override = 0;
            virtual void onUnhover() override = 0;

            virtual bool isHovered() const override;

    };
}