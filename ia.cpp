#include "ia.h"

 Ia::Ia(int p){
 	player = p;
 	for(int i = 0; i < 4; ++i) vect4[i] = i; 
 }

 Ia::~Ia(){}

 int Ia::getPlayer(){
 	return player;
 }

double Ia::max(double a, double b){
	if(a > b) return a;
	else return b;
}

double Ia::min(double a, double b){
	if(a < b) return a;
	else return b;
}

int Ia::inverseDir(int d){
	switch (d){
		case 0:
			return 1;
			break;
		case 1:
			return 0;
			break;
		case 2:
			return 3;
			break;
		case 3:
			return 2;
			break;
		default:
			return d;
			break;
	}
}

double Ia::minMax(Logica& logica, int deep, bool maxp, int& movement){
	
    int v;
    double bestv;
    int sida = 0;

    if(logica.ended(0)) return -9999;
    if(logica.ended(1)) return 9999;
    if(deep <= 0) return logica.getValueOfBoard();

    if(maxp){
	    bestv = -88888;
	    for(int i = 0; i < 4; ++i){
	    	Logica logica2 = logica;
	    	if(logica2.movePlayer(i, 1)){
	    		v = minMax(logica2, deep-1, false, sida);
	    		if(v > bestv) {movement = i;}
	    		bestv = max(bestv, v);
	    	}
	    }
	/*   for(int i = 4; i < 148; ++i){
	    	Logica logica2 = logica;
	    	if(logica2.buildwall(i-4)){
	    		v = minMax(logica2, deep-1, false, sida);
	    		if(v > bestv) {movement = i;}
	    		bestv = max(bestv, v);
	    	}	
	    }*/
	    return bestv;
    }
    else {
    	bestv =  88888;
    	for(int i = 3; i >= 0; --i){
    		Logica logica2 = logica;
	    	if(logica2.movePlayer(i, 0)){
	    		v = minMax(logica2, deep-1, true, sida);
	    		if(v < bestv) {movement = i;}
	    		bestv = min(bestv, v);
	    	}
	    }
/*   	   for(int i = 4; i < 148; ++i){
	    	Logica logica2 = logica;
	    	if(logica2.buildwall(i-4)){
	    		v = minMax(logica2, deep-1, false, sida);
	    		if(v > bestv) {movement = i;}
	    		bestv = max(bestv, v);
	    	}	
	    }*/

   	    return bestv;
    }




















	/*
	double bestv, v, action;
	if(logica.ended(0)){
		return -2000000;
	}
	if(logica.ended(1)){
		return 2000000;
	}
	if(deep <= 0){
		return logica.getValueOfBoard();
	}
	
	if(maxp){
		bestv = -9999999999;
		for(int i = 0; i < 4; ++i){
			if(logica.movePlayer(i, player)){
				int decdeep = deep -1;
				std::cout << "inception" << std::endl;
				v = minMax(logica, decdeep, 21321321, false, movement);
				if(deep = inideep and v > bestv) { movement = 144+i; std::cout << "movment = 144 + " << i << std::endl;}
				bestv = max(bestv, v);
				logica.movePlayer(inverseDir(i), player);
			}
		}
		for(int i = 0; i < 144; ++i){
			if(logica.buildwall(i)){
				int decdeep = deep -1;
				v = minMax(logica, decdeep, true, movement);
				if(v > bestv) movement = i;
				bestv = max(bestv, v);
				logica.unbuildwall(i);
			}
		}
		return bestv;
	} 
	else {
		bestv = 9999999999;
		for(int i = 0; i < 4; ++i){
			if(logica.movePlayer(i, player)){
				int decdeep = deep -1;
				std::cout << "inception" << std::endl;
				v = minMax(logica, decdeep, 21321321, true, movement);
				if(deep = inideep and v < bestv) { movement = 144+i; std::cout << "movment = 144 + " << i << std::endl;}
				bestv = min(bestv, v);
				logica.movePlayer(inverseDir(dir[i]), player);
			}
		}
		for(int i = 0; i < 144; ++i){
			if(logica.buildwall(i)){
								int decdeep = deep -1;

				v = minMax(logica, decdeep, false, movement);
				if(v<bestv) movement = i;
				bestv = min(bestv, v);
				logica.unbuildwall(i);
			}
		}
		return bestv;
	}*/
}