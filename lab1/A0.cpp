#include <iostream>

using namespace std;


int countWords(string input) {
	int num = 0;
	bool lastCharIsSpace = true;

	for (char& c : input) {
		if (c == ' ' || c == '\t' || c == '\n') {
			lastCharIsSpace = true;
		} else {
			if (lastCharIsSpace) num++;
			lastCharIsSpace = false;
		}
	}

	return num;
}


int main(int argc, char** argv) {

	int numberOfWords;
	string inputString = argv[1];

	numberOfWords = countWords(inputString);

	cout << numberOfWords << endl;

	return 0;

}
