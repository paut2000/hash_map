#pragma once
#include "probe.h"

template <typename T, typename K>
class AbstractHash
{
private:

	int Mersenne_number(int value);
	int key_conversion_coagulate(long long key); //преобразование ключа свёрткой

	int mod = 1; //значение для преобразования свёрткой. Вычисляется в конструкторе.

protected:

	int hash(int key); //модульное хэширование 

	int Capasity = 0;
	int Size = 0;

public:
	
	AbstractHash(int quantity);
	int capacity();
	int size();
	bool empty();
	virtual void clear() = 0;
	virtual T& at(K key) = 0;
	virtual void add(K key, T value) = 0;
	virtual void remove(K key) = 0;

	virtual void out() = 0;
	int get_probe_quantity();

	class Iterator
	{
	public:

		virtual const Iterator& operator=(const Iterator&) = 0;
		virtual T& operator*() = 0;
		virtual const Iterator& operator++() = 0;
		virtual const Iterator& operator--() = 0;

		virtual const bool operator==(const Iterator&) = 0;
		virtual const bool operator!=(const Iterator&) = 0;

	};

	virtual Iterator* begin() = 0;
	virtual Iterator* end() = 0;

};

template<typename T, typename K>
inline int AbstractHash<T, K>::Mersenne_number(int value)
{
	if (value <= 251) return 251;
	if (value <= 509) return 509;
	if (value <= 1021) return 1021;
	if (value <= 2039) return 2039;
	if (value <= 4093) return 4093;
	if (value <= 8191) return 8191;
	if (value <= 16381) return 16381;
	if (value <= 32749) return 32749;
	if (value <= 65521) return 65521;
	if (value <= 131071) return 131071;
	if (value <= 262139) return 262139;
	if (value <= 524287) return 524287;
	if (value <= 1048573) return 1048573;
	return 0;
}

template<typename T, typename K>
int AbstractHash<T, K>::key_conversion_coagulate(long long key)
{
	int coagulate_key = 0;
	for (int i = 0; key; coagulate_key += key % mod ^ i, key /= mod, i++);
	return coagulate_key;
}

template<typename T, typename K>
inline int AbstractHash<T, K>::hash(int key)
{
	return key_conversion_coagulate(key) % Capasity;
}

template<typename T, typename K>
inline AbstractHash<T, K>::AbstractHash(int quantity)
{
	Capasity = Mersenne_number(quantity);
	for (int i = Capasity; i != 0; i /= 10, mod *= 10);
}

template<typename T, typename K>
inline int AbstractHash<T, K>::capacity()
{
	return Capasity;
}

template<typename T, typename K>
inline int AbstractHash<T, K>::size()
{
	return this->Size;
}

template<typename T, typename K>
inline bool AbstractHash<T, K>::empty()
{
	return !this->Size;
}

template<typename T, typename K>
inline int AbstractHash<T, K>::get_probe_quantity()
{
	return probe;
}
