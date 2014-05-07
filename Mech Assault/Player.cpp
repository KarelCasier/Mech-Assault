#include "Player.h"
#include "CommandQueue.h"
#include "Mech.h"

#include <map>
#include <string>
#include <algorithm>



struct MechMover
{
	MechMover(float vx, float vy)
	: velocity(vx, vy)
	{
	}

	void operator() (Mech& mech, sf::Time) const
	{
		mech.accelerate(velocity);
	}

	sf::Vector2f velocity;
};

Player::Player()
{
	//Set initial key bindings
	mKeyBinding[sf::Keyboard::A] = MoveLeft;
	mKeyBinding[sf::Keyboard::D] = MoveRight;
	mKeyBinding[sf::Keyboard::W] = MoveUp;
	mKeyBinding[sf::Keyboard::S] = MoveDown;

	//Set initial action bindings
	initializeActions();

	// Assign all categories to player's mech
	for (auto& pair : mActionBinding)
		pair.second.category = Category::PlayerMech;
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
	if (event.type == sf::Event::KeyPressed)
	{
		//Check if pressed key is mapped to action
		auto found = mKeyBinding.find(event.key.code);
		if (found != mKeyBinding.end() && !isRealtimeAction(found->second))
			commands.push(mActionBinding[found->second]);
	}
}

void Player::handleRealtimeInput(CommandQueue& commands)
{
	//Go through all assigned keys and check if any are pressed
	for (auto pair : mKeyBinding)
	{
		//If key is pressed, lookup action and trigger the corresponding command
		if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
			commands.push(mActionBinding[pair.second]);
	}
}

void Player::assignKey(Action action, sf::Keyboard::Key key)
{
	// Remove all keys that already map to action
	for (auto itr = mKeyBinding.begin(); itr != mKeyBinding.end();)
	{
		if (itr->second == action)
			mKeyBinding.erase(itr++);
		else
			++itr;
	}

	// Insert new binding
	mKeyBinding[key] = action;
}

sf::Keyboard::Key Player::getAssignedKey(Action action) const
{
	for (auto pair : mKeyBinding)
	{
		if (pair.second == action)
			return pair.first;
	}

	return sf::Keyboard::Unknown;
}

void Player::initializeActions()
{
	const float playerSpeed = 20.f;

	mActionBinding[MoveLeft].action		= derivedAction<Mech>(MechMover(-playerSpeed, 0.f));
	mActionBinding[MoveRight].action	= derivedAction<Mech>(MechMover(+playerSpeed, 0.f));
	mActionBinding[MoveUp].action		= derivedAction<Mech>(MechMover(0.f, -playerSpeed));
	mActionBinding[MoveDown].action		= derivedAction<Mech>(MechMover(0.f, +playerSpeed));
}

bool Player::isRealtimeAction(Action action)
{
	switch (action)
	{
	case MoveLeft:
	case MoveRight:
	case MoveUp:
	case MoveDown:
		return true;

	default:
		return false;
	}
}
