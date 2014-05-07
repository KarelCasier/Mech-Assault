#include "Entity.h"
#define _USE_MATH_DEFINES
#include <math.h>

const double Entity::FRICTION = 0.9;
const double Entity::GRAVITY = 200;

//Entity::Entity()
//: mMaxSpeed(500)
//, mMaxFallSpeed(200)
//, hasFriction(false)
//, hasGravity(false)
//{
//}

void Entity::setVelocity(sf::Vector2f velocity)
{
	mVelocity = velocity;
}

void Entity::setVelocity(float vx, float vy)
{
	mVelocity.x = vx;
	mVelocity.y = vy;
}

sf::Vector2f Entity::getVelocity() const
{
	return mVelocity;
}

void Entity::accelerate(sf::Vector2f velocity)
{
	mVelocity += velocity;
}

void Entity::accelerate(float vx, float vy)
{
	//std::cout << "Rotation: " << (this->getRotation() - 90) << std::endl;
	//std::cout << "X-Comp: " << v * (cos((this->getRotation() - 90) * M_PI / 180)) << std::endl;
	//std::cout << "Y-Comp: " << v * (sin((this->getRotation() - 90) * M_PI / 180)) << std::endl << std::endl;
	if (abs(mVelocity.x) < mMaxSpeed)
		mVelocity.x += vx * (cos((this->getRotation() - 90) * M_PI / 180)); //The -90 is to account for the reversal of the xy-plane
	//if (abs(mVelocity.y) < mMaxSpeed)
	mVelocity.y += vy * (sin((this->getRotation() - 90) * M_PI / 180));
}

void Entity::enableFriction()
{
	hasFriction = true;
}

void Entity::enableGravity()
{
	hasGravity = true;
}

void Entity::updateCurrent(sf::Time dt)
{
	if (hasFriction)
	{
		mVelocity.x *= FRICTION;
		mVelocity.y *= FRICTION;
	}
	if (hasGravity)
	{
		mVelocity.y += GRAVITY * dt.asSeconds();
	}
	move(mVelocity * dt.asSeconds());
}

//void Entity::selfUpdate(sf::Time dt)
//{
//	//Left blank to allow to be overridden
//}