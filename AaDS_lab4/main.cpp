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
	cout << "���������� ���������: " << endl;
	int n;
	cin >> n;
	HashTable <T, K> cch(n); // ������� ��������
	vector <K> v(n);
	cout << "����������� ������������� ��� ������� ��������: " << endl;
	double alfa;
	cin >> alfa;
	int q = cch.capacity() * alfa;
	long long int add_probe_cch = 0, remove_probe_cch = 0, at_probe_cch = 0;
	for (int i = 0; i < q; i++) { //�������������� ����������
		K key = rand() * rand();
		T value = 0;
		try {
			cch.add(key, value);
			v.push_back(key);
		}
		catch (exception ex) {}
	}

	for (int i = 0; i < q / 2; i++) { //�����
		if (i % 10 != 0) { // 10% ��������
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

	for (int i = 0; i < q / 2; i++) { //��������
		if (i % 10 != 0) { // 10% ��������
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

	for (int i = 0; i < q / 2; i++) { //����������
		if (i % 10 != 0) { // 10% ��������
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
	HashTable <T, K> oah(n); // �������� ���������
	oah.sf_open_addressing();

	long long int add_probe_oah = 0, remove_probe_oah = 0, at_probe_oah = 0;

	cout << "����������� ������������� ��� �������� ���������: " << endl;
	cin >> alfa;
	q = oah.capacity() * alfa;
	for (int i = 0; i < q; i++) { //�������������� ����������
		K key = rand() * rand();
		T value = 0;
		try {
			oah.add(key, value);
			v.push_back(key);
		}
		catch (exception ex) {}
	}

	for (int i = 0; i < q / 2; i++) { //�����
		if (i % 10 != 0) { // 10% ��������
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

	for (int i = 0; i < q / 2; i++) { //��������
		if (i % 10 != 0) { // 10% ��������
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

	for (int i = 0; i < q / 2; i++) { //����������
		if (i % 10 != 0) { // 10% ��������
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

	cout << "���������� � ������� � ��������� ��������: " << 1 + add_probe_cch / double(n) << endl;
	cout << "�������� �� ������� � ��������� ��������: " << 1 + remove_probe_cch / double(n) << endl;
	cout << "����� � ������� � ��������� ��������: " << 1 + at_probe_cch / double(n) << endl;
	cout << endl;
	cout << "���������� � ������� � �������� ����������: " << 1 + add_probe_oah / double(n) << endl;
	cout << "�������� �� ������� � �������� ����������: " << 1 + remove_probe_oah / double(n) << endl;
	cout << "����� � ������� � �������� ����������: " << 1 + at_probe_oah / double(n) << endl;
	cout << endl;

}


template<typename T, typename K>
void Menu()
{
	for (;;) {

		cout << "������ ����������� ���-�������: " << endl;
		int size;
		cin >> size;
		HashTable<T, K> h(size);
		typename HashTable<T, K>::iterator it1 = h.begin();
		typename HashTable<T, K>::iterator it2 = h.begin();

		cout << "���������� ��������:" << endl;
		cout << "0. � ���������� ��������" << endl;
		cout << "1. � �������� ����������" << endl;
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

			cout << "�������������� ������ ��� ������������:--------------------------------------------------------------" << endl;
			cout << "0.  ������� ������� � �������" << endl;
			cout << "1.  ���������� ������������� ����� ���������� ���������" << endl;
			cout << "�������� ������:-------------------------------------------------------------------------------------" << endl;
			cout << "2.  ����� ������ ���������� ��������" << endl;
			cout << "3.  �������� �������" << endl;
			cout << "4.  ������� ������� �� �����" << endl;
			cout << "5.  ������ �� ������/������" << endl;
			cout << "6.  ��������" << endl;
			cout << "7.  ���������� ��������� �������" << endl;
			cout << "8.  ��������� �� �������" << endl;
			cout << "������ ��������:-------------------------------------------------------------------------------------" << endl;
			cout << "9. ������� �������� ������ foreach (range based for)" << endl;
			cout << "10. ������� ���������, ����������� �� begin" << endl;
			cout << "11. ���������������� 1-�� �������� ++" << endl;
			cout << "12. ���������������� 2-�� �������� ++" << endl;
			cout << "13. ���������������� 1-�� �������� --" << endl;
			cout << "14. ���������������� 2-�� �������� --" << endl;
			cout << "15. ������������ 1-�� �������� *" << endl;
			cout << "16. ������������ 2-�� �������� *" << endl;
			cout << "17. �������� 1-�� � 2-�� ��������� � ������� ==" << endl;
			cout << "18. �������� 1-�� � 2-�� ��������� � ������� !=" << endl;
			cout << "�������������� ���������� ������:--------------------------------------------------------------------" << endl;
			cout << "19. ��������� ���������� ���������� c ���������� �������������� add(�������� rand(), ���� rand())" << endl;
			cout << "20. ��������� ����������� ������������������� for(i = 0; i < n; i++) add(�������� rand(), ���� i)" << endl;

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
						cout << "�������� ����������" << endl;
					else
						cout << "������� ��������" << endl;
					break;
				case 3: {
					cout << "������� ����: ";
					K key;
					cin >> key;
					cout << "������� ��������: ";
					T value;
					cin >> value;
					h.add(key, value);
					break;
				}
				case 4: {
					cout << "������� ����: ";
					K key;
					cin >> key;
					h.remove(key);
					break;
				}
				case 5: {
					cout << "������� ����: ";
					K key;
					cin >> key;
					cout << h.at(key) << endl;
					cout << "�������� ��������? (�� - 1, ��� - 0)" << endl;
					bool b;
					cin >> b;
					if (b) {
						cout << "������� ����� ��������: ";
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
					cout << "������� ���������� ����� ���������: ";
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
					cout << "������� ���������� ����� ���������: ";
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
					cout << "�������� ����� �������" << endl;
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
	cout << "�������� ���-������� �� �������� xi^2\n";
	srand(time(0));

	//����� ���������� ������������
	int P, M;
	cout << "������ �������" << endl;
	cin >> M;

	P = M * 20;
	cout << "���������� ������ � �������=: " << P << endl;


	//������ ������ ���������
	int* counter = new int[M];
	for (int i = 0; i < M; ++i)
		counter[i] = 0;

	//������������


	int keySize = 0;//���-�� ������ ����� 


	for (int i = 0; i < P; ++i) {

		int key = rand() * rand();

		//������� ����������� 
		int coagulate_key = 0;
		for (int i = 0; key; coagulate_key += key % M ^ i, key /= M, i++);
		coagulate_key = coagulate_key % M;


		++(counter[coagulate_key]);
	}

	//������� ����������
	double m1 = M - sqrt((double)M);
	double m2 = M + sqrt((double)M);
	double hi = 0;
	for (int i = 0; i < M; ++i)
	{
		hi += (counter[i] - P / double(M)) * (counter[i] - P / double(M));

	}
	hi = hi * (double(M) / P);

	cout << "���������� [m - sqrt(m)] [XI] [m + sqrt(m)]:\n";
	cout << '[' << m1 << "] [" << hi << "] [" << m2 << "]\n";
	delete[]counter;

}