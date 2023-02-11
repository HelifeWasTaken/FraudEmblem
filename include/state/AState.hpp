/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** IState
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>

// #include "Context.hpp"
#include "Window.hpp"

namespace emblem {
    class StateMachine;

    class AState {
        protected:
            StateMachine *__machine;

            std::vector<entt::entity> __entities;

            void _setMachine(StateMachine *machine) { __machine = machine; }

        public:
            friend class StateMachine;

            AState() = default;
            virtual ~AState() = default;

            virtual void onLoad() = 0;
            virtual void onRelease() = 0;
            virtual void onUpdate(const float &dt) = 0;
            virtual void onEvent(sf::Event &e) {}
            virtual void onRender(Window &window) {}

    };
}
