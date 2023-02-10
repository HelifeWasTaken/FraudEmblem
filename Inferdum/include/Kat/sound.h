#pragma once

#include <SFML/Audio/Sound.hpp>
#include <unordered_map>

namespace kat {

    class SoundManager {
    private:
        std::unordered_map<std::string, sf::SoundBuffer> m_buffers;
        static SoundManager *m_instance;
        sf::Music m_music;
    
    public:
        static void addSound(const std::string& filename);
        static sf::Sound getSound(const std::string& filename);

        static SoundManager& instance();

        SoundManager() = default;

        SoundManager(const SoundManager&) = delete;
        SoundManager& operator=(const SoundManager&) = delete;

        SoundManager(SoundManager&&) = delete;
        SoundManager& operator=(SoundManager&&) = delete;

        ~SoundManager() = default;

        static void playMusic(const std::string& filename);
    };

    SoundManager& SoundManager::instance()
    {
        if (m_instance == nullptr) {
            m_instance = new SoundManager();
        }
        return *m_instance;
    }

    void SoundManager::addSound(const std::string& filename)
    {
        instance().m_buffers[filename].loadFromFile(filename);
    }

    sf::Sound SoundManager::getSound(const std::string& filename)
    {
        sf::Sound sound;
        sound.setBuffer(instance().m_buffers[filename]);
        return sound;
    }

    void SoundManager::playMusic(const std::string& filename)
    {
        instance().m_music.openFromFile(filename);
        instance().m_music.play();
    }

    SoundManager *SoundManager::m_instance = nullptr;
}