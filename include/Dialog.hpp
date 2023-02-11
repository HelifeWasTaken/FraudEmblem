#include "sound.h"
#include <string>
#include "components/sprite.h"
#include "input.h"
#include "resource.h"
#include <queue>

class Dialog
{
private:
    kat::Sprite character;
    int character_id = -1;
    kat::Sprite dialogBox;
    sf::Sound dialog_sound = kat::SoundManager::getSound("dialog");
    sf::Text text;
    sf::Font font;

public:
    struct DialogEvent
    {
        enum {
            INVALID,
            SET_CHARACTER,
            TALK,
            SOUND,
            MUSIC,
            WAIT,
            REMOVE_CHARACTER,
            SHOW_UI,
            HIDE_UI
        } type = INVALID;

        struct {
            struct {
                int id;
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
        } data;

        DialogEvent() = default;
        ~DialogEvent() = default;

        enum {
            NONE,
            SET_CHARACTER_REPLACING,
            SET_CHARACTER_ENTERING,
            STARTED_WAITING,
            FINISHED_WAITING
        } optional_state = NONE;
    };

    static DialogEvent setCharacter(int id)
    {
        DialogEvent event;
        event.type = DialogEvent::SET_CHARACTER;
        event.data.set.id = id;
        return event;
    }

    static DialogEvent talk(std::string text)
    {
        DialogEvent event;
        event.type = DialogEvent::TALK;
        event.data.talk.text = text;
        return event;
    }

    static DialogEvent sound(std::string filename)
    {
        DialogEvent event;
        event.type = DialogEvent::SOUND;
        event.data.sound.filename = filename;
        return event;
    }

    static DialogEvent music(std::string filename)
    {
        DialogEvent event;
        event.type = DialogEvent::MUSIC;
        event.data.music.filename = filename;
        return event;
    }

    static DialogEvent wait(float time)
    {
        DialogEvent event;
        event.type = DialogEvent::WAIT;
        event.data.wait.time = time;
        return event;
    }

    static DialogEvent removeCharacter()
    {
        DialogEvent event;
        event.type = DialogEvent::REMOVE_CHARACTER;
        return event;
    }

    static DialogEvent showUI()
    {
        DialogEvent event;
        event.type = DialogEvent::SHOW_UI;

        return event;
    }

    static DialogEvent hideUI()
    {
        DialogEvent event;
        event.type = DialogEvent::HIDE_UI;
        return event;
    }

private:
    bool show_ui = false;
    float text_speed = 0.0005f;
    float text_timer = 0.0f;
    float sprite_move = 70000.f;
    sf::Sound _optional_sound;

    std::queue<DialogEvent> events;

public:

    Dialog(kat::ResourceManager& r)
    {
        character.create(r.getResource<kat::Texture>("dialog_faces"));
        dialogBox.create(r.getResource<kat::Texture>("dialog_box"));
        font = r.getResource<sf::Font>("dialog_font");
        text = sf::Text("", font);

        character.setPosition(-150, 330);
        character.setScale(2, 2);
        dialogBox.setPosition(0, 500);
        text.setPosition(100, 500);
    }

    Dialog& addEvent(DialogEvent event)
    {
        events.push(event);
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
        {
            switch (event.optional_state)
            {
            case DialogEvent::NONE:
            {
                event.optional_state = DialogEvent::SET_CHARACTER_REPLACING;
                break;
            }
            case DialogEvent::SET_CHARACTER_REPLACING:
            {
                if (character_id == -1)
                {
                    character_id = event.data.set.id;
                    event.optional_state = DialogEvent::SET_CHARACTER_ENTERING;
                    // Face 96 80
                    // Face per line 7
                    // Size per face 128 112
                    character.setTextureRect(sf::IntRect((character_id % 7) * 128, (character_id / 7) * 112, 96, 80));
                }
                else if (character.getPosition().x + character.getGlobalBounds().width < 0)
                {
                    character_id = -1;
                    std::cout << "Character removed" << std::endl;
                }
                else
                {
                    character.move(-dt * sprite_move, 0);
                }
                break;
            }
            case DialogEvent::SET_CHARACTER_ENTERING:
            {
                if (character.getPosition().x < 0)
                {
                    character.move(dt * sprite_move, 0);
                }
                else
                {
                    events.pop();
                }
                break;
            }
            }
            break;
        }
        case DialogEvent::REMOVE_CHARACTER:
        {
            if (character_id != -1)
            {
                character.move(-dt * sprite_move, 0);
                if (character.getPosition().x + character.getGlobalBounds().width < 0)
                {
					character_id = -1;
                    events.pop();
                }
            }
            else
            {
                events.pop();
            }
            break;
        }
        case DialogEvent::SHOW_UI:
        {
            show_ui = true;

            events.pop();
            break;
        }
        case DialogEvent::HIDE_UI:
        {
            show_ui = false;
            events.pop();
            break;
        }
        case DialogEvent::TALK:
        {

            if (event.data.talk.text.empty())
            {
                std::cout << "empty input is: " << (int)kat::InputManager::getKeyState(kat::Keyboard::Key::Enter) << std::endl;
                if (kat::InputManager::getKeyState(kat::Keyboard::Key::Enter) == kat::InputState::Released)
                {
                    text_timer = 0.0f;
                    text.setString("");
                    events.pop();
                }
                return;
            }

            text_timer += dt;
            std::cout << "text_timer: " << text_timer << std::endl;

            if (text_timer >= text_speed)
            {
                text_timer -= text_speed;

                if (kat::InputManager::getKeyState(kat::Keyboard::Key::Enter) == kat::InputState::Released)
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
                    std::cout << "hey" << std::endl;
                }
            }
            break;
        }
        case DialogEvent::SOUND:
        {
            _optional_sound = kat::SoundManager::getSound(event.data.sound.filename);
            _optional_sound.play();
            events.pop();
            break;
        }
        case DialogEvent::MUSIC:
        {
            kat::SoundManager::playMusic(event.data.music.filename);
            events.pop();
            break;
        }
        case DialogEvent::WAIT:
        {
            switch (event.optional_state)
            {
            case DialogEvent::NONE:
            {
                event.optional_state = DialogEvent::STARTED_WAITING;
                break;
            }
            case DialogEvent::STARTED_WAITING:
            {
                event.data.wait.time -= dt;
                if (event.data.wait.time <= 0)
                {
                    event.optional_state = DialogEvent::FINISHED_WAITING;
                }
                break;
            }
            case DialogEvent::FINISHED_WAITING:
            {
                events.pop();
                break;
            }
            }
            break;
        }
        break;
        }
    }

    bool isFinished() const
    {
        return events.empty();
    }

    void draw(kat::Window& window)
    {
        if (events.empty())
        {
            return;
        }
        if (show_ui)
        {
            window.draw(dialogBox);
            window.draw(text);
        }
        if (character_id != -1)
        {
            window.draw(character);
        }
    }
};
