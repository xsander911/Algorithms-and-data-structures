#include <iostream>
#include <sstream>
#include <map>

using namespace std;

/*

*/

int main() {

	int k;
	
	cin >> k;
	if (k < 1 || k > 5)
		return 0;

	int rows = 4, cols = 4;
	int i = 0, j = 0;
	
	string numbers[4];
	
	getline(cin, numbers[0]);
	for (i = 0; i < rows; i++)
		getline(cin, numbers[i]);
	
	map<char, int> numberRepetition;
	
	int number = 0;
	int maximumScore = 0;
	
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
		
			if (numbers[i][j] == '.') continue;
			numberRepetition[numbers[i][j]] += 1;

		}
	}

	map <char, int> ::iterator it = numberRepetition.begin();
	for (; it != numberRepetition.end(); it++) {
		if (it->second <= k * 2)
			maximumScore++;
	}

	cout << maximumScore << endl;

	return 0;
}