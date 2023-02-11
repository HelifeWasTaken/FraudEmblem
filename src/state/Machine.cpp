/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Machine
*/

#include "state/Machine.hpp"
#include "Context.hpp"

void emblem::StateMachine::load(const std::string &name) {
    if (this->__states.find(name) == this->__states.end())
        throw std::runtime_error("State " + name + " not found");
    if (!__current) {
        __current = this->__states[name].get();
        __current->onLoad();
    } else {
        __pending.push(this->__states[name].get());
    }
}

void emblem::StateMachine::update(const float &dt) {
    if (__current)
        __current->onUpdate(dt);
}

void emblem::StateMachine::event(sf::Event &event) {
    if (__current) {
        __current->onEvent(event);
    }
}

void emblem::StateMachine::render() {
    if (__current) {
        __current->onRender(emblem::Context::window());
    }
    emblem::Context::window().render();
}

void emblem::StateMachine::ping() {
    if (__pending.empty())
        return;
    if (__current) {
        __current->onRelease();
    }
    __current = __pending.top();
    __pending.pop();
    __current->onLoad();
}
