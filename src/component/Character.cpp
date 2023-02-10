/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Character
*/

#include "Character.hpp"

entt::entity emblem::createCharacter(const std::string &filename, const nlohmann::json &json) {
    auto &registry = emblem::Context::entt();
    auto entity = registry.create();

    registry.emplace<kat::Texture>(entity);
    auto &texture = registry.get<kat::Texture>(entity).load(filename);

    registry.emplace<kat::Sprite>(entity, texture);
    auto &sprite = registry.get<kat::Sprite>(entity);

    registry.emplace<kat::Animator>(entity, sprite);
    auto &animator = registry.get<kat::Animator>(entity);

    for (size_t i = 0; i < json.size(); ++i) {
        animator.addAnimation(json.at(i).at("name"))
    }
}
