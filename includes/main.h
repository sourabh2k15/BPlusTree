#include <BPTree.h>

#include <fstream>
#include <stdexcept>

#define OUTPUT_FILE_PATH "output_file.txt"

using namespace std;

void parseInput(int, char**);
void processQueries(string);
vector<string> buildQuery(string);
