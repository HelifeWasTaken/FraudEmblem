/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Focusable
*/

#pragma once

#include "gui/widget/Static.hpp"

namespace emblem::gui {
    class Focusable : public virtual Static {
        bool __focused = false;

        public:
            Focusable() = default;
            virtual ~Focusable() override = default;

            virtual void onUpdate(const float &dt) override;
            virtual void onEvent(sf::Event &e) override;

            virtual void onFocus() override = 0;
            virtual void onUnfocus() override = 0;

            virtual bool isFocused() const override;

    };
}
