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

vector<string> consoleCmd(const string &input, bool bifurcate);
void timer_start(function<void(void)> func, unsigned int interval);
bool syncRick();
vector<string> rickGetInfo();

int main() {

    // Get the sha256sum of the image 
    string filename = "kulning.jpg"; 
    string cmd = "sha256sum ";
    cmd = cmd + filename; 
    vector<string> sumVec = consoleCmd(cmd, true); 
    cout << filename << " " << "hash: " << sumVec[0] << endl;

    // Load credentials as environment variables
    // string loadRickCreds = "cat /home/siddhartha/.komodo/RICK/RICK.conf";
    // vector<string> loadRickRes = consoleCmd(loadRickCreds);
    // for (auto str: loadRickRes)
        // cout << "loadRickRes: " << str << endl;

    // Test sync rick chain
    string getInfoCmd = "curl --silent --user user2570792372:pass00a0ab69baea20579d7dcf36ed9577969af32731e01b7651ab81c5496df4a12f64 --data-binary '{\"jsonrpc\": \"1.0\", \"id\":\"curltest\", \"method\": \"getinfo\", \"params\": [] }' -H 'content-type: text/plain;' http://127.0.0.1:25435/ | jq '. | {result: .result}'"; 
    vector<string> syncRes = consoleCmd(getInfoCmd, false);
    cout << syncRes[0] << endl;

    Json::Value root;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse(syncRes[0].c_str(), root );
    if (!parsingSuccessful) {
        cout << "Failed to parse" << reader.getFormattedErrorMessages();
        return 0;
    }
    cout << root.get("result.synced", "false").asString() << endl; 
    
    // Launch RICK chain
    // string launchRick = "/home/$USER/komodo/src/komodod -pubkey=$pubkey -ac_name=RICK -ac_supply=90000000000 -ac_reward=100000000 -ac_cc=3 -ac_staked=10 -addnode=95.217.44.58 -addnode=138.201.136.145 &";
    // vector<string> rickLaunchRes = consoleCmd(launchRick); 

    // while (true) {
        
        // if (res == "finished")
            // break;
    // }

    return 0;
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

void timer_start(function<void(void)> func, unsigned int interval) {
    // thread([func, interval]() {
        // while (true)
        // {
            // func();
            // std::this_thread::sleep_for(std::chrono::milliseconds(interval));
        // }
    // }).detach();
}

bool syncRick() { 
    string cmd = "curl --user user2570792372:pass00a0ab69baea20579d7dcf36ed9577969af32731e01b7651ab81c5496df4a12f64 --data-binary '{\"jsonrpc\": \"1.0\", \"id\":\"curltest\", \"method\": \"getinfo\", \"params\": [] }' -H 'content-type: text/plain;' http://127.0.0.1:25435/"; 

    // thread([consoleCmd, 5000]()) { 
        // while (true) { 
            // consoleCmd(cmd);
            // if (res == true) {
                // break;
            // }
        // }
    // }

    return true;
}

vector<string> rickGetInfo() {
    string cmd = "curl --user user2570792372:pass00a0ab69baea20579d7dcf36ed9577969af32731e01b7651ab81c5496df4a12f64 --data-binary '{\"jsonrpc\": \"1.0\", \"id\":\"curltest\", \"method\": \"getinfo\", \"params\": [] }' -H 'content-type: text/plain;' http://127.0.0.1:25435/"; 
    string data; 
    FILE * stream;
    const int max_buffer = 256;
    char buffer[max_buffer];
    cmd.append(" 2>&1");

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

    while (!instream.eof()) { 
        string temp;
        instream >> temp;
        res.push_back(temp); 
    }

    return res;   
}
