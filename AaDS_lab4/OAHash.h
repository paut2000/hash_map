#pragma once
#include "AbstractHash.h"

template <typename T, typename K>
class OAHash : public AbstractHash <T, K>
{
private:

	struct Cell {
		bool busy = false;
		K key;
		T value;
	} *table = nullptr;

	int quadratic_probing(int k, int i);

public:

	OAHash(int quantity);
	~OAHash();
	virtual void clear() override;
	T& at(K key) override;
	virtual void add(K key, T value) override;
	virtual void remove(K key) override;

	virtual void out() override;

	class iterator : public AbstractHash<T, K>::Iterator
	{
	private:

		friend class OAHash;

		OAHash *oahash = nullptr;
		Cell* cell = nullptr;
		int i = 0;

	public:

		virtual const iterator& operator=(const AbstractHash<T, K>::Iterator& it) override {
			this->oahash = (dynamic_cast<const iterator&>(it)).oahash;
			this->cell = (dynamic_cast<const iterator&>(it)).cell;
			return *(this);
		}

		virtual T& operator*() override {
			if (this->cell != nullptr)
				return this->cell->value;
			throw std::invalid_argument("Нелья разыменовать итератор end");
		}

		virtual const iterator& operator++() override {
			for (int i = this->i + 1; i < this->oahash->capacity(); i++)
				if (this->oahash->table[i].busy) {
					this->cell = &(this->oahash->table[i]);
					this->i = i;
					return (*this);
				}
			this->cell = nullptr;
			return (*this);
		}

		virtual const iterator& operator--() override {
			for (int i = this->i - 1; i >= 0; i--)
				if (this->oahash->table[i].busy) {
					this->cell = &(this->oahash->table[i]);
					this->i = i;
					return (*this);
				}
			throw std::invalid_argument("operator--: выход за пределы таблицы");
		}

		virtual const bool operator==(const AbstractHash<T, K>::Iterator& it) override {
			return (dynamic_cast<const iterator&>(it)).cell == this->cell;
		}

		virtual const bool operator!=(const AbstractHash<T, K>::Iterator& it) override {
			return (dynamic_cast<const iterator&>(it)).cell != this->cell;
		}

	};

	virtual iterator* begin() override {
		iterator* it = new iterator;
		it->oahash = this;
		for (int i = 0; i < this->capacity(); i++)
			if (table[i].busy) {
				it->cell = &(this->table[i]);
				it->i = i;
				return it;
			}
		it->cell = nullptr;
		it->i = this->capacity();
		return it;
	}

	virtual iterator* end() override {
		iterator* it = new iterator;
		it->oahash = this;
		it->cell = nullptr;
		it->i = this->capacity();
		return it;
	}

};

template<typename T, typename K>
inline int OAHash<T, K>::quadratic_probing(int k, int i)
{
	return (k + 3 * i + 5 * i * i) % this->Capasity;
}

template<typename T, typename K>
inline OAHash<T, K>::OAHash(int quantity) : AbstractHash<T, K>::AbstractHash(quantity)
{
	this->table = new Cell[this->AbstractHash<T, K>::Capasity];
}

template<typename T, typename K>
inline OAHash<T, K>::~OAHash()
{
	delete[] table;
}

template<typename T, typename K>
inline void OAHash<T, K>::clear()
{
	for (int i = 0; i < this->Capasity; i++)
		table[i].busy = false;
	this->Size = 0;
}

template<typename T, typename K>
inline T& OAHash<T, K>::at(K key)
{
	probe = 0;
	int i = 0, j = this->hash(key);
	for (; i < this->Capasity && table[j].busy; i++, j = quadratic_probing(j, i)) {
		probe++;
		if (table[j].busy && table[j].key == key)
			return this->table[j].value;
	}
	throw std::invalid_argument("Такого ключа нет в коллекции");
}

template<typename T, typename K>
inline void OAHash<T, K>::add(K key, T value)
{
	probe = 0;

	int i = 0, j = this->hash(key);
	for (; i < this->Capasity && table[j].busy; i++, j = quadratic_probing(j, i)) {
		probe++;
		if (table[j].busy && table[j].key == key)
			throw std::invalid_argument("Такой ключ уже есть");
	}
	if (i == this->Capasity)
		throw std::invalid_argument("В таблице нет места для этого ключа");
	table[j].key = key;
	table[j].value = value;
	table[j].busy = true;
	this->Size++;
}

template<typename T, typename K>
inline void OAHash<T, K>::remove(K key)
{
	probe = 0;
	
	int i = 0, j = this->hash(key);
	for (; i < this->Capasity && table[j].busy; i++, j = quadratic_probing(j, i)) {
		probe++;
		if (table[j].busy && table[j].key == key) {
			table[j].busy = false;
			this->Size--;
			return;
		}
	}
	throw std::invalid_argument("Такого ключа нет в коллекции");
}

template<typename T, typename K>
inline void OAHash<T, K>::out()
{
	for (int i = 0; i < this->Capasity; i++)
		if (table[i].busy)
			std::cout << i << ": " << table[i].key << ", " << table[i].value << std::endl;
}