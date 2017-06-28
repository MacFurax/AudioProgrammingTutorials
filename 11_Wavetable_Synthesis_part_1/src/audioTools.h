#ifndef audioTools_h
#define audioTools_h

#include "ofMain.h"
//-------------------------------------------------
class oscillator {

public:
	void setup(float _frequency, double _phase, float _amplitude, int _sampleRate);
	float getSample();

	void setFrequency(float _freq);
	void setAmplitude(float _amp);

private:
	int sampleRate;
	float frequency;
	double phase;
	double phaseInc;
	float amplitude;
	float currentSample;
};
//----------------
struct stereoFrame {
	float leftSample;
	float rightSample;
};


//----------------------------------------------------------
class panner {

public:
	stereoFrame pan(float input, float position);

private:
	float constant = (sqrt(2) / (float)2);
};

class parameterSmoother {

public:

	parameterSmoother(float smoothingTimeMS, int sampleRate) {
		a = exp(-TWO_PI / (smoothingTimeMS * 0.001 * sampleRate));
		b = 1.0 - a;
		z = 0.0;
	}

	void setup(float smoothingTimeMS, int sampleRate) {
		a = exp(-TWO_PI / (smoothingTimeMS * 0.001 * sampleRate));
		b = 1.0 - a;
		z = 0.0;
	}
	
	inline float process(float input) {
		z = (input * b) + (z * a);
		return z;
	}

private:
	float a;
	float b;
	float z;
};

struct smoothValue {
	float targetValue;
	float currentValue;
	parameterSmoother* smoother;
};

inline float linearInterp(float x0, float x1, float y0, float y1, float x){

	if (x1 == x0) { return 0; }//avoid divideBy0
	float scalar = (x - x0) / (x1 - x0);//gather normalized position between two x values

	float result = (y0*scalar) + (y1*(1 - scalar));

	return result;
}
inline float linearInterp(float y0, float y1, float x) {//this version assumes integer x values
	
	float scalar = x - (int)x;//how far away are we from y0?
	return (y0*(1 - scalar)) + (y1*scalar);
}


//-----------------------------------------------------------------------meters
class circleMeter {

public:
	void setup(ofVec2f _location, float _radius, int sampleLength);
	void setup(float x, float y, float radius, int sampleLength);

	void feedMeter(float input);
	void update();
	void draw();

	void clearClip() {
		clipped = false;
	}
	void setResolution(int _resolution) {
		if (_resolution > 2) {
			resolution = _resolution;
		}else{
			_resolution = 2;
		}
	}

private:

	smoothValue rms;
	ofVec2f location;
	float radius;
	bool clipped;
	int counter;
	int numToAverage;
	float accumulatedSamples;
	double numToAverageRecip;

	int resolution;//resolution of circle

};


//-----standard meter
enum {
	VERTICAL,
	HORIZONTAL
};

class meter {

public:
	void setup(ofVec2f _location, int width, int height, int sampleLength);

	void feedMeter(float input);
	void update();
	void draw();

	void clearClip() {
		clipped = false;
	}

private:

	smoothValue rms;
	ofVec2f location;
	bool clipped;
	int counter;
	int numToAverage;
	float accumulatedSamples;
	double numToAverageRecip;

	int width, height;
	int mode;
};

#endif