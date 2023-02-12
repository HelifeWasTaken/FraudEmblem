/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Static
*/

#include "gui/widget/Static.hpp"

namespace emblem::gui {

    void Static::cook(const sf::Vector2f &pos, const sf::Vector2f &size) {
        if (__cooked)
            return;
        __rect = sf::FloatRect(pos, size);
        __cooked = true;
    }

    sf::Vector2f Static::getPosition() const {
        return sf::Vector2f(__rect.left, __rect.top);
    }

    sf::Vector2f Static::getSize() const {
        return sf::Vector2f(__rect.width, __rect.height);
    }

    sf::Vector2f Static::getOrigin() const {
        return sf::Vector2f(0, 0);
    }

    sf::Vector2f Static::getScale() const {
        return sf::Vector2f(1, 1);
    }

    float Static::getRotation() const {
        return 0;
    }

    sf::Color Static::getColor() const {
        return sf::Color::White;
    }

    bool Static::isFocused() const {
        return false;
    }

    bool Static::isHovered() const {
        return false;
    }

    bool Static::isPressed() const {
        return false;
    }

    bool Static::isDragged() const {
        return false;
    }

    bool Static::isDropped() const {
        return false;
    }

    Widget &Static::setPosition(const sf::Vector2f &pos) {
        return *this;
    }

    Widget &Static::setSize(const sf::Vector2f &size) {
        return *this;
    }

    Widget &Static::setOrigin(const sf::Vector2f &origin) {
        return *this;
    }

    Widget &Static::setScale(const sf::Vector2f &scale) {
        return *this;
    }

    Widget &Static::setRotation(const float &rotation) {
        return *this;
    }

    Widget &Static::setColor(const sf::Color &color) {
        return *this;
    }

}
