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

emblem::BattleState::BattleState(const std::filesystem::path &path) : AState(),
__mapData(0, 0),
__cursorAnimator(__cursorCell) {
    std::ifstream file(path);

    auto json = nlohmann::json::parse(file);

    __mapData = Map(json.at("size").at("width"), json.at("size").at("height"));

    std::string rawKey = json.at("texture");
    rawKey = rawKey.substr(0, rawKey.size() - (rawKey.size() - rawKey.find_last_of('.')));

    __map.create(emblem::Context::getResource<kat::Texture>("texture:" + rawKey));

    for (size_t x = 0; x < __mapData.getWidth(); x++) {
        for (size_t y = 0; y < __mapData.getHeight(); y++) {
            __mapData.getCell(x, y).setCellType(json.at("data")[y * __mapData.getWidth() + x]);
        }
    }

    for (auto &entry : json.at("enemies")) {
        auto &pos = entry.at("position");
        createCharacter(entry.at("name"), Point(pos.at("x"), pos.at("y")), emblem::EntityType::VILLAIN);
    }

    file.close();
}

void emblem::BattleState::onLoad() {
    std::cout << "Loading Battle State" << std::endl;

    __cursor.x = 7;
    __cursor.y = 5;

    __cursorCell.create(emblem::Context::getResource<kat::Texture>("texture:misc/cursor"));
    __cursorCell.setPosition(8 + __cursor.x * 16, 8 + __cursor.y * 16);

    __cursorCell.setOrigin(12, 12);

    __cursorAnimator.reloadSprite(__cursorCell);
    __cursorAnimator.addAnimationSpritesheet("idle", std::vector<kat::FrameIndex>{0, 1, 2, 3}, kat::FrameSize(24, 24), 0.2f);

    __cursorAnimator.play("idle");

    createCharacter("assasin", Point(9, 8), emblem::EntityType::HERO);
    createCharacter("assasin", Point(8, 9), emblem::EntityType::HERO);

    // trans.x = 11;
    // trans.y = 9;

    // __mapData.getCell(11, 9).setCellType(emblem::CellType::ENTITY);
    // __mapData.getCell(11, 9).setEntityType(emblem::EntityType::HERO);

    emblem::Context::window().getView("default").setCenter(8 + __cursor.x * 16, __cursor.y * 16);
}

void emblem::BattleState::onRelease() {
    for (auto &entity : __entities) {
        emblem::Context::entt().destroy(entity);
    }
}

void emblem::BattleState::onUpdate(const float &dt) {
    auto pos = emblem::Context::entt().view<kat::Sprite, emblem::Transform>();
    auto view = emblem::Context::entt().view<kat::Animator>();

    if (__pathManager) {
        if (!__pathManager->update(__selectedEntity, dt)) {
            delete __pathManager;
            __pathManager = nullptr;
            __mapData.getCell(__selectedStart.x, __selectedStart.y).setCellType(emblem::CellType::EMPTY);
            __mapData.getCell(__selectedEnd.x, __selectedEnd.y).setCellType(emblem::CellType::ENTITY);
            __mapData.getCell(__selectedEnd.x, __selectedEnd.y).setEntityType(__mapData.getCell(__selectedStart.x, __selectedStart.y).getEntityType());
            __path.clear();
            __wallCell.clear();
            __emptyCell.clear();
            __characters.insert(std::make_pair(__selectedEnd, __characters.at(__selectedStart)));
            __characters.erase(__selectedStart);

            __action = true;
            __cursor = __selectedEnd;

            int64_t x = __cursor.x;
            int64_t y = __cursor.y;

            x = std::clamp<int64_t>(x, 7, __mapData.getWidth() - 8);
            y = std::clamp<int64_t>(y, 5, __mapData.getHeight() - 5);

            emblem::Context::window().getView("default").setCenter(8 + x * 16, y * 16);

            __cursorCell.setPosition(8 + __cursor.x * 16, 8 + __cursor.y * 16);

            __generateAttackArea();
        }
    } else {
        for (auto [entity, sprite, transform] : pos.each()) {
            sprite.setPosition(8 + transform.x * 16, 8 + transform.y * 16);
        }
    }

    for (auto [entity, anim] : view.each()) {
        anim.update(dt);
    }

    __cursorAnimator.update(dt);

    for (auto &ptr : __wallCell) {
        dynamic_cast<sf::RectangleShape*>(ptr.get())->setTextureRect(sf::IntRect(__shading, __shading, 15, 15));
    }

    for (auto &ptr : __emptyCell) {
        dynamic_cast<sf::RectangleShape*>(ptr.get())->setTextureRect(sf::IntRect(__shading, __shading, 15, 15));
    }

    __elapsed += dt;
    if (__elapsed > 0.05f) {
        __elapsed = 0;
        if (++__shading > 105)
            __shading = 0;
    }

    if (__machine)
        __machine->ping();
}

void emblem::BattleState::onEvent(sf::Event &e) {
    auto &win = emblem::Context::window();

    if (e.type == e.KeyPressed) {
        if (e.key.code == sf::Keyboard::Up) {
            if (__cursor.y > 0)
                --__cursor.y;
            if (__selected && !__path.contains(std::make_pair(__cursor, CellType::EMPTY)))
                ++__cursor.y;
        }
        if (e.key.code == sf::Keyboard::Down) {
            if (__cursor.y < __mapData.getHeight() - 1)
                ++__cursor.y;
            if (__selected && !__path.contains(std::make_pair(__cursor, CellType::EMPTY)))
                --__cursor.y;
        }
        if (e.key.code == sf::Keyboard::Left) {
            if (__cursor.x > 0)
                --__cursor.x;
            if (__selected && !__path.contains(std::make_pair(__cursor, CellType::EMPTY)))
                ++__cursor.x;
        }
        if (e.key.code == sf::Keyboard::Right) {
            if (__cursor.x < __mapData.getWidth() - 1)
                ++__cursor.x;
            if (__selected && !__path.contains(std::make_pair(__cursor, CellType::EMPTY)))
                --__cursor.x;
        }

        if (e.key.code == sf::Keyboard::Enter) {
            if (__action) {
                if (__path.contains(std::make_pair(__cursor, CellType::ENTITY))) {
                    auto &victim = __characters.at(__cursor);
                    auto &victimStats = emblem::Context::entt().get<emblem::Stats>(victim);

                    auto &stats = emblem::Context::entt().get<emblem::Stats>(__selectedEntity);

                    victimStats.damage(std::clamp<size_t>(stats.atk - victimStats.def, 0, stats.atk));

                    std::cout << "damage: " << std::clamp<size_t>(stats.atk - victimStats.def, 0, stats.atk) << std::endl;
                    std::cout << victimStats << std::endl;

                    if (!victimStats.isAlive()) {
                        __characters.erase(__cursor);
                        __mapData.getCell(__cursor.x, __cursor.y).setCellType(emblem::CellType::EMPTY);
                        emblem::Context::entt().destroy(victim);
                    }
                }
            } else if (__selected) {
                auto &stats = emblem::Context::entt().get<emblem::Stats>(__selectedEntity);

                __selectedEnd = __cursor;
                auto shortPath = __mapData.findShortestPathTo(__selectedStart.x, __selectedStart.y, __selectedEnd.x, __selectedEnd.y, stats.mov);

                __path = emblem::pathToArea(shortPath);

                __wallCell.clear();
                __emptyCell.clear();

                __generateArea();
                if (__pathManager)
                    delete __pathManager;
                __pathManager = new emblem::PathManager(shortPath);
                __selected = false;
            } else {
                if (__mapData.getCell(__cursor.x, __cursor.y).getCellType() == CellType::ENTITY && __mapData.getCell(__cursor.x, __cursor.y).getEntityType() != EntityType::HERO) {
                    auto &entity = __characters.at(__cursor);

                    __selectedEntity = entity;

                    auto &stats = emblem::Context::entt().get<emblem::Stats>(__selectedEntity);

                    __path = __mapData.getAviablePaths(__cursor.x, __cursor.y, stats.mov);

                    __selected = true;

                    __selectedStart = __cursor;

                    __wallCell.clear();
                    __emptyCell.clear();

                    __generateArea();
                }
            }
        }

        if (e.key.code == sf::Keyboard::Escape) {
            __path.clear();
            __selected = false;
        }

        int64_t x = __cursor.x;
        int64_t y = __cursor.y;

        x = std::clamp<int64_t>(x, 7, __mapData.getWidth() - 8);
        y = std::clamp<int64_t>(y, 5, __mapData.getHeight() - 5);

        emblem::Context::window().getView("default").setCenter(8 + x * 16, y * 16);

        __cursorCell.setPosition(8 + __cursor.x * 16, 8 + __cursor.y * 16);
    }
}

void emblem::BattleState::onRender(emblem::Window &window) {
    window.draw(__map, "default", 0);

    auto view = emblem::Context::entt().view<kat::Sprite>();

    for (auto &ptr : __wallCell) {
        window.draw(ptr, "default", 64);
    }

    for (auto &ptr : __emptyCell) {
        window.draw(ptr, "default", 64);
    }

    window.draw(__cursorCell, "default", 92);

    for (auto [entity, sprite] : view.each()) {
        window.draw(sprite, "default", 128);
    }
}

void emblem::BattleState::createCharacter(const std::string &name, const Point &pos, const emblem::EntityType &type) {
    if (__mapData.getCell(pos.x, pos.y).getCellType() != CellType::EMPTY)
        return;

    auto &registry = emblem::Context::entt();

    auto newbie = emblem::CharacterFactory::createCharacter(name);

    auto &sprite = registry.get<kat::Sprite>(newbie);
    sprite.setPosition(8 + pos.x * 16, 8 + pos.y * 16);

    auto &anim = registry.get<kat::Animator>(newbie);
    anim.play("idle");

    auto &transform = registry.get<emblem::Transform>(newbie);
    transform.x = pos.x;
    transform.y = pos.y;

    __mapData.setEntity(pos.x, pos.y, type);

    __characters.insert(std::make_pair(pos, newbie));

    __entities.push_back(newbie);
}

void emblem::BattleState::__generateArea() {
    if (!__wallCell.empty() && !__emptyCell.empty())
        return;
    for (auto &[pos, type] : __path) {
        sf::RectangleShape *cell = new sf::RectangleShape(sf::Vector2f(15, 15));
        cell->setTexture(emblem::Context::getResource<kat::Texture>("texture:misc/shading").raw_handle());
        if (type == CellType::WALL) {
            cell->setFillColor(sf::Color(255, 0, 0, 128));
            cell->setPosition(pos.x * 16, pos.y * 16);
            __wallCell.emplace_back(cell);
        } else {
            cell->setFillColor(sf::Color(0, 0, 255, 128));
            cell->setPosition(pos.x * 16, pos.y * 16);
            __emptyCell.emplace_back(cell);
        }
    }
}

void emblem::BattleState::__generateAttackArea() {
    auto &transform = emblem::Context::entt().get<emblem::Transform>(__selectedEntity);
    auto &stats = emblem::Context::entt().get<emblem::Stats>(__selectedEntity);

    if (__mapData.getCell(transform.x + 1, transform.y).getCellType() == CellType::EMPTY ||
        (__mapData.getCell(transform.x + 1, transform.y).getCellType() == CellType::ENTITY &&
         __mapData.getCell(transform.x + 1, transform.y).getEntityType() == EntityType::HERO))
        __path.insert(std::make_pair<emblem::Point, emblem::CellType>({transform.x + 1, transform.y}, __mapData.getCell(transform.x + 1, transform.y).getCellType()));
    if (__mapData.getCell(transform.x - 1, transform.y).getCellType() == CellType::EMPTY ||
        (__mapData.getCell(transform.x - 1, transform.y).getCellType() == CellType::ENTITY &&
         __mapData.getCell(transform.x - 1, transform.y).getEntityType() == EntityType::HERO))
        __path.insert(std::make_pair<emblem::Point, emblem::CellType>({transform.x - 1, transform.y}, __mapData.getCell(transform.x - 1, transform.y).getCellType()));
    if (__mapData.getCell(transform.x, transform.y + 1).getCellType() == CellType::EMPTY ||
        (__mapData.getCell(transform.x, transform.y + 1).getCellType() == CellType::ENTITY &&
         __mapData.getCell(transform.x, transform.y + 1).getEntityType() == EntityType::HERO))
        __path.insert(std::make_pair<emblem::Point, emblem::CellType>({transform.x, transform.y + 1}, __mapData.getCell(transform.x, transform.y + 1).getCellType()));
    if (__mapData.getCell(transform.x, transform.y - 1).getCellType() == CellType::EMPTY ||
        (__mapData.getCell(transform.x, transform.y - 1).getCellType() == CellType::ENTITY &&
         __mapData.getCell(transform.x, transform.y - 1).getEntityType() == EntityType::HERO))
        __path.insert(std::make_pair<emblem::Point, emblem::CellType>({transform.x, transform.y - 1}, __mapData.getCell(transform.x, transform.y - 1).getCellType()));

    for (auto &[transform, type] : __path) {
        sf::RectangleShape *cell = new sf::RectangleShape(sf::Vector2f(15, 15));
        cell->setTexture(emblem::Context::getResource<kat::Texture>("texture:misc/shading").raw_handle());
        cell->setFillColor(sf::Color(255, 0, 127, 128));
        cell->setPosition(transform.x * 16, transform.y * 16);
        __emptyCell.emplace_back(cell);
    }

}
