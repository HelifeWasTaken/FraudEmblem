/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Button
*/

#pragma once
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
// include all SFML
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include "Window.hpp"
#include "Kat.h"

namespace emblem {
    class Button {
        public:
            Button();
            Button(const std::string &text, const sf::Vector2f &pos, const sf::Vector2f &size, const sf::Color &color);
            virtual ~Button() = default;

            void setText(const std::string &text);
            void setPos(const sf::Vector2f &pos);
            void setSize(const sf::Vector2f &size);
            void setColor(const sf::Color &color);
            void setFont(const sf::Font &font);
            void setCallback(const std::function<void()> &callback);

            void update(const float &dt);
            void render(emblem::Window &window);
            Button *getButton();

            std::string getText() const;
            sf::Vector2f getPos() const;
            sf::Vector2f getSize() const;
            sf::Color getColor() const;
            sf::Font getFont() const;

            bool isHovered() const;
            bool isClicked() const;

            kat::shared_drawable_t __button = std::make_shared<sf::Text>();
            sf::Font __font;
            sf::Text *__label;
            sf::RectangleShape __rect;
            std::function<void()> __callback;
            bool __hovered = false;
            bool __clicked = false;
    };
};