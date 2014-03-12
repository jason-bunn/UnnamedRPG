#include <gamestates/StateStack.hpp>
#include <gamestates/State.hpp>
#include <ForEach.hpp>

#include <cassert>

StateStack::StateStack(State::Context context)
: mStack()
, mPendingList()
, mContext(context)
, mFactories()
{

}

void StateStack::Update(sf::Time dt)
{
    //Iterate from top to bottom, stop as soon as update() returns false
    for(auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
    {
        if(!(*itr)->Update(dt))
            break;
    }

    ApplyPendingChanges();
}

void StateStack::Draw()
{
    //Draw all active states from bottom to top
    FOREACH(State::Ptr& state, mStack)
    {
        state->Draw();
    }
}

void StateStack::HandleEvent(const sf::Event& event)
{
    // Iterate from top to bottom, stop as soon as handleEvent() returns false
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
	{
		if (!(*itr)->HandleEvent(event))
			break;
	}

	ApplyPendingChanges();
}

void StateStack::PushState(States::ID stateID)
{
    mPendingList.push_back(PendingChange(Push, stateID));
}

void StateStack::PopState()
{
    mPendingList.push_back(PendingChange(Pop));
}

void StateStack::ClearStates()
{
    mPendingList.push_back(PendingChange(Clear));
}

bool StateStack::IsEmpty() const
{
    return mStack.empty();
}

State::Ptr StateStack::CreateState(States::ID stateID)
{
    auto found = mFactories.find(stateID);
    assert(found != mFactories.end());

    return found->second();
}

void StateStack::ApplyPendingChanges()
{
    FOREACH(PendingChange change, mPendingList)
    {
        switch(change.action)
        {
        case Push:
            mStack.push_back(CreateState(change.stateID));
            break;

        case Pop:
            mStack.pop_back();
            break;

        case Clear:
            mStack.clear();
            break;
        }

    }

    mPendingList.clear();
}

StateStack::PendingChange::PendingChange(Action action, States::ID stateID)
: action(action)
, stateID(stateID)
{

}
