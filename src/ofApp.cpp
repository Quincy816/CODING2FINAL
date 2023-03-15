#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(0);
    ofSetFullscreen(true);
    ofSetFrameRate(30);

    // Set the window size to the camera image size
    ofSetWindowShape(ofGetScreenWidth(), ofGetScreenHeight());
    // Open the camera
    videoGrabber.setup(ofGetScreenWidth(), ofGetScreenHeight());
    

    // Set the threshold and minimum area for human detection
    threshold = 30;
    minArea = 100;
    // Initialize the human detector
    contourFinder.setMinArea(minArea);
    contourFinder.setThreshold(threshold);
    // load the music
    music.load("touch.wav");
    // Initialize the playback status as not playing
    isPlaying = false;
    
    

for (int i = 0; i < numColumns; i++) {
    // Control the color of the columns
    ofColor columnColor[numColumns];
    columnColor[i] = ofColor::fromHsb(ofMap(i, 0, numColumns, 0, 255), 255, 255,180);
}
    ofEnableDepthTest();
    ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
    //sphere settings
    auto ico_sphere = ofIcoSpherePrimitive(250, 5);
    this->base_mesh = ico_sphere.getMesh();
    ofSoundStreamSetup(0, 1, this, ofGetFrameRate(), 256, 4);
}

//--------------------------------------------------------------
void ofApp::update(){
    //update camera image
    videoGrabber.update();
    if (videoGrabber.isFrameNew()) {
        // convert image to grayscale
        ofxCv::convertColor(videoGrabber, gray, CV_RGB2GRAY);
        // Perform background subtraction
        background.setLearningRate(0.1);
        background.update(gray, thresholded);
        // Find contours
        contourFinder.findContours(thresholded);
        // Process human motion data
        if (contourFinder.size() > 0) {
            // Get the largest contour
            ofPolyline largestContour = contourFinder.getPolyline(0);
            // Calculate the center point of the largest contour
            ofPoint center = largestContour.getBoundingBox().getCenter();
            // Calculate the area of the largest contour
            float area = contourFinder.getContourArea(0);
            // Process human motion data, such as calculating motion strength based on center point and area
            float data = center.x / ofGetWidth();
            
            float *fft = ofSoundGetSpectrum(512);

        float avgFFT = 0.0f;
            for (int i = 0; i < 512; i++) {
                avgFFT += fft[i];
            }
            avgFFT /= 512.0f;
            
            
            ofSeedRandom(39);

            this->draw_mesh = this->base_mesh;
            auto noise_seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));
            auto spectrum = ofSoundGetSpectrum(512);
            auto magnitude = 0.f;
            for (int i = 0; i < 512; i++) {
                magnitude += spectrum[i];
            }
            magnitude /= 512;

            for (auto& v : this->draw_mesh.getVertices()) {
                for (int i = 0; i < 3; i++) {
                    auto rotation_x = glm::rotate(glm::mat4(), ofMap(ofNoise(glm::vec4(v * 0.0035, noise_seed.x + ofGetFrameNum() * 0.01)), 0, 1, -30, 30 + magnitude * 400) * (float)DEG_TO_RAD, glm::vec3(1, 0, 0));
                    auto rotation_y = glm::rotate(glm::mat4(), ofMap(ofNoise(glm::vec4(v * 0.0035, noise_seed.y + ofGetFrameNum() * 0.01)), 0, 1, -30, 30 + magnitude * 400) * (float)DEG_TO_RAD, glm::vec3(0, 1, 0));
                    auto rotation_z = glm::rotate(glm::mat4(), ofMap(ofNoise(glm::vec4(v * 0.0035, noise_seed.z + ofGetFrameNum() * 0.01)), 0, 1, -30, 30 + magnitude * 400) * (float)DEG_TO_RAD, glm::vec3(0, 0, 1));

                    v = glm::vec4(v, 0) * rotation_z * rotation_y * rotation_x;
                }
            }

        for (int i = 0; i < numParticles; i++) {
                float radius = particleRadius[i] * (1 + avgFFT*80);
                particles[i] = particles[i].normalize() * radius;
            }
            // Calculate the coordinates of the center of the circle
            float angleStep = TWO_PI / numCircles;
            float radiusStep = ofGetWidth() / (numCircles * 2);
            for (int i = 0; i < numCircles; i++) {
                float radius = (i * radiusStep) + (radiusStep / 2);
                float angle = i * angleStep;
                circleCenters[i] = ofVec2f(radius * cos(angle), radius * sin(angle));
            }
            
            // update column height
            for (int i = 0; i < numColumns; i++) {
                float fftIndex = ofMap(i, 0, numColumns, 0, 512);
                float columnHeight = fft[static_cast<int>(fftIndex)] * 500*data;
                float columnHeights[numColumns];
                columnHeights[i] = columnHeight;
                
                // Control the color of the columns
                ofColor columnColor[numColumns];

                        if (i % 2 == 0) {
                            columnColor[i] = ofColor::fromHsb(ofMap(i, 0, numColumns, 0, 255), 255, 255 - data * 50);
                        } else {
                            columnColor[i] = ofColor::fromHsb(ofMap(i, 0, numColumns, 0, 255), 255 - data * 50, 255);
                        }
            }
            
            
        
            // Controlling changes in the rhythm of the music
            if (isPlaying) {
                music.setSpeed(ofMap(data, 0, 1, 1, 1.1));
            }
      
        }
    }
  
}

//--------------------------------------------------------------
void ofApp::draw(){

    
    camera.begin();
  
    
    // draw columns
        float *fft = ofSoundGetSpectrum(128);
        float avgFFT = 0.0f;
        for (int i = 0; i < 128; i++) {
            avgFFT += fft[i];
        }
        avgFFT /= 128.0f;
        
        float angleStep = 360.0f / 128;
        float currentAngle = 0.0f;
        float circleRadius = 400.0f;
        
        for (int i = 0; i < 512; i++) {
            float radius = 3.0f + fft[i] * 4000.0f;
            radius = ofClamp(radius, 0.0f, 100.0f); // 限制最大高度为200
            ofPushMatrix();
            ofTranslate(cos(ofDegToRad(currentAngle)) * circleRadius, sin(ofDegToRad(currentAngle)) * circleRadius, 0.0f);
            ofColor boxcolor = ofColor::fromHsb(0, 0, 255, 150);
            ofSetColor(boxcolor);

            ofDrawBox(0.0f, 0.0f, -radius/2, 15.0f, 15.0f, radius);
            ofPopMatrix();
            currentAngle += angleStep;
        }
    
    ofRotateY(ofGetFrameNum() * 0.9999999999999999);
    ofSetColor(255, 64);
    this->draw_mesh.drawWireframe();
    
    camera.end();
    
    
    // Display human detection results
    ofSetColor(ofColor::paleVioletRed);
    contourFinder.draw();
    
    ofColor color = ofColor::fromHsb(162,7,54,180);
    ofSetColor(color);



   

    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // Press the space bar to start playing music
    if (key == ' ') {
        if (!isPlaying) {
            music.play();
            isPlaying = true;
        } else {
            // Reset playback state and stop playing music if already playing
            isPlaying = false;
            music.stop();
        }
    }
}
