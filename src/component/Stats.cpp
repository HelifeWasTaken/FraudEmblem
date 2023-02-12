/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Stats
*/

#include "component/Stats.hpp"

emblem::Stats::Stats(const nlohmann::json &json) {
    hpMax = json["hp"];
    hp = hpMax;
    atk = json["atk"];
    def = json["def"];
    // mag = json["mag"];
    // res = json["res"];
    // spd = json["spd"];
    lck = json["lck"];
    mov = json["mov"];

    json.find("lvl") != json.end() ? lvl = json["lvl"] : lvl = 1;

    __xpRequired = 10 * lvl * lvl + 40;
}

void emblem::Stats::heal(size_t amount) {
    hp = std::clamp<size_t>(hp + amount, 0, hpMax);
}

void emblem::Stats::damage(size_t amount) {
    if (def > amount)
        amount = 0;
    else
        amount -= def;
    hp = std::clamp<size_t>(hp - amount, 0, hpMax);
}

bool emblem::Stats::isAlive() {
    return hp > 0;
}

void emblem::Stats::xp(size_t amount) {
    __xp += amount;
    if (__xp >= __xpRequired)
        lvlUp();
}

void emblem::Stats::lvlUp() {
    ++lvl;
    __xp = 0;
    __xpRequired = 10 * lvl * lvl + 40;
}

void emblem::Stats::setLvl(size_t lvl) {
    this->lvl = lvl;
    __xp = 0;
    __xpRequired = 10 * lvl * lvl + 40;
}

std::ostream &operator<<(std::ostream &stream, const emblem::Stats &stats) {
    stream << "[ HP: " << stats.hp << "/" << stats.hpMax;
    stream << " | ATK: " << stats.atk;
    stream << " | DEF: " << stats.def;
    // stream << "MAG: " << stats.mag << std::endl;
    // stream << "RES: " << stats.res << std::endl;
    // stream << "SPD: " << stats.spd << std::endl;
    stream << " | LCK: " << stats.lck;
    stream << " | MOV: " << stats.mov;
    stream << " | LVL: " << stats.lvl;
    stream << " | XP: " << stats.xp() << "/" << stats.xpRequired() << " ]";
    return stream;
}
