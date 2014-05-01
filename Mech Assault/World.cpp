#include "World.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include <algorithm>
#include <cmath>

#include "iostream"

World::World(sf::RenderWindow& window)
: mWindow(window)
, mWorldView(window.getDefaultView())
, mTextures()
, mSceneGraph()
, mSceneLayers()
, mWorldBounds(0.f, 0.f, 1000.f, 1000.f)
, mSpawnPosition(mWorldBounds.width / 2.f, mWorldBounds.height / 2.f)
, mPlayerMech(nullptr)
{
	loadTextures();
	buildScene();

	// Prepare the view
	mWorldView.setCenter(mSpawnPosition);
}

void World::update(sf::Time dt)
{
	//Center view on player
	mWorldView.setCenter(mPlayerMech->getWorldPosition());

	//Forward commands to scene graph
	while (!mCommandQueue.isEmpty())
		mSceneGraph.onCommand(mCommandQueue.pop(), dt);

	// Apply movements
	mSceneGraph.update(dt);
}

void World::draw()
{
	mWindow.setView(mWorldView);
	mWindow.draw(mSceneGraph);
}

CommandQueue& World::getCommandQueue()
{
	return mCommandQueue;
}

void World::loadTextures()
{
	//Player
	mTextures.load(TextureID::PlayerMech, "assets/textures/PlayerMech.png");

	mTextures.load(TextureID::Ground, "assets/textures/darkPurple.png");
}

void World::buildScene()
{
	// Initialize the different layers
	for (std::size_t i = 0; i < LayerCount; ++i)
	{
		SceneNode::Ptr layer(new SceneNode());
		mSceneLayers[i] = layer.get();

		mSceneGraph.attachChild(std::move(layer));
	}

	// Prepare the tiled background
	sf::Texture& backTexture = mTextures.get(TextureID::Ground);
	sf::IntRect backTextureRect(mWorldBounds);
	backTexture.setRepeated(true);

	// Add the background sprite to the scene
	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(backTexture, backTextureRect));
	backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
	mFloor = backgroundSprite.get();
	mSceneLayers[Floor]->attachChild(std::move(backgroundSprite));

	// Add player's aircraft
	std::unique_ptr<Mech> Player(new Mech(Mech::Type::Player, mTextures));
	mPlayerMech = Player.get();
	mPlayerMech->setPosition(mSpawnPosition);
	mSceneLayers[Main]->attachChild(std::move(Player));

	//mPlayerMech->enableFriction();
	//mPlayerMech->enableGravity();
}