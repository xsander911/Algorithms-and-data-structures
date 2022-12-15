/*
ID - 69462250 (upd)

--������� ������--

������ ������� � ���� ���������� ���������� O(n3) :D 
����������� ����: ��� ������� ��������� ������� ��� ������� key = ���������� �����, value = ���������� ����������
����� �������� ������ �������� � ������� ���������� ���� 
� ����� ���������� ����������, ��� ���� ����������� �� ������� �������, � ������ ��������� ��������� ������� ����������� ����� �� �������, 
���������� �����,� ��� � ����� ������� ��������� :D

������� ������
��� ����������
�� ������� ��� ������� - key = ���������� �����, value = map, � �������� key = ����� ���������, value = ���������� ����������

��� ��������
������ ����� - key = �����, value = �����

��� ����������� �������� 
������ �������� ��������� �� ������ � ������� ����������� ������� � �����������)))))))))
������ ��������� ������ � ���� ���� ������ ��������� � �������������, � ����� ���������� ��� ����������, ����� �� ����� ������������� ������
�� ������� ������: ������ ����� �� �������������, ���� ������������ ����������, �� �� ������ ���������(�����������)

����� ����������, ��� � �������� ����� �� ���������� �� ������� ��������
-	�� ������ �������� ������� �� ����������� �� ���������� ������
		���������, ���� �� � ��� ��� ���������� ����� � ���-�������, ���� ���, �� �������� � ���� ����� � �������
		���� ����, �� ����� �� ������ � �������� ����� � �������� ���������, � ������� ���� ��� �����, � ����� ���������� ����������
		
- ����� ��������� ������ �������� relevance ��������� ����������� ��� �������
- ����� ������� �� (��� ���������� �������, ��� �� ����� 5 ����������, � ����� �� �������� ������ ��� ������ �������������) :D ���� ������� ������)
 
-- �������������� ������������ --
unordered_map ����� ������� ���������� ����� � ���� ���� ����, ������� ������������ �� ���� ����������
� ������� ����� ����� �������� � ����: ����� ��������� � ���������� ����������.
��� ��� �� ��������� ���������, ����� ��������(������) � ����� ������� ���������, ������ � ���� ������ �� ����� ������� � ����, 
� ����� ����� ���������� ��������� ������ �������������, �� ����� ���������� � ������ ��������� 1, ����� ��������������� ����������� ���������.
����� �� �������� �����, ��������� ������� ��� ����� �����, � ������� ����� ����� ��������� - i, �������� �������������� �� 1, 
��� ����� ��������� ���-�� ����������(�������������� ������ ���, ��� �������� � ���� �������, ���� �� ���������.
�� ������������ ���������� ������ ���� ����, �� ������������ � ���������� � ���������� ���������� � ���������.

����� �� ��������� ������ ��������, ������ ������ ���������� �����. �� ���������� �� ������� ��������, � ������ ������� �� ����� ����� 
� ��������� ���� �� ��� � ����� ��� �������. ���� ����, �� ��������� �� ����� ����� ������ (����� ���������+1 � ����������).

����� ������������ ������� �������� relevance �� �� ��������� �������� �������, ���������� ������ � ����� ���������.
����� ����������(���������� �� �� ������������), �� ������� �������� �������: 
	������ ����������� �� ����� �� ����� 5 ����������
	����� ������� ����� ���������, ��������� ������������� �� ��������� ����. ���� ����� ����, ����� �� �������.

-- ��������� ��������� --

����� �� �������� ������������ ������������� �� ����������:
�������� ���� - ���������� ���������� �������� - n;
�������������� ���� - ���������� ���������� ���� � ������� - m;
���� ����� ������������ � �������, ���������� �������� ������� - k; 
���������� O(nLog(n)), � ������ O(n^2)
����� ���������� O(n2) ���� if � for-�� � while-��

����� ������� ��� � ������ ������ O(n*m*k), �� ���������� �������(��� ������ ������� ������� 4+ �������, �� �������� TL) 
���� ������� ��������� �� 0.7 ����� �������
�� �� ����������, ��� �� ����� ��������� ����� � �� ����� � ���������. ����� �����, �������� ������ �� �����

�������� ��������� ���������: O(n*m*k)

-- ���������������� ��������� --

������ ����� ��� ���� ���������� - n, ��� ��� ���� ���������� ����� � �������� map - ��� m, ������� ��� O(n*m) ��� ����������
������ ���� ������� - ������ ����� - k, ��� ��� map ����� �������� � ���������, �� � ����������� �� ������, ���� ���������� ����� �� + ��� q � �����
������� ����� O(k*q)
Vector �������� relevance n*m - ��������*������

�������� ���������������� ���������: O(n*m)
*/
 

#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>

using namespace std;

struct relevance {
	int relevanceSum;	//������������� ���������
	int numberDocument;	//����� ���������
	bool operator <(const relevance& other) {
		if (this->relevanceSum > other.relevanceSum) return true;
		if (this->relevanceSum < other.relevanceSum) return false;
		if (this->numberDocument < other.numberDocument) return true;
		if (this->numberDocument > other.numberDocument) return false;
		return false;
	}
};

void generateRelevance(vector<vector<relevance>>& relevanceDocuments,
			unordered_map<string, map<int, int>>& documents,
		   vector<unordered_map<string, string>>& query) {
	
	int relevanceSumm = 0;
	for (int i = 0; i < query.size(); i++) {
		auto begin = query[i].begin();
		while (begin != query[i].end()) {

			if (documents.find(begin->second) != documents.end()) {
				auto beginDoc = documents[begin->second].begin();
				while (beginDoc != documents[begin->second].end()) {
					relevanceDocuments[i][beginDoc->first].numberDocument = beginDoc->first + 1;
					relevanceDocuments[i][beginDoc->first].relevanceSum += beginDoc->second;
					beginDoc++;
				}
				begin++;
			}
			else
				begin++;
		}
	}
	for (int i = 0; i < relevanceDocuments.size(); i++)
		sort(relevanceDocuments[i].begin(), relevanceDocuments[i].end());

}

void printRelevanceDocuments(vector<vector<relevance>>& relevanceDocuments) {
	
	for (int i = 0; i < relevanceDocuments.size(); i++) {
		int len = relevanceDocuments[i].size() <= 5 ? relevanceDocuments[i].size() : 5;
		for (int j = 0; j < len; j++) {

			if (relevanceDocuments[i][j].relevanceSum != 0)
				cout << relevanceDocuments[i][j].numberDocument << " ";
		}

		cout << endl;
	}
}

int main() {

	int n;
	cin >> n;
	if (n < 1 || n > 10000)
		return 0;
	//���� - �����, �������� - ����� ��������� � ����������
	unordered_map<string, map<int, int>> documents;

	string word;
	getline(cin, word);

	for (int i = 0; i < n; i++) {

		getline(cin, word);
		istringstream  words(word);

		while (words >> word) {
			documents[word][i] += 1;
		}
	}

	int m;
	cin >> m;
	//����� ��������, ���� �����, �������� �����
	vector<unordered_map<string, string>> query(m);
	getline(cin, word);
	for (int i = 0; i < m; i++) {
		getline(cin, word);
		istringstream  words(word);

		while (words >> word) {
			if (query[i].find(word) == query[i].end()) {
				query[i].insert({ word, word });
			}
		}
	}
	//��������� � �� ������������� ��� �������
	vector<vector<relevance>> relevanceDocuments(m, vector<relevance>(n));
	/*���������� ������ ���������� �� �� �������������*/
	generateRelevance(relevanceDocuments, documents, query);
	/*������� ������ ����������*/
	printRelevanceDocuments(relevanceDocuments);

	return 0;
}