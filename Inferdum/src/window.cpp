#include "Kat/window.h"
#include <SFML/System/String.hpp>

namespace kat {

    Window& Window::create(WindowHandle handle, const ContextSettings& settings)
    {
        m_window.create(handle, settings);
        return *this;
    }

    Window& Window::create(VideoMode mode, const std::string& title, WindowStyle style, const ContextSettings& settings)
    {
        m_window.create(mode, title, (u32)style, settings);
        return *this;
    }

    Window::Window(VideoMode mode, const std::string& title, WindowStyle style, const ContextSettings& settings)
    {
        create(mode, title, style, settings);
    }

    Window::Window(WindowHandle handle, const ContextSettings& settings)
    {
        create(handle, settings);
    }

    Window& Window::close()
    {
        m_window.close();
        return *this;
    }

    bool Window::isOpen() const
    {
        return m_window.isOpen();
    }

    bool Window::poll(sf::Event& event)
    {
        return m_window.pollEvent(event);
    }

    Window& Window::setFps(const FpsLimit& limit)
    {
        m_window.setFramerateLimit(limit);
        return *this;
    }

    bool Window::hasFocus() const
    {
        return m_window.hasFocus();
    }

    WindowSize Window::size() const
    {
        return m_window.getSize();
    }

    Window &Window::clear() {
        m_window.clear();
        return *this;
    }

    Window &Window::display() {
        m_window.display();
        return *this;
    }


    sf::RenderWindow& Window::get_handle()
    {
        return m_window;
    }

    const sf::RenderWindow& Window::get_handle() const
    {
        return m_window;
    }
}