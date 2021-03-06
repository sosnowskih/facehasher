/**
 * facehasher.hpp
 * CS 201
 * Henryk Sosnowski and Bryan Beus
 * October 12, 2019
 * 
 */

#ifndef _FACEHASHER_HPP_
#define _FACEHASHER_HPP_

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
#include <opencv2/opencv.hpp>

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

// Send a command to the console
vector<string> consoleCmd(const string &input, bool bifurcate);

// Create a sha256sum hash of a file
vector<string> createHash(string &filename, bool& canContinue);

// Create a KV store transaction and process it on the blockchain
vector<string> createKVStore(const vector<string> & sumVec, bool& canContinue);

// Request a json response from a software daemon
Json::Value convertVecToJson(const vector<string> & input);

// Capture an image from a webcam
void image_capture(bool & canContinue);

#endif
