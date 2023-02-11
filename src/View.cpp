/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** View
*/

#include "View.hpp"

emblem::View::View(const sf::FloatRect &viewport) : __handle(viewport) {}

emblem::View::View(const sf::Vector2f &pos, const sf::Vector2f &size) : __handle(pos, size) {}

emblem::View::View(const float &x, const float &y, const float &width, const float &height) : __handle(sf::Vector2f(x, y), sf::Vector2f(width, height)) {}

emblem::View &emblem::View::setCenter(const float &x, const float &y) {
    __handle.setCenter(x, y);
    return *this;
}

emblem::View &emblem::View::setCenter(const sf::Vector2f &pos) {
    __handle.setCenter(pos);
    return *this;
}

emblem::View &emblem::View::setSize(const float &width, const float &height) {
    __handle.setSize(width, height);
    return *this;
}

emblem::View &emblem::View::setSize(const sf::Vector2f &size) {
    __handle.setSize(size);
    return *this;
}

emblem::View &emblem::View::setRotation(const float &angle) {
    __handle.setRotation(angle);
    return *this;
}

emblem::View &emblem::View::setViewport(const sf::FloatRect &viewport) {
    __handle.setViewport(viewport);
    return *this;
}

emblem::View &emblem::View::reset(const sf::FloatRect &viewport) {
    __handle.reset(viewport);
    return *this;
}

const sf::Vector2f &emblem::View::getCenter() const {
    return __handle.getCenter();
}

const sf::Vector2f &emblem::View::getSize() const {
    return __handle.getSize();
}

float emblem::View::getRotation() const {
    return __handle.getRotation();
}

const sf::FloatRect &emblem::View::getViewport() const {
    return __handle.getViewport();
}

emblem::View &emblem::View::move(const float &x, const float &y) {
    __handle.move(x, y);
    return *this;
}

emblem::View &emblem::View::move(const sf::Vector2f &offset) {
    __handle.move(offset);
    return *this;
}

emblem::View &emblem::View::rotate(const float &angle) {
    __handle.rotate(angle);
    return *this;
}

emblem::View &emblem::View::zoom(const float &factor) {
    __handle.zoom(factor);
    return *this;
}


sf::View &emblem::View::get_handle() {
    return __handle;
}

const sf::View &emblem::View::get_handle() const {
    return __handle;
}
