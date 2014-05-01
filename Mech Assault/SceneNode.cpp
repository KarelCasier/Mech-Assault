#include "SceneNode.h"
#include "Command.hpp"

#include <algorithm>
#include <cassert>

SceneNode::SceneNode()
: mChildren()
, mParent(nullptr)
{
}

void SceneNode::update(sf::Time dt)
{
	updateCurrent(dt);
	updateChildren(dt);
}

void SceneNode::updateCurrent(sf::Time dt)
{
	//Virtual function to be overridden by derived classes
}

void SceneNode::updateChildren(sf::Time dt)
{
	for (const Ptr& child : mChildren)
	{
		child->update(dt);
	}
}

void SceneNode::attachChild(Ptr child)
{
	child->mParent = this;
	mChildren.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode& child)
{
	//1 -> take surroundings by reference (i.e. child)
	//2 -> arguments to take in (i.e. elements of mChildren)
	//3 -> return type (could leave out as lambdas can automatically determine return type)
	//4 -> gets a raw pointer to p (i.e. not a unique_ptr)
	//5 -> compare address of the child to the pointer int mChildren
	//                                                             1    2         3               4          5
	auto found = std::find_if(mChildren.begin(), mChildren.end(), [&](Ptr& p) -> bool { return p.get() == &child; });
	//found now contains an iterator that points to the element found
	//Check if child is actually found
	assert(found != mChildren.end()); // If statement is false -> create a breakpoint // DEBUGING ONLY

	Ptr result = (std::move(*found)); //Transfer ownership
	(*found)->mParent = nullptr;
	mChildren.erase(found); //Since found is an iterator, if is easy to erase
	return result;
}

sf::Transform SceneNode::getWorldTransform() const
{
	sf::Transform transform = sf::Transform::Identity;

	for (const SceneNode* node = this; node != nullptr; node = node->mParent) //Loop up to the main sceneGraph applying the transforms
	{
		transform *= node->getTransform();
	}

	return transform;
}

sf::Vector2f SceneNode::getWorldPosition() const
{
	return getWorldTransform() * sf::Vector2f();
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform(); //Combines parent transforms and child transforms

	drawCurrent(target, states);
	drawChildren(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	//Virtual function to be overridden by derived classes
}

void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const Ptr& child : mChildren)
	{
		child->draw(target, states);
	}
}

void SceneNode::onCommand(const Command& command, sf::Time dt)
{
	//std::cout << command.category << " & " << getCategory() << std::endl;
	//Command current node, if category matches
	if (command.category & this->getCategory())
	{
		command.action(*this, dt);
	}

	for (Ptr& child : mChildren)
	{
		child->onCommand(command, dt);
	}
}

unsigned int SceneNode::getCategory() const
{
	return Category::Scene;
}