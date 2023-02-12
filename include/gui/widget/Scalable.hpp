/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Scalable
*/

#pragma once

#include "gui/widget/Static.hpp"

namespace emblem::gui {
    class Scalable : public virtual Static {
        sf::Vector2f __scale = sf::Vector2f(1, 1);

        public:
            Scalable() = default;
            virtual ~Scalable() override = default;

            virtual sf::Vector2f getScale() const override;
            virtual Widget &setScale(const sf::Vector2f &scale) override;

    };
}
