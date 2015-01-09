#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

        void drawReflectLine(ofPoint startPt, float nextAngle);
        void drawReflectLineShape(ofPoint startPt, float angle, ofPolyline circle);
        
        bool shapeSegmentIntersection(ofPoint a, ofPoint b, ofPolyline poly, ofPoint & intersection);
        
        void keyPressed(int key);

    
        ofPoint TL;
        ofPoint TR;
        ofPoint BL;
        ofPoint BR;
        ofPolyline topSide;
        ofPolyline leftSide;
        ofPolyline rightSide;
        ofPolyline bottomSide;
    
        int num;
        int reflectionNum;
        float initAngle;
    
};


