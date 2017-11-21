#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sstream>
#include <fstream>
#include <string>

#define TESTNO 2

using namespace std;

/**
	Tests all the cases for insert i.e leaf insert, leaf overflow and split, index insert and index overflow
*/

// utility to read file input to string
string openFile(string filepath){
	string text = "", str;

	ifstream inFile;
	inFile.open(filepath.c_str());

	if(!inFile.good()) cout << "error reading file" << endl;
	
	while(inFile >> str){
		text += str + "\n";
	}
	inFile.close();
	
	return text;
}

int main(){
	ostringstream s;
	// running test command to generate output
	s << "./treesearch " << "tests/data/input" << TESTNO << ".txt";
	system(s.str().c_str());
	
	// asserting if output is right
	string result1 = openFile("output_file.txt");
	string result2 = openFile("tests/data/output2.txt");

	if(result1 == result2) cout << "test " << TESTNO << " passing" << endl;
	else cout << "test1 failing" << endl;
	
	return 0;
}
