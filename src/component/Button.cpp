/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Button
*/

#include <iostream>
#include <string>
#include "component/Button.hpp"

namespace emblem {
    Button::Button()
    {
        if (!__font.loadFromFile("../assets/OldLondon.ttf"))
            std::cerr << "Error: Could not load font" << std::endl;

        __label = dynamic_cast<sf::Text *>(__button.get());
    }

    Button::Button(const std::string &text, const sf::Vector2f &pos, const sf::Vector2f &size, const sf::Color &color) {
        if (!__font.loadFromFile("../assets/OldLondon.ttf"))
            std::cerr << "Error: Could not load font" << std::endl;


        __label = dynamic_cast<sf::Text *>(__button.get());

        __label->setFont(__font);
        __label->setString(text);
        __label->setPosition(pos);
        __label->setCharacterSize(60);

        // __label->setFillColor(color);
    }

    void Button::setText(const std::string &text) {
        __label->setString(text);
    }

    void Button::setPos(const sf::Vector2f &pos) {
        __label->setPosition(pos);
    }

    void Button::setSize(const sf::Vector2f &size) {
        __label->setCharacterSize(size.x);
    }

    void Button::setColor(const sf::Color &color) {
        __label->setFillColor(color);
    }

    void Button::setFont(const sf::Font &font) {
        __label->setFont(font);
    }

    void Button::setCallback(const std::function<void()> &callback) {
        __callback = callback;
    }

    void Button::update(const float &dt) {
        __hovered = false;
        __clicked = false;
        sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition());
        sf::FloatRect textRect = __label->getGlobalBounds();
        if (textRect.contains(mousePos)) {
            __hovered = true;
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                __clicked = true;
            if (__clicked && __callback)
                __callback();
        }
    }

    void Button::render(emblem::Window &window) {
        if (!__button) {
            std::cerr << "Error: Button is not initialized" << std::endl;
            return;
        }
        std::string str = __label->getString();
        // if (__hovered)
            window.draw(__button, "default", 0);
        // else if (__clicked)
        //     window.draw(__button, "default", 0);
        // else
        //     window.draw(__button, "default", 0);
    }

    std::string Button::getText() const {
        return __label->getString();
    }
    
    sf::Vector2f Button::getPos() const {
        return __label->getPosition();
    }

    sf::Vector2f Button::getSize() const {
        return sf::Vector2f(__label->getCharacterSize(), __label->getCharacterSize());
    }

    sf::Color Button::getColor() const {
        return __label->getFillColor();
    }

    sf::Font Button::getFont() const {
        return __font;
    }

    Button *Button::getButton() {
        return this;
    }

    bool Button::isHovered() const {
        return __hovered;
    }

    bool Button::isClicked() const {
        return __clicked;
    }
};