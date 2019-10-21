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
#include <experimental/filesystem>
#include cp = <childprocess>

// #include "facehasher.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;
using std::noskipws;
using std::getline;
using std::istringstream;
using std::find; 
namespace fs = std::experimental::filesystem;

int main(int argv, char **argc) {

	cout << "Current path is " << fs::current_path() << endl;

	cp.exec("./komodod -ac_name=RICK", res, err) {
		isLaunched = listen(getinfo == true);
	}

	string facehashed;
	cp.exec("curl --user $rpcuser:$rpcpassword --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "kvupdate", "params": ["examplekey", "examplevalue", "2", "examplepassphrase"] }' -H 'content-type: text/plain;' http://127.0.0.1:9801", res, err) {
		facehashed = res[0];

	}

	guiProgram.displayFaceHash(facehashed);
}
