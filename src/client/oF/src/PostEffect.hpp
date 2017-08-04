#pragma once
#include "ofMain.h"

class PostEffect {
public:
    void setup();
    void begin();
    void end();
    void draw();
    
    void setMode(int m) { mode = m; };
    void resize(int w, int h);
    
private:
    ofFbo base;
    ofFbo composite;
    
    // 0: color, 1: grey, 2: inverse
    int mode = 0;
    
    bool isGrey = false;
    bool isNega = false;
    ofShader greyConv;
    ofShader passThru;
    float opacity = 0.0;
};
