/*
 * Effect.h
 *
 *  Created on: Jun 24, 2018
 *      Author: tf
 */

#ifndef EFFECT_H_
#define EFFECT_H_

class Effect {
public:
	virtual ~Effect() {}
	virtual void init() = 0;
	virtual void update();
};




#endif /* EFFECT_H_ */
