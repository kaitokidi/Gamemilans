#include "presentacio.h"

//Constructor
Presentacio::Presentacio(sf::RenderWindow &window) :window_game(window) {
	ptex = NULL;
	delay = delay = 10;
	windowWidth = window_game.getSize().x;
	windowHeight = window_game.getSize().y;
	if(!Background.loadFromFile("pics/portada.png")){
		std::cout << "soc una mica curtet i no se carregar la portada" << std::endl;
	}//else std::cout << "Background loaded" << std::endl;
	if(!font.loadFromFile("font/LinBiolinum_R.otf")){
		std::cout << "Can't find the font file" << std::endl;
	}
}

//Destructor
Presentacio::~Presentacio(){};


void Presentacio::portada(){

	ptex = &Background;
	
	int pos_x, pos_y;
	pos_x = pos_y = delay = 0;

	float scalex, scaley;
	if(windowWidth > windowHeight){
		scaley = scalex =  windowWidth/float(ptex->getSize().x);
		delay = windowHeight - ptex->getSize().y*scalex;
		pos_y+=delay/2;
	} else {
		scalex = scaley = windowHeight/float(ptex->getSize().y);
		delay = windowWidth - ptex->getSize().x*scalex;
		pos_x+=delay/2;
	}

	sprite.setTexture(*ptex, true);
	sprite.setScale(scalex, scaley);

	sprite.setPosition(pos_x, pos_y);
	window_game.draw(sprite);

}

int Presentacio::handler(){

	sf::Event event;
	int mouse_x, mouse_y;
	if(window_game.pollEvent(event)){
		switch (event.type) {
			// window closed 
			case sf::Event::Closed:
				window_game.close();
				exit(0);
				break;
			// mouse pressed
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left) {
					mouse_x = event.mouseButton.x;
					mouse_y = event.mouseButton.y;
					if((mouse_x >= 5*windowWidth/6) and (mouse_y >= (7*(windowHeight-delay)/8)+delay/2 )) return 0;
					else return -1;
				}
				break;
			case sf::Event::TextEntered:
				if(event.text.unicode >= 48 and event.text.unicode <= 57)
				 	sentence += (char)event.text.unicode;
				else if(event.text.unicode == 8 and sentence.getSize() > 0)
					sentence.erase(sentence.getSize()-1, sentence.getSize());
				text.setString(sentence);
				window_game.clear();
				window_game.draw(text);
				if(sentence.getSize() > 0 and event.text.unicode == 13) {
					while(sentence.getSize() > 4) sentence.erase(sentence.getSize()-1, sentence.getSize()); 
					return std::atoi(sentence.toAnsiString().c_str());
				}
			// key pressed	
			case  sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::N){
					if(sentence.getSize() <= 2) return 0;
				}
				else return -2;
				break; 
			// we don't process other types of events
			default:
				break;
		}  
	}
	return -3;
}

void Presentacio::inst(int n){

	sf::Texture inst;
	if(n == 1) inst.loadFromFile("pics/instruccions1.png");
	if(n == 2) inst.loadFromFile("pics/instruccions2.png");
	ptex = &inst;
	
	int pos_x, pos_y;
	pos_x = pos_y = delay = 0;

	float scalex, scaley;
	if(windowWidth > windowHeight){
		scaley = scalex =  windowWidth/float(ptex->getSize().x);
		delay = windowHeight - ptex->getSize().y*scalex;
		pos_y+=delay/2;
	} else {
		scalex = scaley = windowHeight/float(ptex->getSize().y);
		delay = windowWidth - ptex->getSize().x*scalex;
		pos_x+=delay/2;
	}

	sprite.setTexture(*ptex, true);
	sprite.setScale(scalex, scaley);
	sprite.setPosition(pos_x, pos_y);
	window_game.draw(sprite);

}


void Presentacio::prepareText(){
	int i, j;
	i = 1*windowWidth/14;
	j = 1*((windowHeight-delay)/2)+delay/2;
	sentence.clear();
	text.setFont(font);
	text.setCharacterSize(40);
	text.setColor(sf::Color(0,0,0));
	text.setStyle(sf::Text::Bold);
	text.setPosition(i, j);
}


void Presentacio::murs(){
	sf::Texture murs;
	murs.loadFromFile("pics/murs.png");
	ptex = &murs;
	int pos_x, pos_y;
	pos_x = pos_y = delay = 0;
	float scalex, scaley;
	if(windowWidth > windowHeight){
		scaley = scalex =  windowWidth/float(ptex->getSize().x);
		delay = windowHeight - ptex->getSize().y*scalex;
		pos_y+=delay/2;
	} else {
		scalex = scaley = windowHeight/float(ptex->getSize().y);
		delay = windowWidth - ptex->getSize().x*scalex;
		pos_x+=delay/2;
	}
	sprite.setTexture(*ptex, true);
	sprite.setScale(scalex, scaley);
	sprite.setPosition(pos_x, pos_y);
	window_game.draw(sprite);	
	window_game.draw(text);
}
