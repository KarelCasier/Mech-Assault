#pragma once
//#include <SFML\Graphics.hpp>
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "SceneNode.h"
#include "CommandQueue.h"
#include "Command.hpp"
#include "SpriteNode.h"
#include "Mech.h"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <array>
#include <queue>

// Forward declaration
namespace sf
{
	class RenderWindow;
}

class World
	: private sf::NonCopyable
{
public:
	explicit		World(sf::RenderWindow& window);
	void			update(sf::Time dt);
	void			draw();

	CommandQueue&	getCommandQueue();

private:
	void			loadTextures();
	void			buildScene();

private:
	enum Layer
	{
		Floor,
		Main,
		LayerCount
	};

private:
	sf::RenderWindow&					mWindow;
	sf::View							mWorldView;
	TextureHolder						mTextures;

	SceneNode							mSceneGraph;
	std::array<SceneNode*, LayerCount>	mSceneLayers;
	CommandQueue						mCommandQueue;

	sf::FloatRect						mWorldBounds;
	sf::Vector2f						mSpawnPosition;
	Mech*								mPlayerMech;
	SpriteNode*							mFloor;
};
