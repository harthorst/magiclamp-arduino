#ifndef Graph_h
#define Graph_h

#include "Arduino.h"

class Graph {
	public:
		Graph();
		int getRel(int actual, byte dir);
		int getX(int actual);
		int getY(int actual);
		int getBottomLed(int actual);
		int getTopLed(int actual);
};

#endif
