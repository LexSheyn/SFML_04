#include "stdafx.h"
#include "Player.h"

//Private functions
void Player::initVariables()
{
	this->animationState = PLAYER_ANIMATION_STATES::IDLE; //It can be used just like 'IDLE'
}

void Player::initTexture(std::string file_path)
{
	if (!this->textureSheet.loadFromFile(file_path))
	{
		std::cout << "ERROR::Player::Could not load texture: " << file_path << "\n";
	}
}

void Player::initSprite(sf::Texture& texture_name)
{
	this->sprite.setTexture(texture_name);
	this->currentFrame = sf::IntRect(0, 0, 40, 50);

	this->sprite.setTextureRect(this->currentFrame);
	this->sprite.setScale(3.f, 3.f);
}

void Player::initAnimations()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Player::initPhysics()
{
	this->velocityMax = 10.f;
	this->velocityMin = 1.f;
	this->acceleration = 2.f;
	this->drag = 0.88f;
	this->gravity = 4.f;
	this->velocityMaxY = 15.f;
}


//Constructors and Distructors
Player::Player()
{
	this->initVariables();
	this->initTexture("Textures/Player/player_sheet.png"); //Should use "../" before file path for compiled game to run it without VS2019
	this->initSprite(this->textureSheet);
	this->initAnimations();
	this->initPhysics();
}

Player::~Player()
{

}

//Accessors
const bool Player::getAnimationSwitch()
{
	bool animation_switch = this->animationSwitch;

	if (this->animationSwitch == true)
	{
		this->animationSwitch = false;
	}

	return animation_switch;
}

const sf::Vector2f Player::getPosition() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getGlobalBounds() const
{
	return this->sprite.getGlobalBounds();
}

//Modifiers
void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::resetVelocityY()
{
	this->velocity.y = 0.f;
}

//Functions
void Player::resetAnimationTimer()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Player::move(const float dir_x, const float dir_y)
{
	//Acceleration
	this->velocity.x += dir_x * this->acceleration;

	//Limiting velocity
	if (std::abs(this->velocity.x) > this->velocityMax)
	{
		this->velocity.x = this->velocityMax * ((this->velocity.x < 0.f) ? -1.f : 1.f);
	}
}

void Player::updatePhysics()
{
	//Gravity
	this->velocity.y += 1.f * this->gravity;

	//Limiting gravity
	if (std::abs(this->velocity.y) > this->velocityMaxY)
	{
		this->velocity.y = this->velocityMaxY * ((this->velocity.y < 0.f) ? -1.f : 1.f);
	}

	//Deceleration
	this->velocity *= this->drag;

	//Limiting deceleration
	if (std::abs(this->velocity.x) < this->velocityMin)
	{
		this->velocity.x = 0.f;
	}

	if (std::abs(this->velocity.y < this->velocityMin))
	{
		this->velocity.y = 0.f;
	}

	this->sprite.move(this->velocity);
}

void Player::updateMovement()
{
	this->animationState = PLAYER_ANIMATION_STATES::IDLE;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) //Left
	{
		this->move(-1.f, 0.f);
		this->animationState = PLAYER_ANIMATION_STATES::MOVING_LEFT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) //Right
	{
		this->move(1.f, 0.f);
		this->animationState = PLAYER_ANIMATION_STATES::MOVING_RIGHT;
	}

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) //Up
	//{
	//	this->sprite.move(0.f, -1.f);
	//}
	//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) //Down
	//{
	//	this->sprite.move(0.f, 1.f);
	//}
}

void Player::updateAnimations()
{
	if (this->animationState == PLAYER_ANIMATION_STATES::IDLE)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f || this->getAnimationSwitch() == true)
		{
			this->currentFrame.top = 0;
			this->currentFrame.left += 40;

			if (this->currentFrame.left >= 160)
			{
				this->currentFrame.left = 0;
			}

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animationState == PLAYER_ANIMATION_STATES::MOVING_RIGHT)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f)
		{
			this->currentFrame.top = 51;
			this->currentFrame.left += 40;

			if (this->currentFrame.left >= 360)
			{
				this->currentFrame.left = 0;
			}

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
		this->sprite.setScale(3.f, 3.f);
		this->sprite.setOrigin(0.f, 0.f);
	}
	else if (this->animationState == PLAYER_ANIMATION_STATES::MOVING_LEFT)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f)
		{
			this->currentFrame.top = 51;
			this->currentFrame.left += 40;

			if (this->currentFrame.left >= 360)
			{
				this->currentFrame.left = 0;
			}

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
		this->sprite.setScale(-3.f, 3.f);
		this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 3.f, 0.f);
	}
	else
	{
		this->animationTimer.restart();		
	}
}

void Player::update()
{
	this->updateMovement();
	this->updateAnimations();
	this->updatePhysics();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);

	sf::CircleShape circle;
	circle.setFillColor(sf::Color::Red);
	circle.setRadius(5.f);
	circle.setPosition(this->sprite.getPosition());

	target.draw(circle);
}