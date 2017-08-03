#include "VoxelPanel.hpp"

void VoxelPanel::setup(int width, int height){
    
    w = width;
    h = height;
    
    shader.load("shader/scene/VoxelPanel");
    shader.begin();
    shader.setUniform2i("size", w, h);
    shader.end();
    
    mesh = ofMesh::box(5., 5., 5., 1,1,1);
    
    fbo.allocate(w, h, GL_RGB32F);
    
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
    
    shader.setUniformTexture("tex", fbo.getTexture(), 0);
    
    mesh.drawInstanced(OF_MESH_FILL, w * h);
    
    shader.end();

}

void VoxelPanel::debugDraw() {
    fbo.draw(0,0);
}
