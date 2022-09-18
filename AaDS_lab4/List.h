#pragma once
#include <ostream>
#include <iomanip>
#include "probe.h"

template <typename T, typename K>
class List {
private:
	
	struct Node {
		K key = 0;
		T value = 0;
		Node* next = nullptr;
	} *head = nullptr;

	int Size = 0;

public:

	T& at(K key);
	T& at_position(int position);
	void add(K key, T value);
	void remove(K key);
	void clear();
	void out();
	bool empty();
	int size();

};

template<typename T, typename K>
inline T& List<T, K>::at(K key)
{
	probe = 0;
	for (Node* ptr = head; ptr; ptr = ptr->next) {
		probe++;
		if (ptr->key == key) return ptr->value;
	}
	throw std::invalid_argument("Такого ключа нет в коллекции");
}

template<typename T, typename K>
inline T& List<T, K>::at_position(int position)
{
	int i = 0;
	for (Node* ptr = head; ptr; ptr = ptr->next, i++) {
		if (i == position) return ptr->value;
	}
	throw std::invalid_argument("Такой позиции нет в списке");
}

template<typename T, typename K>
inline void List<T, K>::add(K key, T value)
{
	probe = 0;
	if (!head) {
		probe++;
		head = new Node();
		head->key = key;
		head->value = value;
	}
	else {
		Node* ptr = head;
		for (; ptr->next; ptr = ptr->next) {
			probe++;
			if (ptr->key == key) throw std::invalid_argument("Такой ключ уже есть в коллекции");
		}
		if (ptr->key == key) throw std::invalid_argument("Такой ключ уже есть в коллекции");
		ptr->next = new Node();
		ptr = ptr->next;
		ptr->key = key;
		ptr->value = value;
	}
	Size++;
}

template<typename T, typename K>
inline void List<T, K>::remove(K key)
{
	probe = 0;
	if (head) {
		if (head->key == key) {
			probe++;
			Node* ptr = head;
			head = head->next;
			delete ptr;
		}
		else {
			for (Node* ptr = head->next, *prev_ptr = head; ptr; prev_ptr = ptr, ptr = ptr->next) {
				probe++;
				if (ptr->key == key) {
					prev_ptr->next = ptr->next;
					delete ptr;
					Size--;
					break;
				}
			}
		}
		return;
	}
	throw std::invalid_argument("Невозможно удалить: Такого ключа нет в коллекции");
}

template<typename T, typename K>
inline void List<T, K>::clear()
{
	if (head) {
		if (head->next) {
			Node* ptr = head->next, * prev_ptr = head;
			for (; ptr; prev_ptr = ptr, ptr = ptr->next)
				delete prev_ptr;
			delete ptr;
		}
		else
			delete head;
	}
	Size = 0;
}

template<typename T, typename K>
inline void List<T, K>::out()
{
	for (Node* ptr = head; ptr; ptr = ptr->next)
		std::cout << std::setw(20) << ptr->key << ", " << ptr->value;
	std::cout << std::endl;
}

template<typename T, typename K>
inline bool List<T, K>::empty()
{
	return !head;
}

template<typename T, typename K>
inline int List<T, K>::size()
{
	return Size;
}
