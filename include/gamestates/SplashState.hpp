#ifndef GAMESTATES_SPLASHSTATE_HPP
#define GAMESTATES_SPLASHSTATE_HPP

#include <gamestates/State.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class SplashState : public State
{
private:
    sf::Sprite          mBackgroundSprite;
    sf::Text            mText;

    sf::Time            mTestLoadTime;

public:
                        SplashState(StateStack& stack, Context context);

    virtual void        Draw();
    virtual bool        Update(sf::Time dt);
    virtual bool        HandleEvent(const sf::Event& event);
};
#endif // GAMESTATES_SPLASHSTATE_HPP
