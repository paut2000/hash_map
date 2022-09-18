#pragma once
#include "AbstractHash.h"
#include "CCHash.h"
#include "OAHash.h"

template <typename T, typename K>
class HashTable
{
private:

	AbstractHash <T, K> *hashtable = nullptr;
	bool form = false; //false - цепочки коллизий, true - открытая адресация
	int quantity = 0;
	
public:

	HashTable(int quantity);
	~HashTable();

	int capacity();
	int size();
	bool empty();
	void clear();
	T& at(K key);
	void add(K key, T value);
	void remove(K key);
	void sf_collision_chains();
	void sf_open_addressing();
	bool what_form();

	void out();
	int get_probe_quantity();

	class iterator
	{
	private:

		friend class HashTable;

		typename AbstractHash<T, K>::Iterator* It = nullptr;

	public:

		const iterator& operator=(const iterator&);
		T& operator*();
		const iterator& operator++();
		const iterator& operator--();

		const bool operator==(const iterator&);
		const bool operator!=(const iterator&);

	};

	const iterator begin();
	const iterator end();

};

template<typename T, typename K>
inline HashTable<T, K>::HashTable(int quantity)
{
	if (quantity <= 0) throw std::invalid_argument("Нельзя создать HashTable размером <= 0");
	this->quantity = quantity;
	hashtable = new CCHash<T, K>(quantity);
}

template<typename T, typename K>
inline HashTable<T, K>::~HashTable()
{
	if (hashtable) delete hashtable;
}

template<typename T, typename K>
inline int HashTable<T, K>::capacity()
{
	return hashtable->capacity();
}

template<typename T, typename K>
inline int HashTable<T, K>::size()
{
	return hashtable->size();
}

template<typename T, typename K>
inline bool HashTable<T, K>::empty()
{
	return hashtable->empty();
}

template<typename T, typename K>
inline void HashTable<T, K>::clear()
{
	hashtable->clear();
}

template<typename T, typename K>
inline T& HashTable<T, K>::at(K key)
{
	if (key <= 0) throw std::invalid_argument("Ключ <= 0 запрещён");
	return hashtable->at(key);
}

template<typename T, typename K>
inline void HashTable<T, K>::add(K key, T value)
{
	if (key <= 0) throw std::invalid_argument("Ключ <= 0 запрещён");
	hashtable->add(key, value);
}

template<typename T, typename K>
inline void HashTable<T, K>::remove(K key)
{
	if (key <= 0) throw std::invalid_argument("Ключ <= 0 запрещён");
	hashtable->remove(key);
}

template<typename T, typename K>
inline void HashTable<T, K>::sf_collision_chains()
{
	if (hashtable) delete hashtable;
	hashtable = new CCHash<T, K>(quantity);
	form = false;
}

template<typename T, typename K>
inline void HashTable<T, K>::sf_open_addressing()
{
	if (hashtable) delete hashtable;
	hashtable = new OAHash<T, K>(quantity);
	form = true;
}

template<typename T, typename K>
inline bool HashTable<T, K>::what_form()
{
	return form;
}

template<typename T, typename K>
inline void HashTable<T, K>::out()
{
	hashtable->out();
}

template<typename T, typename K>
inline int HashTable<T, K>::get_probe_quantity()
{
	return hashtable->get_probe_quantity();
}

template<typename T, typename K>
inline const typename HashTable<T, K>::iterator HashTable<T, K>::begin()
{
	HashTable<T, K>::iterator it;
	it.It = hashtable->begin();
	return it;
}

template<typename T, typename K>
inline const typename HashTable<T, K>::iterator HashTable<T, K>::end()
{
	HashTable<T, K>::iterator it;
	it.It = hashtable->end();
	return it;
}

template<typename T, typename K>
inline const typename HashTable<T, K>::iterator& HashTable<T, K>::iterator::operator=(const iterator& it)
{
	this->It = it.It;
	return (*this);
}

template<typename T, typename K>
inline T& HashTable<T, K>::iterator::operator*()
{
	return this->It->operator*();
}

template<typename T, typename K>
inline const typename HashTable<T, K>::iterator& HashTable<T, K>::iterator::operator++()
{
	this->It->operator++();
	return (*this);
}

template<typename T, typename K>
inline const typename HashTable<T, K>::iterator& HashTable<T, K>::iterator::operator--()
{
	this->It->operator--();
	return (*this);
}

template<typename T, typename K>
inline const bool HashTable<T, K>::iterator::operator==(const iterator& it)
{
	return *(this->It) == *(it.It);
}

template<typename T, typename K>
inline const bool HashTable<T, K>::iterator::operator!=(const iterator& it)
{
	return *(this->It) != *(it.It);
}
