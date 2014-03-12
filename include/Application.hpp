#ifndef APPLICATION_HPP
#define APPLICATION_HPP

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
private:
    static const sf::Time       TimePerFrame;

public:

                                Application();
                                ~Application();

    void                        Run();
    void                        Init();

private:
    void                        ProcessInput();
    void                        Update(sf::Time dt);
    void                        Render();
};
#endif // APPLICATION_HPP
