#include "Kat/components/texture.h"

namespace kat {

    Texture& Texture::load(sf::Texture* texture)
    {
        m_texture = std::shared_ptr<sf::Texture>(texture);
        return *this;
    }

    Texture& Texture::load(shared_texture_t& texture)
    {
        m_texture = texture;
        return *this;
    }

    Texture& Texture::load(const Texture& texture)
    {
        m_texture = texture.m_texture;
        return *this;
    }

    Texture& Texture::load(const std::string& filename, const Frame& area)
    {
        m_texture = std::make_shared<sf::Texture>();
        if (m_texture->loadFromFile(filename, area) == false) {
            m_texture = nullptr;
        }
        return *this;
    }

    Texture& Texture::load(const Memory data, std::size_t size, const Frame& area)
    {
        m_texture = std::make_shared<sf::Texture>();
        if (m_texture->loadFromMemory(data, size, area) == false) {
            m_texture = nullptr;
        }
        return *this;
    }

    Texture& Texture::create(const TextureSize& size)
    {
        m_texture = std::make_shared<sf::Texture>();
        if (m_texture->create(size.x, size.y) == false) {
            m_texture = nullptr;
        }
        return *this;
    }

    TextureSize Texture::size() const
    {
        return m_texture->getSize();
    }

    Texture& Texture::update(const Pixels pixels)
    {
        m_texture->update(pixels);
        return *this;
    }

    Texture& Texture::update(const Pixels pixels, const Frame& frame)
    {
        m_texture->update(pixels, (u32)frame.width, (u32)frame.height,
                                  (u32)frame.left, (u32)frame.top);
        return *this;
    }

    Texture& Texture::update(const sf::Texture *sfml_texture)
    {
        m_texture->update(*sfml_texture);
        return *this;
    }

    Texture& Texture::update(const sf::Texture *sfml_texture, const TextureCoordinate& x, const TextureCoordinate& y)
    {
        m_texture->update(*sfml_texture, x, y);
        return *this;
    }

    Texture& Texture::update(const Texture& texture)
    {
        m_texture->update(*texture.m_texture);
        return *this;
    }

    Texture& Texture::update(const Texture& texture, const TextureCoordinate& x, const TextureCoordinate& y)
    {
        m_texture->update(*texture.m_texture, x, y);
        return *this;
    }

    Texture& Texture::update(const sf::Window& sfml_window)
    {
        m_texture->update(sfml_window);
        return *this;
    }

    Texture& Texture::update(const sf::Window& sfml_window, const TextureCoordinate& x, const TextureCoordinate& y)
    {
        m_texture->update(sfml_window, x, y);
        return *this;
    }

    Texture& Texture::update(const Window& window)
    {
        return update(window.get_handle());
    }

    Texture& Texture::update(const Window& window, const TextureCoordinate& x, const TextureCoordinate& y)
    {
        return update(window.get_handle(), x, y);
    }

    Texture& Texture::setSmooth(bool smooth)
    {
        m_texture->setSmooth(smooth);
        return *this;
    }

    bool Texture::isSmooth() const { return m_texture->isSmooth(); }

    bool Texture::repeated() const { return m_texture->isRepeated(); }

    bool Texture::repeated(bool rep)
    {
        m_texture->setRepeated(rep);
        return repeated();
    }

    sf::Texture* Texture::raw_handle() { return m_texture.get(); }

    Texture::Texture()
        : m_texture(std::make_shared<sf::Texture>())
    {
    }

    Texture::Texture(sf::Texture* texture)
        : m_texture(texture)
    {
    }

    Texture& Texture::operator=(sf::Texture* texture)
    {
        m_texture = shared_texture_t(texture);
        return *this;
    }

    Texture::Texture(const shared_texture_t& texture)
        : m_texture(texture)
    {
    }

    Texture& Texture::operator=(const shared_texture_t& texture)
    {
        m_texture = texture;
        return *this;
    }

    Texture::Texture(shared_texture_t&& texture)
        : m_texture(std::move(texture))
    {
    }

    Texture& Texture::operator=(shared_texture_t&& texture)
    {
        m_texture = std::move(texture);
        return *this;
    }

}