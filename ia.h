#ifndef IA
#define IA

#include <vector>
#include "logica.h" 
#include <iostream>
class Ia {

	public:

		Ia(int p);
		~Ia();
		double minMax(Logica& logica, int deep, bool maxp, int& movement);
		int getPlayer();

	private:

		int player;
		double max(double a, double b);
		double min(double a, double b);
		int inverseDir(int d);
		int vect4[4];

};

#endif