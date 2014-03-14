#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <sstream>

namespace sf
{
    class Sprite;
    class Text;
}

//since std::to_string doesn't work on MinGw we have to implement our own
template <typename T>
std::string toString(const T& value);

void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& text);

#include <Utility.inl>

#endif // UTILITY_HPP
