/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Resizable
*/

#pragma once

#include "gui/widget/Static.hpp"

namespace emblem::gui {
    class Resizable : public virtual Static {
        public:
            Resizable() = default;
            virtual ~Resizable() override = default;

            virtual Widget &setSize(const sf::Vector2f &size) override;

    };
}
