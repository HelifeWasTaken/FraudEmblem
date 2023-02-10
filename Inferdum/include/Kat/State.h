#pragma once

#include <memory>
#include <stack>
#include <string>
#include <unordered_map>

namespace kat
{

class StateMachine;

class State
{
  public:
    friend class StateMachine;

    State() = default;
    virtual ~State() = default;

    virtual void on_enter()
    {
    }
    virtual void on_exit()
    {
    }
    virtual void on_update() = 0;
    virtual void on_event()
    {
    }

    StateMachine &state_machine();
    const StateMachine &state_machine() const;

  private:
    StateMachine *m_stateMachine;

    void _set_state_machine(StateMachine *stateMachine);
};

class StateMachine
{
  private:
    std::stack<State *> m_states;
    std::unordered_map<std::string, std::unique_ptr<State>> m_statesMap;
    State *m_pendingState = nullptr;
    State *m_currentState = nullptr;

    size_t m_to_pop = 0;
    bool m_must_clear = false;

    void _pop();
    bool _clear();
    bool _set();

  public:
    StateMachine() = default;
    ~StateMachine() = default;

    void update();

    void event();

    void set_state(const std::string &stateName);

    void push_state(const std::string &stateName);

    void pop_state();

    void clear_states();

    template <typename T, typename... Args> void register_state(const std::string &stateName, Args &&... args)
    {
        m_statesMap.emplace(stateName, std::make_unique<T>(std::forward<Args>(args)...));
        m_statesMap.at(stateName)->_set_state_machine(this);
    }

    bool empty() const;

    bool in_transition() const;

    bool updatable() const;
};

} // namespace kat