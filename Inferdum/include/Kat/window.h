#pragma once

#include <string>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>

#include "./meta.h"
#include "./vector.h"

namespace kat {

    template<typename DrawableObject, typename _Window>
    concept SfmlDrawable = requires(const DrawableObject& drawable, _Window& window) {
        window.draw(drawable);
    };

    template<typename DrawableObject, typename _Window>
    concept KatDrawable = requires(const DrawableObject& drawable, _Window& window) {
        drawable.draw(window);
    };

    /**
     * @brief A window handle.
     */
    using WindowHandle = sf::WindowHandle;

    /**
     * @brief Context settings.
     */
    using ContextSettings = sf::ContextSettings;

    /**
     * @brief ContextSettings attributes.
     */
    using ContextAttribute = sf::ContextSettings::Attribute;

    /**
     * @brief A video mode.
     */
    using VideoMode = sf::VideoMode;

    /**
     * @brief Window style.
     */
    enum class WindowStyle : u32 {
        None = sf::Style::None,
        Titlebar = sf::Style::Titlebar,
        Resize = sf::Style::Resize,
        Close = sf::Style::Close,
        Fullscreen = sf::Style::Fullscreen,
        Default = sf::Style::Default
    };

    /**
     * @brief Fps limit.
     */
    using FpsLimit = u32;

    /**
     * @brief A window size.
     */
    using WindowSize = Vector2u;

    class Window {
    public:
        /**
         * @brief Creates a window from a handle.
         * 
         * @param handle The handle of the window.
         * @param settings The settings of the window.
         * @return Window& Reference to self.
         */
        Window& create(WindowHandle handle, const ContextSettings& settings = ContextSettings());

        /**
         * @brief Creates a window from a video mode.
         * 
         * @param mode The video mode of the window.
         * @param title The title of the window.
         * @param style The style of the window.
         * @param settings The settings of the window.
         * @return Window& Reference to self.
         */
        Window& create(VideoMode mode, const std::string& title = "Kat", WindowStyle style = WindowStyle::Default, const ContextSettings& settings = ContextSettings());

        /**
         * @brief Creates a window from a video mode.
         * 
         * @param mode The video mode of the window.
         * @param title The title of the window.
         * @param style The style of the window.
         * @param settings The settings of the window.
         */
        Window(VideoMode mode, const std::string& title = "Kat", WindowStyle style = WindowStyle::Default, const ContextSettings& settings = ContextSettings());

        /**
         * @brief Creates a window from a handle.
         * 
         * @param handle The handle of the window.
         * @param settings The settings of the window.
         */
        Window(WindowHandle handle, const ContextSettings& settings = ContextSettings());

        /**
         * @brief Closes the window.
         * 
         * @return Window& Reference to self.
         */
        Window& close();

        /**
         * @brief Checks if the window is open.
         * 
         * @return true If the window is open.
         * @return false If the window is closed.
         */
        bool isOpen() const;

        /**
         * @brief Polls an event from the window.
         * 
         * @param event The event to poll.
         * @return true If an event was polled.
         * @return false If no event was polled.
         */
        bool poll(sf::Event& event);

        /**
         * @brief Sets the framerate limit of the window.
         * 
         * @param limit The framerate limit.
         * @return Window& Reference to self.
         */
        Window& setFps(const FpsLimit& limit);

        /**
         * @brief Checks if the window has focus.
         * 
         * @return true If the window has focus.
         * @return false If the window does not have focus.
         */
        bool hasFocus() const;

        /**
         * @brief Gets the size of the window.
         *
         * @return WindowSize The size of the window.
         */
        WindowSize size() const;

        Window &clear();
        Window &display();

        /**
         * @brief Gets the handle of the window.
         * 
         * @return sf::RenderWindow& The handle of the window.
         */
        sf::RenderWindow& get_handle();

        /**
         * @brief Gets the handle of the window. (const)
         * 
         * @return sf::RenderWindow& The handle of the window.
         */
        const sf::RenderWindow& get_handle() const;

        /**
         * @brief Draws a drawable to the window.
         * @param drawable The drawable to draw.
         * @return Window& Reference to self.
         */
        template<typename Drawable>
        requires KatDrawable<Drawable, Window>
        Window& draw(const Drawable& drawable) {
            drawable.draw(*this);
            return *this;
        }

        /**
         * @brief Draws a drawable to the window.
         * @param drawable The drawable to draw.
         * @return Window& Reference to self.
         */
        template<typename Drawable>
        requires SfmlDrawable<Drawable, sf::RenderWindow>
        Window& draw(const Drawable& drawable) {
            m_window.draw(drawable);
            return *this;
        }

    private:
        sf::RenderWindow m_window;
    };

}