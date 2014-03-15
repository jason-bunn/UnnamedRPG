#ifndef GAMESTATES_MENUSTATE_HPP
#define GAMESTATES_MENUSTATE_HPP

#include <gamestates/State.hpp>
#include <gui/Container.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class MenuState : public State
{
public:

                            MenuState(StateStack& stack, Context context);


    virtual void            Draw();
    virtual bool            Update(sf::Time dt);
    virtual bool            HandleEvent(const sf::Event& event);

private:
    sf::Sprite              mBackgroundSprite;
    GUI::Container          mGuiContainer;
};
#endif // GAMESTATES_MENUSTATE_HPP
