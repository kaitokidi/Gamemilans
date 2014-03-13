#include "board.h" 
 
//Constructor
Board::Board(sf::RenderWindow &window) :window_game(window) {
	float scalex, scaley;
	
	winlove.loadFromFile("pics/gril.png");
	fullwall.loadFromFile("pics/fullwall.png"); 
	secondplayer.loadFromFile("pics/love.png");
	firstplayer.loadFromFile("pics/unlove.png");
	winunlove.loadFromFile("pics/winunlove.png");
	emptywall.loadFromFile("pics/emptywall.png");
	emptyground.loadFromFile("pics/emptyground.png");
	
	
	ptex = NULL;
	delay = delay = 10;
	windowWidth = window_game.getSize().x;
	windowHeight = window_game.getSize().y;
	costat = (windowHeight - (delay + delay))/12;	
	
	for(int i = 0; i < BOARD_X_SIZE+BOARD_X_SIZE-1; ++i) {
		if(i%2 == 1) 
			for(int j = 0; j < BOARD_Y_SIZE+BOARD_Y_SIZE-1; ++j){ 
				if(j%2 == 1 and i != 0 and j != 0) ground[i][j] = full_wall;
				else ground[i][j] = empty_wall;
			}
		else { 
			for(int j = 0; j < BOARD_Y_SIZE+BOARD_Y_SIZE-1; ++j){
				if(j%2 == 1) ground[i][j] = empty_wall;
				else ground[i][j] = empty_ground;
			}
		}
	}
	build_wall(8, 1);
	build_wall(8, 15);
}

//Restart
void Board::restart(){
	
	for(int i = 0; i < BOARD_X_SIZE+BOARD_X_SIZE-1; ++i) {
		if(i%2 == 1) 
			for(int j = 0; j < BOARD_Y_SIZE+BOARD_Y_SIZE-1; ++j){ 
				if(j%2 == 1 and i != 0 and j != 0) ground[i][j] = full_wall;
				else ground[i][j] = empty_wall;
			}
		else { 
			for(int j = 0; j < BOARD_Y_SIZE+BOARD_Y_SIZE-1; ++j){
				if(j%2 == 1) ground[i][j] = empty_wall;
				else ground[i][j] = empty_ground;
			}
		}
	}

	build_wall(8, 1);
	build_wall(8, 15);
}

//Destructor
Board:: ~Board(){};

//Return true if there is a wall on the position x, y, of the board
bool Board::is_wall_zone (int x, int y){ /*done*/
	return (ground[x][y] == empty_wall or ground[x][y] == full_wall); 
}  

//Return true if there is a full wall on the position x, y, of the board
bool Board::is_full_ground (int x, int y){ /*done*/
	return (ground[x][y] == full_ground);
}

//Return true if there is a full wall on the position x, y, of the board
bool Board::is_full_wall (int x, int y){ /*done*/
	return (ground[x][y] == full_wall);
}

//Return true if there is an empty wall on the position x, y, of the board
bool Board::is_empty_wall (int x, int y){ /*done*/
	return (ground[x][y] == empty_wall); 
}

//Changes the actual state to either empty or full wall in the position x, y, of the board
void Board::change_wall(int x, int y){ /*done*/
	if (ground[x][y] == empty_wall) ground[x][y] = full_wall;
	else ground[x][y] = empty_wall;
}

//For a given x, return true if there are no walls between the initial y and the final y
bool Board::not_a_wall_between_y (int inity, int lasty, int x){ /*done*/
	int y, z;
	if(inity < lasty) { y = inity; z = lasty; }
	else { y = lasty; z = inity; }
	for (int i = y; i < z; ++i){
		if((ground[x][i] == full_wall)) return false;
	}
	return true;
}

//For a given y, return true if there are no walls between the initial x and the final x
bool Board::not_a_wall_between_x (int initx, int lastx, int y){ /*done*/
	int x, z;
	if(initx < lastx) { x = initx; z = lastx; }
	else { x = lastx; z = initx; }
	for (int i = x; i < z; ++i){
		if((ground[i][y] == full_wall)) return false;
	}
	return true;
}
    
//Convert the input of the mouse in a position on the wall
int Board::fixed (int k){ /*           PER IAs*/
/*
	int b = costat + costat/3;
	int fk = (k-delay)/b;

	int elemPos = fk*2;
	if((k-delay)%b > costat) elemPos++;

	return elemPos;*/ return k;
}

int Board::fixed (int k, bool useless){

	int b = costat + costat/3;
	int fk = (k-delay)/b;

	int elemPos = fk*2;
	if((k-delay)%b > costat) elemPos++;

	return elemPos;
}
   
//Display a player on the given position and changes the board table and the player position
void Board::draw_player (int x, int y, playerenum player){ /*done*/
	ptex = &emptyground;
	
	int pos_x, pos_y;
	float scalex, scaley;
	ground[x][y] = full_ground;

	pos_x = delay + (x/2)*costat + (x/2)*(costat/3);
	pos_y = delay + (y/2)*costat + (y/2)*(costat/3);
	scalex = costat/float(ptex->getSize().x);
	scaley = costat/float(ptex->getSize().y);

	sprite.setTexture(*ptex);
	sprite.setPosition(pos_x, pos_y);
	sprite.setScale(scalex, scaley);
	window_game.draw(sprite);
	
	if(player == first) ptex = &firstplayer;
	else ptex = &secondplayer;
	sprite.setTexture(*ptex);
	sprite.setPosition(pos_x, pos_y);
	scalex = costat/float(ptex->getSize().x);
	scaley = costat/float(ptex->getSize().y);
	sprite.setScale(scalex, scaley);
	window_game.draw(sprite);
	
	window_game.display();

}

//Set the x, y, position of the board to empty_ground 
void Board::delete_player(int x, int y){ /*done*/
	ptex = &emptyground;
	
	int pos_x, pos_y;
	float scalex, scaley;
	ground[x][y] = empty_ground;
	pos_x = delay + (x/2)*costat + (x/2)*(costat/3);
	pos_y = delay + (y/2)*costat + (y/2)*(costat/3);
	scalex = costat/float(ptex->getSize().x);
	scaley = costat/float(ptex->getSize().y);
	
	sprite.setTexture(*ptex);
	sprite.setPosition(pos_x, pos_y);
	sprite.setScale(scalex, scaley);
	window_game.draw(sprite);
	window_game.display();
	
}

//Return true if there are no walls after the wall you want to move
bool Board::legitmove (int origx, int origy, int destx, int desty){
	if(origx < 0 || origy < 0 || destx < 0 || desty < 0)return false;
	if(origx > 16 or origy > 16 or destx > 16 or desty > 16)return false;
	if(origx == destx) {
		if(desty > origy) return (ground[origx][desty-1] == empty_wall);
		if(desty < origy) return (ground[origx][origy-1] == empty_wall);
	}
	else if(origy == desty) {
		if(destx > origx) return (ground[destx-1][origy] == empty_wall);
		if(destx < origx) return (ground[origx-1][origy] == empty_wall);
	}
	return true;
}

//Draws the visible board with the values of the board table
void Board::draw(){ /*done*/

	int pos_x , pos_y; 
	float scalex, scaley;
	bool do_print = false;
	
	for(int x = 0; x < 17; ++x){
		for(int y = 0; y < 17; ++y){
			//Set Values
			if(ground[x][y] == empty_ground){							//ground
				pos_x = delay + (x/2)*costat + (x/2)*(costat/3);
				pos_y = delay + (y/2)*costat + (y/2)*(costat/3);
				do_print = true;
				ptex = &emptyground;
				scalex = costat/float(ptex->getSize().x);
				scaley = costat/float(ptex->getSize().y);
			}
			else if(x%2 == 1 and y%2 == 1 and (x != 0) and (y != 0)) {	//murs fixes
				pos_x = delay + (x/2+1)*costat + (x/2)*(costat/3);
				pos_y = delay + (y/2+1)*costat + (y/2)*(costat/3);
				do_print = true;
				ptex = &fullwall;
				scalex = (costat/3)/float(ptex->getSize().x);
				scaley = (costat/3)/float(ptex->getSize().y);
			}
			else if(ground[x][y] == full_wall){ 						//murs construits
				if(x%2 == 0){										//fullwallvert
					pos_x = delay + (x/2)*costat + (x/2)*(costat/3);
					pos_y = delay + (y/2+1)*costat + (y/2)*(costat/3);
					do_print = true;
					ptex = &fullwall;
					scalex = (costat)/float(ptex->getSize().x);
					scaley = (costat/3)/float(ptex->getSize().y);
				}
				if(x%2 == 1){										//fullwallhor
					pos_x = delay + (x/2+1)*costat + (x/2)*(costat/3);
					pos_y = delay + (y/2)*costat + (y/2)*(costat/3);
					do_print = true;
					ptex = &fullwall;
					scalex = (costat/3)/float(ptex->getSize().x);
					scaley = (costat)/float(ptex->getSize().y);
				}
			}
			else if(ground[x][y] == empty_wall){						//empty wall
				if(x%2 == 0){										//verticalemptywall
					pos_x = delay + (x/2)*(costat) + (x/2)*(costat/3);
					pos_y = delay + (y/2+1)*costat + (y/2)*(costat/3);
					do_print = true;
					ptex = &emptywall;
					scalex = (costat)/float(ptex->getSize().x);
					scaley = (costat/3)/float(ptex->getSize().y);
				}
				if(x%2 == 1){										//horitzontalemptywall
					pos_x = delay + (x/2+1)*costat + (x/2)*(costat/3);
					pos_y = delay + (y/2)*costat + (y/2)*(costat/3);
					do_print = true;
					ptex = &emptywall;
					scalex = (costat/3)/float(ptex->getSize().x);
					scaley = (costat)/float(ptex->getSize().y);
				}
			}
			//print with values
			if(do_print){
				do_print = false;
				sprite.setTexture(*ptex);
				sprite.setPosition(pos_x, pos_y);
				sprite.setScale(scalex, scaley);
				window_game.draw(sprite);
			}
		}
	}
	//and display
	window_game.display();
}

//Call to the function draw_wall with the boolean value which selects either if vertical or horizontal
void Board::build_wall (int x, int y){  /*done*/
	bool vertical = true;
	if(x%2 == 1) vertical = false;

	if(vertical){
		draw_wall (x, y, true);
	}
	else {
		draw_wall (x, y, false);
	}
}

//Changes the value of the position x, y, on the board to full ground
void Board::draw_wall(int x, int y, bool vertical){  /*done*/
	ground[x][y] = full_wall;
}

//Changes the value of the position x, y, on the board to empty ground
void Board::unbuild_wall(int x, int y){ /*done*/
	bool vertical = (x%2 != 1);

	if(vertical){
		undraw_wall(x, y, true);
	}
	else {
		undraw_wall(x, y, false);
	}
}

//Changes the value of the position x, y, on the board to empty ground
void Board::undraw_wall(int x, int y, bool vertical){ /*done*/
	ground[x][y] = empty_wall;
}

//USELESS
void Board::print_actual_player(playerenum aplayer){
//no se on es fa servir, estaria bé buscar-ho i borrar-ho
}

//Displays the end_of_game 'animation'
void Board::end_the_game (playerenum winner){  /*done*/
	
	if (winner == second) ptex = &winlove;
	else ptex = &winunlove;

	int pos_x , pos_y; 
	float scalex, scaley;
	bool do_print = false;
	
	for(int x = 0; x < 17; ++x){
		for(int y = 0; y < 17; ++y){
			if(ground[x][y] == empty_ground or ground[x][y] == full_ground){
				pos_x = delay + (x/2)*costat + (x/2)*(costat/3);
				pos_y = delay + (y/2)*costat + (y/2)*(costat/3);
				do_print = true;
				scalex = costat/float(ptex->getSize().x);
				scaley = costat/float(ptex->getSize().y);
			}
			if(do_print){
				do_print = false;
				sprite.setTexture(*ptex);
				sprite.setScale(scalex, scaley);
				sprite.setPosition(pos_x, pos_y);
				window_game.draw(sprite);

				sf::Clock clock;
				sf::Time timer = clock.getElapsedTime();
				while (clock.getElapsedTime().asSeconds() < 0.005) { }
				clock.restart();

				window_game.display();
			}
		}
	}
}

int Board::getStepsToWin(int px, int py, int obj, std::queue<sf::Vector3i>& cua, std::vector < std::vector <bool> >& visitat){
	sf::Vector3i pos;
	sf::Vector3i npos;

	visitat[px][py] = true;
	while(!cua.empty()){

		pos = cua.front();
		cua.pop();
		visitat[pos.x][pos.y] = true;
	
		if(pos.y == obj) return pos.z;

		for(int i = 0; i < 4; ++i){
			npos.x = pos.x+movx[i];
			npos.y = pos.y+movy[i];

			if((legitmove(pos.x, pos.y, npos.x, npos.y)) and (not is_wall_zone(npos.x, npos.y) and (not (visitat[npos.x][npos.y])))) {
				npos.z = pos.z+1;
				cua.push(npos);
			}
		}
	}
	return -1;
}

