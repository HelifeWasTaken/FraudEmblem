/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Menu
*/

#pragma once

#include <vector>

#include "gui/widget/Movable.hpp"
#include "gui/widget/Resizable.hpp"
#include "gui/widget/Colorable.hpp"

#include "gui/widget/MenuItem.hpp"

#include "components/sprite.h"

namespace emblem::gui {

    class Menu : public Movable, public Resizable, public Colorable {
        std::vector<MenuItem> __items;

        kat::low_vertex_t __background = std::make_shared<std::vector<sf::Vertex>>();
        kat::low_vertex_t __frame = std::make_shared<std::vector<sf::Vertex>>();

        kat::low_drawable_t __backgroundDrawable;
        kat::low_drawable_t __frameDrawable;
        kat::Sprite __selector;

        size_t __index = 0;

        void __generateBackground();
        void __generateFrame();

        public:
            Menu();
            virtual ~Menu() override = default;

            virtual void onLoad() override;
            virtual void onUnload() override;
            virtual void onUpdate(const float &dt) override;
            virtual void onEvent(sf::Event &e) override;
            virtual void onRender(emblem::Window &window) override;

            void addItem(const MenuItem &item);

    };
}
