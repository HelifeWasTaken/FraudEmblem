/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Window
*/

#include "Window.hpp"

emblem::Window::Window(kat::WindowHandle handle, const kat::ContextSettings& settings) : __handle(handle, settings) {}

emblem::Window::Window(kat::VideoMode mode, const std::string& title, kat::WindowStyle style, const kat::ContextSettings& settings) : __handle(mode, title, style, settings) {}

emblem::Window& emblem::Window::create(kat::WindowHandle handle, const kat::ContextSettings& settings) {
    __handle.create(handle, settings);
    return *this;
}

emblem::Window& emblem::Window::create(kat::VideoMode mode, const std::string& title, kat::WindowStyle style, const kat::ContextSettings& settings) {
    __handle.create(mode, title, style, settings);
    return *this;
}

emblem::Window& emblem::Window::close() {
    __handle.close();
    return *this;
}

bool emblem::Window::isOpen() const {
    return __handle.isOpen();
}

bool emblem::Window::poll(sf::Event& event) {
    return __handle.poll(event);
}

emblem::Window& emblem::Window::setFps(const kat::FpsLimit& limit) {
    __handle.setFps(limit);
    return *this;
}

bool emblem::Window::hasFocus() const {
    return __handle.hasFocus();
}

kat::WindowSize emblem::Window::size() const {
    return __handle.size();
}

emblem::Window &emblem::Window::clear() {
    __handle.clear();
    return *this;
}

emblem::Window &emblem::Window::render() {
    for (auto &view : __views) {
        __handle.get_handle().setView(std::get<emblem::ViewRender>(view).first.get_handle());
        std::get<emblem::ViewRender>(view).second.draw(__handle);
    }
    __handle.display();
    return *this;
}

emblem::Window &emblem::Window::registerView(const std::string& name, const View& view, kat::ZAxis z) {
    // dichotomic search
    size_t i = 0;

    for (size_t step = __views.size() / 2; step > 0; step /= 2) {
        while (i + step < __views.size() && std::get<kat::ZAxis>(__views.at(i + step)) <= z) {
            i += step;
        }
    }
    if (i < __views.size() && std::get<kat::ZAxis>(__views.at(i)) == z) {
        for (; std::get<kat::ZAxis>(__views.at(i)) == z; ++i) {
            if (std::get<std::string>(__views.at(i)) == name) {
                throw std::runtime_error("View with name '" + name + "' already exists");
            }
        }
    }
    __views.insert(__views.begin() + i - 1, { z, name, { view, kat::BatchRenderer() } });
    return *this;
}

emblem::View &emblem::Window::getView(const std::string& name) {
    // dichotomic search
    for (auto &entry : __views) {
        if (std::get<std::string>(entry) == name)
            return std::get<ViewRender>(entry).first;
    }
    throw std::runtime_error("View with name '" + name + "' does not exist");
}

emblem::ViewRender &emblem::Window::getViewRender(const std::string& name) {
    // dichotomic search
    for (auto &entry : __views) {
        if (std::get<std::string>(entry) == name)
            return std::get<ViewRender>(entry);
    }
    throw std::runtime_error("View with name '" + name + "' does not exist");
}

kat::Window& emblem::Window::get_handle() {
    return __handle;
}

const kat::Window& emblem::Window::get_handle() const {
    return __handle;
}

