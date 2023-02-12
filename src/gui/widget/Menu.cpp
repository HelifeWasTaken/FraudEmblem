/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Menu
*/

#include "gui/widget/Menu.hpp"
#include "Context.hpp"

namespace emblem::gui {

    Menu::Menu() {
        __backgroundDrawable.second = Context::getResource<kat::Texture>("texture:gui/menu_back").raw_handle();
        __frameDrawable.second = Context::getResource<kat::Texture>("texture:gui/menu_frame").raw_handle();

        __selector.create(Context::getResource<kat::Texture>("texture:gui/menu_selector"));
    }

    void Menu::onLoad() {
        __index = 0;

        for (auto &item : this->__items) {
            item.onLoad();
        }
        setPosition({0, 0});
        setColor(sf::Color::Red);
        __generateBackground();
        __generateFrame();
    }

    void Menu::onUnload() {
        for (auto &item : this->__items) {
            item.onUnload();
        }
    }


    void Menu::onUpdate(const float &dt) {

    }

    void Menu::onEvent(sf::Event &e) {
        if (e.type == sf::Event::KeyPressed) {
            if (e.key.code == sf::Keyboard::Up) {
                if (__index > 0) {
                    --__index;
                }
            } else if (e.key.code == sf::Keyboard::Down) {
                if (__index < this->__items.size() - 1) {
                    ++__index;
                }
            } else if (e.key.code == sf::Keyboard::Return) {
                __items.at(__index).onPress();
            }
        }
    }

    void Menu::onRender(emblem::Window &window) {
        for (auto &item : this->__items) {
            item.onRender(window);
        }
        __backgroundDrawable.first = __background;
        __frameDrawable.first = __frame;

        window.draw(__backgroundDrawable, "gui", 1024);
        window.draw(__frameDrawable, "gui", 1025);
    }

    void Menu::addItem(const MenuItem &item) {
        this->__items.push_back(item);

        auto pos = getPosition();
        this->__items.back().setPosition({ pos.x + 64, 12 + pos.y + 64 + (__items.size() - 1) * 64 });

        __generateBackground();
        __generateFrame();
    }

    void Menu::__generateBackground() {
        __background->clear();
        sf::Vertex __vertex;
        __vertex.color = getColor();
        std::cout << __vertex.color.r << " " << __vertex.color.g << " " << __vertex.color.b << " " << __vertex.color.a << std::endl;
        for (size_t i = 0; i < 5; ++i) {
            for (size_t j = 0; j < __items.size() + 2; ++j) {
                for (int x = 0; x < 4; ++x) {
                    __vertex.position = getPosition();
                    __vertex.texCoords = sf::Vector2f(((i > 0) + (i == 4)) * 16, ((j > 0) + (j == (__items.size() + 1))) * 16);
                    //----
                    __vertex.position.x += (i + (x > 0 && x < 3)) * 16;
                    __vertex.position.y += (j + (x > 1)) * 16;
                    //----
                    __vertex.texCoords.x += (x > 0 && x < 3) * 16;
                    __vertex.texCoords.y += (x > 1) * 16;
                    //----
                    __background->push_back(__vertex);
                }
            }
        }
    }

    void Menu::__generateFrame() {
        __frame->clear();
        sf::Vertex __vertex;
        __vertex.color = sf::Color::White;
        for (size_t i = 0; i < 5; ++i) {
            for (size_t j = 0; j < __items.size() + 2; ++j) {
                for (int x = 0; x < 4; ++x) {
                    __vertex.position = getPosition();
                    __vertex.texCoords = sf::Vector2f(((i > 0) + (i == 4)) * 16, ((j > 0) + (j == (__items.size() + 1))) * 16);
                    //----
                    __vertex.position.x += (i + (x > 0 && x < 3)) * 16;
                    __vertex.position.y += (j + (x > 1)) * 16;
                    //----
                    __vertex.texCoords.x += (x > 0 && x < 3) * 16;
                    __vertex.texCoords.y += (x > 1) * 16;
                    //----
                    __frame->push_back(__vertex);
                }
            }
        }
    }

}
