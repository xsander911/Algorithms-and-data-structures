/*
ID - 69462250 (upd)

--ПРИНЦИП РАБОТЫ--

Первое решение у меня получилось сложностью O(n3) :D 
Изначальная идея: для каждого документа собрать хеш таблицу key = уникальное слово, value = количество повторений
также собираем вектор запросов с набором уникальных слов 
с такой концепцией получается, что надо проходиться по каждому запросу, в каждом документе проверять наличие уникального слова из запроса, 
получилось долго,и тут я решил сделать нормально :D

Рабочая версия
Для документов
Мы создаем хеш таблицу - key = уникальное слово, value = map, у которого key = номер документа, value = количество повторений

Для запросов
вектор хешей - key = слово, value = слово

Для релевантных запросов 
создал красивую структуру по образу и подобию предыдущего спринта с сортировкой)))))))))
данная структура хранит в себе поля номера документа и релевантности, а также перегрузку для сортировки, чтобы мы могли отсортировать данные
по условию задачи: номера доков по релевантности, если релеватность одинаковая, то по номеру документа(возрастание)

Тогда получается, что в основном цикле мы проходимся по вектору запросов
-	На каждой итерации запроса мы пробегаемся по уникальным словам
		проверяем, есть ли у нас это уникальное слово в хеш-таблице, если нет, то двигаемс¤ к след слову к запросе
		если есть, то бежим по данным в найденом ключе и добавл¤ем документы, в которых есть эти слова, а также количество повторений
		
- далее собранный вектор структур relevance сортируем необходимым нам образом
- далее выводим их (тут используем условие, что не более 5 документов, а также не выводить данные где нулева¤ релевантность) :D ужас выгл¤дит наверн)
 
-- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --
unordered_map будет хранить уникальные ключи в виде всех слов, которые присутствуют во всех документах
У каждого слова будет описание в виде: номер документа и количество повторений.
Так как мы считывает построчно, номер итерации(строки) и будет номером документа, только в моем случае мы будем считать с нуля, 
а когда будем записывать финальные данные релевантности, мы будем прибавлять к номеру документа 1, чтобы соответствовать стандартной нумерации.
Когда мы получаем слово, генерится корзина для этого ключа, в корзину пишем номер документа - i, значение инкрементируем на 1, 
тем самым фиксируем кол-во повторений(инкрементируем каждый раз, как попадаем в туже корзину, того же документа.
Мы сформировали корректные данные всех слов, их причастность к документам и количество повторений в документе.

Далее мы формируем вектор запросов, запрос хранит уникальные слова. Мы проходимся по вектору запросов, в каждом запросе мы берем слово 
и проверяем есть ли оно в нашей хеш таблице. Если есть, то добавляем по этому слову данные (номер документа+1 и повторения).

После формирования вектора структур relevance мы их сортируем согласно условию, компаратор указан в самой структуре.
После сортировки(полагаемся на ее корректность), мы выводим согласно условию: 
	ставим ограничение на вывод не более 5 документов
	когда выводим номер документа, проверяем релевантность на равенство нулю. Если равна нулю, тогда не выводим.

-- ВРЕМЕННАЯ СЛОЖНОСТЬ --

Когда мы начинаем формирование релевантности мы используем:
Основной цикл - перебирает количество запросов - n;
Дополнительный цикл - перебирает количество слов в запросе - m;
если слово присутствует в таблице, перебираем значения корзины - k; 
сортировка O(nLog(n)), в худшем O(n^2)
вывод информации O(n2) плюс if в for-ах и while-ах

Итого выходит что в худшем случае O(n*m*k), но отработало быстрее(мой первый вариант работал 4+ секунды, не проходил TL) 
этот вариант отработал за 0.7 самое большее
но мы выигрываем, что мы сразу проверяем слова и не лезем в документы. Нашли слово, спарсили данные по слову

Итоговая временная сложность: O(n*m*k)

-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --

Вектор хешей для слов документов - n, хеш для слов документов имеет в значении map - еще m, выходит что O(n*m) уже получается
Вектор слов запроса - вектор хешей - k, так как map будет бороться с коллизией, то в зависимости от метода, если используем листы то + еще q и тогда
выходит снова O(k*q)
Vector векторов relevance n*m - документ*запрос

Итоговая пространственная сложность: O(n*m)
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
	int relevanceSum;	//релевантность документа
	int numberDocument;	//номер документа
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
	//ключ - слово, значение - номер документа и повторения
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
	//набор запросов, ключ слово, значение слово
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
	//документы и их релевантность для запроса
	vector<vector<relevance>> relevanceDocuments(m, vector<relevance>(n));
	/*генерирует список документов по их релевантности*/
	generateRelevance(relevanceDocuments, documents, query);
	/*выводит список документов*/
	printRelevanceDocuments(relevanceDocuments);

	return 0;
}