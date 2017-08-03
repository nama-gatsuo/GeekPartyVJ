#pragma once

#include "ofMain.h"
#include "ofxTrueTypeFontUC.h"
#include "ofxDeferredShading.h"
#include "ofxGui.h"
#include "ofxJSONElement.h"

#include "ReadJsonThread.hpp"
#include "CommonUtil.hpp"
#include "TweetObj.hpp"
#include "VoxelPanel.hpp"

using namespace ofxDeferredShading;

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void windowResized(int w, int h);
    
    void setupDeferred();
    void updateDeferredParam();
    
    void exit();
    
private:
    ReadJsonThread thread;
    ofxJSONElement json;
    
    ofxTrueTypeFontUC font;
    VoxelPanel vp;
    
    int currentTwi = 0;
    TweetObj twi[2];
    
    ofEasyCam cam;
    
    // for shading
    ofxDeferredProcessing deferred;
    PointLightPass* lightingPass;
    SsaoPass* ssaoPass;
    ShadowLightPass* shadowLightPass;
    HdrBloomPass* hdrBloomPass;
    DofPass* dofPass;
    
    SmoothPoint lp1, lp2;
    SmoothPoint camPos;
    SmoothPoint camLook;
    // gui
    bool isShow = false;
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
    
    ofParameterGroup shadow;
    ofParameter<float> sha_amb;
    ofParameter<float> sha_dif;
    ofParameter<float> sha_dark;
    ofParameter<float> sha_blend;
    
    ofParameterGroup dof;
    ofParameter<float> dof_blur;
    ofParameter<float> dof_ape;
    ofParameter<float> dof_focal;
    
    ofParameter<float> dt;
};
