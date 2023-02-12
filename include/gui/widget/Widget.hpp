/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Widget
*/

#pragma once

#include "Window.hpp"

namespace emblem::gui {

    class Widget {
        public:
            Widget();
            virtual ~Widget() = default;

            // Basic Event
            virtual void onLoad() = 0;
            virtual void onRelease() = 0;
            virtual void onUpdate(const float &dt);
            virtual void onEvent(sf::Event &e) {}
            virtual void onRender(Window &window) {}

            // Special Event
            virtual void onFocus() {}
            virtual void onUnfocus() {}
            virtual void onHover() {}
            virtual void onUnhover() {}
            virtual void onClick() {}
            virtual void onUnclick() {}
            virtual void onDrag() {}
            virtual void onDrop() {}

            // Getters
            virtual sf::Vector2f getPosition() const = 0;
            virtual sf::Vector2f getSize() const = 0;
            virtual sf::Vector2f getOrigin() const = 0;
            virtual sf::Vector2f getScale() const = 0;
            virtual float getRotation() const = 0;
            virtual sf::Color getColor() const = 0;

            virtual bool isHover() const = 0;
            virtual bool isClicked() const = 0;
            virtual bool isDragged() const = 0;
            virtual bool isDropped() const = 0;

            // Setters
            virtual Widget &setPosition(const sf::Vector2f &pos) = 0;
            virtual Widget &setSize(const sf::Vector2f &size) = 0;
            virtual Widget &setOrigin(const sf::Vector2f &origin) = 0;
            virtual Widget &setScale(const sf::Vector2f &scale) = 0;
            virtual Widget &setRotation(const float &rotation) = 0;
            virtual Widget &setColor(const sf::Color &color) = 0;

    };
}