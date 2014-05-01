#include "Mech.h"
#include "ResourceHolder.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

TextureID toTextureID(Mech::Type type)
{
	switch (type)
	{
	case Mech::Type::Player:
		return TextureID::PlayerMech;
		break;
	case Mech::Type::Enemy:
		return TextureID::PlayerMech;
		break;
	default:
		return TextureID::PlayerMech;
		break;
	}
}

Mech::Mech(Type type, const TextureHolder& textures)
: mType(type)
, mSprite(textures.get(toTextureID(type)))
{
	sf::FloatRect bounds = mSprite.getLocalBounds();
	mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

//void Mech::selfUpdate(sf::Time dt)
//{
//	//Update legs here
//}

void Mech::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}

unsigned int Mech::getCategory() const
{
//Calling parent function instead of this function????
	switch (mType)
	{
	case Mech::Type::Player:
		return Category::PlayerMech;
		break;
	case Mech::Type::Enemy:
		return Category::EnemyMech;
		break;
	default:
		return Category::Unknown;
		break;
	}
}