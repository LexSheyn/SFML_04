#include "stdafx.h"
#include "Game.h"

//Private functions
void Game::initWindow()
{
	this->window.create(sf::VideoMode(1120, 630), "Game 04", sf::Style::Close | sf::Style::Titlebar);
	this->window.setFramerateLimit(60);
}

void Game::initPlayer()
{
	this->player = new Player();
}


//Constructors and Distructors
Game::Game()
{
	this->initWindow();
	this->initPlayer();
}

Game::~Game()
{
	//Deleting player
	delete this->player;
}


//Accessors
const sf::RenderWindow& Game::getWindow() const
{
	return this->window;
}

//Modifiers


//Functons
void Game::updatePollEvents()
{
	//Polling window events
	while (this->window.pollEvent(this->ev))
	{
		if (this->ev.type == sf::Event::Closed)
		{
			this->window.close();
		}
		else if (this->ev.type == sf::Event::KeyPressed && this->ev.key.code == sf::Keyboard::Escape)
		{
			this->window.close();
		}

		if 
		(
			this->ev.type == sf::Event::KeyReleased &&
			(
				this->ev.key.code == sf::Keyboard::A ||
				this->ev.key.code == sf::Keyboard::D ||
				this->ev.key.code == sf::Keyboard::W ||
				this->ev.key.code == sf::Keyboard::S
			)
		)
		{
			this->player->resetAnimationTimer();
		}
	}
}

void Game::updatePlayer()
{
	this->player->update();
}

void Game::updateCollision()
{
	//Collision bottom of the screen
	if (this->player->getPosition().y + this->player->getGlobalBounds().height > this->window.getSize().y)
	{
		this->player->resetVelocityY();

		this->player->setPosition
		(
			this->player->getPosition().x,
			this->window.getSize().y - this->player->getGlobalBounds().height
		);
	}
}

void Game::update()
{
	this->updatePlayer();
	this->updateCollision();
}

void Game::renderPlayer()
{
	this->player->render(this->window);
}

void Game::render()
{
	//Clearing window
	this->window.clear(); //using 'sf::Color::Black' by default

	//Rendering player
	this->renderPlayer();

	//Displaying new frame
	this->window.display();
}