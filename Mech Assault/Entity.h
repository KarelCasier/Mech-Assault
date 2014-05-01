#pragma once
#include "SceneNode.h"

class Entity : public SceneNode
{
public:
	void				setVelocity(sf::Vector2f vel);
	void				setVelocity(float x, float y);
	void				accelerate(sf::Vector2f velocity);
	void				accelerate(float vx, float vy);
	void				enableFriction();
	void				enableGravity();

	sf::Vector2f		getVelocity() const;

private:
	virtual void		updateCurrent(sf::Time dt);
	//virtual void		selfUpdate(sf::Time dt);

private:
	static const double	FRICTION;
	static const double	GRAVITY;

	float				mMaxSpeed;
	sf::Vector2f		mVelocity;
	float				mMaxFallSpeed;
	bool				hasFriction;
	bool				hasGravity;
};