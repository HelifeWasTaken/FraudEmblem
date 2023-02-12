/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** MenuItem
*/

#include "gui/widget/MenuItem.hpp"
#include "Context.hpp"

namespace emblem::gui {

    MenuItem::MenuItem() {
        sf::Text *__txt = dynamic_cast<sf::Text *>(this->__text.get());
        __txt->setFont(Context::font());
        __txt->setCharacterSize(32);
        __txt->setFillColor(sf::Color::White);
    }

    void MenuItem::onUpdate(const float &dt) {
        Movable::onUpdate(dt);

        Clickable::onUpdate(dt);
    }

    void MenuItem::onEvent(sf::Event &e) {
        Movable::onEvent(e);

        Clickable::onEvent(e);
    }

    void MenuItem::onRender(emblem::Window &window) {
        window.draw(this->__text, "font", 1026);
    }

    void MenuItem::onPress() {
        __callback();
    }

    void MenuItem::onRelease() {}

    Widget &MenuItem::setPosition(const sf::Vector2f &pos) {
        Movable::setPosition(pos);
        sf::Text *__txt = dynamic_cast<sf::Text *>(this->__text.get());
        __txt->setPosition(pos);
        return *this;
    }

    MenuItem &MenuItem::setText(const std::string &text) {
        sf::Text *__txt = dynamic_cast<sf::Text *>(this->__text.get());
        __txt->setString(text);
        return *this;
    }

    void MenuItem::setCallback(const std::function<void()> &callback) {
        this->__callback = callback;
    }

}
