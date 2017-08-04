#pragma once

#include "ofMain.h"
#include "ofxTrueTypeFontUC.h"
#include "ofxDeferredShading.h"
#include "ofxGui.h"
#include "ofxJSONElement.h"
#include "ofxSyphon.h"
#include "ofxOsc.h"

#include "ReadJsonThread.hpp"
#include "CommonUtil.hpp"
#include "TweetObj.hpp"
#include "VoxelPanel.hpp"
#include "PostEffect.hpp"

using namespace ofxDeferredShading;

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void windowResized(int w, int h);
    
    void randomize();
    
    void setupDeferred();
    void updateDeferredParam();
    
    void exit();
    
private:
    const int wSize = 200, hSize = 150;
    
    bool isShowSyphon = false;
    bool isShowTwi = false;
    bool isShowBulbs = false;
    
    PostEffect pe;
    
    ReadJsonThread thread;
    ofxJSONElement json;
    ofxTrueTypeFontUC font;
    
    ofxOscReceiver receiver;
    SmoothValue volume;
    
    VoxelPanel vp;

    ofxSyphonClient client;

    int currentTwi = 0;
    TweetObj twi[2];
    
    ofEasyCam cam;
    
    // for shading
    ofxDeferredProcessing deferred;
    PointLightPass* lightingPass;
    SsaoPass* ssaoPass;
    HdrBloomPass* hdrBloomPass;
    DofPass* dofPass;
    
    SmoothPoint lp1, lp2;
    SmoothPoint camPos;
    SmoothPoint camLook;
    
    // gui
    bool isShowPanel = false;
    ofxPanel panel;
    ofParameterGroup pl1;
    ofParameter<ofVec3f> pl1_pos;
    ofParameter<ofFloatColor> pl1_diff;
    ofParameter<ofFloatColor> pl1_spe;
    ofParameter<float> pl1_int;
    ofParameter<float> pl1_rad;
    
    ofParameterGroup pl2;
    ofParameter<ofVec3f> pl2_pos;
    ofParameter<ofFloatColor> pl2_diff;
    ofParameter<ofFloatColor> pl2_spe;
    ofParameter<float> pl2_int;
    ofParameter<float> pl2_rad;
    
    ofParameterGroup ao;
    ofParameter<float> ao_rad;
    ofParameter<float> ao_dark;
    
    ofParameterGroup dof;
    ofParameter<float> dof_blur;
    ofParameter<float> dof_ape;
    ofParameter<float> dof_focal;
    
    ofParameter<float> dt;
};
