#ifndef BURST
#define BURST

#include "Animate.hpp"
#include "MacroStrand.hpp"

struct Burst : public Animation {
	MacroStrand* lights;
	int offset;
	int life;
	int width;
	int spread;
	HSV color;
	int growRate;
	int decayRate;
	boolean growing;
	uint8_t temp;
	uint8_t v;
	
	Burst(MacroStrand* lts, int o, int l, int w, HSV c, double g, double d) : lights(lts), offset(o), life(l), width(w), color(c) { 
		temp = color.v;
		growRate = temp / (g != 0 ? life * g : 1);
		decayRate = temp / (d != 0 ? life * d : 1);
		growing = true;
		color.v = 0;
		spread = width;
	}
	boolean next() {
	//	if (life <= 0) return false;
		if (life <= 0) {
			life = 100;
			spread = width;
			v = 0;
			growing = true;
		}
			
		if (growing) grow();
		else decay();
		
		for (int i = spread / 2; i > 0; i--) {
			lights->get(offset + i).prepHSV(color.h, color.s, v / (i + 1));
			lights->get(offset - i).prepHSV(color.h, color.s, v / (i + 1));
		}
		
		life--;
		
		return true;
	}
	void grow() {
		v += growRate;
		if (v >= temp) {
			v = temp;
			growing = false;
		}
	}
	void decay() {
		v -= decayRate;
		if (v <= 0) v = 0;
		spread += 2;
	}
};

#endif