#include <gamestates/MenuState.hpp>
#include <gui/Button.hpp>
#include <Utility.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

MenuState::MenuState(StateStack& stack, Context context)
: State(stack, context)
, mGuiContainer()
{
    //set background texture
    //sf::Texture& texture = context.textures->Get(Textures::TitleScreen);
    mBackgroundSprite.setTexture(context.textures->Get(Textures::MenuScreen));

    //menu buttons
    auto playButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    playButton->setPosition(768,300);
    playButton->setText("Play");
    playButton->setCallBack([this] ()
                            {
                                RequestStackPop();
                                RequestStackPush(States::Game);
                            });

    auto settingsButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    settingsButton->setPosition(768, 350);
    settingsButton->setText("Settings");
    //settingsButton->setCallBack([this] ()
    //                            {
     //                               requestStackPush(States::Settings);
     //                           });

    auto exitButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    exitButton->setPosition(768, 400);
    exitButton->setText("Exit");
    exitButton->setCallBack([this] ()
                            {
                                RequestStackPop();
                            });

    mGuiContainer.pack(playButton);
    mGuiContainer.pack(settingsButton);
    mGuiContainer.pack(exitButton);
}

void MenuState::Draw()
{
    sf::RenderWindow& window = *GetContext().window;

    window.setView(window.getDefaultView());

    window.draw(mBackgroundSprite);
    window.draw(mGuiContainer);
}

bool MenuState::Update(sf::Time)
{
    return true;
}

bool MenuState::HandleEvent(const sf::Event& event)
{
    mGuiContainer.handleEvent(event);
    return false;
}

