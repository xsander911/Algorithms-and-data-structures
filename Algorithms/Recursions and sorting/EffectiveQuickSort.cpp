/*
ID - 69415490 (upd)
--ПРИНЦИП РАБОТЫ--

У нас есть входные данные в виде Имя(name) Количество задач(P) Количество штрафов(F)

Необходимо отсортировать данные методом quick sort in-place:
	- по количеству задач(убывание)
	- если у участников совпадает количество задач, сортируем этих участников по штрафам(возрастание)
	- если у участников совпадает количество задач, количество штрафов, тогда сортируем их по именам в лексикографисеском порядке

Создаём структуру с лямбдой, в которой происходит проверка P, F, name 
struct user {
		int P;
		int F;
		std::string name;

		bool operator <(const user& other)
		{
			if (this->P > other.P) return true;
			if (this->P < other.P) return false;
			if (this->F < other.F) return true;
			if (this->F > other.F) return false;
			if (this->name < other.name) return true;
			return false;
		}
	};

C помощью перегруженного оператора будем проверять сразу все все параметры P, F, name

-- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --
Данная реализация сортировки неустойчива, но наш подход решает эту проблему, так как мы сортируем по определенным параметрам.
Если мы сортируем по задачам, нам не важен порядок остальных данных. Далее, чтобы соблюсти порядок данных участников с одинаковым колвом задач
мы начинаем сортировать их в ДИАПАЗОНЕ этих повторяющихся задач по штрафам. Далее, если у нас есть ДИАПАЗОН одинаковых задач и штрафов, мы также
сортируем в этом ДИАПАЗОНЕ уже по именам участников и меняем строки основного вектора. Т.е. наш swap меняет не само значение P, F или name,
а непосредственно идекс вектора, которых хранит эту структуру.
-- ВРЕМЕННАЯ СЛОЖНОСТЬ --
Сложность сортировки QuickSort занимает O(nlog(n)), в худшем случаем занимает O(n^2). Сложность данной сортировки зависит от выбора pivot,
в моей реализации выбирать pivot можно двумя методами: либо крайний элемент либо медиану, данные методы медианы есть в определении функции
medianaString - возвращает медиану среди набора строк, и mediana - возвращает медиану среди int набора.

Метод поиска повторяющихся P searchSequence занимает сложность O(n) так как там один цикл и while считает не повторяющиеся i, а просто инкрементирует его
если символы  равны между собой, следующая итерация по циклу for, продолжится с i, который обсчитался в while
Метод подсчета F searchSubSequence занимает O(n^2), за счет того, что у нас вложенные циклы, но это как раз оптимизирует программу, для того
чтобы не проходить лиший раз по всему вектору, мы проходимся только по тем диапазонам, где у нас повторяется P

-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
Так как мы используем метод QuickSort in-place мы двигаемся внутри своего вектора и не создаем дополнительных данных для храненя.
Доп данные создаются только для хранения повторяющихся P и F, а это не превышает рамера массива n. Следовательно сложность O(n)

*/
#include <iostream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

namespace QuickSort {

	struct user {
		int P;
		int F;
		std::string name;

		bool operator <(const user& other)
		{
			if (this->P > other.P) return true;
			if (this->P < other.P) return false;
			if (this->F < other.F) return true;
			if (this->F > other.F) return false;
			if (this->name < other.name) return true;
			return false;
		}
	};

	int partition(vector<user>& arr, int low, int high)
	{
		user pivot = arr[high];

		int i = (low - 1);

		for (int j = low; j <= high - 1; j++)
		{
			if (arr[j] < pivot)
			{
				i++;
				swap(arr[i], arr[j]);
			}
		}
		swap(arr[i + 1], arr[high]);
		return (i + 1);
	}

	void quickSort(vector<user>& arr, int low, int high)
	{
		if (low < high)
		{
			int pivot = partition(arr, low, high);

			quickSort(arr, low, pivot - 1);
			quickSort(arr, pivot + 1, high);
		}
	}

}

int main() {
	int n;
	cin >> n;
	if (n < 1 || n > 100000)
		return 0;

	int P, F, i;
	string name;
	vector<QuickSort::user> users(n);

	for (i = 0; i < n; i++) {

		cin >> users[i].name;
		cin >> users[i].P;
		cin >> users[i].F;

		getline(cin, name);
	}

	QuickSort::quickSort(users, 0, n - 1);

	for (i = 0; i < users.size(); i++)
		cout << users[i].name << endl;

	return 0;
}