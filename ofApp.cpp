#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	auto noise_seed = ofRandom(1000);
	int radius_span = 60;
	for (int radius = 0; radius <= 600; radius += radius_span) {

		vector<glm::vec2> vertices;
		for (int deg = 0; deg < 360; deg += 120) {

			auto noise_deg_1 = ofMap(ofNoise(noise_seed, radius * 0.001 - ofGetFrameNum() * 0.005), 0, 1, -270, 270);
			auto noise_deg_2 = ofMap(ofNoise(noise_seed, (radius + radius_span) * 0.001 - ofGetFrameNum() * 0.005), 0, 1, -270, 270);

			auto location_1 = glm::vec2(radius * cos((deg + noise_deg_1) * DEG_TO_RAD), radius * sin((deg + noise_deg_1) * DEG_TO_RAD));
			auto location_2 = glm::vec2((radius + radius_span) * cos((deg + noise_deg_2) * DEG_TO_RAD), (radius + radius_span) * sin((deg + noise_deg_2) * DEG_TO_RAD));

			this->draw_arrow(location_2, location_1, 18, ofColor(255));

			vertices.push_back(location_1);
		}

		/*
		ofNoFill();
		ofSetLineWidth(0.75);
		ofSetColor(139);

		ofBeginShape();
		ofVertices(vertices);
		ofEndShape(true);
		*/
	}

	/*
	int start = 275;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
void ofApp::draw_arrow(glm::vec2 location, glm::vec2 target, float size, ofColor color) {

	auto angle = std::atan2(target.y - location.y, target.x - location.x);
	auto translate_location = target - glm::vec2(size * 1.5 * cos(angle), size * 1.5 * sin(angle));
	auto distance = glm::distance(translate_location, location);

	ofPushMatrix();
	ofTranslate(translate_location);

	ofSetColor(color);
	ofFill();
	ofBeginShape();
	ofVertex(glm::vec2(size * cos(angle), size * sin(angle)));
	ofVertex(glm::vec2(size * 0.25 * cos(angle + PI * 0.5), size * 0.25 * sin(angle + PI * 0.5)));
	ofVertex(glm::vec2(size * 0.25 * cos(angle - PI * 0.5), size * 0.25 * sin(angle - PI * 0.5)));
	ofEndShape();

	ofBeginShape();
	ofVertex(glm::vec2(size * 0.25 * cos(angle + PI * 0.5), size * 0.25 * sin(angle + PI * 0.5)) * 0.25);
	ofVertex(glm::vec2(size * 0.25 * cos(angle + PI * 0.5), size * 0.25 * sin(angle + PI * 0.5)) * 0.25 - glm::vec2(distance * cos(angle), distance * sin(angle)));
	ofVertex(glm::vec2(size * 0.25 * cos(angle - PI * 0.5), size * 0.25 * sin(angle - PI * 0.5)) * 0.25 - glm::vec2(distance * cos(angle), distance * sin(angle)));
	ofVertex(glm::vec2(size * 0.25 * cos(angle - PI * 0.5), size * 0.25 * sin(angle - PI * 0.5)) * 0.25);

	ofEndShape();

	ofPopMatrix();

	ofDrawCircle(location, 5);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}