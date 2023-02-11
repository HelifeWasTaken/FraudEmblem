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
#include "Dialog.hpp"

int main(void) {
    
    auto &win = emblem::Context::window();
    sf::Event e;
    sf::Clock c;

    kat::InputManager::instance();

    kat::ResourceManager res;
    
    sf::Font font;
    font.loadFromFile("../assets/OldLondon.ttf");
    kat::SoundManager::addSound("dialog", "../assets/dialog.wav");
    res.addResource("dialog_faces", kat::Texture().load("../assets/dialog_faces.png"));
    res.addResource("dialog_box", kat::Texture().load("../assets/dialog_box.png"));
    res.addResource("dialog_font", font);


    win.setFps(60);

    Dialog d(res);
   
    d.addEvent(Dialog::showUI())
        .addEvent(Dialog::music("../assets/tchoupi.ogg"))
        .addEvent(Dialog::setCharacter(0))
        .addEvent(Dialog::talk("Hi traveler!"))
        .addEvent(Dialog::talk("Fuck!"))
        .addEvent(Dialog::setCharacter(12))
        .addEvent(Dialog::talk("Hi traveler!"));

    while (win.isOpen()) {
        win.clear();
        while (win.poll(e)) {
            if (e.type == sf::Event::Closed)
                win.close();
            kat::InputManager::instance().updateEvent(e);
        }
        d.update(c.getElapsedTime().asSeconds());
        d.draw(win);
        win.display();
        c.restart();
        kat::InputManager::nextFrame();
    }
    
    return 0;
}
