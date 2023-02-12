/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Window
*/

#include <iostream>

#include "Window.hpp"

emblem::Window::Window(kat::WindowHandle handle, const kat::ContextSettings& settings) : __handle(handle, settings) {
    registerView("default", __handle.get_handle().getDefaultView());
    registerView("gui", __handle.get_handle().getDefaultView(), 1);
    registerView("font", __handle.get_handle().getDefaultView(), 2);
}

emblem::Window::Window(kat::VideoMode mode, const std::string& title, kat::WindowStyle style, const kat::ContextSettings& settings) : __handle(mode, title, style, settings) {
    registerView("default", __handle.get_handle().getDefaultView());
    registerView("gui", __handle.get_handle().getDefaultView(), 1);
    registerView("font", __handle.get_handle().getDefaultView(), 2);
}

emblem::Window& emblem::Window::create(kat::WindowHandle handle, const kat::ContextSettings& settings) {
    __handle.create(handle, settings);
    registerView("default", __handle.get_handle().getDefaultView());
    registerView("gui", __handle.get_handle().getDefaultView(), 1);
    registerView("font", __handle.get_handle().getDefaultView(), 2);
    return *this;
}

emblem::Window& emblem::Window::create(kat::VideoMode mode, const std::string& title, kat::WindowStyle style, const kat::ContextSettings& settings) {
    __handle.create(mode, title, style, settings);
    registerView("default", __handle.get_handle().getDefaultView());
    registerView("gui", __handle.get_handle().getDefaultView(), 1);
    registerView("font", __handle.get_handle().getDefaultView(), 2);
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
    clear();
    for (auto &[z, pair] : __views) {
        __handle.get_handle().setView(pair.second.first.get_handle());
        pair.second.second.draw(__handle);
    }
    __handle.display();
    return *this;
}

emblem::Window &emblem::Window::registerView(const std::string& name, const View& view, kat::ZAxis z) {
    // Basic check to avoid useless search

    __views.insert(std::make_pair(z, std::make_pair(name, std::make_pair(view, kat::BatchRenderer()))));
    return *this;
}

emblem::View &emblem::Window::getView(const std::string& name) {
    for (auto &[_, pair] : __views) {
        if (pair.first == name)
            return pair.second.first;
    }
    throw std::runtime_error("View with name '" + name + "' does not exist");
}

emblem::ViewRender &emblem::Window::getViewRender(const std::string& name) {
    for (auto &[_, pair] : __views) {
        if (pair.first == name)
            return pair.second;
    }
    throw std::runtime_error("View with name '" + name + "' does not exist");
}

kat::Window& emblem::Window::get_handle() {
    return __handle;
}

const kat::Window& emblem::Window::get_handle() const {
    return __handle;
}

