#ifndef GAMESTATES_TITLESTATE_HPP
#define GAMESTATES_TITLESTATE_HPP

#include <gamestates/State.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class TitleState : public State
{
private:
    sf::Sprite              mBackgroundSprite;
    sf::Text                mText;

    bool                    mShowText;
    sf::Time                mTextEffectTime;

public:

                            TitleState(StateStack& stack, Context context);

    virtual void            Draw();
    virtual bool            Update(sf::Time dt);
    virtual bool            HandleEvent(const sf::Event& event);
};
#endif // GAMESTATES_TITLESTATE_HPP
