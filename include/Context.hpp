/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Context
*/

#pragma once

#include <filesystem>
#include <SFML/Window.hpp>

#include "entt/entt.hpp"
#include "Window.hpp"
#include "resource.h"
#include "state/Machine.hpp"
#include "component/Character.hpp"
#include "gui/GuiHandler.hpp"

namespace emblem {
    class Context {
        entt::registry __registry;
        Window __window;
        kat::ResourceManager __resources;
        StateMachine __stateMachine;
        GuiHandler __guiHandler;

        std::filesystem::path __assetsPath = "../assets";

        sf::Event ___event;
        sf::Clock __clock;

        sf::Font __font;

        static Context *__instance;

        Context();

        protected:
            static void _loadTextures(const std::filesystem::path &path);

        public:
            ~Context() = default;

            static Context &instance();

            static entt::registry &entt();
            static Window &window();
            static kat::ResourceManager &resources();
            static sf::Font &font();
            static GuiHandler &guiHandler();

            static std::filesystem::path &assetsPath();
            static void loadResources();

            template<typename T>
            static T &getResource(const std::string& name) {
                return resources().getResource<T>(name);
            }

            static StateMachine &stateMachine();

            template<typename T, typename... Args>
            static Context &registerState(const std::string &name, Args &&... args) {
                instance().__stateMachine.registerState<T>(name, std::forward<Args>(args)...);
                return instance();
            }

            static void load(const std::string &name);

            static void update();
            static void event();
            static void render();
    };
}
