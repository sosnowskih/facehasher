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
using std::this_thread;
using std::chrono;

vector<string> consoleCmd(const string &input);

int main() {

    // Get the sha256sum of the image 
    string filename = "kulning.jpg"; 
    string cmd = "sha256sum ";
    cmd = cmd + filename; 
    vector<string> sumVec = consoleCmd(cmd); 
    cout << filename << " " << "hash: " << sumVec[0] << endl;

    // Load credentials as environment variables
    
    // Launch RICK chain
    string launchRick = "/home/$USER/komodo/src/komodod -pubkey=$pubkey -ac_name=RICK -ac_supply=90000000000 -ac_reward=100000000 -ac_cc=3 -ac_staked=10 -addnode=95.217.44.58 -addnode=138.201.136.145 &";
    vector<string> rickLaunchRes = consoleCmd(launchRick); 

    while (true) {
        
        if (res == "finished")
            break;
    }

    return 0;
}

vector<string> consoleCmd(const string &input) {

    // Reference to this tutorial
    // https://www.jeremymorgan.com/tutorials/c-programming/how-to-capture-the-output-of-a-linux-command-in-c/

    string cmd = input;
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

void timer_start(function<void(void)> func, unsigned int interval) {
    thread([func, interval]() {
        while (true)
        {
            func();
            this_thread::sleep_for(chrono::milliseconds(interval));
        }
    }).detach();
}

vector<string> rickGetInfo() {
    string cmd = "curl --user $rpcuser:$rpcpassword --data-binary '{\"jsonrpc\": \"1.0\", \"id\":\"curltest\", \"method\": \"getinfo\", \"params\": [] }' -H 'content-type: text/plain;' http://127.0.0.1:$rpcport/";
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
