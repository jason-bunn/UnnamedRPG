
#include <gamestates/State.hpp>
#include <gamestates/StateStack.hpp>

State::Context::Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts)//, Player& palyer)
: window(&window)
, textures(&textures)
, fonts(&fonts)
//, player(&player)
{

}

State::State(StateStack& stack, Context context)
: mStack(&stack)
, mContext(context)
{

}

State::~State()
{

}

void State::RequestStackPush(States::ID stateID)
{
    mStack->PushState(stateID);
}

void State::RequestStackPop()
{
    mStack->PopState();
}

void State::RequestStackClear()
{
    mStack->ClearStates();
}

State::Context State::GetContext() const
{
    return mContext;
}
