/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Character
*/

#include "component/Character.hpp"
#include "item/Weapon.hpp"
#include "item/Accessory.hpp"

entt::entity emblem::createCharacter(const nlohmann::json &json) {
    auto &registry = emblem::Context::entt();
    auto &resources = emblem::Context::resources();
    auto entity = registry.create();

    std::string rawKey = json.at("texture");

    rawKey = rawKey.substr(0, rawKey.size() - (rawKey.size() - rawKey.find_last_of('.')));
    std::cout << "rawKey " << std::quoted(rawKey, '\'') << std::endl;

    registry.emplace<kat::Texture>(entity);
    auto &texture = registry.get<kat::Texture>(entity).load(
        resources.getResource<kat::Texture>(
            "texture:" + rawKey
        )
    );

    registry.emplace<kat::Sprite>(entity);
    auto &sprite = registry.get<kat::Sprite>(entity).create(texture);

    registry.emplace<kat::Animator>(entity, sprite);
    auto &animator = registry.get<kat::Animator>(entity);

    registry.emplace<emblem::Transform>(entity);
    auto &transform = registry.get<emblem::Transform>(entity);

    registry.emplace<emblem::Inventory>(entity);
    registry.emplace<emblem::Equipment>(entity);
    registry.emplace<emblem::Play>(entity);

    sprite.setOrigin(16, 16);
    sprite.setPosition(8 + transform.x * 16, 8 + transform.y * 16);

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

        if (entry.find("flipX") != entry.end()) {
            animator.getAnimation(entry.at("name")).flipX = entry.at("flipX");
        }

        if (entry.find("flipY") != entry.end()) {
            animator.getAnimation(entry.at("name")).flipY = entry.at("flipY");
        }
    }

    animator.playAnimation("idle");

    return entity;
}

emblem::Stats &emblem::getStats(entt::entity &entity) {
    auto &registry = emblem::Context::entt();

    return registry.get<emblem::Stats>(entity);
}

emblem::Transform &emblem::getTransform(entt::entity &entity) {
    auto &registry = emblem::Context::entt();

    return registry.get<emblem::Transform>(entity);
}

emblem::Inventory &emblem::getInventory(entt::entity &entity) {
    auto &registry = emblem::Context::entt();

    return registry.get<emblem::Inventory>(entity);
}

emblem::Equipment &emblem::getEquipment(entt::entity &entity) {
    auto &registry = emblem::Context::entt();

    return registry.get<emblem::Equipment>(entity);
}

void emblem::equipWeapon(entt::entity &entity, const size_t &index) {
    auto &registry = emblem::Context::entt();
    auto &inventory = getInventory(entity);
    auto &equipment = getEquipment(entity);

    if (index >= inventory.size())
        return;

    Stack &item = inventory.getItemStack(index);

    try {
        dynamic_cast<const emblem::Weapon &>(item.item());
        equipment.equipWeapon(item);
    } catch (std::bad_cast &e) {
        return;
    }
}

void emblem::equipAccessory(entt::entity &entity, const size_t &index) {
    auto &registry = emblem::Context::entt();
    auto &inventory = getInventory(entity);
    auto &equipment = getEquipment(entity);

    if (index >= inventory.size())
        return;

    Stack &item = inventory.getItemStack(index);

    try {
        dynamic_cast<const emblem::Accessory &>(item.item());
        equipment.equipAccessory(item);
    } catch (std::bad_cast &e) {
        return;
    }
}

emblem::CharacterFactory &emblem::CharacterFactory::instance() {
    if (!__instance)
        __instance = new emblem::CharacterFactory();
    return *__instance;
}

void emblem::CharacterFactory::loadCharacters(const std::string &dirPath) {
    auto dir = std::filesystem::directory_iterator(dirPath);

    for (auto entry : dir) {
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
    auto &transform = registry.get<emblem::Transform>(entity);
    auto &animator = registry.get<kat::Animator>(entity);

    if (index == (size_t)-1) {
        animator.play("idle");
        transform.x = path[0].x;
        transform.y = path[0].y;
        return false;
    }

    auto &next = path[index];

    Point direction = { transform.x - next.x, transform.y - next.y };

    float __lorp = 0.0f;

    time = std::clamp(time + dt * SPEED, 0.0f, 1.0f);

    std::cout << "time: " << time << std::endl;
    std::cout << "delta: " << dt << std::endl;
    std::cout << "transform: " << transform.x << ", " << transform.y << std::endl;
    std::cout << "next: " << next.x << ", " << next.y << std::endl;
    std::cout << "direction: " << direction.x << ", " << direction.y << std::endl;

    if (time >= 1.0f) {
        time = 0.0f;
        transform.x = next.x;
        transform.y = next.y;
        --index;
        return true;
    } else if (direction.x >= 1) {
        animator.play("walk_west");
        __lorp = std::lerp(transform.x * 16 + 8, next.x * 16 + 8, time);
        sprite.setPosition(__lorp, transform.y * 16 + 8);
    } else if (direction.y >= 1) {
        animator.play("walk_north");
        __lorp = std::lerp(transform.y * 16 + 8, next.y * 16 + 8, time);
        sprite.setPosition(transform.x * 16 + 8, __lorp);
    } else if (direction.x <= -1) {
        animator.play("walk_east");
        __lorp = std::lerp(transform.x * 16 + 8, next.x * 16 + 8, time);
        sprite.setPosition(__lorp, transform.y * 16 + 8);
    } else if (direction.y <= -1) {
        animator.play("walk_south");
        __lorp = std::lerp(transform.y * 16 + 8, next.y * 16 + 8, time);
        sprite.setPosition(transform.x * 16 + 8, __lorp);
    }
    //     sprite.move(0, cspeed);
    // } else if (abs(direction.x) < cspeed && direction.x != 0) {
    //     --index;
    //     // sprite.setPosition(next.x * 16 + 8, sprite.getPosition().y);
    // } else if (abs(direction.y) < cspeed && direction.y != 0) {
    //     --index;
    //     // sprite.setPosition(sprite.getPosition().x, next.y * 16 + 8);
    // }
    return true;
}
