#pragma once
#include "AbstractHash.h"
#include "List.h"

template <typename T, typename K>
class CCHash : public AbstractHash <T, K>
{
private:

	List <T, K>* list;

public:

	CCHash(int size);
	virtual void clear() override;
	virtual T& at(K key) override;
	virtual void add(K key, T value) override;
	virtual void remove(K key) override;

	virtual void out() override;

	class iterator : public AbstractHash<T, K>::Iterator
	{
	private:

		friend class CCHash;

		CCHash* cchash = nullptr;

		int i = 0; //по таблице
		int j = 0; //по листу

	public:

		virtual const iterator& operator=(const AbstractHash<T, K>::Iterator& It) override {
			this->cchash = (dynamic_cast<const iterator&>(It)).cchash;
			this->i = (dynamic_cast<const iterator&>(It)).i;
			this->j = (dynamic_cast<const iterator&>(It)).j;
			return *(this);
		}

		virtual T& operator*() override {
			if (i < cchash->capacity())
				return cchash->list[i].at_position(j);
			throw std::invalid_argument("Нелья разыменовать итератор end");
		}

		virtual const iterator& operator++() override {
			if (this->cchash->list[i].size() > ++j) //движение по списку
				return *(this);
			for (int i = this->i + 1; i < this->cchash->capacity(); i++) //движение по таблице
				if (!this->cchash->list[i].empty()) {
					this->i = i;
					this->j = 0;
					return (*this);
				}
			this->i = this->cchash->capacity(); //если нет больше элементов
			this->j = 0;
			return (*this);
		}

		virtual const iterator& operator--() override {
			if (--j >= 0) //движение по списку
				return *(this);
			for (int i = this->i - 1; i >= 0; i--) //движение по таблице
				if (!this->cchash->list[i].empty()) {
					this->i = i;
					this->j = this->cchash->list[i].size() - 1;
					return (*this);
				}
			this->i = this->cchash->capacity(); //если нет больше элементов
			this->j = 0;
			return (*this);
		}

		virtual const bool operator==(const AbstractHash<T, K>::Iterator& It) override {
			if (this->i == (dynamic_cast<const iterator&>(It)).i && this->j == (dynamic_cast<const iterator&>(It)).j)
				return true;
			else
				return false;
		}

		virtual const bool operator!=(const AbstractHash<T, K>::Iterator& It) override {
			return !this->operator==(It);
		}

	};

	virtual iterator* begin() override {
		iterator* it = new iterator;
		it->cchash = this;
		for (int i = 0; i < this->capacity(); i++)
			if (!this->list[i].empty()) {
				it->i = i;
				it->j = 0;
				return it;
			}
		it->i = this->capacity();
		it->j = 0;
		return it;
	}

	virtual iterator* end() override {
		iterator* it = new iterator;
		it->cchash = this;
		it->i = this->capacity();
		it->j = 0;
		return it;
	}

};

template<typename T, typename K>
inline CCHash<T, K>::CCHash(int quantity) : AbstractHash<T, K>::AbstractHash(quantity)
{
	this->list = new List<T, K>[this->AbstractHash<T, K>::Capasity];
}

template<typename T, typename K>
inline void CCHash<T, K>::clear()
{
	for (int i = 0; i < this->Capasity; i++)
		list[i].clear();
	this->Size = 0;
}

template<typename T, typename K>
inline T& CCHash<T, K>::at(K key)
{
	return list[this->hash(key)].at(key);
}

template<typename T, typename K>
inline void CCHash<T, K>::add(K key, T value)
{
	list[this->hash(key)].add(key, value);
	this->Size++;
}

template<typename T, typename K>
inline void CCHash<T, K>::remove(K key)
{
	list[this->hash(key)].remove(key);
	this->Size--;
}

template<typename T, typename K>
inline void CCHash<T, K>::out()
{
	if (list)
		for (int i = 0; i < this->Capasity; i++) {
			if (!list[i].empty()) {
				std::cout << i << ": ";
				list[i].out();
			}
		}
}
