/**************LOGICA*********************/
#ifndef Logic
#define Logic 
#include "board.h"
#include <vector>
#include "aux.h"


class Logica { 

  struct Player {
      int animationposition;
      int pos_x;
      int pos_y;
  };
  
  public:
    //constructor
    Logica (Board &boardRef);
    //destructor
    ~Logica();

	void restart();
	int getActualPlayer();
    bool buildwall(int i);
	bool ok(int x, int y);
    bool ended(int player);
    bool unbuildwall(int i);
	bool click(int x, int y);
	double getValueOfBoard();
   	void print_me_the_players();
  	void print_me_random_wall();
	bool movePlayer(int d, int player);
	int get_player_position_x(int actualplayer);
	int get_player_position_y(int actualplayer);
	bool my_player_near(int actualplayer, int x, int y);
	bool have_a_way(playerenum player, std::vector< std::vector< bool> > &visitat, int x, int y);

  private:
    
	Board &board;
	Player players [2];
	playerenum actualplayer;
	
	void mou_a_cantonada(int &fx);
	playerenum next_player(playerenum actualp);
};

#endif
