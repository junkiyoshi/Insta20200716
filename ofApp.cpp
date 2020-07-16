#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_MULTIPLY);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofColor color;
	vector<ofColor> color_list;
	vector<int> hex_list = { 0x264653, 0x2a9d8f, 0xe9c46a, 0xf4a261, 0xe76f51 };
	for (auto hex : hex_list) {

		color.setHex(hex);
		color_list.push_back(color);
	}

	for (int x = 60 + 75; x < ofGetWidth() - 60; x += 150) {

		for (int y = 60 + 75; y < ofGetHeight() - 60; y += 150) {

			ofPushMatrix();
			ofTranslate(x, y);

			for (int k = 0; k < color_list.size(); k++) {

				auto noise_seed_deg = ofRandom(1000);
				auto noise_seed_radius = ofRandom(1000);

				vector<glm::vec2> vertices;
				for (int i = 0; i < 25; i++) {

					auto noise_deg = ofMap(ofNoise(noise_seed_deg, (ofGetFrameNum() + i) * 0.001), 0, 1, -360, 360);
					auto noise_radius = ofMap(ofNoise(noise_seed_radius, (ofGetFrameNum() + i) * 0.01), 0, 1, -75, 75);
					vertices.push_back(glm::vec2(noise_radius * cos(noise_deg * DEG_TO_RAD), noise_radius * sin(noise_deg * DEG_TO_RAD)));
				}

				ofSetColor(color_list[k]);
				for (int i = 0; i < 10; i++) {

					ofRotateZ(36);

					ofBeginShape();
					ofVertices(vertices);
					ofEndShape();
				}
			}

			ofPopMatrix();
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}