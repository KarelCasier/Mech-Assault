#pragma once
#include "Entity.h"
#include "ResourceIdentifiers.h"

#include <SFML/Graphics/Sprite.hpp>

class Mech : public Entity
{
public:
	enum class Type
	{
		Player,
		Enemy,
	};

public:
							Mech(Mech::Type type, const TextureHolder& textures);
	virtual unsigned int	getCategory() const;

private:
	virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	//virtual void			selfUpdate(sf::Time dt);

private:
	Mech::Type				mType;
	sf::Sprite				mSprite;

};