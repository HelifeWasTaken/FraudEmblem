#include "Kat/State.h"

namespace kat
{

StateMachine &State::state_machine()
{
    return *m_stateMachine;
}

const StateMachine &State::state_machine() const
{
    return *m_stateMachine;
}

void State::_set_state_machine(StateMachine *stateMachine)
{
    m_stateMachine = stateMachine;
}

void StateMachine::_pop()
{
    if (m_to_pop && !m_states.empty())
    {
        m_states.top()->on_exit();
        m_states.pop();
        --m_to_pop;
    }
    if (!m_states.empty())
    {
        m_currentState = m_states.top();
    }
}

bool StateMachine::_clear()
{
    if (!m_must_clear)
    {
        return false;
    }
    m_to_pop = m_states.size();
    _pop();
    m_must_clear = !m_states.empty();
    return true;
}

bool StateMachine::_set()
{
    if (m_pendingState == nullptr)
    {
        return false;
    }
    m_must_clear = true;
    _clear();
    if (m_currentState != nullptr)
    {
        return true;
    }
    m_pendingState->on_enter();
    m_states.push(m_pendingState);
    m_currentState = m_pendingState;
    m_pendingState = nullptr;
    return true;
}

void StateMachine::update()
{
    if (!_set())
    {
        if (!_clear())
        {
            _pop();
        }
    }
    if (m_currentState != nullptr)
    {
        m_currentState->on_update();
    }
}

void StateMachine::event()
{
    if (m_currentState != nullptr && m_to_pop == 0)
    {
        m_currentState->on_event();
    }
}

void StateMachine::set_state(const std::string &stateName)
{
    m_pendingState = m_statesMap.at(stateName).get();
}

void StateMachine::push_state(const std::string &stateName)
{
    m_currentState = m_statesMap.at(stateName).get();
    m_states.push(m_currentState);
}

void StateMachine::pop_state()
{
    ++m_to_pop;
}

void StateMachine::clear_states()
{
    m_must_clear = true;
}

bool StateMachine::in_transition() const
{
    return m_pendingState != nullptr;
}

bool StateMachine::empty() const
{
    return m_states.empty();
}

bool StateMachine::updatable() const
{
    return in_transition() || !empty();
}
} // namespace kat