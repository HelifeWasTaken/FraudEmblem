/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Character
*/

#include "component/Character.hpp"

entt::entity emblem::createCharacter(const nlohmann::json &json) {
    auto &registry = emblem::Context::entt();
    auto entity = registry.create();

    std::string path = json.at("texture");
    path = "../assets/textures/" + path;

    registry.emplace<kat::Texture>(entity);
    auto &texture = registry.get<kat::Texture>(entity).load(path);

    registry.emplace<kat::Sprite>(entity);
    auto &sprite = registry.get<kat::Sprite>(entity).create(texture);

    registry.emplace<kat::Animator>(entity, sprite);
    auto &animator = registry.get<kat::Animator>(entity);

    nlohmann::json stats = json.at("stats");

    registry.emplace<emblem::Stats>(entity, stats);

    nlohmann::json anim = json.at("animations");

    for (auto entry : anim) {
        kat::FrameSize __size;
        kat::FrameIndexList __indexes;

        for (auto j : entry.at("frames")) {
            __indexes.push_back(j);
        }

        __size.x = entry.at("size").at("width");
        __size.y = entry.at("size").at("height");

        animator.addAnimationSpritesheet(
            entry.at("name"),
            __indexes,
            __size,
            entry.at("speed"),
            entry.at("loop")
        );
    }

    return entity;
}

emblem::CharacterFactory &emblem::CharacterFactory::instance() {
    if (!__instance)
        __instance = new emblem::CharacterFactory();
    return *__instance;
}

void emblem::CharacterFactory::loadCharacters(const std::string &dirPath) {
    auto dir = std::filesystem::directory_iterator(dirPath);

    for (auto entry : dir) {
        std::cout << entry.path().string() << std::endl;
        std::cout << entry.path().stem() << std::endl;
        std::ifstream file(entry.path().string());
        registerCharacter(entry.path().stem().string(), nlohmann::json::parse(file));
        file.close();
    }
}

void emblem::CharacterFactory::registerCharacter(const std::string &name, const nlohmann::json &json) {
    instance().__characters.insert({name, json});
}

entt::entity emblem::CharacterFactory::createCharacter(const std::string &name) {
    return emblem::createCharacter(instance().__characters.at(name));
}

bool updateCharacter(float dt) {
    auto &registry = emblem::Context::entt();
    bool moving = false;

    for (auto [e, path] : registry.view<emblem::PathManager>().each()) {
        moving |= path.update(e, dt);
    }
    for (auto [_, animator] : registry.view<kat::Animator>().each()) {
        animator.update(dt);
    }
    return moving;
}

emblem::CharacterFactory *emblem::CharacterFactory::__instance = nullptr;

bool emblem::PathManager::update(entt::entity &entity, float dt) {
    auto &registry = emblem::Context::entt();
    auto &sprite = registry.get<kat::Sprite>(entity);
    auto &animator = registry.get<kat::Animator>(entity);

    auto current = sprite.getPosition();
    auto &next = path[index];

    sf::Vector2f direction = { current.x - next.x, current.y - next.y };
    auto cspeed = SPEED * dt;

    if (index >= path.size()) {
        animator.play("idle");
        return false;
    }

    if (abs(direction.x) < cspeed) {
        direction.x = 0;
        sprite.setPosition(next.x, sprite.getPosition().y);
    } else if (abs(direction.y) < cspeed) {
        sprite.setPosition(sprite.getPosition().x, next.y);
    } else if (direction.x == 0 && direction.y == 0) {
        index++;
        return true;
    } else if (direction.x >= cspeed) {
        animator.play("walk_left");
        sprite.move(-cspeed, 0);
    } else if (direction.y >= cspeed) {
        animator.play("walk_up");
        sprite.move(0, -cspeed);
    } else if (direction.x <= -cspeed) {
        animator.play("walk_right");
        sprite.move(cspeed, 0);
    } else if (direction.y <= -cspeed) {
        animator.play("walk_down");
        sprite.move(0, cspeed);
    }
    return true;
}
