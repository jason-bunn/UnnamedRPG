
#include <Application.hpp>
#include <gamestates/SplashState.hpp>
#include <gamestates/TitleState.hpp>
#include <gamestates/MenuState.hpp>

const sf::Time Application::TimePerFrame = sf::seconds(1.0f/60.0f);

Application::Application()
: mWindow(sf::VideoMode(550, 220), "Splash Window", sf::Style::None)
, mTextures()
, mFonts()
, mStateStack(State::Context(mWindow, mTextures, mFonts))
, mDisplayStats(false)
, mStatisticsText()
, mStatisticsUpdateTime()
, mStatisticsNumFrames(0)

{
    mFonts.Load(Fonts::Main, "media/SF Square Head.ttf");
    mFonts.Load(Fonts::InGame, "media/8bm.ttf");

    //load splash image
    mTextures.Load(Textures::SplashScreen, "media/images/Badlands.png");
    mTextures.Load(Textures::TitleScreen, "media/images/MenuScreen.png");
    mTextures.Load(Textures::MenuScreen, "media/images/MenuScreen.png");
    mTextures.Load(Textures::Buttons, "media/images/NewButtons.png");
    //initialize framerate/debug text
    mStatisticsText.setFont(mFonts.Get(Fonts::Main));
    mStatisticsText.setColor(sf::Color::White);
    mStatisticsText.setPosition(5.0f, 5.0f);
    mStatisticsText.setCharacterSize(10u);

    //register states and push the title state onto the stack
    RegisterStates();
    mStateStack.PushState(States::Splash);

}

Application::~Application()
{

}

void Application::Init()
{

}

void Application::Run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while(mWindow.isOpen())
    {
        sf::Time dt = clock.restart();
        timeSinceLastUpdate += dt;
        while(timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;

            //process inputs
            ProcessInput();

            //update logic
            Update(TimePerFrame);

            //check if state stack is empty
            if(mStateStack.IsEmpty())
            {
                mWindow.close();
            }
        }

        //update statistics
        UpdateStatistics(dt);

        Render();
    }
}

void Application::ProcessInput()
{
    sf::Event event;
    while(mWindow.pollEvent(event))
    {
        //send events to current state
        mStateStack.HandleEvent(event);

        //close the window if event registered
        if(event.type == sf::Event::Closed)
        {
            mWindow.close();
        }
    }
}

void Application::Update(sf::Time dt)
{
    //send update to current state
    mStateStack.Update(dt);
}

void Application::Render()
{
    mWindow.clear();

    //send draw call to current state
    mStateStack.Draw();
    //set the view of the main window
    mWindow.setView(mWindow.getDefaultView());

    if(mDisplayStats)
        mWindow.draw(mStatisticsText);

    mWindow.display();
}

void Application::UpdateStatistics(sf::Time dt)
{
    mStatisticsUpdateTime += dt;
    mStatisticsNumFrames +=1;
    if(mStatisticsUpdateTime >= sf::seconds(1.0f))
    {
        mStatisticsText.setString("FPS: " + toString(mStatisticsNumFrames));

        mStatisticsUpdateTime -= sf::seconds(1.0f);
        mStatisticsNumFrames = 0;
    }
}

void Application::RegisterStates()
{
    mStateStack.RegisterState<SplashState>(States::Splash);
    mStateStack.RegisterState<TitleState>(States::Title);
    mStateStack.RegisterState<MenuState>(States::Menu);
    //mStateStack.RegisterState<GameState>(States::Game);
    //mStateStack.RegisterState<PauseState>(States::Pause);
   // mStateStack.RegisterState<SettingsState>(States::Settings);
   // mStateStack.RegisterState<GameOverState>(States::GameOver);
}

