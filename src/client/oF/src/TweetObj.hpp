#pragma once

#include "ofMain.h"
#include "ofxTrueTypeFontUC.h"

#include "CommonUtil.hpp"

class TweetObj {
public:
    TweetObj(){};
    TweetObj(string name, string text){
        this->name = name;
        int num = text.size();
        
        int h = 180;
        float fs = 12.;
        
        // 7 letters x 2 lines
        if (num < 42) {
            this->text = splitBySize(text, 21);
            textSize = 2.0;
            textStart = h / 2.;
        // 7 letters x 3 line2
        } else if (num < 63) {
            this->text = splitBySize(text, 21);
            textSize = 2.0;
            textStart = h / 2. - fs * textSize;
        
        } else {
            this->text = splitBySize(text, 50);
            textSize = 1.0;
            textStart = h / 2. - fs * num / 21. / 2.;
        }
        
        color.setHsb(ofRandom(1.0), 0.6, 1.0);
        opacity.to(1.0);
    };
    
    void draw(ofxTrueTypeFontUC &font){
        opacity.update(1.0);
        color.a = opacity.get();
        
        ofPushStyle();
        ofPushMatrix();
        
        ofScale(0.9, 0.9);
        ofSetColor(1.0 * 255, opacity.get() * 255);
        font.drawStringAsShapes(name, 4, 28);
        
        ofPopMatrix();
        
        ofPushMatrix();
        ofTranslate(0, textStart);
        ofScale(textSize, textSize);
        
        ofSetColor(color);
        for (int i = 0; i < text.size(); i++) {
            font.drawStringAsShapes(text[i], 4, 20*i);
        }
        
        ofPopMatrix();
        ofPopStyle();
    };
    
    void erase() { opacity.to(0.0); };
private:
    string name;
    vector<string> text;
    bool isLarge;
    float textSize;
    float textStart;
    
    SmoothValue opacity;
    ofFloatColor color;
};
