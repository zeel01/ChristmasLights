#ifndef MCR_STRND
#define MCR_STRND

#include <FastLED.h>

struct HSV {
	uint8_t h;
	uint8_t s;
	uint8_t v;
	
	HSV() : HSV(0, 0, 0) { }
	HSV(uint8_t hue, uint8_t saturation, uint8_t value) : h(hue), s(saturation), v(value) { }
};

struct Strand {
	CRGB* leds;
	int pin;
	int length;
	
	Strand(int p, int l) : pin(p), length(l) {
		leds = new CRGB[length];	
	}
};

struct Pixel {
	Strand* strand;
	int offset;
	
	Pixel (Strand* s, int o) : strand(s), offset(o) { };
	void prepColor(int r, int g, int b) {
		strand->leds[offset].setRGB(r, g, b);
	}
	void prepHSV(int h, int s, int v) {
		strand->leds[offset].setHSV(h, s, v);
	}
	void prepHSV(HSV hsv) {
		strand->leds[offset].setHSV(hsv.h, hsv.s, hsv.v); 
	}
};

struct MacroStrand {
	Strand** strands;
	int numStrands;
	int totalPoints = 0;
	
	MacroStrand (Strand** s, int numS) : strands(s), numStrands(numS) {
		for (int i = 0; i < numStrands; i++) totalPoints += strands[i]->length;
	}
	void doit(int o, int r, int g, int b) {
		while (o >= totalPoints) o -= totalPoints;
		
		for (int i = 0; i < numStrands; i++) {
			if (o >= strands[i]->length) o -= strands[i]->length;
			else strands[i]->leds[o].setRGB(r, g, b);
		}
	}
	Pixel get(int o) {
		while (o >= totalPoints) o -= totalPoints;
		
		for (int i = 0; i < numStrands; i++) {
			if (o >= strands[i]->length) o -= strands[i]->length;
			else return Pixel(strands[i], o);
		}
	}	
};

#endif