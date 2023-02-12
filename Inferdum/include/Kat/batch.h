#pragma once

#include <SFML/Graphics/Drawable.hpp>

#include "./window.h"

#include <memory>
#include <iostream>

namespace kat {

    using shared_drawable_t = std::shared_ptr<sf::Drawable>;
    using Batch = std::vector<shared_drawable_t>;
    using ZAxis = int;

    class BatchRenderer {
    private:
        std::vector<
            std::pair<ZAxis, Batch>
        > m_batches;

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
            if (m_batches.empty()) {
                m_batches.push_back({ z, { drawable } });
                return;
            }
            if (m_batches.back().first <= z) {
                if (m_batches.back().first == z) {
                    m_batches.back().second.push_back(drawable);
                } else {
                    m_batches.push_back({ z, { drawable } });
                }
            }
            if (m_batches.front().first >= z) {
                if (m_batches.front().first == z) {
                    m_batches.front().second.push_back(drawable);
                } else {
                    m_batches.insert(m_batches.begin(), { z, { drawable } });
                }
            }

            // dicotomy search as m_batches is sorted
            size_t i = 0;

            for (size_t step = m_batches.size() / 2; step > 0; step /= 2) {
                while (i + step < m_batches.size() && m_batches[i + step].first <= z) {
                    i += step;
                }
            }
            if (i < m_batches.size() && m_batches[i].first == z) {
                m_batches[i].second.push_back(drawable);
            } else {
                m_batches.insert(m_batches.begin() + i, { z, { drawable } });
            }
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
            for (const auto& [z, batch] : m_batches) {
                for (const auto& drawable : batch) {
                    window.draw(*drawable);
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