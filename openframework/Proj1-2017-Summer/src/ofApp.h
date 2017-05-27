#pragma once

#include "ofMain.h"
#include <vector>

#define BLOCKSIZE 200
#define BLOCKHEIGHT 200
#define TURNINGSHARPNESS 0.5
#define BLOCKSTODRAW 9


class building{
public:
    ofVec3f center;
    int width;
    int height;
    int deep;
    building(ofVec3f v, int w, int h, int d){
        width = w;
        height = h;
        deep = d;
        center = v;
    }
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        enum Turning{NOTURN, TURNLEFT, TURNRIGHT, TURNUP, TURNDOWN};
		
		ofLight light; // creates a light and enables lighting
        ofMaterial material;
		//ofCamera cam;
		ofEasyCam cam; // add mouse controls for camera movement
		int deeps[10];
		float w=50, h=50, d=100, initX = 0, initY = -200, initZ = 0;
        std::vector<building> buildings;
        ofVec2f visibleBlockCenters[BLOCKSTODRAW];
		
        int newBlock =0;
        ofVec2f currentBlockCenter;
		float rotation, camSpeed = 1, tarSpeed = 1;
        ofVec3f camPos = ofVec3f(-200, -200, 400);
        ofVec3f camTarPos = ofVec3f(-100, -100, 400);
        ofVec3f camVelocity = ofVec3f(0, 0, 0);
        ofVec3f camTarVelocity = ofVec3f(1, 1, 0);
        Turning ifTurn = NOTURN;
    
        ofShader shader;
    
};


void drawBuilding(int w, int h, int d, int windowType);
void drawBuildingLines(float w, float h, float d,int windowType);
void subdivide(ofVec3f, int halfWidth, int halfHeight,int maxZ, std::vector<building> &);