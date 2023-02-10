class Dialog
{
private:
    kat::Sprite *character = nullptr;
    kat::Sprite dialogBox = kat::Sprite("dialog_box.png");
    kat::Sound dialog_sound = kat::SoundManager::getSound("dialog.wav");
    kat::Text text = kat::Text("dialog.ttf", 16);

    struct DialogEvent
    {
        enum {
            SET_CHARACTER
            TALK
            SOUND,
            MUSIC,
            WAIT,
            REMOVE_CHARACTER,
            SHOW_UI,
            HIDE_UI
        } type;

        union {
            struct {
                kat::Sprite *character;
            } set;
            struct {
                std::string text;
            } talk;
            struct {
                std::string filename;
            } sound;
            struct {
                std::string filename;
            } music;
            struct {
                float time;
            } wait;

            static DialogEvent setCharacter(kat::Sprite *character)
            {
                DialogEvent event;
                event.type = SET_CHARACTER;
                event.data.set.character = character;
                return event;
            }

            static DialogEvent talk(std::string text)
            {
                DialogEvent event;
                event.type = TALK;
                event.data.talk.text = text;
                return event;
            }

            static DialogEvent sound(std::string filename)
            {
                DialogEvent event;
                event.type = SOUND;
                event.data.sound.filename = filename;
                return event;
            }

            static DialogEvent music(std::string filename)
            {
                DialogEvent event;
                event.type = MUSIC;
                event.data.music.filename = filename;
                return event;
            }

            static DialogEvent wait(float time)
            {
                DialogEvent event;
                event.type = WAIT;
                event.data.wait.time = time;
                return event;
            }

            static DialogEvent removeCharacter()
            {
                DialogEvent event;
                event.type = REMOVE_CHARACTER;
                return event;
            }

            static DialogEvent showUI()
            {
                DialogEvent event;
                event.type = SHOW_UI;
                return event;
            }

            static DialogEvent hideUI()
            {
                DialogEvent event;
                event.type = HIDE_UI;
                return event;
            }

        } data;

        enum {
            NONE,
            SET_CHARACTER_REPLACING,
            SET_CHARACTER_ENTERING,
            STARTED_WAITING,
            FINISHED_WAITING
        } optional_state = NONE;
    };

    bool show_ui = false;
    float text_speed = 0.1f;
    float text_timer = 0.0f;
    sf::Sound _optional_sound;

public:

    Dialog() = default;

    Dialog& addEvent(DialogEvent event)
    {
        events.push_back(event);
        return *this;
    }

    void update(float dt)
    {
        if (events.empty())
        {
            return;
        }

        auto& event = events.front();
        switch (event.type)
        {
        case DialogEvent::SET_CHARACTER:
            switch (event.optional_state)
            {
            case NONE:
                event.optional_state = SET_CHARACTER_REPLACING;
                break;
            case SET_CHARACTER_REPLACING:
                if (!character)
                {
                    character = event.data.set.character;
                    event.optional_state = SET_CHARACTER_ENTERING;
                }
                else if (character->getPosition().x + character->getSize().x < 0)
                {
                    character = nullptr;
                    break;
                }
                else
                {
                    character->move(-dt * 100, 0);
                }
                break;
            case SET_CHARACTER_ENTERING:
                if (character->getPosition().x + character->getSize().x < 0)
                {
                    character->move(dt * 100, 0);
                }
                else
                {
                    events.pop_front();
                }
                break;
            }
            break;
        case DialogEvent::REMOVE_CHARACTER:
            if (character)
            {
                character->move(-dt * 100, 0);
                if (character->getPosition().x + character->getSize().x < 0)
                {
                    character = nullptr;
                    events.pop_front();
                }
            }
            else
            {
                events.pop_front();
            }
            break;
        case DialogEvent::SHOW_UI:
            show_ui = true;
            events.pop_front();
            break;
        case DialogEvent::HIDE_UI:
            show_ui = false;
            events.pop_front();
            break;
        case DialogEvent::TALK:
            text_timer += dt;
            if (text_timer >= text_speed)
            {
                text_timer -= text_speed;

                if (event.data.talk.text.empty())
                {
                    if (kat::Input::isKeyPressed(kat::Key::Enter))
                    {
                        text_timer = 0.0f;
                        text.setString("");
                        events.pop_front();
                    }
                }
                else if (kat::Input::isKeyPressed(kat::Key::Enter))
                {
                    text_timer = 0.0f;
                    text.setString(event.data.talk.text);
                    event.data.talk.text.clear();
                    dialog_sound.play();
                }
                else
                {
                    text.setString(text.getString() + event.data.talk.text[0]);
                    event.data.talk.text.erase(0, 1);
                    dialog_sound.play();
                }
            }
            break;
        case DialogEvent::SOUND:
            _optional_sound.setBuffer(kat::SoundManager::getSound(event.data.sound.filename));
            _optional_sound.play();
            events.pop_front();
            break;
        case DialogEvent::MUSIC:
            kat::SoundManager::playMusic(event.data.music.filename);
            events.pop_front();
            break;
        case DialogEvent::WAIT:
            case NONE:
                event.optional_state = STARTED_WAITING;
                break;
            case STARTED_WAITING:
                event.data.wait.time -= dt;
                if (event.data.wait.time <= 0)
                {
                    event.optional_state = FINISHED_WAITING;
                }
                break;
            case FINISHED_WAITING:
                events.pop_front();
                break;
        }
    }

    bool isFinished() const
    {
        return events.empty();
    }

    void draw(kat::Window& window)
    {
        if (show_ui)
        {
            window.draw(dialog_box);
            window.draw(text);
        }
        if (character)
        {
            window.draw(*character);
        }
    }
};
