#include <iostream>
#include <vector>
using namespace std;
/*


*/
int main() {

	int n;
	cin >> n;
	if (n < 1 || n > 1000000)
		return 0;

	if (n == 1) {
		//есть хотя бы один ноль
		cout << 0 << endl;
		return 0;
	}
	if (n == 2) {
		int first, end;
		cin >> first;
		cin >> end;
		first = first > 0 ? 1 : 0;
		end = end > 0 ? 1 : 0;
		cout << first << " " << end << endl;
		return 0;
	}

	int i = 0, countLeft = 0, countRight = 0, value = 0;
	int detectLeftZero = 0, detectRightZero = 0;
	vector<int> data, direct, reverse, zeroindex;

	for (i = 0; i < n; i++) {
		cin >> value;
		if (!value)
			zeroindex.push_back(i);
		data.push_back(value);
	}
	/*
	or
	while(cin >> value)
		data.push_back(value);
	*/
	reverse.resize(n);

	for (i = 0; i < n; i++) {
		//прямой
		if (data[i] == 0) {
			direct.push_back(0);
			countLeft = 0;
		}
		else {
			countLeft++;
			direct.push_back(countLeft);
		}
		//обратный
		if (data[n - 1 - i] == 0) {
			reverse[n - 1 - i] = 0;
			countRight = 0;
		}
		else {
			countRight++;
			reverse[n - 1 - i] = countRight;
		}

	}

	if (zeroindex.size() == 1) {

		if (zeroindex[0] == 0) {
			for (i = 0; i < n; i++) {

				cout << direct[i] << " ";

			}
			cout << endl;
		}
		else if (zeroindex[0] == (n - 1)) {
			for (i = 0; i < n; i++) {

				cout << reverse[i] << " ";

			}
			cout << endl;
		}
		else {

			for (i = 0; i < zeroindex[0]; i++) {

				cout << reverse[i] << " ";

			}
			for (i = zeroindex[0]; i < n; i++) {

				cout << direct[i] << " ";

			}
			cout << endl;

		}
	}
	else {

		if (zeroindex[0] == 0 && zeroindex[zeroindex.size() - 1] == (n - 1)) {

			for (i = 0; i < n; i++)
				cout << min(direct[i], reverse[i]) << " ";
			
			cout << endl;

		}
		else if (zeroindex[0] == 0 && zeroindex[zeroindex.size() - 1] < (n - 1)) {

			for (i = 0; i < zeroindex[zeroindex.size() - 1]; i++)
				cout << min(direct[i], reverse[i]) << " ";

			for (i = zeroindex[zeroindex.size() - 1]; i < n; i++)
				cout << direct[i] << " ";
			
			cout << endl;

		}
		else if (zeroindex[0] > 0 && zeroindex[zeroindex.size() - 1] == (n - 1)) {

			for (i = 0; i < zeroindex[0]; i++)
				cout << reverse[i] << " ";

			for (i = zeroindex[0]; i < n; i++)
				cout << min(direct[i], reverse[i]) << " ";
			
			cout << endl;

		}
		else if (zeroindex[0] > 0 && zeroindex[zeroindex.size() - 1] < (n - 1)) {

			for (i = 0; i < zeroindex[0]; i++)
				cout << reverse[i] << " ";

			for (i = zeroindex[0]; i < zeroindex[zeroindex.size() - 1]; i++)
				cout << min(direct[i], reverse[i]) << " ";
			
			for (i = zeroindex[zeroindex.size() - 1]; i < n; i++)
				cout << direct[i] << " ";
			
			cout << endl;

		}

	}
	
	return 0;
}