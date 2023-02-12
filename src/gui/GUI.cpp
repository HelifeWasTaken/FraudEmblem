/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** GUI
*/

#include "gui/GUI.hpp"
#include "Context.hpp"

namespace emblem {

    void GUI::load() {
        for (auto &[_, layer] : __layers) {
            for (auto &widget : layer.widgets) {
                widget->onLoad();
            }
        }
    }

    void GUI::unload() {
        for (auto &[_, layer] : __layers) {
            for (auto &widget : layer.widgets)
                widget->onUnload();
        }
    }

    void GUI::update(const float &dt) {
        for (auto &[_, layer] : __layers) {
            for (auto &widget : layer.widgets)
                widget->onUpdate(dt);
        }
    }

    void GUI::event(sf::Event &e) {
        for (auto &[_, layer] : __layers) {
            for (auto &widget : layer.widgets)
                widget->onEvent(e);
        }
    }

    void GUI::render(emblem::Window &window) {
        for (auto &[_, layer] : __layers) {
            for (auto &widget : layer.widgets)
                widget->onRender(window);
        }
    }

    void GUI::addWidget(gui::Widget *widget, int64_t layer) {
        if (!__layers.contains(layer))
            __layers.insert({layer, Layer()});
        widget->bindtoGUI(this);
        widget->onLoad();
        __layers.at(layer).widgets.emplace_back(widget);
    }

    // void GUI::removeWidget(gui::Widget &widget, int64_t layer) {
    //     if (!__layers.contains(layer))
    //         return;
    //     auto &widgets = __layers.at(layer).widgets;
    //     widgets.erase(std::remove(widgets.begin(), widgets.end(), &widget), widgets.end());
    // }

    void GUI::clearLayer(int64_t layer) {
        if (!__layers.contains(layer))
            return;
        __layers.at(layer).widgets.clear();
    }
}
