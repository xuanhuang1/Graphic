
#include "ofApp.h"

//========================================================================
void drawBuilding(int w, int h, int d,int windowType){
	ofFill();
	ofSetColor(100,100,100);
	ofDrawBox(0,0,0,w,h,d);
    ofDrawCircle(0,0,5);
    
    ofFill();
    ofSetColor(100,100,100);
    if(windowType == 0){
        ofDrawBox(w/2 ,0,0, 5, h*2/3, d/2);
        ofDrawBox(-w/2,0,0, 5, h*2/3, d/2);
        ofDrawBox(0,-h/2,0, w*2/3, 5, d/2);
        ofDrawBox(0, h/2,0, h*2/3, 5, d/2);
    }else{
    	int windowWid = 10, windowHei = 15, windowThick = 3;
    	int row = w/(windowWid+10), col = d/(windowHei+10);
    	float leffupX = -w/2, leffupY = -h/2 +h/float(2*row), leftDownz = -d/2 + d/float(col*2);
    	for (int i = 0; i < row; ++i){
    		for (int j = 1; j < col; ++j){
                
        		ofDrawBox(leffupX, leffupY + i*h/float(row),
        				  leftDownz + j*d/float(col),
        				   windowThick, windowWid, windowHei);
        		ofDrawBox(-leffupX, leffupY + i*h/float(row),
        				  leftDownz + j*d/float(col),
        				   windowThick, windowWid, windowHei);
        		ofDrawBox(leffupX + w/float(2*row) + i*w/float(row),
        				  leffupY - h/float(2*row),
        				  leftDownz + j*d/float(col),
        				  windowWid, windowThick, windowHei);
        		ofDrawBox(leffupX + w/float(2*row) + i*w/float(row),
        				 -leffupY + h/float(2*row),
        				  leftDownz + j*d/float(col),
        				  windowWid, windowThick, windowHei);

    		}
    	}
    	
    }

}

void drawBuildingLines(float w, float h, float d,int windowType){
    ofNoFill();
    ofSetLineWidth(2);
    ofSetColor(70);
    
    //ofDrawBox(0,0,0,w,h,d);
    ofDrawLine(w/2,h/2,-d/2 ,w/2,h/2, d/2);
    ofDrawLine(-w/2,h/2,-d/2 ,-w/2,h/2, d/2);
    ofDrawLine(w/2,-h/2,-d/2 ,w/2,-h/2, d/2);
    ofDrawLine(-w/2,-h/2,-d/2 ,-w/2,-h/2, d/2);
    
}

void subdivide(ofVec3f center, int halfWidth, int halfHeight, int maxZ, std::vector<building> &blds){
    
    // center has xyz coordinates, assumes z is UP
    ofVec3f leftTopCenter = ofVec3f(center.x-halfWidth, center.y+halfWidth, 0);
    ofVec3f rightTopCenter =  ofVec3f(center.x+halfWidth, center.y+halfWidth, 0);
    ofVec3f leftBottomCenter = ofVec3f(center.x-halfWidth, center.y-halfWidth, 0);
    ofVec3f rightBottomCenter = ofVec3f(center.x+halfWidth, center.y-halfWidth, 0);
    
    if (halfWidth < 30) // we're very small, don't subdivide anymore
    {
        // save center, halfWidth, and halfHeight as a block to fill with buildings
        /*ofNoFill();
        ofDrawBox(leftTopCenter.x, leftTopCenter.y, leftTopCenter.z,
                  2*halfWidth, 2*halfHeight, center.x);
        ofDrawBox(rightTopCenter.x, rightTopCenter.y, rightTopCenter.z,
                  2*halfWidth, 2*halfHeight, center.x);
        ofDrawBox(leftBottomCenter.x, leftBottomCenter.y, leftBottomCenter.z,
                  2*halfWidth, 2*halfHeight, center.x);
        ofDrawBox(rightBottomCenter.x, rightBottomCenter.y, rightBottomCenter.z,
                  2*halfWidth, 2*halfHeight, center.x);*/
        float streetPortion = 0.3;
        building aBld = building(leftTopCenter, 2*halfWidth*ofRandom(1-streetPortion, 1.0),
                                 2*halfHeight*ofRandom(1-streetPortion, 1.0), maxZ*ofRandom(0.5,0.9));
        building bBld = building(rightTopCenter, 2*halfWidth*ofRandom(1-streetPortion, 1.0),
                                 2*halfHeight*ofRandom(1-streetPortion, 1.0), maxZ*ofRandom(0.5,0.9));
        building cBld = building(leftBottomCenter, 2*halfWidth*ofRandom(1-streetPortion, 1.0),
                                 2*halfHeight*ofRandom(1-streetPortion, 1.0), maxZ*ofRandom(0.5,0.9));
        building dBld = building(rightBottomCenter, 2*halfWidth*ofRandom(1-streetPortion, 1.0),
                                 2*halfHeight*ofRandom(1-streetPortion, 1.0), maxZ*ofRandom(0.5,0.9));
        blds.push_back(aBld);
        blds.push_back(bBld);
        blds.push_back(cBld);
        blds.push_back(dBld);
        
        return;
    }
    float rdm1 =ofRandom(0.4, 0.5);
    float rdm2 =ofRandom(0.4, 0.5);
    float rdm3 =ofRandom(0.4, 0.5);
    float rdm4 =ofRandom(0.4, 0.5);
    
    subdivide (leftTopCenter, halfWidth * rdm1, halfHeight * rdm1, maxZ, blds);
    subdivide (rightTopCenter, halfWidth * rdm2, halfHeight * rdm2, maxZ, blds);
    subdivide (leftBottomCenter, halfWidth * rdm3, halfHeight * rdm3, maxZ, blds);
    subdivide (rightBottomCenter, halfWidth * rdm4, halfHeight * rdm4, maxZ, blds);
}