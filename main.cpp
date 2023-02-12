/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** main
*/

#include <iostream>


#include "Context.hpp"
#include "component/Character.hpp"
#include "resource.h"
#include "state/BattleState.hpp"
#include "state/MenuState.hpp"
// #include "Dialog.hpp"

int main(void) {
    emblem::Context::loadResources();

    // emblem::CharacterFactory::loadCharacters("../assets/characters/");
    // auto &registry = emblem::Context::entt();
    // auto &resources = emblem::Context::resources();
    // auto ent = emblem::CharacterFactory::createCharacter("map_assasin");
    // // auto &stat = registry.get<emblem::Stats>(ent);
    // auto &sprite = registry.get<kat::Sprite>(ent);
    // sprite.setOrigin(16, 16);
    // // sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    // auto &anim = registry.get<kat::Animator>(ent).playAnimation("idle");
    auto &win = emblem::Context::window();

    win.getView("default").setCenter(0, 0).setSize(240, 160);
    win.registerView("mainmenu", win.get_handle().get_handle().getDefaultView(), 3);

    emblem::Context::registerState<emblem::MenuState>("menu");
    emblem::Context::load("menu");

    emblem::Context::registerState<emblem::BattleState>("battle", "../assets/scene/battle_test.json");
    // emblem::Context::load("battle");

    while (win.isOpen()) {
        emblem::Context::update();
        emblem::Context::render();
    }
    return 0;
}
