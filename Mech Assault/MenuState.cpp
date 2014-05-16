#include "MenuState.h"
#include "Utility.hpp"
#include "ResourceHolder.h"

#include <SFML/Graphics/RenderWindow.hpp>

MenuState::MenuState(StateStack& stack, Context context)
: State(stack, context)
{
	sf::Text playOption;
	playOption.setFont(context.fonts->get(FontID::Main));
	playOption.setString("Play");
	centerOrigin(playOption);
	playOption.setPosition(context.window->getView().getSize() / 2.f);

	sf::Text exitOption;
	exitOption.setFont(context.fonts->get(FontID::Main));
	exitOption.setString("Exit");
	centerOrigin(exitOption);
	exitOption.setPosition(context.window->getView().getSize().x / 2.f, playOption.getPosition().y + playOption.getGlobalBounds().height * 2);

	mOptions.push_back(playOption);
	mOptions.push_back(exitOption);

	updateOptionsText();
}

void MenuState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	for (sf::Text& text : mOptions)
		window.draw(text);
}

bool MenuState::update(sf::Time dt)
{

	return true;
}

bool MenuState::handleEvent(const sf::Event& event)
{
	if (event.key.code == sf::Keyboard::Up)
	{
		if (mOptionIndex > 0)
			mOptionIndex--;
		else
			mOptionIndex = mOptions.size() - 1;

		updateOptionsText();
	}
	else if (event.key.code == sf::Keyboard::Down)
	{
		if (mOptionIndex < mOptions.size() - 1)
			mOptionIndex++;
		else
			mOptionIndex = 0;

		updateOptionsText();
	}

	if (event.key.code == sf::Keyboard::Return)
	{
		if (mOptionIndex == Play)
		{
			requestStackPop();
			requestStackPush(StateID::Game);
		}
		else if (mOptionIndex == Exit)
		{
			requestStackPop();
		}
	}
	
	return true;
}

void MenuState::updateOptionsText()
{
	if (mOptions.empty())
		return;

	//White all texts
	for (sf::Text& text : mOptions)
		text.setColor(sf::Color::White);

	//Red selected text
	mOptions[mOptionIndex].setColor(sf::Color::Red);
}