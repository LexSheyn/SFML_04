#pragma once
class Tile
{
private:

	//Sprite
	sf::Sprite sprite;

	//Variables
	const bool damaging;

	//Private functions

public:

	//Constructors and Distructors
	Tile(sf::Texture& texture_sheet, sf::IntRect texture_rect, bool damaging = false);
	virtual ~Tile();

	//Accessors
	const sf::FloatRect getGlobalBounds() const;

	//Modifiers


	//Functions
	void update();
	void render(sf::RenderTarget& target);
};

