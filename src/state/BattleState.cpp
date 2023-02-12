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

#include "item/Weapon.hpp"
#include "item/Accessory.hpp"

#include "gui/GuiHandler.hpp"
#include "gui/widget/Menu.hpp"
#include "gui/widget/MenuItem.hpp"

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

    __cursorPos.x = 7;
    __cursorPos.y = 5;

    __cursorCell.create(emblem::Context::getResource<kat::Texture>("texture:misc/cursor"));
    __cursorCell.setPosition(8 + __cursorPos.x * 16, 8 + __cursorPos.y * 16);

    __cursorCell.setOrigin(12, 12);

    __cursorAnimator.reloadSprite(__cursorCell);
    __cursorAnimator.addAnimationSpritesheet("idle", std::vector<kat::FrameIndex>{0, 1, 2, 3}, kat::FrameSize(24, 24), 0.2f);

    __cursorAnimator.play("idle");

    createCharacter("assasin", Point(9, 8), emblem::EntityType::HERO);
    createCharacter("assasin", Point(8, 9), emblem::EntityType::HERO);

    emblem::Context::window().getView("default").setCenter(8 + __cursorPos.x * 16, __cursorPos.y * 16);

    auto &Gui = emblem::Context::guiHandler();

    auto menuItem = emblem::gui::MenuItem();
    menuItem.setText("1");
    auto menuItem2 = emblem::gui::MenuItem();
    menuItem2.setText("2");
    auto menuItem3 = emblem::gui::MenuItem();
    menuItem3.setText("3");
    auto menu = new emblem::gui::Menu();
    menu->addItem(menuItem);
    menu->addItem(menuItem2);
    menu->addItem(menuItem3);

    Gui.newGui("test");

    Gui.getGui("test").addWidget(menu);
}

void emblem::BattleState::onRelease() {
    for (auto &entity : __entities) {
        emblem::Context::entt().destroy(entity);
    }
}

void emblem::BattleState::onUpdate(const float &dt) {
    auto play = emblem::Context::entt().view<kat::Sprite, emblem::Play>();
    auto pos = emblem::Context::entt().view<kat::Sprite, emblem::Transform>();
    auto view = emblem::Context::entt().view<kat::Animator>();

    if (__pathManager) {
        if (!__pathManager->update(__selectedEntity, dt)) {
            delete __pathManager;
            __pathManager = nullptr;

            __mapData.getCell(__selectedStart.x, __selectedStart.y).setCellType(emblem::CellType::EMPTY);
            __mapData.getCell(__selectedEnd.x, __selectedEnd.y).setCellType(emblem::CellType::ENTITY);
            __mapData.getCell(__selectedEnd.x, __selectedEnd.y).setEntityType(__mapData.getCell(__selectedStart.x, __selectedStart.y).getEntityType());

            __area.clear();
            __cells.clear();

            __characters.insert(std::make_pair(__selectedEnd, __characters.at(__selectedStart)));
            __characters.erase(__selectedStart);

            __state = ATTACK;
            // __state = SELECT;
            __cursorPos = __selectedEnd;

            int64_t x = __cursorPos.x;
            int64_t y = __cursorPos.y;

            x = std::clamp<int64_t>(x, 7, __mapData.getWidth() - 8);
            y = std::clamp<int64_t>(y, 5, __mapData.getHeight() - 5);

            emblem::Context::window().getView("default").setCenter(8 + x * 16, y * 16);

            __cursorCell.setPosition(8 + __cursorPos.x * 16, 8 + __cursorPos.y * 16);

            // auto &play = emblem::Context::entt().get<emblem::Play>(__selectedEntity);
            // play.canPlay = false;

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

    for (auto [entity, sprite, play] : play.each()) {
        if (play.canPlay)
            sprite.setColor(sf::Color::White);
        else
            sprite.setColor(sf::Color(127, 127, 127));
    }

    __cursorAnimator.update(dt);

    for (auto &ptr : __cells) {
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
            if (__cursorPos.y > 0)
                --__cursorPos.y;
            if ((__state == MOVE || __state == ATTACK) && (__area.find(__cursorPos) == __area.end()))
                ++__cursorPos.y;
        }
        if (e.key.code == sf::Keyboard::Down) {
            if (__cursorPos.y < __mapData.getHeight() - 1)
                ++__cursorPos.y;
            if ((__state == MOVE || __state == ATTACK) && (__area.find(__cursorPos) == __area.end()))
                --__cursorPos.y;
        }
        if (e.key.code == sf::Keyboard::Left) {
            if (__cursorPos.x > 0)
                --__cursorPos.x;
            std::cout << __cursorPos.x << "x" << __cursorPos.y << std::endl;
            std::cout << __area.size() << std::endl;
            for (auto &[transform, _] : __area) {
                std::cout << transform.x << "x" << transform.y << std::endl;
            }
            if ((__state == MOVE || __state == ATTACK) && (__area.find(__cursorPos) == __area.end()))
                ++__cursorPos.x;
        }
        if (e.key.code == sf::Keyboard::Right) {
            if (__cursorPos.x < __mapData.getWidth() - 1)
                ++__cursorPos.x;
            if ((__state == MOVE || __state == ATTACK) && (__area.find(__cursorPos) == __area.end()))
                --__cursorPos.x;
        }

        if (e.key.code == sf::Keyboard::M) {
            Context::guiHandler().open("test");
        }

        if (e.key.code == sf::Keyboard::Enter) {
            if (__state == ATTACK) {
                if (__area.at(__cursorPos) == CellType::ENTITY) {
                    auto &victim = __characters.at(__cursorPos);
                    auto &victimStats = emblem::Context::entt().get<emblem::Stats>(victim);

                    auto &stats = emblem::Context::entt().get<emblem::Stats>(__selectedEntity);

                    victimStats.damage(std::clamp<size_t>(stats.atk - victimStats.def, 0, stats.atk));

                    std::cout << "damage: " << std::clamp<size_t>(stats.atk - victimStats.def, 0, stats.atk) << std::endl;
                    std::cout << victimStats << std::endl;

                    if (!victimStats.isAlive()) {
                        __characters.erase(__cursorPos);
                        __mapData.getCell(__cursorPos.x, __cursorPos.y).setCellType(emblem::CellType::EMPTY);
                        emblem::Context::entt().destroy(victim);
                    }
                }
            } else if (__state == MOVE) {
                if (__mapData.isEmpty(__cursorPos.x, __cursorPos.y)) {
                    auto &stats = emblem::Context::entt().get<emblem::Stats>(__selectedEntity);

                    __selectedEnd = __cursorPos;
                    auto shortPath = __mapData.excludeWall(false).findShortestPathTo(__selectedStart.x, __selectedStart.y, __selectedEnd.x, __selectedEnd.y, stats.mov);

                    __area = emblem::pathToArea(shortPath);

                    __cells.clear();

                    __generateMoveArea();
                    if (__pathManager)
                        delete __pathManager;
                    __pathManager = new emblem::PathManager(shortPath);
                }
            } else {
                if (__mapData.getCell(__cursorPos.x, __cursorPos.y).getCellType() == CellType::ENTITY && __mapData.getCell(__cursorPos.x, __cursorPos.y).getEntityType() != EntityType::HERO) {
                    auto &entity = __characters.at(__cursorPos);

                    __selectedEntity = entity;

                    auto &stats = emblem::Context::entt().get<emblem::Stats>(__selectedEntity);
                    auto &play = emblem::Context::entt().get<emblem::Play>(__selectedEntity);

                    if (play.canPlay) {
                        __mapData.setIgnore(__mapData.getCell(__cursorPos.x, __cursorPos.y));
                        __area = __mapData.excludeWall(false).getAvailablePaths(__cursorPos.x, __cursorPos.y, stats.mov);

                        __state = MOVE;

                        __selectedStart = __cursorPos;

                        __cells.clear();

                        __generateMoveArea();
                    }
                }
            }
        }

        if (e.key.code == sf::Keyboard::Escape) {
            if (__state == MOVE) {
                __area.clear();
                __state = SELECT;
            }
        }

        int64_t x = __cursorPos.x;
        int64_t y = __cursorPos.y;

        x = std::clamp<int64_t>(x, 7, __mapData.getWidth() - 8);
        y = std::clamp<int64_t>(y, 5, __mapData.getHeight() - 5);

        emblem::Context::window().getView("default").setCenter(8 + x * 16, y * 16);

        __cursorCell.setPosition(8 + __cursorPos.x * 16, 8 + __cursorPos.y * 16);
    }
}

void emblem::BattleState::onRender(emblem::Window &window) {
    window.draw(__map, "default", 0);

    auto view = emblem::Context::entt().view<kat::Sprite>();

    for (auto &ptr : __cells) {
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

void emblem::BattleState::__generateMoveArea() {
    if (!__cells.empty())
        return;
    for (auto &[pos, type] : __area) {
        sf::RectangleShape *cell = new sf::RectangleShape(sf::Vector2f(15, 15));
        cell->setTexture(emblem::Context::getResource<kat::Texture>("texture:misc/shading").raw_handle());
        if (type == CellType::WALL) {
            cell->setFillColor(sf::Color(255, 0, 0, 128));
        } else if (type == CellType::IGNORE) {
            cell->setFillColor(sf::Color(0, 0, 128, 128));
        } else {
            cell->setFillColor(sf::Color(0, 0, 255, 128));
        }
        cell->setPosition(pos.x * 16, pos.y * 16);
        __cells.emplace_back(cell);
    }
}

void emblem::BattleState::__generateAttackArea() {
    auto &transform = emblem::Context::entt().get<emblem::Transform>(__selectedEntity);
    auto &stats = emblem::Context::entt().get<emblem::Stats>(__selectedEntity);
    auto &equipment = emblem::Context::entt().get<emblem::Equipment>(__selectedEntity);

    if (equipment.weapon().isNull())
        __area = __mapData.excludeWall(true).getAvailablePaths(transform.x, transform.y, 1);
    else
        __area = __mapData.excludeWall(true).getAvailablePaths(transform.x, transform.y, equipment.weapon().item<Weapon>().range());
    __area.insert(std::make_pair<Point, CellType>({transform.x, transform.y}, emblem::CellType::IGNORE));

    for (auto &[transform, type] : __area) {
        sf::RectangleShape *cell = new sf::RectangleShape(sf::Vector2f(15, 15));
        cell->setTexture(emblem::Context::getResource<kat::Texture>("texture:misc/shading").raw_handle());
        if (type == IGNORE) {
            cell->setFillColor(sf::Color(127, 0, 127, 128));
        } else {
            cell->setFillColor(sf::Color(255, 0, 127, 128));
        }
        cell->setPosition(transform.x * 16, transform.y * 16);
        __cells.emplace_back(cell);
    }

    __area.at({transform.x, transform.y}) = CellType::EMPTY;

}
