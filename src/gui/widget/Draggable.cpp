/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Draggable
*/

#include "gui/widget/Draggable.hpp"

namespace emblem::gui {

    void Draggable::onEvent(sf::Event &e) {
        if (e.type == sf::Event::MouseButtonPressed) {
            if (e.mouseButton.button == sf::Mouse::Left) {
                if (__rect.contains(e.mouseButton.x, e.mouseButton.y)) {
                    __dragging = true;
                    __dragOffset = sf::Vector2f(e.mouseButton.x, e.mouseButton.y) - getPosition();
                    onDrag();
                }
            }
        }
        if (e.type == sf::Event::MouseButtonReleased) {
            if (e.mouseButton.button == sf::Mouse::Left) {
                if (__dragging) {
                    __dragging = false;
                    onDrop();
                }
            }
        }
        if (e.type == sf::Event::MouseMoved) {
            if (__dragging) {
                setPosition(sf::Vector2f(e.mouseMove.x, e.mouseMove.y) - __dragOffset);
            }
        }
    }

    void Draggable::onUpdate(const float &dt) {
        if (__dragging) {
            setPosition(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y) - __dragOffset);
        }
    }

    bool Draggable::isDragged() const {
        return __dragging;
    }

    bool Draggable::isDropped() const {
        return !__dragging;
    }
}
