/**************MAIN.cpp****************/
#include "ia.h"
#include <string>
#include "board.h"
#include <sstream>
#include <cstdlib>
#include "logica.h"
#include <iostream> 
#include "presentacio.h"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"
#include "SFML/Network.hpp"
#include "SFML/Graphics.hpp"
#include <vector>

int main(int argc, char *argv[]){

	srand(time(NULL));
	int mouse_x, mouse_y; 

	sf::RenderWindow window_game (sf::VideoMode(900, 700), "Gamemilans!",
	sf::Style::Resize|sf::Style::Close);
	
//	sf::RenderWindow window_game (sf::VideoMode::getDesktopMode(), "Gamemilans!",
//		sf::Style::Resize|sf::Style::Close);

	sf::Music music;
	if (!music.openFromFile("music/GameSong1.ogg")) std::cout << " no puc carregar la musica " << std::endl;
	music.play();
	music.setPitch(1);
	music.setLoop(true);

		sf::Clock clock;
		
	window_game.setVerticalSyncEnabled(true);

		window_game.display();
		Presentacio p(window_game);
		p.portada();
		window_game.display();

			p.portada(); 
			window_game.display();
		while (p.handler() != 0){
		}
		window_game.clear();

			p.inst(1); 
			window_game.display();
		while (p.handler() != 0){
		}
		window_game.clear();

			p.inst(2); 
			window_game.display();
		while (p.handler() != 0){
		}
		window_game.clear();

		p.prepareText();
		int n_murs = p.handler();
		int oldmurs = n_murs;
			p.murs(); 
			window_game.display();
		while (n_murs < 0){
			n_murs = p.handler();
			if(n_murs != oldmurs){
				p.murs(); 
				window_game.display();
				oldmurs = n_murs;
			}
		}
		window_game.clear();

	Board taulell(window_game);
	Logica logica(taulell);
 	Ia ia(0);
 	Ia ia2(1);

	taulell.draw();
	logica.print_me_the_players();
	for(int i = 0; i < n_murs; ++i)
		logica.print_me_random_wall();

	bool is_server = false;
	bool online = false;
	bool ia_playing = false;

	int port;
	if(argc >= 2){
		int n;
		if(argc >= 3) {
			if((*(argv[2])) == 'S') is_server = true;
			if((*(argv[2])) == 'I') ia_playing = true;
			if((*(argv[2])) != 'I') online = true;
		}
		if((*(argv[1]))-'0' >= 0) n = atoi((argv[1]));
		else n = 2; /*(?) think it have no sense*/
		for(int i = 0; i < n; ++i) logica.print_me_random_wall();	
	}
	taulell.draw();
	window_game.display(); 
	
	sf::TcpSocket socket;
	sf::TcpSocket client;
	sf::TcpListener listener;

	if( (argc >= 3) and online) { 	//Is online so you have to connect the socket
		port = 53000;
		if(not is_server){
			//Connect the socket
			sf::Socket::Status status = socket.connect("127.0.0.1", port);
			if (status != sf::Socket::Done)	{
				std::cout << "Not conected the socket okly" << std::endl;
			}
			else std::cout << "I'm Conected to the port " << port << std::endl;
		} else /*if (is_server)*/ {
			//Bind the listener to a port
			if (listener.listen(port) != sf::Socket::Done) {
				std::cout << "Not listened okly" << std::endl;
			}
			else std::cout << "Im Listening at the port " << port << std::endl;
			// Accept the connection
			if (listener.accept(client) != sf::Socket::Done) {
				std::cout << "Not accepted the client okly" << std::endl;
			}
			else std::cout << "Conection Accepted" << std::endl;
		}
	}

//	std::cout << "-----------------The gaem is starting here biach ---------------------" << std::endl;

	bool serverTurn = true;
	clock.restart();
	int asong = 0;
	int msong = 6;
	// Mentre estigui oberta 
	while(window_game.isOpen()){

		if(asong == 0 or clock.getElapsedTime().asSeconds() >= 54){
			if(asong == 0) asong = 2;
				std::stringstream s;
				s << "music/GameSong" << asong+1 << ".ogg";
				if (!music.openFromFile(s.str())) std::cout << " no puc carregar la song " << asong+1 << std::endl;
				music.play();
				++asong;
				if(asong > msong) asong = 3;
			clock.restart();
		}
		sf::Event event;
		// If you are playing online and it is not your turn
		while(online and ((not is_server and serverTurn) or (is_server and not serverTurn))){

			float data[2];
			std::size_t received;

			//	std::cout << " I'm gonna wait for data... " << std::endl;
			if(not is_server){
				if (socket.receive(&data, sizeof(float)*2, received) != sf::Socket::Done)	{
				//	std::cout << "Not recived okly" << std::endl;
				} 
				else {
					logica.click(taulell.fixed(data[0], true), taulell.fixed(data[1], true));
					serverTurn = false;
				//	std::cout << "Rebut" << std::endl;
				}
			}
			else if(is_server){
				if (client.receive(&data, sizeof(float)*2, received) != sf::Socket::Done)	{
				//	std::cout << "Not recived okly" << std::endl;
				} 
				else {
					logica.click(taulell.fixed(data[0], true), taulell.fixed(data[1], true));
					serverTurn = true;
				//	std::cout << "rebut" << std::endl;
				}
			}

			//Empty the pollEvent
			while(window_game.pollEvent(event)){
				switch (event.type)	{
					// window closed 
					case sf::Event::Closed:
					window_game.close();
					break;
					default:
					break;
				}
			}
			window_game.display(); 
		}

		bool acted = false;
		while(window_game.pollEvent(event)){

			// mira els events
			switch (event.type) {
				// window closed 
				case sf::Event::Closed:
				window_game.close();
				break;

				// mouse pressed
				case sf::Event::MouseButtonPressed:
//					std::cout << " clicked " << std::endl;
					if (event.mouseButton.button == sf::Mouse::Left) {
						mouse_x = event.mouseButton.x;
						mouse_y = event.mouseButton.y;
					}
					if(not acted and (online and ((is_server and serverTurn) or (not is_server and not serverTurn))) ){
						if(online) {
							float data[2];
							data[0] = mouse_x;
							data[1] = mouse_y;
							// TCP socket:
							if(is_server and logica.click(taulell.fixed(data[0], true), taulell.fixed(data[1], true))){
								//	std::cout << " I'm the server who will send u data biach! " << std::endl;
								if (client.send(&data, sizeof(float)*2) != sf::Socket::Done) {
								//	std::cout << "not sent okly server->client" << std::endl;
								}
								else {
									serverTurn = false;
								//	std::cout << "sent okly S->C!!!" << std::endl;
								}
							}
							else if(not is_server and logica.click(taulell.fixed(data[0], true), taulell.fixed(data[1], true))){
								//	std::cout << " This client want's to send u shiet... " << std::endl;
								if (socket.send(&data, sizeof(float)*2) != sf::Socket::Done) {
								//	std::cout << "not sent okly client->server" << std::endl;
								}
								else {
								serverTurn = true;
								//	std::cout << "sent okly S->C!!!" << std::endl;
								}
							}
						}
						acted = true;
					}
					else {
						if(ia_playing and serverTurn) {
							int movement, deep, i, j;
							double bestvalue;
							movement = -1;
							deep = 2;
							std::cout << "Calculant..." << std::endl;
							if(serverTurn) bestvalue = ia.minMax(logica, deep, false, movement);
							else bestvalue = ia2.minMax(logica, deep, true, movement);

							std::cout << "bestval: " << bestvalue << " movement: "<< movement<< std::endl;

							if(movement < 4){
								if(serverTurn){
									i = logica.get_player_position_x(ia.getPlayer())+movx[movement];
									j = logica.get_player_position_y(ia.getPlayer())+movy[movement];
								}
								else{
									i = logica.get_player_position_x(ia2.getPlayer())+movx[movement];
									j = logica.get_player_position_y(ia2.getPlayer())+movy[movement];	
								}
							}
							else{
								movement -= 4;
								i = (movement*2+1)%17;
								j = (movement*2+1)/17;
							}
							
							std::cout << "initial pos " << logica.get_player_position_x(logica.getActualPlayer()) << " , " << logica.get_player_position_y(logica.getActualPlayer()) << " delay: " << movx[movement] << " , " << movy[movement] << std::endl;
							std::cout << "ia "<< logica.getActualPlayer() << " clicked on " << i << " " << j << std::endl;
							
							if(logica.click(i, j)) {
								if(serverTurn)serverTurn = false;
								else serverTurn = true;
								std::cout << "Torn acabat " << std::endl;
							}
						}
						else {
							int mx, my;
							mx = taulell.fixed(mouse_x, true);
							my = taulell.fixed(mouse_y, true);
							if(logica.click(mx, my)){
								if(serverTurn)serverTurn = false;
								else serverTurn = true;
							}
						}
					}
					break;
					
				case  sf::Event::KeyPressed:		/* These is not working online :$ */
					if (online and is_server and event.key.code == sf::Keyboard::R or (not online and event.key.code == sf::Keyboard::R)) {
						taulell.restart();
						logica.restart();
						taulell.draw();
						logica.print_me_the_players();
						if(argc >= 2) {	
							int n;
							if((*(argv[1]))-'0' >= 0 or true) n = atoi((argv[1]))/* - '0'*/;
							else n = 2;
							for(int i = 0; i < n; ++i) logica.print_me_random_wall();
						}
					}
				break;
				
				// we don't process other types of events
				default:
				break;
			}  
		}
		window_game.display(); 
	}
	return 0;
}