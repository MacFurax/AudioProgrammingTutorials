#include "audioTools.h"


//----------------------------------------------oscillator
void oscillator::setup(float _frequency, double _phase, float _amplitude, int _sampleRate) {
	frequency = _frequency;
	phase = _phase;
	amplitude = _amplitude;
	sampleRate = _sampleRate;
	phaseInc = (TWO_PI*frequency) / (double)sampleRate;
	currentSample = 0;
}

float oscillator::getSample() {
	currentSample = sin(phase) * amplitude;
	phase += phaseInc;
	return currentSample;
}

void oscillator::setFrequency(float _freq) {
	frequency = _freq;
	phaseInc = (TWO_PI*frequency) / (double)sampleRate;
}

void oscillator::setAmplitude(float _amp) {
	amplitude = _amp;
}


//---------------------------------------

stereoFrame panner::pan(float input, float position) {
	stereoFrame currentFrame;

	if (position > 1) {
		position = 1;
	}

	if (position < -1) {
		position = -1;
	}

	float theta = position * 45;
	theta = ofDegToRad(theta);

	float sinTheta = sin(theta);
	float cosTheta = cos(theta);

	currentFrame.leftSample = input *  constant * (sinTheta - cosTheta);
	currentFrame.rightSample = input * constant * (sinTheta + cosTheta);

	return currentFrame;
}

//--------------------------------------------------------
void circleMeter::setup(ofVec2f _location, float _radius, int sampleLength) {
	clipped = false;
	counter = 0;
	location = _location;
	radius = _radius;
	resolution = 30;

	if (sampleLength > 100) {
		numToAverage = sampleLength;
	}else{
		numToAverage = 100;
	}

	numToAverageRecip = 1 / (double)numToAverage;

	rms.smoother = new parameterSmoother(50, 60);

}
void circleMeter::setup(float x, float y, float _radius, int sampleLength) {
	clipped = false;
	counter = 0;
	location.x = x;
	location.y = y;
	radius = _radius;
	resolution = 30;

	if (sampleLength > 100) {
		numToAverage = sampleLength;
	}
	else {
		numToAverage = 100;
	}
	numToAverageRecip = 1 / (double)numToAverage;

	rms.smoother = new parameterSmoother(50, 60);
}

void circleMeter::feedMeter(float input) {

	if (input >= 0.99) {
		clipped = true;
	}
	if (input > 0) {
		accumulatedSamples += input;
	}else {
		accumulatedSamples += input * -1;
	}
	counter++;
	if (counter >= numToAverage) {
		rms.targetValue = accumulatedSamples * numToAverageRecip;
		accumulatedSamples = 0;
		counter = 0;
	}
}
void circleMeter::update() {
	rms.currentValue = rms.smoother->process(rms.targetValue);
}

void circleMeter::draw() {

	ofSetCircleResolution(resolution);
	if (clipped) {
		ofSetColor(200, 20, 20);
		ofDrawCircle(location, radius*1.08);
	}
	ofSetColor(0);
	ofDrawCircle(location, radius);
	ofSetColor(20, 200, 20);
	ofDrawCircle(location, rms.currentValue*radius);
}

//--------------------------------------------------------
void meter::setup(ofVec2f _location, int _width, int _height, int sampleLength) {
	clipped = false;
	counter = 0;
	location = _location;
	width = _width;
	height = _height;

	if (sampleLength > 100) {
		numToAverage = sampleLength;
	}
	else {
		numToAverage = 100;
	}

	if (width > height) {
		mode = HORIZONTAL;
	}else {
		mode = VERTICAL;
	}

	numToAverageRecip = 1 / (double)numToAverage;
	rms.smoother = new parameterSmoother(400, 60);
}

void meter::feedMeter(float input) {

	if (fabs(input) >= 0.99) {
		clipped = true;
	}

	accumulatedSamples += fabs(input);
	
	counter++;
	if (counter >= numToAverage) {
		rms.targetValue = accumulatedSamples * numToAverageRecip;
		accumulatedSamples = 0;
		counter = 0;
	}
}
void meter::update() {
	rms.currentValue = rms.smoother->process(rms.targetValue);
}

void meter::draw() {
	switch (mode) {
	case VERTICAL:
		ofSetColor(0);
		ofDrawRectangle(location.x, location.y, width, height);
		if (clipped) {
			ofSetColor(200, 20, 20);
			ofDrawRectangle(location.x, location.y, width, height*0.05);
		}
		ofSetColor(20, 200, 20);
		ofDrawRectangle(location.x, location.y + height - (rms.currentValue*height), width, (height*rms.currentValue));
		break;
	case HORIZONTAL:
		ofSetColor(0);
		ofDrawRectangle(location.x, location.y, width, height);
		if (clipped) {
			ofSetColor(200, 20, 20);
			ofDrawRectangle(location.x + width, location.y, width*0.05, height);
		}
		ofSetColor(20, 200, 20);
		ofDrawRectangle(location.x, location.y, width*rms.currentValue, height);
		break;
	default:
		break;
	}
	
}