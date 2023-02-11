/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Window
*/

#pragma once

#include <unordered_map>

#include "batch.h"
#include "View.hpp"
#include "window.h"

namespace emblem {

    using ViewRender = std::pair<View, kat::BatchRenderer>;

    class Window {
        kat::Window __handle;

        std::vector<std::tuple<kat::ZAxis, std::string, ViewRender>> __views;

        public:
            Window();
            ~Window();

            Window(kat::WindowHandle handle, const kat::ContextSettings& settings = sf::ContextSettings());
            Window(kat::VideoMode mode, const std::string& title = "Kat", kat::WindowStyle style = kat::WindowStyle::Default, const kat::ContextSettings& settings = sf::ContextSettings());

            Window& create(kat::WindowHandle handle, const kat::ContextSettings& settings = sf::ContextSettings());
            Window& create(kat::VideoMode mode, const std::string& title = "Kat", kat::WindowStyle style = kat::WindowStyle::Default, const kat::ContextSettings& settings = sf::ContextSettings());

            Window& close();

            bool isOpen() const;

            bool poll(sf::Event& event);

            Window& setFps(const kat::FpsLimit& limit);

            bool hasFocus() const;

            kat::WindowSize size() const;

            Window &clear();

            Window &render();

            Window &registerView(const std::string& name, const View& view, kat::ZAxis z = 0);

            View &getView(const std::string& name);
            ViewRender &getViewRender(const std::string& name);

            kat::Window& get_handle();
            const kat::Window& get_handle() const;

            template<typename Drawable>
            requires kat::KatDrawable<Drawable, Window>
            Window& draw(const Drawable& drawable, const std::string &view = "default", kat::ZAxis z = 0) {
                auto &viewRender = getViewRender(view);

                viewRender.second.add(drawable, z);
                return *this;
            }
    };
}
