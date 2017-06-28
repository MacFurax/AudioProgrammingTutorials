#pragma once

#include "ofMain.h"

class audioParams {
public:

	static int sampleRate;
	static int nbrOutputChannels;
	static int bufferSize;
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		
		void audioOut( ofSoundBuffer &outBuffer);

		float frequency;
		float phase;
		float phaseInc;
		float amplitude;
};
