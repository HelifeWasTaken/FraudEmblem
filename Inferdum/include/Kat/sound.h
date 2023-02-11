#pragma once

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Music.hpp>
#include <unordered_map>
#include <string>

namespace kat {

    class SoundManager {
    private:
        std::unordered_map<std::string, sf::SoundBuffer> m_buffers;
        static SoundManager *m_instance;
        sf::Music m_music;
    
    public:
        static void addSound(const std::string &name, const std::string& filename);
        static sf::Sound getSound(const std::string& name);

        static SoundManager& instance();

        SoundManager() = default;

        SoundManager(const SoundManager&) = delete;
        SoundManager& operator=(const SoundManager&) = delete;

        SoundManager(SoundManager&&) = delete;
        SoundManager& operator=(SoundManager&&) = delete;

        ~SoundManager() = default;

        static void playMusic(const std::string& filename);
    };
}