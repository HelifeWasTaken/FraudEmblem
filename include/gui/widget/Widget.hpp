/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Widget
*/

#pragma once

#include <cstdint>
#include <array>

#include "Window.hpp"

namespace emblem {

    class GUI;

    namespace gui {

        class Widget {
            // std::array<uint32_t, 16> __luuid;

            protected:
                GUI *__gui = nullptr;

            public:
                Widget() = default;
                virtual ~Widget() = default;

                // Basic
                virtual void onLoad() = 0;
                virtual void onUnload() = 0;
                virtual void onUpdate(const float &dt) = 0;
                virtual void onEvent(sf::Event &e) {}
                virtual void onRender(emblem::Window &window) {}

                // Basic Event
                virtual void onHover() {}
                virtual void onUnhover() {}
                virtual void onPress() {}
                virtual void onRelease() {}

                // Special Event
                virtual void onFocus() {}
                virtual void onUnfocus() {}
                virtual void onDrag() {}
                virtual void onDrop() {}

                // Getters
                virtual sf::Vector2f getPosition() const = 0;
                virtual sf::Vector2f getSize() const = 0;
                virtual sf::Vector2f getOrigin() const = 0;
                virtual sf::Vector2f getScale() const = 0;
                virtual float getRotation() const = 0;
                virtual sf::Color getColor() const = 0;

                virtual bool isFocused() const = 0;
                virtual bool isHovered() const = 0;
                virtual bool isPressed() const = 0;
                virtual bool isDragged() const = 0;
                virtual bool isDropped() const = 0;

                // Setters
                virtual Widget &setPosition(const sf::Vector2f &pos) = 0;
                virtual Widget &setSize(const sf::Vector2f &size) = 0;
                virtual Widget &setOrigin(const sf::Vector2f &origin) = 0;
                virtual Widget &setScale(const sf::Vector2f &scale) = 0;
                virtual Widget &setRotation(const float &rotation) = 0;
                virtual Widget &setColor(const sf::Color &color) = 0;

                void bindtoGUI(GUI *gui) { this->__gui = gui; }

        };
    }
}