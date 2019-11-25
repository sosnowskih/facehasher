/**
 * facehasher_main.cpp
 * CS 201
 * Henryk Sosnowski and Bryan Beus
 * October 12, 2019
 * Outputs data for facehasher into a GUI display
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include <functional>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/writer.h>
#include <jsoncpp/json/value.h>

#include "facehasher.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;
using std::noskipws;
using std::getline;
using std::istringstream;
using std::ostringstream;
using std::find; 
using std::ifstream;
using std::function;
using std::setw;
using std::left;
using std::right;

// Clear the console
void clearConsole();

// Wait for user response
void waitForContinue();

int main(int argv, char **argc) {

	// Initiate bool to track if each stage of the program passes successfully, and to cease program if any section fails
	bool canContinue = true;

	clearConsole();

	cout << "Capturing an image from the first available webcam..." << endl;

	// Capture an image from a webcam
	image_capture(canContinue);

	// Test if image capture performed successfully
	if (!canContinue)
		return 0;

	// Begin processing hash 
	cout << endl << "Creating a hash of the captured image..." << endl;

	// Choose file name that is hashed by default
	string filename = "image.jpg";

	// Create vector to hold file hash
	vector<string> sumVec = createHash(filename, canContinue);

	// Test if hash performed successfully
	if (!canContinue)
		return 0; 

	// Print hash to console
	cout << endl << "Hash created successfully. The value is: " << sumVec[0] << endl;
	cout << endl << "Storing the hash in the RICK blockchain for permanent safekeeping." << endl;

	// Obtain the kvStore response as a string
	vector<string> kvStore = createKVStore(sumVec, canContinue);

	// Test if createKVStore performed successfully
	if (!canContinue) {
		cout << "CreateKVStore func did not perform as expected" << endl;
		return 0; 
	}

	// Convert the kvStore value to a Json::Value object for parsing 
	Json::Value jsonKVStore = convertVecToJson(kvStore);

	// Test that json values were properly converted, and if not, end program
	if (jsonKVStore.size() < 3) {
		cout << endl << "jsonKVStore value is too small" << endl;
		return 0;
	}

	// Print json values to console

	cout << endl;
	cout << "Congratulations, a hash proving your visual data is now permanently recorded in the RICK blockchain, and will reach the Bitcoin security service in twenty to thirty minutes." << endl;
	cout << "Please save the image.jpg file found in the root directory of this project, as well as the following information: " << endl;
	cout << "key: " << jsonKVStore["result"].get("key", "default value").asString() << endl;
	cout << "value: " << jsonKVStore["result"].get("value", "default value").asString() << endl;
	cout << "txid: " << jsonKVStore["result"].get("txid", "default value").asString() << endl;
	cout << "height: " << jsonKVStore["result"].get("height", "default value").asString() << endl;

	cout << endl << "Thank you." << endl;

	waitForContinue();

	return 0;

}

// Clear the console
void clearConsole() {

    // Clear the console
    cout << "\033[2J\033[1;1H";
}

// Wait for user response
void waitForContinue() {
    cout << endl << "Press enter to continue...";
    getchar();
}


