/**
 * notarization.cpp
 * CS 201
 * Henryk Sosnowski and Bryan Beus
 * October 12, 2019
 * Hashes the image and inserts the hash into a notarized blockchain
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

// #include "facehasher.hpp"

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

int main() {

    // Choose file name that is hashed by default
    string filename = "kulning.jpg";

    // Create vector to hold file hash
    vector<string> sumVec = createHash(filename);

    // Print hash to console
    cout << filename << " " << "hash: " << sumVec[0] << endl;

    // Obtain the kvStore response as a string
    vector<string> kvStore = createKVStore(sumVec);

    // Convert the kvStore value to a Json::Value object for parsing 
    Json::Value jsonKVStore = convertVecToJson(kvStore);

    // To display returned values, create vector to store names of values
    vector<string> valNames {"key", "value", "txid", "height"};

    // Display returned values
    for (int i = 0; i < 4; i++) {
        // Set preferences for left side of console printout
        cout << setw(20);
        cout << left;
        
        // Print value name
        cout << valNames[i] << ": ";

        // Set preference for right side of console printout
        cout << setw(30);
        cout << right;

        // Print value
        jsonKVStore["result"].get(valNames[i], "default value").asString() << endl;

    }
    return 0;
}

vector<string> createHash(string &filename) { 
    // Initiate the string that holds the sha256sum command to run in the terminal
    string cmd = "sha256sum ";

    // Add filename to the sha256sum command
    cmd = cmd + filename; 

    vector<string> sumVec = consoleCmd(cmd, true); 

    return sumVec;
}

Json::Value convertVecToJson(const vector<string> & input) { 
    
    Json::CharReaderBuilder builder;
    Json::CharReader* reader = builder.newCharReader();

    Json::Value json;
    string errors;

    bool parsingSuccessful = reader -> parse(
            input[0].c_str(),
            input[0].c_str() + input[0].size(),
            &json,
            &errors
    );
    delete reader;

    if (!parsingSuccessful) {
        cout << "Failed to parse the JSON, errors: " << endl;
        cout << errors << endl;
        return 0;
    }

    return json;
}

vector<string> createKVStore(const vector<string> & sumVec) {

    time_t t = std::time(0);
    string key = std::to_string(t);

    string updateKey = "curl --silent --user user2570792372:pass00a0ab69baea20579d7dcf36ed9577969af32731e01b7651ab81c5496df4a12f64 --data-binary '{\"jsonrpc\": \"1.0\", \"id\":\"curltest\", \"method\": \"kvupdate\", \"params\": [\"" + key + "\", \"" + sumVec[0] + "\", \"2\"] }' -H 'content-type: text/plain;' http://127.0.0.1:25435"; 

    vector<string> sendKey = consoleCmd(updateKey, false); 

    return sendKey; 
}

vector<string> consoleCmd(const string &input, bool bifurcate) {

    // Reference to this tutorial
    // https://www.jeremymorgan.com/tutorials/c-programming/how-to-capture-the-output-of-a-linux-command-in-c/

    string cmd = input;
    string data; 
    FILE * stream;
    const int max_buffer = 256;
    char buffer[max_buffer];

    if (bifurcate)
        cmd.append(" 2>&1");

    // cout << "Executing: " << cmd << endl;
    stream = popen(cmd.c_str(), "r");

    if (stream) {
        while (!feof(stream)) {
            if (fgets(buffer, max_buffer, stream) != NULL)
                data.append(buffer); 
        }
        pclose(stream);
    }

    istringstream instream(data); 
    vector<string> res; 
    if (bifurcate) { 
        while (!instream.eof()) { 
            string temp;
            instream >> temp;
            res.push_back(temp); 
        }
    } else {
        res.push_back(data);
    }

    return res; 
}

