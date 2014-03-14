#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <Utility.hpp>
#include <ResourceHolder.hpp>
#include <ResourceIdentifiers.hpp>
#include <gamestates/StateStack.hpp>

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>
#include <string>


class Application
{
public:
    sf::RenderWindow            mWindow;
    bool                        mDisplayStats;
    TextureHolder               mTextures;
    FontHolder                  mFonts;

private:
    static const sf::Time       TimePerFrame;
    StateStack                  mStateStack;

    sf::Text                    mStatisticsText;
    sf::Time                    mStatisticsUpdateTime;
    std::size_t                 mStatisticsNumFrames;

public:

                                Application();
                                ~Application();

    void                        Run();
    void                        Init();

private:
    void                        ProcessInput();
    void                        Update(sf::Time dt);
    void                        Render();

    void                        UpdateStatistics(sf::Time dt);
    void                        RegisterStates();
};
#endif // APPLICATION_HPP
