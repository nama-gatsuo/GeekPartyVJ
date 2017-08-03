#pragma once
#include "ofMain.h"
#include "ofxJSONElement.h"

class ReadJsonThread : public ofThread{
    
public:
    void threadedFunction(){
        
        while (isThreadRunning()) {
            if(lock()){
                
                if (json.openLocal("json/twi.json")) {
                    if (json["id"].asInt64() != cachedId) {
                        isNew = true;
                        cachedId = json["id"].asInt64();
                    }
                }
                
                unlock();
                sleep(100);
            }
        }
    };
    bool checkNew(){
        ofScopedLock lock(mutex);
        if (isNew) {
            isNew = false;
            return true;
        } else {
            return isNew;
        }

    };
    ofxJSONElement * getJson() {
        ofScopedLock lock(mutex);
        return &json;
    };
    
private:
    ofxJSONElement json;
    int64_t cachedId = 0;
    bool isNew = false;
};
