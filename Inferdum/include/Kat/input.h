#pragma once

#include <SFML/Window/Event.hpp>

#include "./window.h"

namespace kat {

enum class InputState {
    Idle,
    Released,
    Pressed,
    Held
};

using Joystick = sf::Joystick;
using Keyboard = sf::Keyboard;
using Mouse = sf::Mouse;
using Event = sf::Event;
using JoystickId = unsigned int;
using JoystickButton = unsigned int;
using MouseButton = sf::Mouse::Button;
using MousePosition = Vector2i;

/**
 * \class InputManager
 *
 * \brief Manages input events from various sources, such as the keyboard, mouse, and joystick.
 *
 * The InputManager class has an array of joystick states, an array of keyboard states, and an array of mouse button states. It has private methods for updating the state of the inputs based on events received from the window. It also has methods for checking the state of specific inputs (e.g., isKeyPressed, isMouseButtonPressed, isJoystickButtonPressed).
 */
class InputManager {
private:
    /**
     * \struct JoystickState
     *
     * \brief Represents the state of a joystick.
     */
    struct JoystickState {
        bool m_Connected = false; ///< Indicates whether the joystick is connected.
        float m_Axes[Joystick::AxisCount] = {0.0f}; ///< The values of the joystick axes.
        InputState m_Buttons[Joystick::ButtonCount] = {InputState::Idle}; ///< The states of the joystick buttons.
    };
        
    JoystickState m_Joysticks[Joystick::Count]; ///< The states of all joysticks.

    InputState m_Keys[Keyboard::KeyCount] = {InputState::Idle}; ///< The states of all keyboard keys.

    InputState m_MouseButtons[Mouse::ButtonCount] = {InputState::Idle}; ///< The states of all mouse buttons.

    static InputManager *m_Instance; ///< The singleton instance of the InputManager.

    /**
     * \brief Constructs a new InputManager.
     *
     * The InputManager constructor is private to enforce the singleton pattern.
     */
    InputManager() = default;

    /**
     * \brief Updates the state of an input based on the new state passed to it.
     *
     * \param[in] state The current state of the input.
     * \param[in] new_state The new state of the input.
     */
    void updateInputState(InputState& state, const InputState &new_state);

    /**
     * \brief Updates the state of the joystick based on the given event.
     *
     * \param[in] event The event to process.
     */
    void updateJoystickEvent(Event& event);

    /**
     * \brief Updates the state of the keyboard based on the given event.
     *
     * \param[in] event The event to process.
     */
    void updateKeyboardEvent(Event& event);

    /**
     * \brief Updates the state of the mouse based on the given event.
     *
     * \param[in] event The event to process.
     */
    void updateMouseEvent(Event& event);

    /**
     * \brief Polls events from the window and passes them to the appropriate event updating method.
     *
     * \param[in] window The window to poll events from.
     */
    void updateEvent(Window& window);

    /**
     * \brief Updates the states of the inputs to their next states.
     *
     * For example, updates the state of a pressed key from pressed to held.
     */
    void _nextFrame();

public:
    /**
     * @brief Returns a reference to the singleton instance of the InputManager.
     * @return Reference to the InputManager instance.
     */
    static InputManager& instance();

    /**
     * @brief Destroys the singleton instance of the InputManager.
     */
    static void destroy();

    /**
     * @brief Updates the InputManager with the current state of user input.
     * @param window The window to use as a reference for mouse position.
     */
    static void update(Window& window);

    /**
     * @brief Advances the InputManager to the next frame.
     */
    static void nextFrame();

    /**
     * @brief Check if a joystick is connected.
     * @param joystick_id The ID of the joystick to check.
     * @return True if the joystick is connected, false if not.
     */
    static bool isJoystickConnected(const JoystickId& joystick_id);

    /**
     * @brief Get the position of a joystick axis.
     * @param joystick_id The ID of the joystick to check.
     * @param axis The axis to check.
     * @return The position of the joystick axis, in the range [-100, 100].
     */
    static float getJoystickAxisPosition(const JoystickId& joystick_id, const Joystick::Axis& axis);

    /**
     * @brief Get the state of a joystick button.
     * @param joystick_id The ID of the joystick to check.
     * @param button The button to check.
     * @return The state of the joystick button.
     */
    static InputState getJoystickButtonState(const JoystickId& joystick_id, const JoystickButton& button);

    /**
     * @brief Get the state of a keyboard key.
     * @param key The key to check.
     * @return The state of the keyboard key.
     */
    static InputState getKeyState(const Keyboard::Key& key);

    /**
     * @brief Get the state of a mouse button.
     * @param button The button to check.
     * @return The state of the mouse button.
     */
    static InputState getMouseButtonState(const Mouse::Button& button);

    /**
     * @brief Get the current position of the mouse.
     * @return The current position of the mouse.
     */
    static MousePosition getMousePosition();

    /**
     * @brief Set the position of the mouse.
     * @param position The new position of the mouse.
     */
    static void setMousePosition(const MousePosition& position);

    /**
     * @brief Set the position of the mouse relative to a window.
     * @param position The new position of the mouse.
     * @param relative_to The window to use as a reference for the mouse position.
     */
    static void setMousePosition(const MousePosition& position, const sf::Window& relative_to);
};

}