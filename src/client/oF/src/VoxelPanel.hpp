#pragma once

#include "ofMain.h"
#include "CommonUtil.hpp"

class VoxelPanel {
public:
    void setup(int width, int height, int div);
    void begin();
    void end();
    void update(float vol);
    void draw(ofCamera& cam, bool isShadow);
    void debugDraw();
    
    void setDivision(float div);
    
    void explode();
    void reset();
    bool isExploded() { return exploded; };
    
private:
    ofFbo fbo;
    float volume;
    unsigned int division;
    ofShader shader;
    ofVboMesh mesh;
    int w, h;
    
    bool exploded = false;
    SmoothValue trans;
};
