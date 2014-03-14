
#include <gamestates/TitleState.hpp>
#include <Utility.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

TitleState::TitleState(StateStack& stack, Context context)
: State(stack, context)
, mText()
, mShowText(true)
, mTextEffectTime(sf::Time::Zero)
{

    context.window->create(sf::VideoMode(1024, 768), "Unnamed RPG", sf::Style::Default);

    //set background sprite
    mBackgroundSprite.setTexture(context.textures->Get(Textures::TitleScreen));

    mText.setFont(context.fonts->Get(Fonts::Main));
    mText.setString("Press any key to start");
    centerOrigin(mText);

    mText.setPosition(sf::Vector2f(context.window->getSize()/ 2u));

}

void TitleState::Draw()
{
    sf::RenderWindow& window = *GetContext().window;
    //draw background image
    window.draw(mBackgroundSprite);

    if(mShowText)
    {
        window.draw(mText);
    }
}

bool TitleState::Update(sf::Time dt)
{
    mTextEffectTime += dt;

    if(mTextEffectTime >= sf::seconds(0.5f))
    {
        mShowText = !mShowText;
        mTextEffectTime = sf::Time::Zero;
    }

    return true;
}

bool TitleState::HandleEvent(const sf::Event& event)
{
    //if any key is pressed, trigger the next screen
    if(event.type == sf::Event::KeyReleased)
    {
        RequestStackPop();
        RequestStackPush(States::Menu);
    }

    return true;
}
