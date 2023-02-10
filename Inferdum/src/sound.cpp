#include "Kat/sound.h"

namespace kat {

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