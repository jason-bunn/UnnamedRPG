#include <gamestates/SplashState.hpp>
#include <Utility.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

SplashState::SplashState(StateStack& stack, Context context)
: State(stack, context)
, mText()
, mTestLoadTime(sf::Time::Zero)
{
    mBackgroundSprite.setTexture(context.textures->Get(Textures::SplashScreen));

    mText.setFont(context.fonts->Get(Fonts::Main));
    mText.setString("Loading...");
    centerOrigin(mText);
    mText.setPosition(sf::Vector2f(context.window->getSize() / 2u));
    //context.textures->Load(Textures::TitleScreen, "media/images/MenuScreen.png");
}

void SplashState::Draw()
{
    sf::RenderWindow& window = *GetContext().window;

    window.draw(mBackgroundSprite);
}

bool SplashState::Update(sf::Time dt)
{
    mTestLoadTime += dt;

    if(mTestLoadTime >= sf::seconds(2))
    {
        RequestStackPop();
        RequestStackPush(States::Title);
    }

    return true;
}

bool SplashState::HandleEvent(const sf::Event& event)
{
    return true;
}
