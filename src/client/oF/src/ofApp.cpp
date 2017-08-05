#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(30);
    font.loadFont("font/hiragino_mincho_pnw6.ttc", 12, true, true);
    
    pe.setup();
    
    vp.setup(wSize, hSize, 1.);
    setupDeferred();
    updateDeferredParam();
    
    client.setup();
    client.set("", "");
    
    camPos.to(cam.getPosition());
    camLook.to(ofVec3f(0.0));
    dt.set(1.0);
    
    thread.startThread();
    
    receiver.setup(7401);
}

//--------------------------------------------------------------
void ofApp::update(){
    updateDeferredParam();
    
    vp.update(volume.get());
    
    lp1.update(dt.get());
    lp2.update(dt.get());
    lightingPass->getLightRef(0).position = lp1;
    lightingPass->getLightRef(1).position = lp2;
    
    camPos.update(dt.get());
    cam.setPosition(camPos);
    cam.lookAt(camLook);
    volume.update(dt.get());
    
    // check json
    if (isShowTwi && thread.checkNew()) {
        json = *thread.getJson();
        string name = json["user"]["name"].asString() + " @" + json["user"]["screen_name"].asString();
        string text = json["text"].asString();
        
        twi[currentTwi].erase();
        currentTwi = 1 - currentTwi;
        
        twi[currentTwi] = TweetObj(name, text);
    }
    
    
    // listen to OSC from Max
    while (receiver.hasWaitingMessages()) {
    
        ofxOscMessage m;
        receiver.getNextMessage(m);
        
        string address = m.getAddress();
        vector<string> pathes = ofSplitString(address, "/");
        
        if (pathes[1] == "bang") {
            
            if (pathes[2] == "0") {
                randomize();
            } else if (pathes[2] == "1") {
                
                float coin = ofRandom(1.);
                if (coin < 0.5) pe.setMode(0);
                else if (coin < 0.55) pe.setMode(1);
                else if (coin < 0.63) pe.setMode(2);
                
                coin = ofRandom(1.);
                if (coin < .3 && vp.isExploded()) {
                    vp.reset();
                }
                if (coin < .05) {
                    vp.explode();
                }
            }
                
        } else if (pathes[1] == "vol") {
            volume.to(m.getArgAsFloat(0)); break;
        } else if (pathes[1] == "p") {
            int i = ofToInt(pathes[2]);
            float val = m.getArgAsInt32(0) / 128.;
            if (i == 4) {
                dt.set(0.001 + 2.0 * val);
            }
        } else if (pathes[1] == "key") {
        
        }
        
    
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    vp.begin();
    // draw something
    
    ofBackground(0);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    
    if (isShowSyphon) {
        client.draw(0, 0, wSize, hSize);
    }
    
    if (isShowTwi) {
        twi[0].draw(font);
        twi[1].draw(font);
    }
    
    ofDisableBlendMode();
    vp.end();
    
    deferred.begin(cam, true);
    vp.draw(cam, false);
    lightingPass->drawLights(cam, false);
    deferred.end(false);
    
    pe.begin();
    deferred.draw();
    pe.end();
    
    pe.draw();
    
    if (isShowPanel) panel.draw();
//    vp.debugDraw();
//    shadowLightPass->debugDraw();
//    deferred.debugDraw();
//    ofDrawBitmapString("fps: " + ofToString(ofGetFrameRate()), 10, 40);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key){
        case ' ': randomize(); break;
        case 's': isShowPanel = !isShowPanel; break;
        case '1': isShowTwi = !isShowTwi; break;
        case '2': isShowSyphon = !isShowSyphon; break;
        case '3': isShowBulbs = !isShowBulbs; break;
    }
}

void ofApp::randomize(){
    float coin = ofRandom(1.);
    if (coin < 0.3) {
        lp1.to(ofPoint(ofRandom(-600, 600), ofRandom(-400, 400), ofRandom(100, 600)));
        lp2.to(ofPoint(ofRandom(-600, 600), ofRandom(-400, 400), ofRandom(100, 600)));
    }
    
    coin = ofRandom(1.);
    if (coin < 0.1) {
        camPos.to(ofPoint(0., 0., 800));
        camLook.to(ofPoint(0.));
    } else if (coin < 0.3) {
        camPos.to(ofPoint(ofRandom(-500, 500), ofRandom(-300, 300), ofRandom(80, 300)));
        camLook.to(ofPoint(ofRandom(-50, 50), ofRandom(-50, 50), ofRandom(-50, 50)));
    }
    
    coin = ofRandom(1.);
    if (coin < 0.08) {
        vp.setDivision(1.0);
    } else if (coin < 0.09){
        vp.setDivision(pow(2., floor(ofRandom(1., 4.))));
    } else if (coin < 0.1){
        vp.setDivision(pow(2., floor(ofRandom(4., 6.))));
    }
    
    coin = ofRandom(1.);
    if (coin < 0.03) {
        isShowTwi = true;
        isShowSyphon = false;
    } else if (coin < 0.06) {
        isShowTwi = false;
        isShowSyphon = true;
    } else if (coin < 0.08) {
        isShowTwi = true;
        isShowSyphon = true;
        //isShowBulbs = !isShowBulbs;
    }
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

void ofApp::exit() {
    thread.stopThread();
}

void ofApp::setupDeferred(){
    deferred.init(ofGetWidth(), ofGetHeight());
    ssaoPass = deferred.createPass<SsaoPass>().get();
    
    lightingPass = deferred.createPass<PointLightPass>().get();
    ofxDeferredShading::PointLight dlight;
    dlight.ambientColor = ofFloatColor(0.005);
    lightingPass->addLight(dlight);
    
    dlight.ambientColor = ofFloatColor(0.0);
    lightingPass->addLight(dlight);
    
    hdrBloomPass = deferred.createPass<HdrBloomPass>().get();
    dofPass = deferred.createPass<DofPass>().get();
    
    // gui
    panel.setup();
    pl1.setName("Point light 1");
    pl1.add(pl1_pos.set("Position", ofVec3f(500,500,500), ofVec3f(-1000), ofVec3f(1000)));
    pl1.add(pl1_diff.set("Diffuse Color", ofFloatColor(0.4)));
    pl1.add(pl1_spe.set("Specular Color", ofFloatColor(1.0, 1.0, 0.9)));
    pl1.add(pl1_rad.set("Radius", 350, 100, 1000));
    pl1.add(pl1_int.set("Intensity", 1.2, 0.1, 3.0));
    panel.add(pl1);
    
    pl2.setName("Point light 2");
    pl2.add(pl2_pos.set("Position", ofVec3f(-600,700,200), ofVec3f(-1000), ofVec3f(1000)));
    pl2.add(pl2_diff.set("Diffuse Color", ofFloatColor(0.4)));
    pl2.add(pl2_spe.set("Specular Color", ofFloatColor(1.0, 1.0, 0.9)));
    pl2.add(pl2_rad.set("Radius", 350, 100, 2000));
    pl2.add(pl2_int.set("Intensity", 1.2, 0.1, 3.0));
    panel.add(pl2);
    
    ao.setName("Ambient Occlusion");
    ao.add(ao_rad.set("Occlusion Radius", 3.6, 0.1, 100.0));
    ao.add(ao_dark.set("Darkness", 0.3, 0.1, 5.0));
    panel.add(ao);
    
    dof.setName("Defocus Blur");
    dof.add(dof_blur.set("Max Blur", 0.5, 0.0, 1.0));
    dof.add(dof_ape.set("Aperture", 0.1, 0.0, 1.0));
    dof.add(dof_focal.set("Focus Distance", 0.06, 0.0, 1.0));
    panel.add(dof);
}

void ofApp::updateDeferredParam(){
    
    lightingPass->getLightRef(0).position = pl1_pos.get();
    lightingPass->getLightRef(0).diffuseColor = pl1_diff.get();
    lightingPass->getLightRef(0).specularColor = pl1_spe.get();
    lightingPass->getLightRef(0).radius = pl1_rad.get();
    lightingPass->getLightRef(0).intensity = pl1_int.get();
    
    lightingPass->getLightRef(1).position = pl2_pos.get();
    lightingPass->getLightRef(1).diffuseColor = pl2_diff.get();
    lightingPass->getLightRef(1).specularColor = pl2_spe.get();
    lightingPass->getLightRef(1).intensity = pl2_int.get();
    lightingPass->getLightRef(1).radius = pl2_rad.get();
    
    ssaoPass->setOcculusionRadius(ao_rad.get());
    ssaoPass->setDarkness(ao_dark.get());
    
    dofPass->setFocus(dof_focal.get());
    dofPass->setMaxBlur(dof_blur.get());
    dofPass->setAperture(dof_ape.get());
    
}
