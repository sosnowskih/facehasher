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

vector<string> consoleCmd(const string &input, bool bifurcate);
vector<string> createHash(string &filename);

int main() {

    // Choose file name that is hashed by default
    string filename = "kulning.jpg";

    // Create vector to hold file hash
    vector<string> sumVec = createHash(filename);

    // 

    time_t t = std::time(0);
    string key = std::to_string(t);

    cout << key << endl;

    string updateKey = "curl --silent --user user2570792372:pass00a0ab69baea20579d7dcf36ed9577969af32731e01b7651ab81c5496df4a12f64 --data-binary '{\"jsonrpc\": \"1.0\", \"id\":\"curltest\", \"method\": \"kvupdate\", \"params\": [\"";
    updateKey = updateKey + key + "\", \"" + sumVec[0] + "\", \"2\"] }' -H 'content-type: text/plain;' http://127.0.0.1:25435"; 
    cout << "updateKey: " << updateKey << endl;

    vector<string> sendKey = consoleCmd(updateKey, false); 
    
    Json::CharReaderBuilder builder2;
    Json::CharReader* reader2 = builder2.newCharReader();

    Json::Value json2;
    string errors2;

    bool parsingSuccessful2 = reader2 -> parse(
            sendKey[0].c_str(),
            sendKey[0].c_str() + sendKey[0].size(),
            &json2,
            &errors2
    );
    delete reader2;

    if (!parsingSuccessful2) {
        cout << "Failed to parse the JSON, errors: " << endl;
        cout << errors2 << endl;
        return 0;
    }

    cout << "key: " << json2["result"].get("key", "default value").asString() << endl;
    cout << "value: " << json2["result"].get("value", "default value").asString() << endl;
    cout << "txid: " << json2["result"].get("txid", "default value").asString() << endl;
    return 0;
}

vector<string> createHash(string &filename) { 
    // Initiate the string that holds the sha256sum command to run in the terminal
    string cmd = "sha256sum ";

    // Add filename to the sha256sum command
    cmd = cmd + filename; 


    vector<string> sumVec = consoleCmd(cmd, true); 
    cout << filename << " " << "hash: " << sumVec[0] << endl;

    return sumVec;
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

