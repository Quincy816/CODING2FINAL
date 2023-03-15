#pragma once

#include "ofMain.h"

#include "ofxCv.h"
#include "opencv2/opencv.hpp"
#include "ofColor.h"



const int numParticles = 100;
const int numColumns = 512;

class ofApp : public ofBaseApp{

 
    public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);


    ofVideoGrabber videoGrabber;
    ofxCv::ContourFinder contourFinder;
    ofxCv::RunningBackground background;
    ofImage thresholded;
    ofImage gray;
    ofSoundPlayer music;
    bool isPlaying;
    int threshold;
    int minArea; 
    
    
    static constexpr int numCircles = 512;
    ofVec2f circleCenters[numCircles];
    ofEasyCam camera;
    ofMesh base_mesh, draw_mesh;
 
    ofVec3f particles[numParticles];
    float particleRadius[numParticles];
    ofColor particleColor[numParticles];
    
    
    
    };
