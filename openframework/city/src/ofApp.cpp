#include "ofApp.h"
#include "ofMain.h"
//#include "ofxUI.h"

//--------------------------------------------------------------
// fog
// extend further
// outline




void ofApp::setup(){
	ofSetVerticalSync(true);
	// this uses depth information for occlusion
	// rather than always drawing things on top of each other
	ofEnableDepthTest();
	
	// ofBox uses texture coordinates from 0-1, so you can load whatever
	// sized images you want and still use them to texture your box
	// but we have to explicitly normalize our tex coords here
	ofEnableNormalizedTexCoords();

	// draw the ofBox outlines with some weight
    ofSetLineWidth(2);//
    
    
    cam.setupPerspective(false, 60, 10, 5000);
    cam.setPosition(camPos);
    cam.lookAt(camTarPos,ofVec3f(0.0f,0.0f,1.0f));

    for(int i = 0; i< 10; i++){
        deeps[i] = d + ofRandom(-0.5, 0.5)*(d+0.0);
    }
    
    subdivide(ofVec3f(0,0,0), BLOCKSIZE/2, BLOCKSIZE/2, 400, buildings);
    
    //
    // setting lights
    //
    ofSetGlobalAmbientColor(ofColor(100,100,100));
    light.setDiffuseColor(ofFloatColor(255.0, 0.0, 0.0f));
    light.setSpecularColor(ofColor(0, 0, 255));
    light.setPointLight();
    light.setPosition(500, 500, 600);
    //light.setSpotConcentration(5);
    //light.setSpotlightCutOff(10);
    
    
    //
    // setting materials
    //
    material.setShininess(120);
    material.setSpecularColor(ofColor(255, 255, 255, 255));
    material.setEmissiveColor(ofColor(0, 0, 0, 255));
    material.setDiffuseColor(ofColor(255, 255, 255, 255));
    material.setAmbientColor(ofColor(255, 255, 255, 255));
    
	rotation = 1;
    camTarVelocity.normalize();
    
    //
    // set up blocks to draw
    //
    currentBlockCenter = ofVec2f(0,0);
    
    for (int i =0; i<BLOCKSTODRAW; i++) {
        int row = i/sqrt(BLOCKSTODRAW) - (int)sqrt(BLOCKSTODRAW)/2;
        int col = i%(int)sqrt(BLOCKSTODRAW) - (int)sqrt(BLOCKSTODRAW)/2;
        visibleBlockCenters[i] = (ofVec2f(currentBlockCenter.x+row*BLOCKSIZE,
                                              currentBlockCenter.y+col*BLOCKSIZE));
    }
    
#ifdef TARGET_OPENGLES
    shader.load("shadersES2/shader");
#else
    if(ofIsGLProgrammableRenderer()){
        shader.load("shadersGL3/shader");
        cout <<"shadersGL3"<<endl;
    }else{
        shader.load("shadersGL2/shader");
    }
#endif
    

}

//--------------------------------------------------------------
void ofApp::update(){
    
    //
    // check target turning
    //
    if (ifTurn == TURNLEFT){
        ofVec3f toTurn = ofVec3f(0,0,1).cross(camVelocity);
        toTurn.normalize();
        camTarVelocity += TURNINGSHARPNESS*toTurn;
    }else if (ifTurn == TURNRIGHT){
        ofVec3f toTurn = camVelocity.cross(ofVec3f(0,0,1));
        toTurn.normalize();
        camTarVelocity += TURNINGSHARPNESS*toTurn;
    }else if (ifTurn == TURNUP){
        camTarPos.z += 5;
    }else if (ifTurn == TURNDOWN){
        camTarPos -= 5;
    }
    ifTurn = NOTURN;
    
    //
    // update camera v
    //
    camVelocity = camTarPos - camPos;
    if ((camPos.z < 1.5*BLOCKHEIGHT && camVelocity.z <0 )|| (camPos.z > 4*BLOCKHEIGHT && camVelocity.z >0 )){
        camVelocity.z = 0;
    }
    camVelocity.normalize();
    camTarVelocity.normalize();
    
    if(ofDist(camPos.x,camPos.y,camPos.z,camTarPos.x,camTarPos.y,camTarPos.z ) < 300){
        camVelocity *= 0.9;
    }
    
    camPos+= camSpeed * camVelocity;
    camTarPos+= tarSpeed * camTarVelocity;
    
    //
    // update current block in
    //
    for (int i =0; i<BLOCKSTODRAW; i++) {
        if ( abs(camPos.x -visibleBlockCenters[i].x) < BLOCKSIZE/2 && abs(camPos.y -visibleBlockCenters[i].y) < BLOCKSIZE/2 ) {
            currentBlockCenter = visibleBlockCenters[i];
            newBlock =1;
            //cout << "center: " << currentBlockCenter <<endl;
        }
    }
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0, 0, 0);
    ofDrawBitmapStringHighlight("buildings", 20, 20);
    
    
    cam.setPosition(camPos - 300*(camTarPos - camPos).normalize() +100*ofVec3f(0,0,1));
    cam.lookAt(camPos,ofVec3f(0.0f,0.0f,1.0f));
    

    
    shader.begin();
    cam.begin();
    
    
    //
    // debug cam targets
    //
    ofNoFill();
    ofSetColor(0, 255, 0);//stroke color
    
    ofDisableLighting();
    glEnable(GL_COLOR_MATERIAL);
    
    
    //
    // axis
    //
    ofSetColor(0, 0, 255);//stroke color
    ofDrawLine(0,0,0, 0, 0,400);
    ofSetColor(0, 255, 0);//stroke color
    ofDrawLine(0,0,0, 0, 400,0);
    ofSetColor(255, 0, 0);//stroke color
    ofDrawLine(0,0,0, 400, 0,0);
    ofDrawCircle(camPos, 5);
    ofDrawCircle(camPos.x, camPos.y, 0 , 30);
    
    ofSetColor(0, 0, 255);//stroke color
    ofDrawCircle(camTarPos, 30);

    
    // transparent fog
    ofPushMatrix();
    ofVec3f fogVec = camPos+  fogDist*(camTarPos - camPos).normalize();
    ofTranslate(fogVec);
    ofVec3f fogAngle = ofVec3f((-camPos+fogVec).x, (-camPos+fogVec).y, 0).normalize();
    
    ofSetColor(0, 255, 0);//stroke color
    float angleZ = -90-180*(atan2(fogAngle.x, fogAngle.y))/PI;
    
    ofRotateZ(angleZ);
    ofColor fog;
    fog.r = 100;
    fog.g = 100;
    fog.b = 100;
    ofSetColor(fog);//stroke color

    ofFill();
    ofDrawBox(0, 0, 0, 2, 1500, 600);
    ofPopMatrix();
    
    //
    // newblock
    //
    if(newBlock){
        cout << endl;
        for (int i =0; i<BLOCKSTODRAW; i++) {
            int row = i/(int)sqrt(BLOCKSTODRAW) - (int)sqrt(BLOCKSTODRAW)/2;
            int col = i%(int)sqrt(BLOCKSTODRAW) - (int)sqrt(BLOCKSTODRAW)/2;
            visibleBlockCenters[i] = (ofVec2f(currentBlockCenter.x+row*BLOCKSIZE,
                                              currentBlockCenter.y+col*BLOCKSIZE));
            //cout << row <<" "<< col <<endl;
        }
        newBlock=0;
    }
    // block chcking
     /*for (int j=0; j<BLOCKSTODRAW; j++) {
        int row = j/(int)sqrt(BLOCKSTODRAW) - 1;
        int col = j%(int)sqrt(BLOCKSTODRAW) - 1;
        ofDrawBox(currentBlockCenter.x+ row*BLOCKSIZE,
                  currentBlockCenter.y+ col*BLOCKSIZE, 20,
                  BLOCKSIZE, BLOCKSIZE, 20);
    }*/
    
    
    for (int j =0; j<BLOCKSTODRAW; j++) {
        int row = j/(int)sqrt(BLOCKSTODRAW) - 1;
        int col = j%(int)sqrt(BLOCKSTODRAW) - 1;
        
        for (int i =0; i<buildings.size(); i++) {
        
        ofPushMatrix();
        
        ofVec3f pos(currentBlockCenter.x+ row*BLOCKSIZE +buildings[i].center.x,
                    currentBlockCenter.y+ col*BLOCKSIZE +buildings[i].center.y,
                    buildings[i].deep/2);
        ofTranslate(pos);
        ofRotateZ(rotation);
    
        drawBuildingLines(buildings[i].width, buildings[i].height, buildings[i].deep, 0);
    
        glDisable(GL_COLOR_MATERIAL);
    
    
        ofEnableLighting();
        light.enable();
        material.begin();
        
        drawBuilding(buildings[i].width, buildings[i].height, buildings[i].deep, 0);
        //ofDrawBox(buildings[i].width, buildings[i].height, 10);
        ofPopMatrix();
        
        material.end();
        light.disable();
        }
    }
    


    cam.end();
    shader.end();
    //cout <<"s"<<endl;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if (key == OF_KEY_LEFT){
        ifTurn = TURNLEFT;
    }
    if (key == OF_KEY_RIGHT){
        ifTurn = TURNRIGHT;
    }
    if (key == OF_KEY_UP){
        ifTurn = TURNUP;
    }
    if (key == OF_KEY_DOWN){
        ifTurn = TURNDOWN;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
