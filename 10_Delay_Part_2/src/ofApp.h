#pragma once

#include "ofMain.h"


class tapIn{
    
public:
    float* buffer;
    int writeIndex;
    int size;
    int sampleRate;
    
	~tapIn() {
		delete[] buffer;
	}
    tapIn(float time_ms, int _sampleRate){
        
        static const int _size = (time_ms*0.001*_sampleRate);
        buffer = new float[_size];
        writeIndex = 0;
        sampleRate = _sampleRate;
        size = _size;
    }
    
    void feed(float currentSample){
        buffer[writeIndex] = currentSample;
        writeIndex++;
        if(writeIndex>=size){ writeIndex = 0;}
    }
    
};

class tapOut{
    
public:
    
    float* ref;
    int size;
    int readPoint;
    int sampleRate;
    
	~tapOut() {}
    tapOut(tapIn* inRef, float time_ms){
        
        ref = inRef->buffer;
        size = inRef->size;
        sampleRate = inRef->sampleRate;
        readPoint = size - (time_ms*0.001*sampleRate)-1;
        
    }
    
    float getSample(){
        float temp = ref[readPoint];
        readPoint++;
        if(readPoint >= size){readPoint = 0;}
        return temp;
    }
    
    
};


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    void exit();
    void audioIn(float* buffer, int bufferSize, int nChannels);
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
    
    
    int bufferSize;
    vector<float> inputBuffer;
    
    tapIn* myTapIn;
    tapOut* myTapOut;
		
};
