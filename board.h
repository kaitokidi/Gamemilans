/**********board.h**********/

#ifndef BOARD
#define BOARD
 
#include "aux.h" 
#include <queue>
#include <vector>
#include <cstdlib>
#include <iostream>
#include "SFML/Graphics.hpp"

//#define BOARD_X_SIZE 9
//#define BOARD_Y_SIZE 9

class Board{
  
  public:
	//Constructor
	Board(sf::RenderWindow &window_g);

	//Destructor
	~Board();
 
	void draw();
	void restart();
	int fixed(int k);
	int fixed(int k, bool useless); 

	void build_wall (int x, int y);
	void change_wall (int x, int y);
	bool is_wall_zone (int x, int y);
	bool is_full_wall (int x, int y);
	void unbuild_wall (int x, int y);
	bool is_empty_wall (int x, int y);
	void delete_player (int x, int y);
	bool is_full_ground (int x, int y);
	void print_actual_player(playerenum aplayer);
	void draw_wall  (int x, int y, bool vertical);
	void undraw_wall (int x, int y, bool vertical);
	bool not_a_wall_between_y(int y, int lasty, int x);
	bool not_a_wall_between_x(int x, int lastx, int y);
	void draw_player   (int x, int y, playerenum player);
	bool legitmove     (int origx, int origy, int destx, int desty);
	int getStepsToWin(int px, int py, int obj, std::queue<sf::Vector3i>& cua, std::vector < std::vector <bool> >& m);

	//this function is a sad one so i leave it alone
	void end_the_game (playerenum winner);

  private:
	  
	sf::RenderWindow &window_game;
	int costat, delay;
	float windowHeight, windowWidth;

	sf::Sprite sprite;

	sf::Texture* ptex;
	
	sf::Texture texture;
	sf::Texture fullwall;
	sf::Texture winlove;
	sf::Texture winunlove;
	sf::Texture emptywall;
	sf::Texture fullground;
	sf::Texture emptyground;
	sf::Texture firstplayer;
	sf::Texture secondplayer;
	sf::Texture animatedfirstplayer;

	tile_type ground [BOARD_X_SIZE+BOARD_X_SIZE-1][BOARD_Y_SIZE+BOARD_Y_SIZE-1];
};
#endif