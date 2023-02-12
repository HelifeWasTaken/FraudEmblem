/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Colorable
*/

#pragma once

#include "gui/widget/Static.hpp"

namespace emblem::gui {
    class Colorable : public virtual Static {
        sf::Color __color = sf::Color::White;

        public:
            Colorable() = default;
            virtual ~Colorable() override = default;

            virtual sf::Color getColor() const override;
            virtual Widget &setColor(const sf::Color &color) override;

    };
}
