/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Movable
*/

#pragma once

#include "gui/widget/Static.hpp"

namespace emblem::gui {
    class Movable : public virtual Static {
        sf::Vector2f __origin;

        public:
            Movable() = default;
            virtual ~Movable() override = default;

            virtual Widget &setPosition(const sf::Vector2f &pos) override;

            virtual sf::Vector2f getOrigin() const override;
            virtual Widget &setOrigin(const sf::Vector2f &origin) override;

    };
}
