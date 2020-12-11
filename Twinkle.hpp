#ifndef TWINKLE
#define TWINKLE

#include "Animate.hpp"
#include "MacroStrand.hpp"
#include "Star.hpp"
#include "AnimList.hpp"

struct Twinkle : public Animation {
	MacroStrand* lights;
	AnimList stars;
	int density;
	int pts;
	int temp;
	int delay;
	
	int time;
	
	Twinkle(MacroStrand* lts, int d) : lights(lts), density(d) {
		pts = lights->totalPoints;
		temp = 200;
		delay = 0;
		time = delay;
		
	//	stars = new Star*[density];
	//	genStarList();
	}
	
	boolean next() {
		dimStars();
		time--;
			
		if (time > 0) return true;
			
		time = delay;
		addStar();
		
		return true;
	}
	void dimStars() {
		stars.runSequence();
	}
	void setColors() {
		for (int i = 0; i < density; i++) {
			
		}
	}
	void genStarList() {
		while (stars.size < density) addStar();
	}
	void addStar() {
		Serial.print(stars.size);
		if (stars.size < density) {
			stars.add(new Star(lights, random(0, pts), random(50, 100), HSV(30, 0, temp), 0, 1));
		}
	}
};

#endif