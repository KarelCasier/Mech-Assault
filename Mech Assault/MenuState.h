#pragma once

#include "StateStack.hpp"
#include "State.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class MenuState : public State
{
public:
	MenuState(StateStack& stack, Context context);

	virtual void			draw();
	virtual bool			update(sf::Time dt);
	virtual bool			handleEvent(const sf::Event& event);

private:
	void					updateOptionsText();

private:
	enum OptionNames
	{
		Play,
		Exit,
	};

	std::vector<sf::Text>	mOptions;
	std::size_t				mOptionIndex;
};