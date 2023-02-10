struct CharacterInfo
{
    std::string type;
    int level;
    int team;

    int x, y;
};

class Wave
{
private:
    std::vector<CharacterInfo> m_characters;

public:
    Wave() = default;

    const std::vector<CharacterInfo>& getCharacters() const
    {
        return m_characters;
    }

    Wave& addCharacter(const CharacterInfo& character)
    {
        m_characters.push_back(character);
        return *this;
    }

    std::vector<CharacterInfo>::iterator begin()
    {
        return m_characters.begin();
    }

    std::vector<CharacterInfo>::iterator end()
    {
        return m_characters.end();
    }
};

class Level
{
private:
    std::queue<Wave> m_waves;

public:
    Level() = default;

    const std::queue<Wave>& getWaves() const
    {
        return m_waves;
    }

    const Wave& currentWave() const
    {
        return m_waves.front();
    }

    Level& addWave(const Wave& wave)
    {
        m_waves.push(wave);
        return *this;
    }

    void nextWave()
    {
        m_waves.pop();
    }

    bool isFinished() const
    {
        return m_waves.empty();
    }

    void reset()
    {
        while (!m_waves.empty())
        {
            m_waves.pop();
        }
    }

    std::queue<Wave>::iterator begin()
    {
        return m_waves.begin();
    }

    std::queue<Wave>::iterator end()
    {
        return m_waves.end();
    }
};