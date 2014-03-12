#ifndef GAMESTATES_STATE_HPP
#define GAMESTATES_STATE_HPP

#include <gamestates/StateIdentifiers.hpp>
#include <ResourceIdentifiers.hpp>

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>

namespace sf
{
    class RenderWindow;
}

class StateStack;
//class Player

class State
{
public:
    typedef std::unique_ptr<State> Ptr;

    struct Context
    {
                Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts);

        sf::RenderWindow*   window;
        TextureHolder*      textures;
        FontHolder*         fonts;
    };

private:
    StateStack*             mStack;
    Context                 mContext;

public:
                            State(StateStack& stack, Context context);
    virtual                 ~State();

    virtual void            Draw() = 0;
    virtual bool            Update(sf::Time dt) = 0;
    virtual bool            HandleEvent(const sf::Event& event) = 0;

protected:
    void                    RequestStackPush(States::ID stateID);
    void                    RequestStackPop();
    void                    RequestStackClear();

    Context                 GetContext() const;
};
#endif // GAMESTATES_STATE_HPP
