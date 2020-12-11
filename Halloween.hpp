#ifndef HALLOWEEN
#define HALLOWEEN

#include "DEBUG.h"

#include <Arduino.h>
#include "Animate.hpp"
#include "MacroStrand.hpp"
#include "Star.hpp"
#include "AnimList.hpp"

struct Halloween : public Animation {
	MacroStrand* lights;
	int* layers;
	
	HSV* color;
//	int* wait;
	int* incr;
	
	int wait;
	
	int level;
	int flare;
	int smold;
	
	uint8_t sat;
	
	int p;
	
	Halloween(MacroStrand* lts, int* lrs) : 
		lights(lts), layers(lrs), wait(0), 
		color(new HSV[17])/*, wait(new int[17])*/, incr(new int[17]), 
		p(lts->totalPoints), level(150), flare(50), smold(-30), sat(255) {
		uint8_t h = 20;
		for (int l = 0; l < 17; l++) {
		//	wait[l]   = 0;
			incr[l]    = 0;
			color[l].h = h;
			color[l].s = sat;
			color[l].v = level;
			h += (50 / 17);
		}
	}
	
	// boolean next() {
		// int v;
		
		// for (int l = 0; l < 17; l++) {
			// if (wait[l] > 0) {
				// wait[l]--;
				
				// color[l].v += incr[l];
				
				// for (int i = layers[l]; i < layers[l + 1]; i++) {						
					// lights->get(i).prepHSV(color[l].h, color[l].s, color[l].v);
				// }
			// }
			// else { 
				// int t    = level + v + random(smold, flare);
				// wait[l] = random(1, (17 - l) + 10) / 2;
				// v    = t - color[l].v;
				// incr[l]  = v / wait[l];
			// }
		// }	
		
	// }
	boolean next() {		
		if (wait > 0) {
			wait--;
			for (int l = 0; l < 17; l++) {
				color[l].v += incr[l];
				
				for (int i = layers[l]; i < layers[l + 1]; i++) {						
					lights->get(i).prepHSV(color[l].h, color[l].s, color[l].v);
				}
			//	delay(10);
			}
		}
		else {
		//	int t = level;
			double dd = random(smold, flare);
			double d = dd;
			
			wait = random(2, 8);
			for (int l = 0; l < 17; l++) {
				int i = l + 1;
				int t   = level + d;
				d       = d * (random(50, 150) / 100.0);
			
			
				int v   = t - color[l].v;
				incr[l] = v / wait;
			//	DPRINTLN(NV(l), NV(t), NV(d), NV(v), NV(incr[l]));
			}
		}
		lights->get(0).prepHSV(255, 255, 255);
	}
};

#endif