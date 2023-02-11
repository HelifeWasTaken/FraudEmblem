/*
** EPITECH PROJECT, 2023
** *
** File description:
** BattleState
*/

#include <iostream>

#include <nlohmann/json.hpp>

#include "state/BattleState.hpp"
#include "state/Machine.hpp"
#include "Context.hpp"

emblem::BattleState::BattleState(const std::filesystem::path &path) : AState(), __mapData(0, 0) {
    std::ifstream file(path);

    auto json = nlohmann::json::parse(file);

    __mapData = Map(json.at("size").at("width"), json.at("size").at("height"));

    std::string rawKey = json.at("texture");
    rawKey = rawKey.substr(0, rawKey.size() - (rawKey.size() - rawKey.find_last_of('.')));

    __map.create(emblem::Context::getResource<kat::Texture>("texture:" + rawKey));

    for (size_t x = 0; x < __mapData.getWidth(); x++) {
        for (size_t y = 0; y < __mapData.getHeight(); y++) {
            std::cout << x << "x" << y << std::endl;
            __mapData.getCell(x, y).setCellType(json.at("data")[y * __mapData.getWidth() + x]);
            std::cout << x << "x" << y << std::endl;
        }
    }

    file.close();
}

void emblem::BattleState::onLoad() {
    std::cout << "Loading Battle State" << std::endl;
    __entities.push_back(emblem::CharacterFactory::createCharacter("map_assasin"));

    __cursor.x = 7;
    __cursor.y = 5;

    __cursorCell.create(emblem::Context::getResource<kat::Texture>("texture:misc/cursor"));
    __cursorCell.setPosition(__cursor.x * 16, __cursor.y * 16);

    // __emptyCell.create(emblem::Context::getResource<kat::Texture>("texture:misc/cell"));

    // __wallCell.create(emblem::Context::getResource<kat::Texture>("texture:misc/wall"));

    emblem::Context::window().getView("default").setCenter(8 + __cursor.x * 16, __cursor.y * 16);
}

void emblem::BattleState::onRelease() {
    for (auto &entity : __entities) {
        emblem::Context::entt().destroy(entity);
    }
}

void emblem::BattleState::onUpdate(const float &dt) {
    auto view = emblem::Context::entt().view<kat::Animator>();

    for (auto [entity, anim] : view.each()) {
        anim.update(dt);
    }

    if (__machine)
        __machine->ping();
}

void emblem::BattleState::onEvent(sf::Event &e) {
    auto &win = emblem::Context::window();

    int64_t x = __cursor.x;
    int64_t y = __cursor.y;

    if (e.type == e.KeyPressed) {
        if (e.key.code == sf::Keyboard::Up) {
            if (__cursor.y > 0)
                __cursor.y--;
        }
        if (e.key.code == sf::Keyboard::Down) {
            if (__cursor.y < __mapData.getHeight() - 1)
                __cursor.y++;
        }
        if (e.key.code == sf::Keyboard::Left) {
            if (__cursor.x > 0)
                __cursor.x--;
        }
        if (e.key.code == sf::Keyboard::Right) {
            if (__cursor.x < __mapData.getWidth() - 1)
                __cursor.x++;
        }
        std::cout << __cursor.x << "x" << __cursor.y << std::endl;
        std::cout << __mapData.getWidth() << "x" << __mapData.getHeight() << std::endl;

        x = std::clamp<int64_t>(x, 7, __mapData.getWidth() - 8);
        y = std::clamp<int64_t>(y, 5, __mapData.getHeight() - 5);

        emblem::Context::window().getView("default").setCenter(8 + x * 16, y * 16);

        __cursorCell.setPosition(__cursor.x * 16, __cursor.y * 16);

        __path = __mapData.getAviablePaths(__cursor.x, __cursor.y, 3);
        std::cout << __path.size() << std::endl;
    }
}

void emblem::BattleState::onRender(emblem::Window &window) {
    window.draw(__map, "default", 0);

    auto view = emblem::Context::entt().view<kat::Sprite>();

    window.draw(__cursorCell, "default", 64);

    for (auto &[pos, type] : __path) {
        sf::RectangleShape *cell = new sf::RectangleShape(sf::Vector2f(14, 14));
        if (type == CellType::WALL) {
            cell->setFillColor(sf::Color(255, 0, 0, 128));
            cell->setPosition(1 + pos.x * 16, 1 + pos.y * 16);
            __wallCell.emplace_back(cell);
            window.draw(__wallCell.back(), "default", 64);
        } else {
            // std::cout << pos.x << "x" << pos.y << std::endl;
            cell->setFillColor(sf::Color(0, 0, 255, 128));
            cell->setPosition(1 + pos.x * 16, 1 + pos.y * 16);
            __emptyCell.emplace_back(cell);
            window.draw(__emptyCell.back(), "default", 64);
        }
    }

    for (auto [entity, sprite] : view.each()) {
        window.draw(sprite, "default", 128);
    }
}

