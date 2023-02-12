/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** GUI
*/

#pragma once

#include <unordered_map>
#include <vector>

#include "gui/widget/Widget.hpp"

namespace emblem {

    class GUI {
        struct Layer {
            bool visible = true;
            std::vector<std::unique_ptr<gui::Widget>> widgets;
        };

        std::unordered_map<int64_t, Layer> __layers;

        public:
            GUI() = default;
            ~GUI() = default;

            void load();
            void unload();
            void update(const float &dt);
            void event(sf::Event &e);
            void render(emblem::Window &window);

            template<typename T>
            requires std::is_base_of_v<gui::Widget, T>
            void newWidget(int64_t layer = 0) {
                if (!__layers.contains(layer))
                    __layers[layer] = Layer();
                __layers.at(layer).widgets.emplace_back(std::make_unique<T>());
            }

            void addWidget(gui::Widget *widget, int64_t layer = 0);
            // void removeWidget(gui::Widget &widget, int64_t layer = 0);
            void clearLayer(int64_t layer = 0);
    };
}