#pragma once

enum PLAYER_ANIMATION_STATES
{
	IDLE = 0,
	MOVING_LEFT, //equals unsigned 1
	MOVING_RIGHT, //equals unsigned 2 and so on...
	JUMPING,
	FALLING,
};

class Player
{
private:

	//Sprite
	sf::Sprite sprite;
	sf::Texture textureSheet;
	sf::Clock animationTimer;

	//Animation
	short animationState;
	sf::IntRect currentFrame;
	bool animationSwitch;
	
	//Physics
	sf::Vector2f velocity;
	float velocityMax;
	float velocityMin;
	float acceleration;
	float drag;
	float gravity;
	float velocityMaxY;

	//Core


	//Private functions
	void initVariables();
	void initTexture(std::string file_path);
	void initSprite(sf::Texture& texture_name);
	void initAnimations();
	void initPhysics();

public:

	//Constructors and Distructors
	Player();
	virtual ~Player();

	//Accessors
	const bool getAnimationSwitch();
	const sf::Vector2f getPosition() const;
	const sf::FloatRect getGlobalBounds() const;

	//Modifiers
	void setPosition(const float x, const float y);
	void resetVelocityY();

	//Functions
	void resetAnimationTimer();
	void move(const float dir_x, const float dir_y);

	void updatePhysics();
	void updateMovement();
	void updateAnimations();

	void update();
	void render(sf::RenderTarget& target);
};

