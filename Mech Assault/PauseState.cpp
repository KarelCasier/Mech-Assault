#include "PauseState.h"

#include "ResourceHolder.h"
#include "Utility.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

PauseState::PauseState(StateStack& stack, Context context)
: State(stack, context)
{
	mPausedText.setFont(context.fonts->get(FontID::Main));
	centerOrigin(mPausedText);
	mPausedText.setCharacterSize(40);
	mPausedText.setColor(sf::Color::White);
	mPausedText.setPosition(context.window->getView().getSize() / 2.f);
	mPausedText.setString("PAUSED");

	mInstructionText.setFont(context.fonts->get(FontID::Main));
	centerOrigin(mInstructionText);
	mInstructionText.setCharacterSize(20);
	mInstructionText.setColor(sf::Color::White);
	mInstructionText.setPosition(mPausedText.getPosition().x, mPausedText.getPosition().y + mPausedText.getGlobalBounds().height + mInstructionText.getGlobalBounds().height + 10);
	mInstructionText.setString("Press Escape to continue /n Press Backspace to exit");

}

void PauseState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(sf::Vector2f(window.getSize()));

	window.draw(backgroundShape);
	window.draw(mPausedText);
	window.draw(mInstructionText);
}

bool PauseState::update(sf::Time dt)
{
	return false; //No background updates
}

bool PauseState::handleEvent(const sf::Event& event)
{
	if (event.key.code == sf::Keyboard::Escape)
	{
		requestStackPop();
	}

	if (event.key.code == sf::Keyboard::BackSpace)
	{
		requestStateClear();
		requestStackPush(StateID::Menu);
	}

	return false; //No background events handled
}