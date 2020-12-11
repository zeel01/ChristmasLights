#include <FastLED.h>
//#include <MemoryFree.h>
#include "MacroStrand.hpp"
#include "Twinkle.hpp"
#include "Halloween.hpp"
#include "Burst.hpp"
#include "DEBUG.h"

const int numStrands = 5;

Strand* strands[numStrands];

MacroStrand* lights;
Twinkle* starlight;
Halloween* halloween;
Burst* burst;

int n = 1;

//template<int DENSITY, int DELAY> void starlight();

int layers[18];

void setup() {
	Serial.begin(9600);
	
	strands[0] = new Strand(2, 133); FastLED.addLeds<WS2811, 2, RGB>(strands[0]->leds, strands[0]->length);
	strands[1] = new Strand(3, 106); FastLED.addLeds<WS2811, 3, RGB>(strands[1]->leds, strands[1]->length);
	strands[2] = new Strand(4, 170); FastLED.addLeds<WS2811, 4, RGB>(strands[2]->leds, strands[2]->length);
	strands[3] = new Strand(5, 150); FastLED.addLeds<WS2811, 5, RGB>(strands[3]->leds, strands[3]->length);
	strands[4] = new Strand(6, 186); FastLED.addLeds<WS2811, 6, RGB>(strands[4]->leds, strands[4]->length);
	
	Serial.println("~ Setup ~");
	
	lights = new MacroStrand(strands, numStrands);
	
	starlight = new Twinkle(lights, 300);
	burst = new Burst(lights, 60, 100, 5, HSV(30, 0, 200), 0, 1);
	halloween = new Halloween(lights, layers);
	
	layers[0]  = 0  ;	// Good R
	layers[1]  = 133;	// Good G
	layers[2]  = 239;	// Good B
	layers[3]  = 326;	// Good R
	layers[4]  = 393;	// Good G
	layers[5]  = 449;	// Good B
	layers[6]  = 500;	// Good R
	layers[7]  = 555;	// Good G
	layers[8]  = 600;	// Good B
	layers[9]  = 640;	// Good R
	layers[10] = 673;	// Good G
	layers[11] = 697;	// Good B
	layers[12] = 714;	// Good R
	layers[13] = 727;	// Good G
	layers[14] = 737;	// Good B
	layers[15] = 741;	// Good R
	layers[16] = 744;	// Good G
	
	layers[17] = 745;	// End
	
}

void loop() {
	verticalWave();
//	staticColor();

//	halloween->next();	
//	layered();
//	candleLight();
	starlight->next();
	burst->next();
	FastLED.show();
}

/*template<int DENSITY>
void starlight(int durration) {
	static int wait = 0;
	static int stars[DENSITY];
	static int temp = 200;
	
	int p = lights->totalPoints;
	int cool = 100 / durration;
	
	for (int i = 0; i < DENSITY; i++) lights->get(stars[i]).prepHSV(0, 0, temp);
	temp -= cool;
	
	if (wait > 0) { 
		wait--;
		return;
	}
	
	wait = durration;
	temp = 200;

	for (int i = 0; i < DENSITY; i++) stars[i] = random(0, p);
}
*/

void layered() {
	int p = lights->totalPoints;
	uint8_t hue = 20;

	for (int l = 0; l < 17; l++) {
		for (int i = layers[l]; i < layers[l + 1]; i++) {
			lights->get(i).prepHSV(hue, 255, 150);
		}
		hue += (40/17);
	}
}
void staticColor() {
	int p = lights->totalPoints;
	for (int i = 0; i < p; i++) lights->get(i).prepHSV(170, 20, 50);
}
void verticalWave() {
	static int n = 0;
	
	int p = lights->totalPoints;
	int width = p / 255;
	
	int color = 0;
	int gap = 0;
	
	for (int i = 0; i < p; i++) {
		lights->get(i + n).prepHSV(color, 255, 100);
		if (gap < width) gap++;
		else {
			if (color < 255) color++;
			else color = 0;
			gap = 0;
		}
	}
	
//	FastLED.show(); 

	if (n < p) n += 25;
	else n = 0;
}

void candleLight() {
	static int wait = 0;
	
	if (wait > 0) {
		wait--;
		return;
	}
	
	int p = lights->totalPoints;
	int level = 150;
	int flare = 15;
	int smold = 5;
	
	//int v = random(level - smold, level + flare);
	for (int i = 0; i < p; i++) lights->get(i).prepHSV(50, 200, random(level - smold, level + flare));
	wait = random(1, 5);
}