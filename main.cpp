#include <main.h>

using namespace std;

/**
	main driver for the program
*/
int main(int argc, char** argv){
	parseInput(argc, argv);
}

/**
    parse input arguments to get input data file path and build queries from file or throw 
    error if file path not provided or bad file path 
 */

void parseInput(int argc, char** argv){
	string path;

	if(argc == 2){
		path = *(++argv);
		ifstream f(path.c_str());
		
		if(!f.good()) cerr << "Couldn't open the specified input file" << endl;	   /** error handling for bad file paths */	
		else processQueries(path);
	}
	else{
		cerr << "Please provide path to input file" << endl;
	}
}

/**
    process input file line by line to build and execute queries 
 */

void processQueries(string filepath){
	int order;
	string s, output = "";
	ofstream opfile;
	ifstream input(filepath);

	input >> order;
	BPTree bptree = BPTree(order);
	
	while(input >> s){
		if(s == "") continue;				
		vector<string> query = buildQuery(s);

		if(query[0] == "I"){
			bptree.insert(atof(query[1].c_str()), query[2]);
		}
		else if(query[0] == "S"){	
			if(query.size() == 3) output += bptree.rangeSearch(atof(query[1].c_str()), atof(query[2].c_str())) + "\n";
			else output += bptree.search(atof(query[1].c_str())) + "\n";
		}
	}			 
	
	opfile.open(OUTPUT_FILE_PATH);
	opfile << output;
	opfile.close();
}

/**  
    parse string to build query ( insert, search or range search) 
*/

vector<string> buildQuery(string s){
	vector<string> query;
	bool start = false;
	string tmp = "";
	
	tmp += s[0];
	query.push_back(tmp);
	
	for(int i = 1; i < (int)s.length(); i++){
		if(start){
			if(s[i] == ',' || s[i] == ')'){
				query.push_back(tmp);
				tmp = "";
				continue;
			}
			tmp += s[i];
		}else{
			if(s[i] == '(') start = true, tmp = "";
		}							
	}
	
	return query;
}

