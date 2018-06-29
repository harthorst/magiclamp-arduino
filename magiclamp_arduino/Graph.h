#ifndef Graph_h
#define Graph_h

#include "Arduino.h"

class Graph {
	public:
		Graph();
		int getRel(int actual, byte dir);
		int getX(int actual);
		int getY(int actual);
};

#endif
