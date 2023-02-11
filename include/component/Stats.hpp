/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Stats
*/

#pragma once

#include <algorithm>
#include <iostream>

#include "nlohmann/json.hpp"

namespace emblem {

    class Stats {
        size_t __xp = 0;
        size_t __xpRequired;


        public:
            Stats(const nlohmann::json &json);
            ~Stats() = default;

            size_t hpMax;
            size_t hp;

            size_t mov;

            size_t atk;
            size_t def;
            size_t lck;

            size_t lvl;


            void heal(size_t amount);
            void damage(size_t amount);

            bool isAlive();

            void xp(size_t amount);

            void lvlUp();

            void setLvl(size_t lvl);

            const size_t &xp() const { return __xp; };
            const size_t &xpRequired() const { return __xpRequired; };
    };
}

std::ostream &operator<<(std::ostream &stream, const emblem::Stats &stats);
