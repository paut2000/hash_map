#include <ctime>
#include <iostream>
#include <vector>
#include "HashTable.h"

using namespace std;

template <typename T, typename K> void Test();
template <typename T, typename K> void Menu();
void TestHash();

int main()
{
	setlocale(LC_ALL, "rus");
	Menu<int, int>();
}

template <typename T, typename K>
void Test()
{
	srand(time(NULL));
	cout << "Количество элементов: " << endl;
	int n;
	cin >> n;
	HashTable <T, K> cch(n); // цепочки коллизий
	vector <K> v(n);
	cout << "Коэффициент заполненности для цепочек коллизий: " << endl;
	double alfa;
	cin >> alfa;
	int q = cch.capacity() * alfa;
	long long int add_probe_cch = 0, remove_probe_cch = 0, at_probe_cch = 0;
	for (int i = 0; i < q; i++) { //Первоначальное заполнение
		K key = rand() * rand();
		T value = 0;
		try {
			cch.add(key, value);
			v.push_back(key);
		}
		catch (exception ex) {}
	}

	for (int i = 0; i < q / 2; i++) { //поиск
		if (i % 10 != 0) { // 10% промахов
			try {
				K key = v.at(rand() % v.size());
				T value = 0;
				cch.at(key);
				at_probe_cch += cch.get_probe_quantity();
			}
			catch (exception ex) {}
		}
		else {
			K key = rand() * rand();
			T value = 0;
			try {
				cch.at(key);
				at_probe_cch += cch.get_probe_quantity();
			}
			catch (exception ex) {
				at_probe_cch += cch.get_probe_quantity();
			}
		}
	}

	for (int i = 0; i < q / 2; i++) { //удаление
		if (i % 10 != 0) { // 10% промахов
			try {
				int r = rand() % v.size();
				K key = v.at(r);
				T value = 0;
				cch.remove(key);
				remove_probe_cch += cch.get_probe_quantity();
				v.erase(v.begin() + r);
			}
			catch (exception ex) {}
		}
		else {
			K key = rand() * rand();
			T value = 0;
			try {
				cch.remove(key);
				remove_probe_cch += cch.get_probe_quantity();
			}
			catch (exception ex) {
				remove_probe_cch += cch.get_probe_quantity();
			}
		}
	}

	for (int i = 0; i < q / 2; i++) { //добавление
		if (i % 10 != 0) { // 10% промахов
			int r = rand() % v.size();
			K key = v.at(r);
			T value = 0;
			try {
				cch.add(key, value);
				add_probe_cch += cch.get_probe_quantity();
				v.push_back(key);
			}
			catch (exception ex) {}
		}
		else {
			K key = rand() * rand();
			T value = 0;
			try {
				cch.add(key, value);
				add_probe_cch += cch.get_probe_quantity();
				v.push_back(key);
			}
			catch (exception ex) {}
		}
	}
		
	v.clear();
	HashTable <T, K> oah(n); // открытая адресация
	oah.sf_open_addressing();

	long long int add_probe_oah = 0, remove_probe_oah = 0, at_probe_oah = 0;

	cout << "Коэффициент заполненности для открытой адресации: " << endl;
	cin >> alfa;
	q = oah.capacity() * alfa;
	for (int i = 0; i < q; i++) { //Первоначальное заполнение
		K key = rand() * rand();
		T value = 0;
		try {
			oah.add(key, value);
			v.push_back(key);
		}
		catch (exception ex) {}
	}

	for (int i = 0; i < q / 2; i++) { //поиск
		if (i % 10 != 0) { // 10% промахов
			try {
				K key = v.at(rand() % v.size());
				T value = 0;
				oah.at(key);
				at_probe_oah += oah.get_probe_quantity();
			}
			catch (exception ex) {}
		}
		else {
			K key = rand() * rand();
			T value = 0;
			try {
				oah.at(key);
				at_probe_oah += oah.get_probe_quantity();
			}
			catch (exception ex) {
				at_probe_oah += oah.get_probe_quantity();
			}
		}
	}

	for (int i = 0; i < q / 2; i++) { //удаление
		if (i % 10 != 0) { // 10% промахов
			try {
				int r = rand() % v.size();
				K key = v.at(r);
				T value = 0;
				oah.remove(key);
				remove_probe_oah += oah.get_probe_quantity();
				v.erase(v.begin() + r);
			}
			catch (exception ex) {}
		}
		else {
			K key = rand() * rand();
			T value = 0;
			try {
				oah.remove(key);
				remove_probe_oah += oah.get_probe_quantity();
			}
			catch (exception ex) {
				remove_probe_oah += oah.get_probe_quantity();
			}
		}
	}

	for (int i = 0; i < q / 2; i++) { //добавление
		if (i % 10 != 0) { // 10% промахов
			int r = rand() % v.size();
			K key = v.at(r);
			T value = 0;
			try {
				oah.add(key, value);
				add_probe_oah += oah.get_probe_quantity();
				v.push_back(key);
			}
			catch (exception ex) {}
		}
		else {
			K key = rand() * rand();
			T value = 0;
			try {
				oah.add(key, value);
				add_probe_oah += oah.get_probe_quantity();
				v.push_back(key);
			}
			catch (exception ex) {}
		}
	}

	cout << "Добавление в таблицу с цепочками коллизий: " << 1 + add_probe_cch / double(n) << endl;
	cout << "Удаление из таблицы с цепочками коллизий: " << 1 + remove_probe_cch / double(n) << endl;
	cout << "Поиск в таблице с цепочками коллизий: " << 1 + at_probe_cch / double(n) << endl;
	cout << endl;
	cout << "Добавление в таблицу с открытой адресацией: " << 1 + add_probe_oah / double(n) << endl;
	cout << "Удаление из таблицы с открытой адресацией: " << 1 + remove_probe_oah / double(n) << endl;
	cout << "Поиск в таблице с открытой адресацией: " << 1 + at_probe_oah / double(n) << endl;
	cout << endl;

}


template<typename T, typename K>
void Menu()
{
	for (;;) {

		cout << "Размер создаваемой хэш-таблицы: " << endl;
		int size;
		cin >> size;
		HashTable<T, K> h(size);
		typename HashTable<T, K>::iterator it1 = h.begin();
		typename HashTable<T, K>::iterator it2 = h.begin();

		cout << "Разрешение коллизий:" << endl;
		cout << "0. С цеппочками коллизий" << endl;
		cout << "1. С открытой адресацией" << endl;
		int type;
		cin >> type;
		switch (type)
		{
		case 0:
			h.sf_collision_chains();
			break;
		case 1:
			h.sf_open_addressing();
			break;
		default:
			break;
		}

		for (;;) {

			cout << "Дополнительные методы для тестирования:--------------------------------------------------------------" << endl;
			cout << "0.  Вывести таблицу в консоль" << endl;
			cout << "1.  Количество просмотренных узлов предыдущей операцией" << endl;
			cout << "Основные методы:-------------------------------------------------------------------------------------" << endl;
			cout << "2.  Опрос метода разрешения коллизий" << endl;
			cout << "3.  Добавить элемент" << endl;
			cout << "4.  Удалить элемент по ключу" << endl;
			cout << "5.  Доступ по чтению/записи" << endl;
			cout << "6.  Очистить" << endl;
			cout << "7.  Количество элементов таблице" << endl;
			cout << "8.  Проверить на пустоту" << endl;
			cout << "Прямой итератор:-------------------------------------------------------------------------------------" << endl;
			cout << "9. Вывести элементы циклом foreach (range based for)" << endl;
			cout << "10. Создать итераторы, указывающие на begin" << endl;
			cout << "11. Инкрементировать 1-ый итератор ++" << endl;
			cout << "12. Инкрементировать 2-ой итератор ++" << endl;
			cout << "13. Декрементировать 1-ый итератор --" << endl;
			cout << "14. Декрементировать 2-ой итератор --" << endl;
			cout << "15. Разыменовать 1-ый итератор *" << endl;
			cout << "16. Разыменовать 2-ой итератор *" << endl;
			cout << "17. Сравнить 1-ый и 2-ой итераторы с помощью ==" << endl;
			cout << "18. Сравнить 1-ый и 2-ой итераторы с помощью !=" << endl;
			cout << "Автоматическое заполнение дерева:--------------------------------------------------------------------" << endl;
			cout << "19. Заполнить случайными значениями c нормальным распределением add(значение rand(), ключ rand())" << endl;
			cout << "20. Заполнить вырожденной последовательностью for(i = 0; i < n; i++) add(значение rand(), ключ i)" << endl;

			int n;
			cin >> n;

			try {
				switch (n)
				{
				case 0:
					h.out();
					break;
				case 1:
					cout << h.get_probe_quantity() << endl;
					break;
				case 2:
					if (h.what_form())
						cout << "Открытвя адрессация" << endl;
					else
						cout << "Цепочки коллизий" << endl;
					break;
				case 3: {
					cout << "Введите ключ: ";
					K key;
					cin >> key;
					cout << "Введите значение: ";
					T value;
					cin >> value;
					h.add(key, value);
					break;
				}
				case 4: {
					cout << "Введите ключ: ";
					K key;
					cin >> key;
					h.remove(key);
					break;
				}
				case 5: {
					cout << "Введите ключ: ";
					K key;
					cin >> key;
					cout << h.at(key) << endl;
					cout << "Изменить значение? (Да - 1, нет - 0)" << endl;
					bool b;
					cin >> b;
					if (b) {
						cout << "Введите новое значение: ";
						T value;
						cin >> value;
						h.at(key) = value;
					}
					break;
				}
				case 6:
					h.clear();
					break;
				case 7:
					cout << h.size() << endl;
					break;
				case 8:
					cout << h.empty() << endl;
					break;
				case 9:
					for (T i : h)
						cout << i << endl;
					break;
				case 10:
					it1 = h.begin();
					it2 = h.begin();
					break;
				case 11:
					++it1;
					break;
				case 12:
					++it2;
					break;
				case 13:
					--it1;
					break;
				case 14:
					--it2;
					break;
				case 15:
					cout << *it1 << endl;
					break;
				case 16:
					cout << *it2 << endl;
					break;
				case 17:
					cout << (it1 == it2) << endl;
					break;
				case 18:
					cout << (it1 != it2) << endl;
					break;
				case 19: {
					cout << "Введите количество новых элементов: ";
					int n;
					cin >> n;
					for (int i = 0; i < n; i++)
						try {
							h.add(rand() * rand(), rand());
						}
						catch (exception ex) {
							cout << ex.what() << endl;
						}
					break;
				}
				case 20: {
					cout << "Введите количество новых элементов: ";
					int n;
					cin >> n;
					for (int i = 0; i < n; i++)
						try {
							h.add(i, rand());
						}
						catch (exception ex) {
							cout << ex.what() << endl;
						}
					break;
				}
				default:
					cout << "Неверный номер команды" << endl;
					break;
				}
			}
			catch (exception ex) {
				cout << ex.what() << endl;
			}
			system("pause");
		}

	}
}

void TestHash() {
	cout << "Качество хэш-функции по критерию xi^2\n";
	srand(time(0));

	//Опрос параметров тестирования
	int P, M;
	cout << "Размер массива" << endl;
	cin >> M;

	P = M * 20;
	cout << "Колличесво ключей в выборке=: " << P << endl;


	//Создаём массив счётчиков
	int* counter = new int[M];
	for (int i = 0; i < M; ++i)
		counter[i] = 0;

	//Тестирование


	int keySize = 0;//кол-во знаков ключа 


	for (int i = 0; i < P; ++i) {

		int key = rand() * rand();

		//функция хэширования 
		int coagulate_key = 0;
		for (int i = 0; key; coagulate_key += key % M ^ i, key /= M, i++);
		coagulate_key = coagulate_key % M;


		++(counter[coagulate_key]);
	}

	//Рассчёт результата
	double m1 = M - sqrt((double)M);
	double m2 = M + sqrt((double)M);
	double hi = 0;
	for (int i = 0; i < M; ++i)
	{
		hi += (counter[i] - P / double(M)) * (counter[i] - P / double(M));

	}
	hi = hi * (double(M) / P);

	cout << "Результаты [m - sqrt(m)] [XI] [m + sqrt(m)]:\n";
	cout << '[' << m1 << "] [" << hi << "] [" << m2 << "]\n";
	delete[]counter;

}