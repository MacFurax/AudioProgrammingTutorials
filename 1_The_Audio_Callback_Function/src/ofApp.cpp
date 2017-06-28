#include "ofApp.h"


int audioParams::sampleRate = 48000;
int audioParams::nbrOutputChannels = 2;
int audioParams::bufferSize = 512;

//--------------------------------------------------------------
void ofApp::setup(){

	frequency = 440;
	amplitude = 0.1;
	phase = 0;
	phaseInc = (TWO_PI*(float)frequency) / (float)audioParams::sampleRate;

	ofSoundStreamSetup(audioParams::nbrOutputChannels, 0, audioParams::sampleRate, audioParams::bufferSize, audioParams::nbrOutputChannels * 2);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	/*float frequency;
	float phase;
	float amplitude;*/

	/*phase = ofGetElapsedTimef() * TWO_PI * frequency;
	phase = fmod(phase, TWO_PI);
	float y = ofMap( sin(phase), 1, -1, 0, ofGetHeight()) * amplitude;
	float x = ofMap( phase, 0, TWO_PI, 0, ofGetWidth());

	ofDrawCircle(x, y, 5);*/

}


//--------------------------------------------------------------
void ofApp::audioOut(ofSoundBuffer &outBuffer)
{
	float sample = 0; // generating a sine wave sample

	for (int i = 0; i < outBuffer.size(); i += 2) {
		
		sample = sin(phase) * amplitude;
		phase += phaseInc;
		//phase = fmod(phase, TWO_PI);

		outBuffer[i] = sample; // writing to the left channel
		outBuffer[i + 1] = sample; // writing to the right channel
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
	frequency = ofMap( x, 0, ofGetWidth(), 40, 2000);
	phaseInc = (TWO_PI*(float)frequency) / (float)audioParams::sampleRate;

	amplitude = ofMap(y, 0, ofGetHeight(), 1.0, 0.0);
}

//--------------------------------------------------------------
void ofApp::exit() {
	ofSoundStreamClose();
}
