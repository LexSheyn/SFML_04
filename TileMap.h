#pragma once

#include "Tile.h"

class TileMap
{
private:

	//Vector for tiles
	std::vector<std::vector<Tile*>> tiles;

	//Private functions

public:

	//Constructors and Distructors
	TileMap();
	virtual ~TileMap();

	//Accessors


	//Modifiers


	//Functions
	void addTile(unsigned x, unsigned y);
	void removeTile(unsigned x, unsigned y);

	void update();
	void render();
};

