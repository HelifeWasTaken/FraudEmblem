#pragma once

#include <SFML/Graphics.hpp>

#include "./texture.h"
#include "../batch.h"

namespace kat {

    /**
     * @brief A shared pointer to a sprite.
     */
    using shared_sprite_t = std::shared_ptr<sf::Sprite>;

    /**
     * @brief An angle
     */
    using Angle = float;

    /**
     * @brief A scale factor.
     */
    using ScaleFactor = float;

    /**
     * @brief A scale.
     */
    using Scale = Vector2<ScaleFactor>;

    /**
     * @brief A sprite color.
     */
    using Color = sf::Color;

    /**
     * @brief A transform.
     */
    using Transform = sf::Transform;

    /**
     * @brief Global bounds.
     */
    using GlobalBounds = FloatRect;

    /**
     * @brief Local bounds.
     */
    using LocalBounds = FloatRect;

    class Sprite {
    public:
        /**
         * @brief Creates a sprite from a texture.
         * 
         * @param texture The texture of the sprite.
         * @return Sprite& Reference to self.
         */
        Sprite& create(Texture& texture);

        /**
         * @brief Creates a sprite from a texture.
         * 
         * @param texture The texture of the sprite.
         * @return Sprite& Reference to self.
         */
        Sprite& create(const shared_texture_t& texture);

        /**
         * @brief Creates a sprite from a texture.
         * 
         * @param texture The texture of the sprite.
         * @return Sprite& Reference to self.
         */
        Sprite& create(sf::Texture* texture);

        /**
         * @brief Sets the position of the sprite.
         * @param x The x position of the sprite.
         * @param y The y position of the sprite.
         * @return Sprite& Reference to self.
         */
        Sprite& setPosition(const Coordinate& x, const Coordinate& y);

        /**
         * @brief Sets the position of the sprite.
         * @param position The position of the sprite.
         * @return Sprite& Reference to self.
         */
        Sprite& setPosition(const Position& position);

        /**
         * @brief Sets the rotation of the sprite.
         * @param angle The angle of the sprite.
         * @return Sprite& Reference to self.
         */
        Sprite& setRotation(const Angle& angle);

        /**
         * @brief Sets the scale of the sprite.
         * @param x The x scale of the sprite.
         * @param y The y scale of the sprite.
         * @return Sprite& Reference to self.
         */
        Sprite& setScale(const ScaleFactor& x, const ScaleFactor& y);
    
        /**
         * @brief Sets the scale of the sprite.
         * @param scale The scale of the sprite.
         * @return Sprite& Reference to self.
         */
        Sprite& setScale(const Scale& scale);

        /**
         * @brief Sets the origin of the sprite.
         * @param x The x origin of the sprite.
         * @param y The y origin of the sprite.
         * @return Sprite& Reference to self.
         */
        Sprite& setOrigin(const Coordinate& x, const Coordinate& y);

        /**
         * @brief Sets the origin of the sprite.
         * @param origin The origin of the sprite.
         * @return Sprite& Reference to self.
         */
        Sprite& setOrigin(const Position& origin);

        /**
         * @brief Gets the position of the sprite.
         * @return Position& The position of the sprite.
         */
        Position getPosition() const;

        /**
         * @brief Gets the rotation of the sprite.
         * @return Angle The rotation of the sprite.
         */
        Angle getRotation() const;

        /**
         * @brief Gets the scale of the sprite.
         * @return Scale The scale of the sprite.
         */
        Scale getScale() const;

        /**
         * @brief Gets the origin of the sprite.
         * @return Position The origin of the sprite.
         */
        Position getOrigin() const;

        /**
         * @brief Moves the sprite.
         * @param x The x offset of the sprite.
         * @param y The y offset of the sprite.
         * @return Sprite& Reference to self.
         */
        Sprite& move(const Coordinate& x, const Coordinate& y);

        /**
         * @brief Moves the sprite.
         * @param offset The offset of the sprite.
         * @return Sprite& Reference to self.
         */
        Sprite& move(const Position& offset);

        /**
         * @brief Rotates the sprite.
         * @param angle The angle to rotate the sprite.
         * @return Sprite& Reference to self.
         */
        Sprite& rotate(const Angle& angle);

        /**
         * @brief Scales the sprite.
         * @param factor The scale factor of the sprite.
         * @return Sprite& Reference to self.
         */
        Sprite& scale(const ScaleFactor& factor);

        /**
         * @brief Scales the sprite.
         * @param x The x scale of the sprite.
         * @param y The y scale of the sprite.
         * @return Sprite& Reference to self.
         */
        Sprite& scale(const ScaleFactor& x, const ScaleFactor& y);

        /**
         * @brief Scales the sprite.
         * @param scale The scale of the sprite.
         * @return Sprite& Reference to self.
         */
        Sprite& scale(const Scale& scale);

        /**
         * @brief Gets the transform of the sprite.
         * @return Transform The transform of the sprite.
         */
        const Transform& getTransform() const;

        /**
         * @brief Gets the inverse transform of the sprite.
         * @return Transform The inverse transform of the sprite.
         */
        const Transform& getInverseTransform() const;

        /**
         * @brief Draws the sprite.
         * @param window The window to draw the sprite to.
         */
        void draw(Window& window) const;

        /**
         * @brief Sets the texture rect of the sprite.
         * @param frame The texture rect of the sprite.
         * @return Sprite& Reference to self.
         */
        Sprite& setTextureRect(const Frame& rect);

        /**
         * @brief Gets the texture rect of the sprite.
         * @return IntRect The texture rect of the sprite.
         */
        Frame getTextureRect() const;

        /**
         * @brief Sets the color of the sprite.
         * @param color The color of the sprite.
         * @return Sprite& Reference to self.
         */
        Sprite& setColor(const Color& color);

        /**
         * @brief Get the texture of the sprite.
         * @return Texture& The texture of the sprite.
         */
        Texture& getTexture();

        /**
         * @brief Get the texture of the sprite.
         * @return const Texture& The texture of the sprite.
         */
        const Texture& getTexture() const;

        /**
         * @brief Gets the color of the sprite.
         * @return Color The color of the sprite.
         */
        const Color& getColor() const;

        /**
         * @brief Gets the global bounds of the sprite.
         * @return GlobalBounds The global bounds of the sprite.
         */
        const GlobalBounds getGlobalBounds() const;

        /**
         * @brief Gets the local bounds of the sprite.
         * @return LocalBounds The local bounds of the sprite.
         */
        const LocalBounds getLocalBounds() const;

        Sprite(Sprite&& other) = default;
        Sprite& operator=(Sprite&& other) = default;
        Sprite(const Sprite& other) = default;
        Sprite() = default;
        ~Sprite() = default;

        const sf::Sprite *raw_handle() const;
        shared_drawable_t as_drawable() const;

    private:
        Texture m_texture;
        shared_sprite_t m_sprite = std::make_shared<sf::Sprite>();
    };
}