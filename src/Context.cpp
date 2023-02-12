/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Context
*/

#include <iostream>

#include "Context.hpp"

// DO NOT TOUCH THIS >:c
emblem::Context::Context() : __window({940, 640}, "Fraud Emblem", kat::WindowStyle::Close) {}

emblem::Context &emblem::Context::instance() {
    if (!__instance)
        __instance = new emblem::Context();
    return *__instance;
}

entt::registry &emblem::Context::entt() {
    return instance().__registry;
}

emblem::Window &emblem::Context::window() {
    return instance().__window;
}

kat::ResourceManager &emblem::Context::resources() {
    return instance().__resources;
}

std::filesystem::path &emblem::Context::assetsPath() {
    return instance().__assetsPath;
}

void emblem::Context::loadResources() {
    auto &resources = emblem::Context::resources();
    auto &assetsPath = emblem::Context::assetsPath();

    _loadTextures(assetsPath / "textures");

    emblem::CharacterFactory::loadCharacters(assetsPath / "characters");
}

emblem::MenuState &emblem::Context::menuState() {
    return instance().__menuState;
}

emblem::StateMachine &emblem::Context::stateMachine() {
    return instance().__stateMachine;
}

void emblem::Context::load(const std::string &name) {
    auto &stateMachine = emblem::Context::stateMachine();
    stateMachine.load(name);
}

void emblem::Context::update() {
    auto &stateMachine = emblem::Context::stateMachine();

    if (window().isOpen()) {
        while (window().poll(instance().___event))
            event();
        instance().___event.type = sf::Event::Count;
        stateMachine.update(instance().__clock.getElapsedTime().asSeconds());
        instance().__clock.restart();
        emblem::Context::stateMachine().ping();
    }
}

void emblem::Context::event() {
    auto &stateMachine = emblem::Context::stateMachine();
    if (instance().___event.type == sf::Event::Closed)
        window().close();
    else
        stateMachine.event(instance().___event);

}

void emblem::Context::render() {
    auto &stateMachine = emblem::Context::stateMachine();
    stateMachine.render();
}

void emblem::Context::_loadTextures(const std::filesystem::path &path) {
    auto &resources = emblem::Context::resources();
    std::string __key;

    // Load textures
    auto dir = std::filesystem::directory_iterator(path);

    for (auto entry : dir) {
        if (std::filesystem::is_directory(entry.path())) {
            _loadTextures(entry.path());
        } else {
            std::cout << "Loading Texture " << entry.path().string();
            __key = entry.path().string();
            __key = __key.substr((assetsPath() / "textures").string().size() + 1);
            __key = __key.substr(0, __key.size() - (__key.size() - __key.find_last_of('.')));
            std::cout << " as " << std::quoted(__key, '\'') << std::endl;
            resources.addResource("texture:" + __key, kat::Texture().load(entry.path().string()));
        }
    }
}

emblem::Context *emblem::Context::__instance = nullptr;
