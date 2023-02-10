#pragma once

#include "../meta.h"
#include "../window.h"

#include <SFML/Graphics/Texture.hpp>

#include <memory>
#include <string>

namespace kat {

    /**
     * @brief A shared pointer to a texture.
     */
    using shared_texture_t = std::shared_ptr<sf::Texture>;

    /**
     * @brief A single frame of an animation.
     */
    using Frame = IntRect;

    /**
     * @brief A texture coordinate.
     */
    using TextureCoordinate = u32;

    /**
     * @brief A frame size.
     */
    using FrameSize = Vector2<TextureCoordinate>;

    /**
     * @brief A texture size.
     */
    using TextureSize = Vector2<TextureCoordinate>;

    /**
     * @brief A coordinate.
     */
    using Coordinate = float;

    /**
     * @brief A position.
     */
    using Position = Vector2<Coordinate>;


    class Texture {
    public:
        /**
         * @brief Loads a texture from a texture pointer.
         * @param texture The texture pointer.
         * @return Texture& Reference to self.
         */
        Texture& load(sf::Texture* texture);

        /**
         * @brief Loads a texture from a shared texture pointer.
         * @param texture The shared texture pointer.
         * @return Texture& Reference to self.
         */
        Texture& load(shared_texture_t& texture);

        /**
         * @brief Loads a texture from a file.
         *        Makes a copy of the texture.
         *        If you want to use a reference (references are hidden)
         *        just copy the class.
         *
         *        Texture texture = Texture().load("texture.png"); // Load
         *        Texture copy = Texture().load(texture); // Copy
         *        Texture texture2 = Texture(copy); // Reference to the copy
         * @param texture Another kat texture.
         */
        Texture& load(const Texture& texture);

        /**
         * @brief Loads a texture from a file.
         * @param filename The filename of the texture.
         * @param area The area of the texture.
         * @return Texture& Reference to self.
         */
        Texture& load(const std::string& filename,
                      const Frame& area = Frame());

        /**
         * @brief Loads a texture from memory.
         * 
         * @param data The data of the texture.
         * @param size The size of the data.
         * @param area The area of the texture.
         * @return Texture& Reference to self.
         */
        Texture& load(const Memory data, std::size_t size,
                      const Frame& area = Frame());

        /**
         * @brief Loads a texture from a file.
         * 
         * @param size The size of the texture.
         * @return Texture& Reference to self.
         */
        Texture& create(const TextureSize& size);

        /**
         * @brief Gets the size of the texture.
         * 
         * @return TextureSize The size of the texture.
         */
        TextureSize size() const;

        /**
         * @brief Updates the texture.
         * 
         * @param pixels The pixels of the texture.
         * @return Texture& Reference to self.
         */
        Texture& update(const Pixels pixels);

        /**
         * @brief Updates the texture.
         * 
         * @param pixels The pixels of the texture.
         * @param frame The frame of the texture.
         * @return Texture& Reference to self.
         */
        Texture& update(const Pixels pixels, const Frame& frame);

        /**
         * @brief Updates the texture from a sfml raw texture pointer.
         * 
         * @param sfml_texture 
         * @return Texture& 
         */
        Texture& update(const sf::Texture *sfml_texture);

        /**
         * @brief Updates the texture from a sfml raw texture pointer.
         * 
         * @param sfml_texture The sfml raw texture pointer.
         * @param x The x position of the texture.
         * @param y The y position of the texture.
         * @return Texture& Reference to self.
         */
        Texture& update(const sf::Texture *sfml_texture,
            const TextureCoordinate& x, const TextureCoordinate& y);

        /**
         * @brief Updates the texture from another texture.
         *
         * @param texture The texture to update from.
         * @return Texture& Reference to self.
         */
        Texture& update(const Texture& texture);

        /**
         * @brief Updates the texture from another texture.
         *
         * @param texture The texture to update from.
         * @param x The x position of the texture.
         * @param y The y position of the texture.
         * @return Texture& Reference to self.
         */
        Texture& update(const Texture& texture, const TextureCoordinate& x,
                        const TextureCoordinate& y);

        /**
         * @brief Updates the texture from a window.
         *
         * @param sfml_window The sfml raw window pointer.
         * @return Texture& Reference to self.
         */
        Texture& update(const sf::Window& sfml_window);

        /**
         * @brief Updates the texture from a window.
         *
         * @param sfml_window The sfml raw window pointer.
         * @param x The x position of the texture.
         * @param y The y position of the texture.
         * @return Texture& Reference to self.
         */
        Texture& update(const sf::Window& sfml_window, const TextureCoordinate& x,
                        const TextureCoordinate& y);

        /**
         * @brief Updates the texture from a window.
         * 
         * @param window The window to update from.
         * @return Texture& Reference to self.
         */
        Texture& update(const Window& window);

        /**
         * @brief Updates the texture from a window.
         * 
         * @param window The window to update from.
         * @param x The x position of the texture.
         * @param y The y position of the texture.
         * @return Texture& Reference to self.
         */
        Texture& update(const Window& window, const TextureCoordinate& x,
                        const TextureCoordinate& y);

        /**
         * @brief Set the Smooth object
         * 
         * @param smooth 
         * @return Texture& 
         */
        Texture& setSmooth(bool smooth);

        /**
         * @brief Is the texture smooth?
         * 
         * @return true The texture is smooth.
         * @return false The texture is not smooth.
         */
        bool isSmooth() const;

        /**
         * @brief Set the Repeated object
         * 
         * @param repeated 
         * @return Texture& 
         */
        bool repeated() const;

        /**
         * @brief Is the texture repeated?
         * 
         * @return true The texture is repeated.
         * @return false The texture is not repeated.
         */
        bool repeated(bool rep);

        /**
         * @brief Get the native handle of the texture.
         * 
         * @return sf::Texture* The native handle of the texture.
         */
        sf::Texture* raw_handle();

        /**
         * @brief Construct a new Texture object
         */
        Texture();

        /**
         * @brief Construct a new Texture object
         * @param texture 
         */
        Texture(sf::Texture* texture);

        /**
         * @brief Construct a new Texture object
         * @param texture 
         * @return Texture& 
         */
        Texture& operator=(sf::Texture* texture);

        /**
         * @brief Construct a new Texture object
         * @param texture 
         */
        Texture(const shared_texture_t& texture);

        /**
         * @brief Construct a new Texture object
         * @param texture 
         * @return Texture& 
         */
        Texture& operator=(const shared_texture_t& texture);

        /**
         * @brief Construct a new Texture object
         * 
         * @param texture 
         */
        Texture(shared_texture_t&& texture);

        /**
         * @brief Construct a new Texture object
         * 
         * @param texture 
         * @return Texture& 
         */
        Texture& operator=(shared_texture_t&& texture);

        /**
         * @brief Construct a new Texture object
         * 
         * @param texture 
         */
        Texture(const Texture&) = default;

        /**
         * @brief Construct a new Texture object
         * 
         * @param texture 
         * @return Texture& 
         */
        Texture& operator=(const Texture&) = default;

        /**
         * @brief Construct a new Texture object
         * 
         * @param texture 
         */
        Texture(Texture&&) = default;

        /**
         * @brief Construct a new Texture object
         * 
         * @param texture 
         * @return Texture& 
         */
        Texture& operator=(Texture&&) = default;

    private:
        shared_texture_t m_texture;
    };
}