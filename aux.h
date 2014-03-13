#ifndef AUX
#define AUX
 
enum tile_type {
		empty_ground, empty_wall, full_ground, full_wall, qtt_types
};

enum playerenum {
	first, second, qtt_players
};

//					  Up BotRightLeft
const int dir[4] = {  0,  1,  2,  3};
//            		  N   S   E   W
const int dirx[4] = { 0,  0,  1, -1};
const int diry[4] = {-1,  1,  0,  0};
//            		  N   S   E   W
const int movx[4] = { 0,  0,  2, -2};
const int movy[4] = {-2,  2,  0,  0};

const int BOARD_X_SIZE = 9;
const int BOARD_Y_SIZE = 9;

#endif