#ifndef STAR
#define STAR

#include "Animate.hpp"
#include "MacroStrand.hpp"

struct Star : public Animation {
	MacroStrand* lights;
	int offset;
	int life;
	HSV color;
	int growRate;
	int decayRate;
	boolean growing;
	uint8_t temp;
	
	Star(MacroStrand* lts, int o, int l, HSV c, double g, double d) : lights(lts), offset(o), life(l), color(c) { 
		temp = color.v;
		growRate = temp / (g != 0 ? life * g : 1);
		decayRate = temp / (d != 0 ? life * d : 1);
		growing = true;
		color.v = 0;
	}
/*	void setTemp(uint8_t t) {
		color.v = t;
	}
	uint8_t getTemp() {
		return color.v;
	}
	void adjustTemp(uint8_t amt) {
		color.v += amt;
	}
*/
	boolean next() {
		if (life <= 0) return false;
		
		if (growing) grow();
		else decay();
		
		lights->get(offset).prepHSV(color);
		
		life--;
		
		return true;
	}
	void grow() {
		color.v += growRate;
		if (color.v >= temp) {
			color.v = temp;
			growing = false;
		}
	}
	void decay() {
		color.v -= decayRate;
		if (color.v <= 0) color.v = 0;
	}
};

#endif