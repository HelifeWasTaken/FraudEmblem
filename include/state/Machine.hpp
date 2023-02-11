/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Machine
*/

#pragma once

#include <memory>
#include <unordered_map>
#include <string>
#include <stack>

#include "AState.hpp"

namespace emblem {
    class StateMachine {
        public:
            using StatePtr = std::unique_ptr<AState>;

        private:
            std::unordered_map<std::string, StatePtr> __states;

            std::stack<AState *> __pending;
            AState *__current = nullptr;

        public:
            StateMachine() = default;
            ~StateMachine() = default;

            template<typename T, typename... Args>
            StateMachine &registerState(const std::string &name, Args &&... args) {
                __states.emplace(name, std::make_unique<T>(std::forward<Args>(args)...));
                __states.at(name)->_setMachine(this);
                return *this;
            }

            void load(const std::string &name);

            void update(const float &dt);
            void event(sf::Event &event);
            void render();

            void ping();

    };
}
