#pragma once

#include <SFML/Graphics/Drawable.hpp>

#include "./window.h"

#include <memory>
#include <iostream>
#include <concepts>
#include <variant>
#include <map>

namespace kat {

    using shared_drawable_t = std::shared_ptr<sf::Drawable>;
    using low_vertex_t = std::shared_ptr<std::vector<sf::Vertex>>;
    using low_drawable_t = std::pair<low_vertex_t, sf::Texture*>;
    using Batch = std::vector<std::variant<shared_drawable_t, low_drawable_t>>;
    using ZAxis = int;

    class BatchRenderer {
    private:
        // Kek
        std::map<ZAxis, Batch> m_batches;

    public:
        /**
         * @brief Adds a drawable to the batch.
         * 
         * @param drawable The drawable to add.
         * @param z The z-axis of the drawable.
         */
        void add(const shared_drawable_t& drawable, ZAxis z = 0)
        {
            // Basic check to avoid useless search
            if (m_batches.contains(z)) {
                m_batches.at(z).push_back(drawable);
                return;
            }
            m_batches.insert({ z, { drawable } });
        }

        void add(const low_drawable_t& drawable, ZAxis z = 0)
        {
            // Basic check to avoid useless search
            if (!m_batches.contains(z)) {
                m_batches[z] = std::vector<std::variant<shared_drawable_t, low_drawable_t>>();
            }
            m_batches.at(z).push_back(drawable);
        }

        /**
         * @brief Adds a drawable to the batch.
         * 
         * @param drawable The drawable to add.
         * @param z The z-axis of the drawable.
         */
        template<typename T>
        void add(T& drawable, ZAxis z = 0)
        {
            add(drawable.as_drawable(), z);
        }

        /**
         * @brief Draws the batch.
         * 
         * @param window The window to draw to.
         */
        void draw(Window& window, bool clear = true)
        {
            for (const auto &[z, batch] : m_batches) {
                for (const auto& drawable : batch) {
                    if (drawable.index() == 0) {
                        window.draw(*std::get<shared_drawable_t>(drawable));
                    } else {
                        auto __drawable = std::get<low_drawable_t>(drawable);
                        auto __vertices = *__drawable.first;
                        auto __texture = __drawable.second;
                        sf::RenderStates __states = sf::RenderStates::Default;
                        __states.texture = __texture;
                        window.get_handle().draw(&__vertices[0], __vertices.size(), sf::Quads, __states);
                    }
                }
            }
            if (clear)
                m_batches.clear();
        }

        /**
         * @brief Clears the batch.
         */
        void clear()
        {
            m_batches.clear();
        }

        /**
         * @brief Constructs a new std::cout << " AAAAAAAAAAAAAAAAAa" << std::endl;Batch Renderer object.
         */
        BatchRenderer() = default;

        /**
         * @brief Destroys the Batch Renderer object.
         */
        ~BatchRenderer() = default;
    };
}