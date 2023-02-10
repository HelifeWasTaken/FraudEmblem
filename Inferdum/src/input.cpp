#include "Kat/input.h"

namespace kat {

    InputManager *InputManager::m_Instance = nullptr;

    void InputManager::updateInputState(InputState& state, const InputState &new_state)
    {
        if (new_state == InputState::Pressed) {
            if (state == InputState::Held)
                return;
            state = InputState::Pressed;
        } else if (new_state == InputState::Released) {
            if (state == InputState::Idle)
                return;
            state = InputState::Released;
        }
    }

    void InputManager::updateJoystickEvent(Event& event)
    {
        switch (event.type) {
        case sf::Event::JoystickConnected:
            m_Joysticks[event.joystickConnect.joystickId].m_Connected = true;
            break;
        case sf::Event::JoystickDisconnected:
            m_Joysticks[event.joystickConnect.joystickId].m_Connected = false;
            break;
        case sf::Event::JoystickMoved:
            m_Joysticks[event.joystickMove.joystickId].m_Axes[event.joystickMove.axis] = event.joystickMove.position;
            break;
        case sf::Event::JoystickButtonPressed:
            updateInputState(m_Joysticks[event.joystickButton.joystickId].m_Buttons[event.joystickButton.button], InputState::Pressed);
            break;
        case sf::Event::JoystickButtonReleased:
            updateInputState(m_Joysticks[event.joystickButton.joystickId].m_Buttons[event.joystickButton.button], InputState::Released);
            break;
        default:
            break;
        }
    }

    void InputManager::updateKeyboardEvent(Event& event)
    {
        switch (event.type) {
        case sf::Event::KeyPressed:
            updateInputState(m_Keys[event.key.code], InputState::Pressed);
            break;
        case sf::Event::KeyReleased:
            updateInputState(m_Keys[event.key.code], InputState::Released);
            break;
        default:
            break;
        }
    }

    void InputManager::updateMouseEvent(Event& event)
    {
        switch (event.type) {
        case sf::Event::MouseButtonPressed:
            updateInputState(m_MouseButtons[event.mouseButton.button], InputState::Pressed);
            break;
        case sf::Event::MouseButtonReleased:
            updateInputState(m_MouseButtons[event.mouseButton.button], InputState::Released);
            break;
        default:
            break;
        }
    }

    void InputManager::updateEvent(Window& window)
    {
        sf::Event event;
        while (window.poll(event)) {
            updateJoystickEvent(event);
            updateKeyboardEvent(event);
            updateMouseEvent(event);
        }
    }

    void InputManager::_nextFrame()
    {
        static const auto update_input_state = [](InputState& state) {
            if (state == InputState::Pressed)
                state = InputState::Held;
            else if (state == InputState::Released)
                state = InputState::Idle;
        };

        for (auto& state : m_Joysticks)
            for (auto& button : state.m_Buttons)
                update_input_state(button);
        std::for_each(std::begin(m_Keys), std::end(m_Keys), update_input_state);
        std::for_each(std::begin(m_MouseButtons), std::end(m_MouseButtons), update_input_state);
    }

    InputManager& InputManager::instance()
    {
        if (!m_Instance)
            m_Instance = new InputManager();
        return *m_Instance;
    }

    void InputManager::destroy()
    {
        if (m_Instance)
            delete m_Instance;
        m_Instance = nullptr;
    }

    void InputManager::update(Window& window)
    {
        m_Instance->updateEvent(window);
    }

    void InputManager::nextFrame()
    {
        m_Instance->_nextFrame();
    }

    bool InputManager::isJoystickConnected(const JoystickId& joystick_id)
    {
        return m_Instance->m_Joysticks[joystick_id].m_Connected;
    }

    float InputManager::getJoystickAxisPosition(const JoystickId& joystick_id, const Joystick::Axis& axis)
    {
        return m_Instance->m_Joysticks[joystick_id].m_Axes[axis];
    }

    InputState InputManager::getJoystickButtonState(const JoystickId& joystick_id, const JoystickButton& button)
    {
        return m_Instance->m_Joysticks[joystick_id].m_Buttons[button];
    }

    InputState InputManager::getKeyState(const Keyboard::Key& key)
    {
        return m_Instance->m_Keys[key];
    }

    InputState InputManager::getMouseButtonState(const Mouse::Button& button)
    {
        return m_Instance->m_MouseButtons[button];
    }

    Vector2i InputManager::getMousePosition()
    {
        return sf::Mouse::getPosition();
    }

    void InputManager::setMousePosition(const MousePosition& position)
    {
        sf::Mouse::setPosition(position);
    }

    void InputManager::setMousePosition(const MousePosition& position, const sf::Window& relative_to)
    {
        sf::Mouse::setPosition(position, relative_to);
    }
}