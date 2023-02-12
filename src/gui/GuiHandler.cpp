/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** GuiHandler
*/

#include "gui/GuiHandler.hpp"

namespace emblem {

    void GuiHandler::__removeRemnant() {
        if (std::find(__openedGui.begin(), __openedGui.end(), __eventGrabs.top()) == __openedGui.end());
            __eventGrabs.pop();
    }

    void GuiHandler::update(const float &dt) {
        if (!__eventGrabs.empty())
            __removeRemnant();
        for (auto &gui : __openedGui) {
            gui->update(dt);
        }
    }

    void GuiHandler::event(sf::Event &event) {
        if (__eventGrabs.empty()) {
            for (auto &gui : __openedGui)
                gui->event(event);
        } else {
            __eventGrabs.top()->event(event);
        }
    }

    void GuiHandler::render(Window &window) {
        for (auto &gui : __openedGui)
            gui->render(window);
    }

    void GuiHandler::newGui(const std::string &name) {
        if (!__guiMap.contains(name))
            __guiMap.insert({name, std::make_shared<GUI>()});
        else
            throw std::runtime_error("GuiHandler: Gui with name " + name + " already exists");
    }

    GUI &GuiHandler::getGui(const std::string &name) {
        if (__guiMap.contains(name))
            return *__guiMap.at(name);
        else
            throw std::runtime_error("GuiHandler: Gui with name " + name + " doesn't exists");
    }

    // void GuiHandler::addGui(const std::string &name, GUIHandle &gui) {
    //     if (!__guiMap.contains(name))
    //         __guiMap.insert({name, gui});
    //     else
    //         throw std::runtime_error("GuiHandler: Gui with name " + name + " already exists");
    // }

    void GuiHandler::removeGui(const std::string &name) {
        if (__guiMap.contains(name))
            __guiMap.erase(name);
        else
            throw std::runtime_error("GuiHandler: Gui with name " + name + " doesn't exists");
    }

    void GuiHandler::open(const std::string &name, bool eventGrab) {
        if (__guiMap.contains(name)) {
            std::cout << __guiMap.at(name) << std::endl;
            __guiMap.at(name)->load();
            __openedGui.push_back(__guiMap.at(name));
            if (eventGrab)
                __eventGrabs.push(__guiMap.at(name));
        } else
            throw std::runtime_error("GuiHandler: Gui with name " + name + " doesn't exists");
    }

    void GuiHandler::close(const std::string &name) {
        if (__guiMap.contains(name)) {
            __guiMap.at(name)->unload();
            __openedGui.erase(std::remove(__openedGui.begin(), __openedGui.end(), __guiMap[name]), __openedGui.end());
        } else
            throw std::runtime_error("GuiHandler: Gui with name " + name + " doesn't exists");
    }

}
