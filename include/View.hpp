/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** View
*/

#pragma once

#include <SFML/Graphics.hpp>

namespace emblem {

    class View {
        public:
            View() = default;
            View(const sf::FloatRect &viewport);
            View(const sf::Vector2f &pos, const sf::Vector2f &size);
            View(const float &x, const float &y, const float &width, const float &height);
            View(const sf::View &view);
            ~View() = default;

            View &setCenter(const float &x, const float &y);
            View &setCenter(const sf::Vector2f &pos);

            View &setSize(const float &width, const float &height);
            View &setSize(const sf::Vector2f &size);

            View &setRotation(const float &angle);

            View &setViewport(const sf::FloatRect &viewport);
            View &reset(const sf::FloatRect &viewport);

            const sf::Vector2f &getCenter() const;
            const sf::Vector2f &getSize() const;

            float getRotation() const;

            const sf::FloatRect &getViewport() const;

            View &move(const float &x, const float &y);
            View &move(const sf::Vector2f &offset);

            View &rotate(const float &angle);
            View &zoom(const float &factor);

            sf::View &get_handle();
            const sf::View &get_handle() const;

        private:
            sf::View __handle;
    };
}
