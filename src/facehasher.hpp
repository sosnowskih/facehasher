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
// #include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include <functional>
// #include <curl/curl.h>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/writer.h>
#include <jsoncpp/json/value.h>
#include <ctime>
#include <opencv2/opencv.hpp>
// #include <filesystem>

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

vector<string> consoleCmd(const string &input, bool bifurcate);
vector<string> createHash(string &filename);
vector<string> createKVStore(const vector<string> & sumVec);
Json::Value convertVecToJson(const vector<string> & input);
void image_capture();

#endif
