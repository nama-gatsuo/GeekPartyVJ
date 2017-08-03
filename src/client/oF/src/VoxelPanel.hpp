#pragma once

#include "ofMain.h"

class VoxelPanel {
public:
    void setup(int width, int height);
    void begin();
    void end();
    void draw(ofCamera& cam, bool isShadow);
    void debugDraw();
private:
    ofFbo fbo;
    ofShader shader;
    ofVboMesh mesh;
    int w, h;
};
