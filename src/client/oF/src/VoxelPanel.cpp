#include "VoxelPanel.hpp"

void VoxelPanel::setup(int width, int height, int div){
    
    w = width / div;
    h = height / div;
    
    division = div;
    
    float bs = 5. * division;
    
    shader.load("shader/scene/VoxelPanel");
    shader.begin();
    shader.setUniform2f("size", w, h);
    shader.setUniform1f("boxSize", bs);
    shader.end();
    
    mesh = ofMesh::box(bs, bs, 5., 1,1,1);
    
    fbo.allocate(width, height, GL_RGB32F);
    trans.setSpeed(0.1);
}

void VoxelPanel::update(float vol){
    volume = vol;
    trans.update(1.);
}
void VoxelPanel::begin(){
    fbo.begin();
    ofClear(0);
}

void VoxelPanel::end(){
    fbo.end();
}

void VoxelPanel::draw(ofCamera& cam, bool isShadow){
    ofMatrix4x4 normalMatrix = ofMatrix4x4::getTransposedOf(cam.getModelViewMatrix().getInverse());
    
    shader.begin();
    shader.setUniform1i("isShadow",isShadow?1:0);
    shader.setUniformMatrix4f("normalMatrix", normalMatrix);
    shader.setUniform1f("farClip", cam.getFarClip());
    shader.setUniform1f("nearClip", cam.getNearClip());
    shader.setUniform1f("vol", volume);
    shader.setUniform1f("trans", trans.get());
    
    shader.setUniformTexture("tex", fbo.getTexture(), 0);
    
    mesh.drawInstanced(OF_MESH_FILL, w * h);
    
    shader.end();

}

void VoxelPanel::debugDraw() {
    fbo.draw(0,0);
}

void VoxelPanel::setDivision(float div) {
    
    w = w * division / div;
    h = h * division / div;
    
    division = div;
    
    float bs = 5. * division;
    
    shader.begin();
    shader.setUniform2f("size", w, h);
    shader.setUniform1f("boxSize", bs);
    shader.end();
    
    mesh = ofMesh::box(bs, bs, 5., 1,1,1);

}

void VoxelPanel::explode(){
    exploded = true;
    trans.to(1.);
}

void VoxelPanel::reset(){
    exploded = false;
    trans.to(.0);
}
