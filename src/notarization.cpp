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
// #include <ctime>

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
// using std::thread;
// using std::time_t;
using std::setw;
using std::left;
using std::right;

// Create a sha256sum hash of a file, from a provided filename
vector<string> createHash(string &filename) { 
    // Initiate the string that holds the sha256sum command to run in the terminal

#ifdef _WIN32
	
    string cmd = "sha256sum.exe ";

#elif __unix__
	
	string cmd = "sha256sum ";

#endif

    // Add filename to the sha256sum command
    cmd = cmd + filename; 

    // Send the complete command to the console for processing
    // Indicate via bool that response string should be bifurcated into separate values
    // This keeps the hash value separate from the name of the file in the response from the sha256 command
    vector<string> sumVec = consoleCmd(cmd, true); 

    // Return result
    return sumVec;
}

// Convert a vector to a json object
Json::Value convertVecToJson(const vector<string> & input) { 
    
    // Delcare json reader and builders for processing
    Json::CharReaderBuilder builder;
    Json::CharReader* reader = builder.newCharReader();

    // Declare final json value to be returned
    Json::Value json;
    
    // Declare string to hold errors
    string errors;

    // Declare bool variable to test if parse is succesful
    // Pass into parse() function the first element in the input vector
    // This element holds the result from the call to the blockchain
    // Also pass in the json variable and errors variable
    bool parsingSuccessful = reader -> parse(
            input[0].c_str(),
            input[0].c_str() + input[0].size(),
            &json,
            &errors
    );

    // Clean up pointer
    delete reader;

    // Test if parsing was successful, and if not, print to console
    if (!parsingSuccessful) {
        cout << "Failed to parse the JSON, errors: " << endl;
        cout << errors << endl;
    }

    // Return json values
    // Or empty vector
    return json;
}

// Send a hash to the RICK blockchain for decentralized storage
vector<string> createKVStore(const vector<string> & sumVec) {

    // Create a timestamp in string form
    // This acts as the key value
    time_t t = std::time(0);
    string key = std::to_string(t);

    // Create the full curl command to execute in the terminal
    string updateKey = "curl --silent --user user3789197396:passe6ba30ce2b58b085b63f739613aee3016766c6dc6daaf9e74b1a89adf47322627a --data-binary '{\"jsonrpc\": \"1.0\", \"id\":\"curltest\", \"method\": \"kvupdate\", \"params\": [\"" + key + "\", \"" + sumVec[0] + "\", \"2\"] }' -H 'content-type: text/plain;' http://127.0.0.1:25435"; 

    // Send string command to consoleCmd() function to process
    // Store returned vector as sendKey
    vector<string> sendKey = consoleCmd(updateKey, false); 

    return sendKey; 
}

// Execute a command in the Unix terminal, from a provided string
// If necessary, cut the returned string response into separate elements in the to-be-returned vector
vector<string> consoleCmd(const string &input, bool bifurcate) {

    // Reference to this tutorial
    // https://www.jeremymorgan.com/tutorials/c-programming/how-to-capture-the-output-of-a-linux-command-in-c/

    // Create string to hold command after adjustments
    string cmd = input;

    // Create string to hold returned data
    string data; 

    // Create file stream and pointer
    FILE * stream;

    // Declare max buffer size
    const int max_buffer = 256;

    // Create buffer array of char type
    char buffer[max_buffer];

    // If bifurcate == true, instruct the console to store all values in the "1" variable in bash terminal
    if (bifurcate)
        cmd.append(" 2>&1");

    //
#ifdef _WIN32

    // Execute the command as a c string, using popen()
    stream = _popen(cmd.c_str(), "r");

#elif __unix__

    // Execute the command as a c string, using popen()
    stream = popen(cmd.c_str(), "r");

#endif
    // If there is a positive returned response
    // Push this response into the data variable
    if (stream) {
        while (!feof(stream)) {
            if (fgets(buffer, max_buffer, stream) != NULL)
                data.append(buffer); 
        }

#ifdef _WIN32 
        // End the shell process
        _pclose(stream);
    }

#elif __unix__ 

        // End the shell process
        pclose(stream);
    }

#endif

    // Declare a stream and a vector to hold final values
    istringstream instream(data); 
    vector<string> res; 

    // If bifurcating result, use the stream to separate each input and push into res
    if (bifurcate) { 
        while (!instream.eof()) { 
            string temp;
            instream >> temp;
            res.push_back(temp); 
        }

    // Otherwise, push the entire response into the first element of the res vector
    } else {
        res.push_back(data);
    }


    return res; 
}

