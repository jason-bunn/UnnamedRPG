#ifndef GAMESTATES_STATESTACK_HPP
#define GAMESTATES_STATESTACK_HPP

#include <gamestates/State.hpp>
#include <gamestates/StateIdentifiers.hpp>
#include <ResourceIdentifiers.hpp>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>

#include <vector>
#include <utility>
#include <functional>
#include <map>

namespace sf
{
    class Event;
    class RenderWindow;
}

class StateStack : private sf::NonCopyable
{
public:
    enum Action
    {
        Push,
        Pop,
        Clear,
    };
private:
    struct PendingChange
    {
        explicit        PendingChange(Action action, States::ID stateID = States::None);

        Action          action;
        States::ID      stateID;
    };
private:
    std::vector<State::Ptr>     mStack;
    std::vector<PendingChange>  mPendingList;

    State::Context              mContext;
    std::map<States::ID, std::function<State::Ptr()>> mFactories;


public:
    explicit            StateStack(State::Context context);

    template <typename T>
    void                RegisterState(States::ID stateID);

    void                Update(sf::Time dt);
    void                Draw();
    void                HandleEvent(const sf::Event& event);

    void                PushState(States::ID stateID);
    void                PopState();
    void                ClearStates();

    bool                IsEmpty() const;

private:
    State::Ptr          CreateState(States::ID stateID);
    void                ApplyPendingChanges();




};

template <typename T>
void StateStack::RegisterState(States::ID stateID)
{
    mFactories[stateID] = [this] ()
    {
        return State::Ptr(new T(*this, mContext));
    };
}

#endif // GAMESTATES_STATESTACK_HPP
