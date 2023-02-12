/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Draggable
*/

#pragma once

#include "gui/widget/Static.hpp"

namespace emblem::gui {
    class Draggable : public virtual Static {
        bool __dragging = false;
        sf::Vector2f __dragOffset;

        public:
            Draggable() = default;
            virtual ~Draggable() override = default;

            virtual void onUpdate(const float &dt) override;
            virtual void onEvent(sf::Event &e) override;

            virtual void onDrag() override = 0;
            virtual void onDrop() override = 0;

            virtual bool isDragged() const override;
            virtual bool isDropped() const override;

    };
}
