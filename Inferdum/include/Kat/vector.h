#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>

namespace kat {
    template<typename T>
    struct Vector2 : public sf::Vector2<T> {
        Vector2() : sf::Vector2<T>() {}
        Vector2(const T& x, const T& y) : sf::Vector2<T>(x, y) {}
        Vector2(const sf::Vector2<T>& other) : sf::Vector2<T>(other) {}

        Vector2(const Vector2& other) = default;
        Vector2(Vector2&& other) = default;
        Vector2& operator=(const Vector2& other) = default;
        Vector2& operator=(Vector2&& other) = default;
    };

    template<typename T>
    struct Vector3 : public sf::Vector3<T> {
        Vector3() : sf::Vector3<T>() {}
        Vector3(const T& x, const T& y, const T& z)
            : sf::Vector3<T>(x, y, z) {}
        Vector3(const sf::Vector3<T>& other) : sf::Vector3<T>(other) {}

        Vector3(const Vector3& other) = default;
        Vector3(Vector3&& other) = default;
        Vector3& operator=(const Vector3& other) = default;
        Vector3& operator=(Vector3&& other) = default;
    };

    template<typename T>
    struct Rect : public sf::Rect<T> {
        Rect() : sf::Rect<T>() {}
        Rect(const T& l, const T& t, const T& w, const T& h)
        {
            this->left = l;
            this->top = t;
            this->width = w;
            this->height = h;
        }

        Rect(const sf::Rect<T>& other) : sf::Rect<T>(other) {}

        Rect(const Rect& other) = default;
        Rect(Rect&& other) = default;
        Rect& operator=(const Rect& other) = default;
        Rect& operator=(Rect&& other) = default;
    };

    using Vector2f = Vector2<f32>;
    using Vector2i = Vector2<i32>;
    using Vector2u = Vector2<u32>;

    using Vector3f = Vector3<f32>;
    using Vector3i = Vector3<i32>;
    using Vector3u = Vector3<u32>;

    using FloatRect = Rect<f32>;
    using IntRect = Rect<i32>;
}