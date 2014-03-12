
#include <Application.hpp>

const sf::Time Application::TimePerFrame = sf::seconds(1.0f/60.0f);

Application::Application()
: mWindow(sf::VideoMode(550, 220), "Splash Window", sf::Style::None)
, mDisplayStats(false)
{

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

        }

        //update statistics

        Render();
    }
}

void Application::ProcessInput()
{
    sf::Event event;
    while(mWindow.pollEvent(event))
    {
        //send events to current state
        //mStateStack.handleEvent(event);

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
    //mStateStack.update(dt);
}

void Application::Render()
{
    mWindow.clear();

    //send draw call to current state
    //mStateStack.draw();
    //set the view of the main window
    mWindow.setView(mWindow.getDefaultView());

    //mWindow.draw(mStatisticsText);

    mWindow.display();
}

