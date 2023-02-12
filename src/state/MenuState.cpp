/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** MenuState
*/

#include "state/MenuState.hpp"

emblem::MenuState::MenuState(const std::filesystem::path &path)
{
    (void)path;
    std::cout << "##############################################################";
}

void emblem::MenuState::onLoad() {

}

void emblem::MenuState::onRelease() {
}

void emblem::MenuState::onUpdate(const float &dt) {
}
/*
void emblem::MenuState::onEvent(sf::Event &e) {
}*/

void emblem::MenuState::onRender(emblem::Window &window) {
}