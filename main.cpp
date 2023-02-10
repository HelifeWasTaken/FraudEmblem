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

int main(void) {
    emblem::CharacterFactory::loadCharacters("../assets/characters/");
    auto &registry = emblem::Context::entt();
    auto ent = emblem::CharacterFactory::createCharacter("test");
    auto &stat = registry.get<emblem::Stats>(ent);
    auto &sprite = registry.get<kat::Sprite>(ent);
    registry.get<kat::Animator>(ent).playAnimation("IDLE");
    auto &win = emblem::Context::window();

    kat::ResourceManager manager;

    manager.addResource("yes", kat::Texture().load("../assets/textures/map/snow_mountains.png"));

    kat::Sprite s;
    s.create(manager.getResource<kat::Texture>("yes"));
    s.scale(2);

    std::cout << stat << std::endl;

    sf::Event e;
    sf::Clock c;

    while (win.isOpen()) {
        auto view = registry.view<kat::Animator>();

        for (auto &&[entity, anim] : view.each()) {
            anim.update(c.getElapsedTime().asSeconds());
        }
        c.restart();

        win.clear();
        while (win.poll(e)) {
            if (e.type == sf::Event::Closed)
                win.close();
        }
        win.draw(s);
        win.draw(sprite);
        win.display();
    }

    return 0;
}
