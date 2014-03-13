#include "logica.h"
#include <iostream> 
#include <queue>

//Constructor
Logica::Logica (Board &boardRef): board(boardRef){ /*done*/
	actualplayer = first;
	players[first].pos_x = 8;
 	players[first].pos_y = 0;
	players[second].pos_x = 8;
	players[second].pos_y = 16;
	board.print_actual_player(actualplayer);
	board.draw_player (18, 0, actualplayer);
}

//Remake all the variables as beginning
void Logica::restart(){ /*done*/
	actualplayer = first;
	players[first].pos_x = 8;
	players[first].pos_y = 0;
	players[second].pos_x = 8;
	players[second].pos_y = 16;
	board.print_actual_player(actualplayer);
	board.draw_player (18, 0, actualplayer);

}

//Destructor
Logica::~Logica(){}

//React in the way it have to in function of where the user have clicked
bool Logica::click(int x, int y){
	bool acted = false;
	bool ret = false;
 	int fx = board.fixed(x);
 	int fy = board.fixed(y);

	if(board.is_wall_zone(fx, fy)){ 														// Clicat en una casella de mur
		std::vector< std::vector< bool> > visitat1 (17, std::vector < bool > (17, false));
		std::vector< std::vector< bool> > visitat2 (17, std::vector < bool > (17, false));
		if (board.is_empty_wall(fx,fy)) {
			board.build_wall(fx, fy);
			if ( have_a_way(first, visitat1, players[first].pos_x, players[first].pos_y) 
				and have_a_way(second, visitat2, players[second].pos_x, players[second].pos_y)) {
				acted = true;
			}
			else board.unbuild_wall(fx, fy);
		}
		board.draw();
	}  
	else { 																					// Clicat en una casella de player
		int posx = players[actualplayer].pos_x;
		int posy = players[actualplayer].pos_y;
		/* if el meu player esta al costat del clic, no hi ha un mur al mig,                  i no està ple */
		if( my_player_near(actualplayer, fx, fy) and board.legitmove(posx, posy, fx, fy) and not(board.is_full_ground(fx, fy))) {
			board.draw_player(fx,fy, actualplayer);
			board.delete_player(posx, posy);
			players[actualplayer].pos_x = fx;
			players[actualplayer].pos_y = fy;
			acted = true;
		}

		int initx, finx, inity, finy;
		if(fy > players[actualplayer].pos_y){
			finy = fy;
			inity = players[actualplayer].pos_y;
		}
		else {
			inity = fy;
			finy = players[actualplayer].pos_y;
		}
		if(fx > players[actualplayer].pos_x){
			finx = fx;
			initx = players[actualplayer].pos_x;
		}
		else {
			initx = fx;
			finx = players[actualplayer].pos_x;
		}

		//Si l'altre player està al costat del click
		if(my_player_near(next_player(actualplayer), fx, fy)){

			bool ok = true;
			/*salt en L*/
			// si no esta a la mateixa x ni y (no es un salt horitzontal ni vertical)
			if((fx != players[actualplayer].pos_x and fy != players[actualplayer].pos_y) 
				//i l'altre player està a dues caselles de distancia (1ground + 1mur)
				and (((abs(players[actualplayer].pos_x - players[next_player(actualplayer)].pos_x)) + (abs(players[actualplayer].pos_y - players[next_player(actualplayer)].pos_y))) == 2)){ 

				int ay, ny, ax, nx; 	//actual.y next.y, actual.x, next.x
				ax = players[actualplayer].pos_x;
				ay = players[actualplayer].pos_y;
				nx = players[next_player(actualplayer)].pos_x;
				ny = players[next_player(actualplayer)].pos_y;
				if((not (board.not_a_wall_between_y(ny, ay, nx))) or (not (board.not_a_wall_between_x(nx, ax, ny)))){
					ok = false;
				}
				if((not (board.not_a_wall_between_y(ny, fy, nx))) or (not (board.not_a_wall_between_x(nx, fx, ny)))){
					ok = false;
				}
				
				if(ok){
					board.draw_player(fx,fy, actualplayer);
					board.delete_player(players[actualplayer].pos_x, players[actualplayer].pos_y);
					players[actualplayer].pos_x = fx;
					players[actualplayer].pos_y = fy;
					acted = true;
			    }
			    else {
// 					std::cout <<"NOT OK" << std::endl;
				}
			}// salt vertical
			else if(fx == players[0].pos_x and fx == players[1].pos_x and my_player_near(actualplayer, players[next_player(actualplayer)].pos_x, players[next_player(actualplayer)].pos_y)
					and (fy != players[0].pos_y and fy != players[1].pos_y) and board.not_a_wall_between_y(inity, finy, fx)){ 
				board.draw_player(fx,fy, actualplayer);
				board.delete_player(players[actualplayer].pos_x, players[actualplayer].pos_y);
				players[actualplayer].pos_x = fx;
				players[actualplayer].pos_y = fy;
				acted = true;
			}//salt horitzontal
			else if(fy == players[0].pos_y and fy == players[1].pos_y and my_player_near(actualplayer, players[next_player(actualplayer)].pos_x, players[next_player(actualplayer)].pos_y) 
					and (fx != players[0].pos_x and fx != players[1].pos_x) and board.not_a_wall_between_x(initx, finx, fy)){ 
				board.draw_player(fx,fy, actualplayer);
				board.delete_player(players[actualplayer].pos_x, players[actualplayer].pos_y);
				players[actualplayer].pos_x = fx;
				players[actualplayer].pos_y = fy;
				acted = true;
			}
		}

		if(players[0].pos_y >= 16) board.end_the_game(first);
		else if (players[1].pos_y == 0) board.end_the_game(second);
	}
	ret = acted;

	board.draw_player(players[actualplayer].pos_x, players[actualplayer].pos_y, actualplayer);
	if(acted){
		actualplayer = next_player(actualplayer);

		board.draw_player (18, 0, actualplayer);
		//board.draw();
		acted = false;
	}

	return ret;
}

//It checks if a player have a way to reach the other side of the board
bool Logica::have_a_way(playerenum player, std::vector< std::vector< bool> > &visitat, int x, int y){

	bool endreached = false;

	if(player == second and y < 1) return true;
	else if(player == first and y >= 16) return true;
	
	if (ok(x, y) and (visitat[x][y] == false)){   
		visitat[x][y] = true;
		for(int i = 0; ((endreached == false) and (i < 4)); ++i){
			if(ok(x+dirx[i], y+diry[i]) and (not board.is_full_wall(x+dirx[i], y+diry[i]))) {
				endreached = have_a_way(player, visitat, x+dirx[i], y+diry[i]);
			}
		}
		return endreached;
	}
}

//Return true if the values are in the range of the board
bool Logica::ok(int x, int y){
	return ((y >= 0 and y <=16 and x >= 0 and x <= 16));
}

/*USELESS*/
void Logica::mou_a_cantonada(int& fx){
	/*it does nothing now*/ fx = fx;
}

//Return true if there is a player near the x, y position of the board
bool Logica::my_player_near(int actualplayer, int x, int y){
	int px = players[actualplayer].pos_x;
	int py = players[actualplayer].pos_y;
	return((px == x+2 and py == y) 
		or (px == x-2 and py == y)
		or (py == y-2 and px == x)
		or (py == y+2 and px == x));
}

//Return the x position of the player
int Logica::get_player_position_x( int actualplayer){
	return players[actualplayer].pos_x;
}

//Return the y position of the player
int Logica::get_player_position_y( int actualplayer){
	return players[actualplayer].pos_y;
}

//Makes the board play both players
void Logica::print_me_the_players(){
	board.draw_player(get_player_position_x(first), get_player_position_y(first), first);
	board.draw_player(get_player_position_x(second), get_player_position_y(second), second);
}

//Return the player that is not currently playing
playerenum Logica::next_player(playerenum actualp){
	if (actualp == first) return second;
	return first;
}

//Makes board set a random wall to full_wall
void Logica::print_me_random_wall(){

	int cont = 0;
	int wallnumber = rand()%142; // rand entre 0 i 142

	std::vector< std::vector< bool> > visitat1 (17, std::vector <bool> (17, false));
	std::vector< std::vector< bool> > visitat2 (17, std::vector <bool> (17, false));	
	
	for(int i = 0; i < 17; ++i){
		for(int j = 0; j < 17; ++j){
			if(board.is_empty_wall(i, j)) {
				++cont;
				if(wallnumber == cont){
					board.build_wall(i, j);
					if(not (have_a_way(first, visitat1, players[first].pos_x, players[first].pos_y) 
					  and have_a_way(second, visitat2, players[second].pos_x, players[second].pos_y))){
						board.unbuild_wall(i, j);
					}
				}
			}
		}
	}
}

bool Logica::ended(int player){
	if(player == 0 and players[player].pos_y > 16) return true;
	else if (player == 1 and players[player].pos_y < 0) return true;
	return false;
}

double Logica::getValueOfBoard(){
	std::queue<sf::Vector3i> c, k;
	std::vector<std::vector<bool> > m (17, std::vector<bool>(17,false));
	std::vector<std::vector<bool> > mm(17, std::vector<bool>(17,false));

	c.push(sf::Vector3i(players[0].pos_x, players[0].pos_y, 0));
	k.push(sf::Vector3i(players[1].pos_x, players[1].pos_y, 0));

	int stwfirst  = board.getStepsToWin(players[0].pos_x, players[0].pos_y, 16, c,  m);
	int stwsecond = board.getStepsToWin(players[1].pos_x, players[1].pos_y,  0, k, mm);
//	std::cout << "first " << stwfirst << ", second " << stwsecond << " valueofBoard: " << (stwfirst - stwsecond) << std::endl;

	return (stwfirst - stwsecond);
}

bool Logica::movePlayer(int d, int p){
	int px = players[p].pos_x;
	int py = players[p].pos_y;
	int nx = px + movx[d];
	int ny = py + movy[d];

	if( board.legitmove(px, py, nx, ny)){
//		std::cout << "          faig el moviment a dir " << d << " player " << p << std::endl;
		//board.draw_player(px+movx[d], py+movy[d], (playerenum)p);
		if(p == 0) if(players[1].pos_x == nx and players[1].pos_y == ny) return false;
		if(p == 1) if(players[0].pos_x == nx and players[0].pos_y == ny) return false;
		players[p].pos_x = nx;
		players[p].pos_y = ny;
		//board.delete_player(px, py);
		return true;
	}
//	std::cout << "          no es un moviment ok a dir " << d << " pel player "<< p << std::endl;
	return false;
}

bool Logica::buildwall(int n){

	std::vector< std::vector<bool> > visitat1 (17, std::vector <bool> (17, false));
	std::vector< std::vector<bool> > visitat2 (17, std::vector <bool> (17, false));	
	
	int i = (n*2+1)/17;
	int j = (n*2+1)%17;

	if(board.is_full_wall(i,j)) return false;

	board.build_wall(i, j);

	if(not (have_a_way(first, visitat1, players[first].pos_x, players[first].pos_y) 
	  and have_a_way(second, visitat2, players[second].pos_x, players[second].pos_y))){
			board.unbuild_wall(i, j);
			return false;
	}
	board.unbuild_wall(i,j);
	return true;
}

int Logica::getActualPlayer(){
	return (int)actualplayer;
}

bool Logica::unbuildwall(int n){

	std::vector< std::vector<bool> > visitat1 (17, std::vector <bool> (17, false));
	std::vector< std::vector<bool> > visitat2 (17, std::vector <bool> (17, false));	
	
	int i = (n*2+1)/17;
	int j = (n*2+1)%17;

	board.unbuild_wall(i, j);
	return true;

}

/*musica: buffalo soldier - Marley nd the wailers, 99 red balloons - nena, broken wings -  mr.mister, the lion sleeps tonight, Mrs.Robinson - simon nd garfunkel */