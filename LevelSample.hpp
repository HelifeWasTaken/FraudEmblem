class Level
{
public:
    struct Spawn
    {
        int x;
        int y;
        std::string type;
        int team;
    };

    struct Event
    {
        std::variant<Dialog, Spawn> event;

        Events(const Dialog& dialog) : event(dialog) {}
    
        Events(const Spawn& spawn) : event(spawn) {}

        bool isDialog() const
        {
            return std::holds_alternative<Dialog>(event);
        }

        bool isSpawn() const
        {
            return std::holds_alternative<Spawn>(event);
        }

        Dialog& getDialog()
        {
            return std::get<Dialog>(event);
        }

        Spawn& getSpawn()
        {
            return std::get<Spawn>(event);
        }
    };

    struct LevelState
    {
        int round;
        int wave;
    };

    struct EventTrigger
    {
        virtual bool isTriggered(const LevelState&) = 0;
    };

    struct RoundTrigger : public EventTrigger
    {
        int round;

        RoundTrigger(int round) : round(round) {}

        bool isTriggered(const LevelState& state) override
        {
            return round >= state.round;
        }
    };

    struct WaveTrigger : public EventTrigger
    {
        int wave;

        WaveTrigger(int wave) : wave(wave) {}

        bool isTriggered(const LevelState& state) override
        {
            return wave >= state.wave;
        }
    };

private:
    std::vector<std::pair<EventTrigger, std::vector<Event>>> events;

    std::vector<Event> event_builder;
    EventTrigger trigger_builder;

public:
    Level() = default;

    Level& setTrigger(const EventTrigger& trigger)
    {
        trigger_builder = trigger;
        return *this;
    }

    Level& addEvent(const Event& event)
    {
        event_builder.push_back(event);
        return *this;
    }

    Level& addDialog(const Dialog& dialog)
    {
        return addEvent(Event(dialog));
    }

    Level& addSpawn(const Spawn& spawn)
    {
        return addEvent(Event(spawn));
    }

    Level& setRoundTrigger(int round)
    {
        return setTrigger(RoundTrigger(round));
    }

    Level& setWaveTrigger(int wave)
    {
        return setTrigger(WaveTrigger(wave));
    }

    Level& buildEvent()
    {
        events.push_back({ trigger_builder, event_builder });
        event_builder.clear();
        return *this;
    }

    std::vector<Event> getEvents(const LevelState& state)
    {
        std::vector<Event> result;
        size_t i = 0;

        while (i < events.size())
        {
            if (events[i].first.isTriggered(state))
            {
                result.insert(result.end(), events[i].second.begin(), events[i].second.end());
                events.erase(events.begin() + i);
            }
            else
            {
                i++;
            }
        }
        return result;
    }

    bool isFinished() const
    {
        return events.empty();
    }
};