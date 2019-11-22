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
#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include <functional>
#include <curl/curl.h>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/writer.h>
#include <jsoncpp/json/value.h>
#include <ctime>

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
using std::thread;
using std::time_t;
using std::setw;
using std::left;
using std::right;

int main(int argv, char **argc) {

	image_capture();

	// Choose file name that is hashed by default
	string filename = "image.jpg";

	// Create vector to hold file hash
	vector<string> sumVec = createHash(filename);

	// Print hash to console
	cout << filename << " " << "hash: " << sumVec[0] << endl;

	// Obtain the kvStore response as a string
	vector<string> kvStore = createKVStore(sumVec);

	// Convert the kvStore value to a Json::Value object for parsing 
	Json::Value jsonKVStore = convertVecToJson(kvStore);

	// Test that json values were properly converted, and if not, end program
	if (jsonKVStore.size() < 4)

	// Print json values to console
	cout << "key: " << jsonKVStore["result"].get("key", "default value").asString() << endl;
	cout << "value: " << jsonKVStore["result"].get("value", "default value").asString() << endl;
	cout << "txid: " << jsonKVStore["result"].get("txid", "default value").asString() << endl;
	cout << "height: " << jsonKVStore["result"].get("height", "default value").asString() << endl;

	return 0;

}

