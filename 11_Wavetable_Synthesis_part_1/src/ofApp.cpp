#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    int sampleRate = 48000;
    int bufferSize = 512;
    
    frequency.targetValue = 440;
    frequency.currentValue = 440;
    frequency.smoother = new parameterSmoother(1000, sampleRate);
    phase = 0;
    
    waveTable = new float[tableSize];
    
    for(int i = 0; i < tableSize; i++){
        
        float theta = ofMap(i, 0, tableSize-1, 0, TWO_PI);
        //theta = (i*TWO_PI)/tableSize
        waveTable[i] = sin(theta);
        
    }
    
    tableFundamentalFreq = sampleRate/float(tableSize);
    phaseInc = frequency.currentValue/tableFundamentalFreq;
    
    ofSoundStreamSetup(2, 0, sampleRate, bufferSize, 4);

}

//--------------------------------------------------------------
void ofApp::update(){
    waveForm.clear();
    for(int i = 0; i < tableSize-1; i++){
        float x = ofMap(i, 0, tableSize-1, 0, ofGetWidth());
        float y = ofMap(waveTable[i], -1, 1, ofGetHeight(), 0);
        waveForm.addVertex(x,y);
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    waveForm.draw();
}
//--------------------------------------------------------------
void ofApp::audioOut(float* buffer, int bufferSize, int nChannels){
    for(int i = 0; i < bufferSize; i++){
        
        
        frequency.currentValue = frequency.smoother->process(frequency.targetValue);
        phaseInc = frequency.currentValue/tableFundamentalFreq;
        
        float currentSample = linearInterp(waveTable[(int)phase], waveTable[int(phase+1)], phase);
        currentSample *= 0.1;
        phase += phaseInc;
        if(phase >= tableSize-1){phase -= (tableSize-1);}
        
        
        buffer[i*nChannels+0] = currentSample;
        buffer[i*nChannels+1] = currentSample;
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
    float octave = ofMap(x, 0, ofGetWidth(), 4, 14.5);
    
    frequency.targetValue = pow(2, octave);
    

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
//--------------------------------------------------------------
void ofApp::exit(){
    ofSoundStreamClose();

}
