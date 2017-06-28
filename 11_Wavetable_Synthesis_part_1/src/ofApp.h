#pragma once

#include "ofMain.h"
#include "audioTools.h"



#define tableSize 2048
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
    void exit();
    void audioOut(float* buffer, int bufferSize, int nChannels);

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    int sampleRate;
    int bufferSize;
    
    //smoothValue frequency;
	parameterSmoother2 frequency;
	float freqSmoothTime = 1000;
    double phaseInc;
    double phase;
    
    float* waveTable;
    float tableFundamentalFreq;
    
    ofPolyline waveForm;
    
    
		
};
