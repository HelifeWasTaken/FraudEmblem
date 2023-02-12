/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Static
*/

#pragma once

#include "gui/widget/Widget.hpp"

namespace emblem::gui {

    // Basic Widget that have no interaction
    class Static : public Widget {
        bool __cooked = false;

        protected:
            sf::FloatRect __rect; // For later uses

        public:
            Static() = default;
            virtual ~Static() override = default;

            // Can only be used once to initialize the widget
            void cook(const sf::Vector2f &pos, const sf::Vector2f &size);

            // Basic
            virtual void onLoad() override {}
            virtual void onUnload() override {}
            virtual void onUpdate(const float &dt) override {}
            virtual void onEvent(sf::Event &e) override {}
            virtual void onRender(emblem::Window &window) override {}

            // Basic Event
            virtual void onHover() override {}
            virtual void onUnhover() override {}
            virtual void onPress() override {}
            virtual void onRelease() override {}

            // Special Event
            virtual void onFocus() override {}
            virtual void onUnfocus() override {}
            virtual void onDrag() override {}
            virtual void onDrop() override {}

            // Getters
            virtual sf::Vector2f getPosition() const override;
            virtual sf::Vector2f getSize() const override;
            virtual sf::Vector2f getOrigin() const override;
            virtual sf::Vector2f getScale() const override;
            virtual float getRotation() const override;
            virtual sf::Color getColor() const override;

            virtual bool isHovered() const override;
            virtual bool isPressed() const override;
            virtual bool isFocused() const override;
            virtual bool isDragged() const override;
            virtual bool isDropped() const override;

            // Setters
            virtual Widget &setPosition(const sf::Vector2f &pos) override;
            virtual Widget &setSize(const sf::Vector2f &size) override;
            virtual Widget &setOrigin(const sf::Vector2f &origin) override;
            virtual Widget &setScale(const sf::Vector2f &scale) override;
            virtual Widget &setRotation(const float &rotation) override;
            virtual Widget &setColor(const sf::Color &color) override;
    };
}
