/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Rotatable
*/

#pragma once

#include "gui/widget/Static.hpp"

namespace emblem::gui {
    class Rotatable : public virtual Static {
        float __angle;

        public:
            Rotatable() = default;
            virtual ~Rotatable() override = default;

            virtual float getRotation() const override;
            virtual Widget &setRotation(const float &rotation) override;

    };
}
