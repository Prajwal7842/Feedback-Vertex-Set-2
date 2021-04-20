#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
	ifstream file; 
	if(argc != 2) {
		cout << "Usage " << argv[0] << " <Input File Name>" << endl;
		return 0;
	}
	file.open(argv[1]);
	string input, output;
	int k;
	vector<string> inputFileName, outputFileName;
	vector<int> K_val;
	while(file >> input >> output >> k) {
		inputFileName.push_back(input);
		outputFileName.push_back(output);
		K_val.push_back(k);
	}
	int l = inputFileName.size();
	for(int i = 0; i < l; i += 1) {
		string command = "../main "+ inputFileName[i] + " " + outputFileName[i] + " " + to_string(K_val[i]);
		const char *c = command.c_str();
		system(c);
		cout << inputFileName[i] << " " << outputFileName[i] << " " << K_val[i] << endl;
	}
	return 0;
}