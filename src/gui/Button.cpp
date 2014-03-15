#include <gui/Button.hpp>
#include <Utility.hpp>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace GUI
{

    Button::Button(const FontHolder& fonts, const TextureHolder& textures)
    : mCallback()
    , mSprite(textures.Get(Textures::Buttons))
    , mText("", fonts.Get(Fonts::Main), 24)
    , mIsToggle(false)
    {
        changeTexture(Normal);

        sf::FloatRect bounds = mSprite.getLocalBounds();
        mText.setPosition(bounds.width / 2.0f, bounds.height / 2.0f);
    }

    void Button::setCallBack(Callback callback)
    {
        mCallback = std::move(callback);
    }

    void Button::setText(const std::string& text)
    {
        mText.setString(text);
        centerOrigin(mText);
    }

    void Button::setText(const std::string& text, int charSize)
    {
        mText.setString(text);
        mText.setCharacterSize(charSize);

        centerOrigin(mText);
    }

    void Button::setToggle(bool flag)
    {
        mIsToggle = flag;
    }

    bool Button::isSelectable() const
    {
        return true;
    }

    void Button::select()
    {
        Component::select();

        changeTexture(Selected);
    }

    void Button::deselect()
    {
        Component::deselect();

        changeTexture(Normal);
    }

    void Button::activate()
    {
        Component::activate();

        //if we are toggle then we should show that the button is pressed and thus toggled
        if(mIsToggle)
        {
            changeTexture(Pressed);
        }

        if(mCallback)
        {
            mCallback();
        }

        //if we are not a toggle then deactivate the button since we are just momentarily activate
        if(!mIsToggle)
        {
            deactivate();
        }
    }

    void Button::deactivate()
    {
        Component::deactivate();

        if(mIsToggle)
        {
            //reset texture to right one depending on if we are selected or not
            if(isSelected())
            {
                changeTexture(Selected);
            }
            else
            {
                changeTexture(Normal);
            }
        }
    }

    void Button::handleEvent(const sf::Event&)
    {

    }

    void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        target.draw(mSprite, states);
        target.draw(mText, states);
    }

    void Button::changeTexture(Type buttonType)
    {
        sf::IntRect textureRect(0, 50*buttonType, 200, 50);
        mSprite.setTextureRect(textureRect);
    }
}
