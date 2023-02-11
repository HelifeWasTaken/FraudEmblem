#include "Kat/components/sprite.h"
#include "Kat/math.h"

namespace kat {

    Sprite& Sprite::create(Texture& texture)
    {
        m_texture = texture;
        m_sprite->setTexture(*texture.raw_handle());
        return *this;
    }

    Sprite& Sprite::create(const shared_texture_t& texture)
    {
        m_texture = Texture(texture);
        m_sprite->setTexture(*texture);
        return *this;
    }

    Sprite& Sprite::create(sf::Texture* texture)
    {
        m_sprite->setTexture(*texture);
        m_texture = Texture(texture);
        return *this;
    }

    Sprite& Sprite::setPosition(const Coordinate& x, const Coordinate& y)
    {
        return setPosition({ x, y });
    }

    Sprite& Sprite::setPosition(const Position& position)
    {
        m_sprite->setPosition(position);
        return *this;
    }

    Sprite& Sprite::setRotation(const Angle& angle)
    {
        m_sprite->setRotation(angle);
        return *this;
    }

    Sprite& Sprite::setScale(const ScaleFactor& x, const ScaleFactor& y)
    {
        return setScale({ x, y });
    }

    Sprite& Sprite::setScale(const Scale& scale)
    {
        m_sprite->setScale(scale);
        return *this;
    }

    Sprite& Sprite::setOrigin(const Coordinate& x, const Coordinate& y)
    {
        return setOrigin({ x, y });
    }

    Sprite& Sprite::setOrigin(const Position& origin)
    {
        m_sprite->setOrigin(origin);
        return *this;
    }

    Position Sprite::getPosition() const
    {
        return m_sprite->getPosition();
    }

    Angle Sprite::getRotation() const
    {
        return m_sprite->getRotation();
    }

    Scale Sprite::getScale() const
    {
        return m_sprite->getScale();
    }

    Position Sprite::getOrigin() const
    {
        return m_sprite->getOrigin();
    }

    Sprite& Sprite::move(const Coordinate& x, const Coordinate& y)
    {
        return move({ x, y });
    }

    Sprite& Sprite::move(const Position& offset)
    {
        m_sprite->move(offset);
        return *this;
    }

    Sprite& Sprite::rotate(const Angle& angle)
    {
        m_sprite->rotate(angle);
        return *this;
    }

    Sprite& Sprite::scale(const ScaleFactor& x, const ScaleFactor& y)
    {
        return scale({ x, y });
    }

    Sprite& Sprite::scale(const Scale& pscale)
    {
        m_sprite->scale(pscale);
        return *this;
    }

    Sprite& Sprite::scale(const ScaleFactor& factor)
    {
        return scale({ factor, factor });
    }

    const Transform& Sprite::getTransform() const
    {
        return m_sprite->getTransform();
    }

    const Transform& Sprite::getInverseTransform() const
    {
        return m_sprite->getInverseTransform();
    }

    void Sprite::draw(Window& window) const
    {
        window.draw(*m_sprite);
    }

    Sprite& Sprite::setTextureRect(const Frame& frame)
    {
        m_sprite->setTextureRect(frame);
        return *this;
    }

    Frame Sprite::getTextureRect() const
    {
        return m_sprite->getTextureRect();
    }

    Sprite& Sprite::setColor(const Color& color)
    {
        m_sprite->setColor(color);
        return *this;
    }

    const Texture& Sprite::getTexture() const
    {
        return m_texture;
    }

    Texture& Sprite::getTexture()
    {
        return m_texture;
    }

    const Color& Sprite::getColor() const
    {
        return m_sprite->getColor();
    }

    const GlobalBounds Sprite::getGlobalBounds() const
    {
        return m_sprite->getGlobalBounds();
    }

    const LocalBounds Sprite::getLocalBounds() const
    {
        return m_sprite->getLocalBounds();
    }

    const sf::Sprite *Sprite::raw_handle() const
    {
        return m_sprite.get();
    }

    shared_drawable_t Sprite::as_drawable() const
    {
        return m_sprite;
    }

    Sprite &Sprite::flipX(bool flip) {
        auto scale = getScale();
        scale.x = std::abs(scale.x);
        if (flip) {
            setScale(-scale.x, scale.y);
        } else {
            setScale(scale.x, scale.y);
        }
        __flipX = flip;
        return *this;
    }

    Sprite &Sprite::flipY(bool flip) {
        auto scale = getScale();
        scale.y = std::abs(scale.y);
        if (flip) {
            setScale(scale.x, -scale.y);
        } else {
            setScale(scale.x, scale.y);
        }
        __flipY = flip;
        return *this;
    }

    bool Sprite::isFlippedX() const {
        return __flipX;
    }

    bool Sprite::isFlippedY() const {
        return __flipY;
    }
}