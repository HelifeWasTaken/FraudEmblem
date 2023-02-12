/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** GuiHandler
*/

#pragma once

#include <vector>
#include <stack>

#include "gui/GUI.hpp"

namespace emblem {
    class GuiHandler {
        using GUIHandle = std::shared_ptr<GUI>;

        std::unordered_map<std::string, GUIHandle> __guiMap;
        std::vector<GUIHandle> __openedGui;
        std::stack<GUIHandle> __eventGrabs;

        void __removeRemnant();

        public:
            GuiHandler() = default;
            ~GuiHandler() = default;

            void update(const float &dt);
            void event(sf::Event &event);
            void render(Window &window);

            void newGui(const std::string &name);
            GUI &getGui(const std::string &name);
            // void addGui(const std::string &name, GUIHandle &gui);
            void removeGui(const std::string &name);

            void open(const std::string &name, bool eventGrab = false);
            void close(const std::string &name);

            bool isOpened(const std::string &name) const {
                return std::find(__openedGui.begin(), __openedGui.end(), __guiMap.at(name)) != __openedGui.end();
            }

            bool doGrabEvent() const { return !__eventGrabs.empty(); }

    };
}
