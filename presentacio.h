#ifndef PRESENT
#define PRESENT
 
#include "aux.h" 
#include <queue>
#include <vector>
#include <cstdlib>
#include <iostream>
#include "SFML/Graphics.hpp"


class Presentacio{
  
public:

	//Constructor
	Presentacio(sf::RenderWindow &window_g);
	//Destructor
	~Presentacio();
	//Event handler
	int handler();
	//Draws the first image
	void portada();
	//Draws the nth instructions image
	void inst(int n);
	//Get the walls player would like to play with
	void murs();
	//set the properties of the Text to be displayed
	void prepareText();

private:

	sf::RenderWindow &window_game;

	int delay;

	float windowHeight, windowWidth;

	sf::Sprite sprite;

	sf::Texture* ptex;

	sf::Texture Background;

	sf::Font font;

	sf::Text text;

	sf::String sentence;
};
#endif