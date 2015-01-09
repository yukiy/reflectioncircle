#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    //ofSetBackgroundAuto(false);
    ofBackground(0,0,0);
        
    TL = ofPoint(10,                10);
    TR = ofPoint(ofGetWidth()-10,   10);
    BL = ofPoint(10,                ofGetHeight()-10);
    BR = ofPoint(ofGetWidth()-10,   ofGetHeight()-10);
    
    topSide.addVertex(TL);
    topSide.addVertex(TR);
    
    bottomSide.addVertex(BL);
    bottomSide.addVertex(BR);
    
    leftSide.addVertex(TL);
    leftSide.addVertex(BL);
    
    rightSide.addVertex(TR);
    rightSide.addVertex(BR);
    
    num = 0;
    reflectionNum = 4;
    initAngle = PI/2;
    
}


//--------------------------------------------------------------
void ofApp::update(){
    
}


//--------------------------------------------------------------
void ofApp::drawReflectLine(ofPoint startPt, float nextAngle){
    
    ofDrawBitmapStringHighlight(ofToString(nextAngle * 180 / PI), startPt);

    ofPoint targetPt = ofPoint(cos(nextAngle)*5000 + startPt.x, sin(nextAngle)*5000 + startPt.y);
    ofPoint hitPt;
    

    //---top
    if(ofLineSegmentIntersection(startPt, targetPt, TL, TR, hitPt)){
        //cout << "intersect top!" << endl;
        //cout << "num: " + ofToString(num) + ": " + ofToString(nextAngle * 180 / PI) << endl;
        ofDrawBitmapString("top intersection at "+ ofToString(num), ofPoint(10, 0+180*num));
        nextAngle = nextAngle * -1;
        ofLineSegmentIntersection(startPt, targetPt, TL, TR, hitPt);
        hitPt.y = hitPt.y + 1;
    }
    
    //---bottom
    else if(ofLineSegmentIntersection(startPt, targetPt, BL, BR, hitPt)){
        //cout << "intersect bottom!" << endl;
        //cout << "num: " + ofToString(num) + ": " + ofToString(nextAngle * 180 / PI) << endl;
        ofDrawBitmapString("bottom intersection at "+ ofToString(num), ofPoint(10, 0+180*num));
        nextAngle = nextAngle * -1;
        ofLineSegmentIntersection(startPt, targetPt, BL, BR, hitPt);
        hitPt.y = hitPt.y - 1;
    }
    
    //---left
    else if(ofLineSegmentIntersection(startPt, targetPt, TL, BL, hitPt)){
        //cout << "intersect left!" << endl;
        //cout << "num: " + ofToString(num) + ": " + ofToString(nextAngle * 180 / PI) << endl;
        ofDrawBitmapString("left intersection at "+ ofToString(num), ofPoint(10, 0+180*num));
        nextAngle = (nextAngle - PI) * -1;
        ofLineSegmentIntersection(startPt, targetPt, TL, BL, hitPt);
        hitPt.x = hitPt.x + 1;
    }
    
    //---right
    else if(ofLineSegmentIntersection(startPt, targetPt, TR, BR, hitPt)){
        //cout << "intersect right!" << endl;
        //cout << "num: " + ofToString(num) + ": " + ofToString(nextAngle * 180 / PI) << endl;
        ofDrawBitmapString("right intersection at "+ ofToString(num), ofPoint(10, 0+180*num));
        nextAngle = (nextAngle - PI) * -1;
        ofLineSegmentIntersection(startPt, targetPt, TR, BR, hitPt);
        hitPt.x = hitPt.x - 1;
    }
    
    else {
        cout << "no intersection at "+ ofToString(num)  << endl;
        cout << "startPt: " + ofToString(startPt.x) + ", " + ofToString(startPt.y) << endl;
        cout << "targetPt: " + ofToString(targetPt.x) + ", " + ofToString(targetPt.y) << endl;
        cout << "p: " + ofToString(hitPt.x) + ", " + ofToString(hitPt.y) << endl;
        ofDrawBitmapString("no intersection at "+ ofToString(num), ofPoint(10, 0+180*num));
    }

    ofDrawBitmapString("startPt: " + ofToString(startPt.x) + ", " +    ofToString(startPt.y),           ofPoint(10, 30+180*num));
    ofDrawBitmapString("targetPt: " + ofToString(targetPt.x) + ", " + ofToString(targetPt.y),           ofPoint(10, 60+180*num));
    ofDrawBitmapString("hitPt: " + ofToString(hitPt.x) + ", " +          ofToString(hitPt.y),           ofPoint(10, 90+180*num));
    ofDrawBitmapString("nextAngle: " + ofToString(nextAngle) + ", " + ofToString(nextAngle * 180 / PI), ofPoint(10,120+180*num));
    ofDrawBitmapString("----------",                                                                    ofPoint(10,150+180*num));

    
    ofLine(startPt, targetPt);
    ofCircle(hitPt.x, hitPt.y, 10);

    num++;
    if(num > reflectionNum){
        num = 0;
        return;
    }else{
        drawReflectLine(hitPt, nextAngle);
    }

}


//--------------------------------------------------------------
void ofApp::drawReflectLineShape(ofPoint startPt, float nextAngle, ofPolyline circle){
    bool doDrawSubLines = false;
    
    ofPoint hitPt;
    ofPoint targetPt = ofPoint(cos(nextAngle)*1000+startPt.x, sin(nextAngle)*1000+startPt.y);
    
    //---intersect shape
    if(shapeSegmentIntersection(startPt, targetPt, circle, hitPt)){
        ofPoint centerPt = circle.getCentroid2D();
        float centerAngle = atan2(hitPt.y-centerPt.y, hitPt.x-centerPt.x);
        float floorAngle = PI/2 + centerAngle;
        float entryAngle = nextAngle - floorAngle;
        float exitAngle = -entryAngle + floorAngle;
        
        if(doDrawSubLines){
            //---center line (white)
            ofSetColor(255, 255, 255);
            ofLine(centerPt, hitPt);
            ofDrawBitmapString(ofToString(centerAngle*180/PI), centerPt);
            
            //---entry line (red)
            ofSetColor(255, 0, 0);
            ofLine(startPt, hitPt);
            ofDrawBitmapString(ofToString(nextAngle*180/PI), 30, 30);
            ofDrawBitmapString(ofToString(entryAngle*180/PI), startPt);
            
            //---floor line (yellow)
            ofSetColor(255, 255, 0);
            float floorx = cos(floorAngle) * 100 + hitPt.x;
            float floory = sin(floorAngle) * 100 + hitPt.y;
            ofLine(hitPt, ofPoint(floorx, floory));
            ofDrawBitmapString(ofToString(floorAngle*180/PI), hitPt);
            
            //---exit line (blue)
            ofSetColor(0, 0, 255);
            float exitx = cos(exitAngle)*100+hitPt.x;
            float exity = sin(exitAngle)*100+hitPt.y;
            ofLine(hitPt, ofPoint(exitx, exity));
            ofDrawBitmapString(ofToString(exitAngle * 180/PI), exitx, exity);
        }
    
        nextAngle = exitAngle;
        hitPt.x += cos(nextAngle);
        hitPt.y += sin(nextAngle);
    }

    //---intersect top edge
    else if(ofLineSegmentIntersection(startPt, targetPt, TL, TR, hitPt)){
        ofSetColor(255,255,255);
        ofDrawBitmapString("top intersection at "+ ofToString(num), ofPoint(10, 0+180*num));
        nextAngle = nextAngle * -1;
        ofLineSegmentIntersection(startPt, targetPt, TL, TR, hitPt);
        hitPt.y = hitPt.y + 1;
    }
    
    //---bottom edge
    else if(ofLineSegmentIntersection(startPt, targetPt, BL, BR, hitPt)){
        ofSetColor(255,255,255);
        ofDrawBitmapString("bottom intersection at "+ ofToString(num), ofPoint(10, 0+180*num));
        nextAngle = nextAngle * -1;
        ofLineSegmentIntersection(startPt, targetPt, BL, BR, hitPt);
        hitPt.y = hitPt.y - 1;
    }
    
    //---left edge
    else if(ofLineSegmentIntersection(startPt, targetPt, TL, BL, hitPt)){
        ofSetColor(255,255,255);
        ofDrawBitmapString("left intersection at "+ ofToString(num), ofPoint(10, 0+180*num));
        nextAngle = (nextAngle - PI) * -1;
        ofLineSegmentIntersection(startPt, targetPt, TL, BL, hitPt);
        hitPt.x = hitPt.x + 1;
    }
    
    //---right edge
    else if(ofLineSegmentIntersection(startPt, targetPt, TR, BR, hitPt)){
        ofSetColor(255,255,255);
        ofDrawBitmapString("right intersection at "+ ofToString(num), ofPoint(10, 0+180*num));
        nextAngle = (nextAngle - PI) * -1;
        ofLineSegmentIntersection(startPt, targetPt, TR, BR, hitPt);
        hitPt.x = hitPt.x - 1;
    }
    
    //---none
    else {
        ofSetColor(255,255,255);
        ofDrawBitmapString("no intersection at "+ ofToString(num), ofPoint(10, 0+180*num));
    }
    
    ofSetColor(0,255,0, 50);
    ofLine(startPt, hitPt);
    ofCircle(hitPt.x, hitPt.y, 5);
    
    num++;
    if(num > reflectionNum){
        num = 0;
        return;
    }else{
        drawReflectLineShape(hitPt, nextAngle, circle);
    }

}


//--------------------------------------------------------------
bool ofApp::shapeSegmentIntersection(ofPoint a, ofPoint b, ofPolyline poly, ofPoint & intersection){
    
    bool isFromInside = false;
    if(poly.inside(a)){
        isFromInside = true;
    };
    
    float len = ofDist(a.x, a.y, b.x, b.y);
    int res = len;
    ofPoint step = (b-a) / res;
    bool bInside = false;
    for (int i = 0; i < res; i++){
        ofPoint checkPt = a + i * step;
        
        if (!isFromInside && poly.inside(checkPt)){
            intersection = poly.getClosestPoint(checkPt);
            return true;
        }

        if (isFromInside && !poly.inside(checkPt)){
            intersection = poly.getClosestPoint(checkPt);
            return true;
        }

    }
    return false;
}



//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetColor(255,255,255,100);
    
    topSide.draw();
    bottomSide.draw();
    leftSide.draw();
    rightSide.draw();

    
    ofPolyline circle;
    int r = 300;
    float vtx = 36;
    ofPoint centerPt = ofPoint(ofGetWidth()/2, ofGetHeight()/2);
    for(int i=0; i<vtx; i++){
        float pct = i/vtx;
        circle.addVertex(cos(pct*TWO_PI)*r+centerPt.x, sin(pct*TWO_PI)*r+centerPt.y);
    }
    circle.close();
//    circle.draw();
    
    ofPoint mousePt = ofPoint(mouseX, mouseY);
    float initAngle = PI*2/3;



    drawReflectLineShape(mousePt, initAngle, circle);
    
    ofDrawBitmapStringHighlight("ReflectionNum: "+ofToString(reflectionNum), 30, 30);
}







//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'a'){
        initAngle += 0.01;
    }
    
    if (key == 's'){
        initAngle -= 0.01;
    }

    if (key == 'z'){
        reflectionNum++;
    }
    if (key == 'x'){
        reflectionNum--;
    }

    if (key == 'c'){
        reflectionNum += 10;
    }
    if (key == 'v'){
        reflectionNum -= 10;
    }

    
    
}

