/*
 * Copyright (C) 2016-2021 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
 *
 * This file is part of the Smitto.
 *
 * Smitto is free software; you can redistribute it and/or modify it under the terms of the
 * GNU Lesser General Public License as published by the Free Software Foundation;
 * either version 3 of the License, or (at your option) any later version.
 *
 * Smitto is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Smitto; see the file LICENSE. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#ifndef DWLOG
#define DWLOG(text)
#define MYDWLOG
#endif

//#define FIND2 (alter find)
#define BASESIZE 10000

namespace Smitto {

template <typename KTYPE, typename TYPE>
class OrderedTimeMap
{
    struct TimePair
    {
		KTYPE time;
        TYPE value;
		TimePair(KTYPE ptime, TYPE pvalue) : time(ptime), value(pvalue) {}
    };
public:
    // первая мысль была, что сбойный инетратор имеет позицию -1. но лишние действия, проще когда он указывает на count
	struct iterator
	{
		iterator(const OrderedTimeMap* cont = Q_NULLPTR, int ppos = -1) : container_(cont), pos_(ppos) {}
		inline bool operator != (const iterator& other) const {return pos_ != other.pos_;}
		inline bool operator == (const iterator& other) const {return pos_ == other.pos_;}
		inline iterator& operator ++ () {pos_++; return *this;}
		inline iterator operator++(int) {iterator r = *this; pos_++; return r;}
		inline iterator& operator -- () {pos_--; return *this;}
		inline iterator operator --(int) {iterator r = *this; pos_--; return r;}
		inline iterator operator + (int n) const {return iterator(container_, pos_+n);}
		inline iterator operator - (int n) const {return iterator(container_, pos_-n);}
		inline KTYPE key() const {if (pos_ >= container_->size() || pos_ < 0) return -1; return container_->dataAt(pos_).time;}
		inline TYPE& value() {return container_->dataAt(pos_).value;}
		inline TYPE value() const {return container_->dataAt(pos_).value;}
		inline int pos() const {return pos_;}

	private:
		const OrderedTimeMap* container_ = Q_NULLPTR;
		int pos_ = -1;
	};

	typedef iterator Iterator;
	typedef iterator ConstIterator;

	inline TYPE operator [](KTYPE key) const {auto it = find(key); if (it != constEnd()) return it.value();
		DWLOG("Промах key"); return emptyVal;}
	TYPE& operator [](KTYPE key);

	TYPE& valueNearPos(KTYPE key, int pos);
	TYPE valueNearPos(KTYPE key, int pos) const {return const_cast<OrderedTimeMap*>(this)->valueNearPos(key, pos);}

	inline TimePair& dataAt(int pos) const {return *(TimePair*)((char*)data_+pos*sizeof(TimePair));}

	inline TYPE value(KTYPE key) const {return const_cast<OrderedTimeMap*>(this)->operator[] (key);}
	inline TYPE& first() {if (count_) return (*(TimePair*)((char*)data_)).value;
		DWLOG("Промах first"); return emptyVal;}
	inline TYPE first() const {return const_cast<OrderedTimeMap*>(this)->first(); }
	inline TYPE& last() {if (count_) return (*(TimePair*)((char*)data_+(count_-1)*sizeof(TimePair))).value;
		DWLOG("Промах last"); return emptyVal;}
	inline TYPE last() const {return const_cast<OrderedTimeMap*>(this)->last();}
	inline KTYPE lastKey() const {return lastKey_;}
	inline KTYPE firstKey() const {return firstKey_;}

	inline bool contains(KTYPE key) const { return constFind(key) != constEnd(); }
	inline int count() const {return count_;}
	inline int size() const {return count_;}
	inline bool isEmpty() const {return !count_;}

#ifdef QLIST_H
	QList<KTYPE> keys() const;
#endif
#ifdef QPAIR_H
	QPair<KTYPE, KTYPE> interval() const {return qMakePair(firstKey_, lastKey_);}
#endif

	inline iterator begin() const {return constBegin();}
	inline iterator end() const {return constEnd();}
	inline iterator constBegin() const {return iterator(this, 0);}
	inline iterator constEnd() const {return iterator(this, count_);}
	iterator find(KTYPE key);
	inline iterator find (KTYPE key) const {return const_cast<OrderedTimeMap*>(this)->find(key);}
	inline iterator constFind (KTYPE key) const {return find(key);}
	iterator lowerBound(KTYPE key) const;
	iterator upperBound(KTYPE key) const {auto it = lowerBound(key); if (constEnd() == it) return it; return ++it;}

	TYPE& insert(KTYPE time, TYPE value);
	void remove(KTYPE key);

	bool equal(const OrderedTimeMap& other) const;
#ifdef QMAP_H
	bool equal(const QMap<KTYPE, TYPE>& other) const;
#endif

	OrderedTimeMap (int size = BASESIZE) {if (size > 0) reserve(size*sizeof(TimePair));}
	OrderedTimeMap(const OrderedTimeMap& other) {
        reserve(other.dataSize_); memcpy(data_, other.data_, dataSize_); count_ = other.count_;
        lastKey_ = other.lastKey_; firstKey_ = other.firstKey_; }
	OrderedTimeMap(OrderedTimeMap&& other) {
        dataSize_= other.dataSize_; data_ = other.data_; lastKey_ = other.lastKey_; firstKey_ = other.firstKey_; count_ = other.count_;
        other.data_ = Q_NULLPTR; other.dataSize_ = 0; other.lastKey_ = 0; other.firstKey_ = 0; other.count_ = 0; }
	OrderedTimeMap& operator = (OrderedTimeMap&& other) {
        dealoc(); dataSize_= other.dataSize_; data_ = other.data_;
        lastKey_ = other.lastKey_; firstKey_ = other.firstKey_;  count_ = other.count_;
        other.data_ = Q_NULLPTR; other.dataSize_ = 0; other.lastKey_ = 0; other.firstKey_ = 0; other.count_ = 0; return *this;}
	OrderedTimeMap& operator = (const OrderedTimeMap& other) {
        if (dataSize_ < other.dataSize_)  {dealoc(); reserve(other.dataSize_); }
        memcpy(data_, other.data_, other.dataSize_); count_ = other.count_;
        lastKey_ = other.lastKey_; firstKey_ = other.firstKey_; return *this;}
	~OrderedTimeMap() {dealoc();}

	inline void clear() {count_ = 0; lastKey_ = 0; firstKey_ = 0;}
	void trimAfter(KTYPE key) {auto it = lowerBound(key); if (it == constBegin()) return; count_ = it.pos()+1; lastKey_ = it.key();}

private:
	KTYPE dataSize_ = 0;
	void *data_ = Q_NULLPTR;
    int count_ = 0;
	KTYPE lastKey_ = 0;
	KTYPE firstKey_ = 0;
    TYPE emptyVal = TYPE(); //0

	void reserve(int k) {if (k > 0) data_ = malloc(dataSize_ = k);}
	void realoc(int addk) {void *ldata = data_; reserve(dataSize_+addk); memcpy(data_, ldata, dataSize_-addk); free(ldata);}
    void dealoc() {if (data_) free(data_); data_ = Q_NULLPTR; dataSize_ = 0; clear();}
};

template <typename KTYPE, typename TYPE>
TYPE& OrderedTimeMap<KTYPE, TYPE>::insert(KTYPE time, TYPE value)
{
    if (!dataSize_)
		reserve(BASESIZE*sizeof(TimePair));
	if (!count_)
	{
		TimePair* pair = (TimePair*)((char*)data_);
		*pair = TimePair(time, value);
		count_++;
		firstKey_ = time;
		lastKey_ = time;
		return pair->value;
	}
	if (time > lastKey_)
	{
		if (KTYPE((count_+1)*sizeof(TimePair)) > dataSize_)
			realoc(dataSize_);
		TimePair* pair = (TimePair*)((char*)data_+count_*sizeof(TimePair));
		*pair = TimePair(time, value);
		count_++;
		lastKey_ = time;
		return pair->value;
	}
	auto it = lowerBound(time);
	if (it.key() == time)
    {
		TimePair* pair = (TimePair*)((char*)data_+it.pos()*sizeof(TimePair));
		pair->value = value;
		return pair->value;
    }
	if (KTYPE((count_+1)*sizeof(TimePair)) > dataSize_)
	{
		void *ldata = data_;
		reserve(2*dataSize_);
		if (it.pos() > 0)
			memcpy((char*)data_, ldata, it.pos()*sizeof(TimePair));
		DWLOG(it.pos() > 0 ? QString("Вставка элемента %1 в середину с увеличением размера").arg(time) :
							 QString("Вставка элемента %1 в начало с увеличением размера").arg(time));
		memcpy((char*)data_+(it.pos()+1)*sizeof(TimePair), (char*)ldata+(it.pos())*sizeof(TimePair), (count_ - it.pos())*sizeof(TimePair));
		free(ldata);
	}
	else
	{
		DWLOG(it.pos() > 0 ? QString("Вставка элемента %1 в середину крайне нежелательна").arg(time) :
							 QString("Вставка элемента %1 в начало крайне нежелательна").arg(time));
		memmove((char*)data_+(it.pos()+1)*sizeof(TimePair), (char*)data_+(it.pos())*sizeof(TimePair), (count_-it.pos())*sizeof(TimePair));
	}
	TimePair* pair = (TimePair*)((char*)data_+it.pos()*sizeof(TimePair));
	*pair = TimePair(time, value);
	if (it.pos() == 0)
		firstKey_ = time;
	count_++;
	return pair->value;
}

template <typename KTYPE, typename TYPE>
void OrderedTimeMap<KTYPE, TYPE>::remove(KTYPE time)
{
	if (time == lastKey_)
	{
		if (--count_)
			lastKey_ = dataAt(count_ - 1).time;
		else
		{
			lastKey_ = 0;
			firstKey_ = 0;
		}
		return;
	}
	DWLOG(QString("Удаление элемента элемента %1 из середины крайне нежелательно").arg(time));
	auto it = lowerBound(time);
	if (it == constEnd())
		return;
	memmove((char*)data_+(it.pos()-1)*sizeof(TimePair), (char*)data_+(it.pos())*sizeof(TimePair), count_-it.pos());
	count_--;
}

template <typename KTYPE, typename TYPE>
bool OrderedTimeMap<KTYPE, TYPE>::equal(const OrderedTimeMap& other) const
{
	if (count_ != other.count() || firstKey_ != other.firstKey_ || lastKey_ != other.lastKey_)
		return false;
	if (sizeof(TYPE) % 8 == 0)
		return memcmp(data_, other.data_, other.count_*sizeof(TimePair)) == 0;
	auto itc = constBegin();
	for (auto it = other.constBegin(); it != other.constEnd(); ++it, ++itc)
		if (it.key() != itc.key() || it.value() != itc.value())
			return false;
	return true;
}

#ifdef QMAP_H
template <typename KTYPE, typename TYPE>
bool OrderedTimeMap<KTYPE, TYPE>::equal(const QMap<KTYPE, TYPE>& other) const
{
	if (count_ != other.count() || firstKey_ != other.firstKey() || lastKey_ != other.lastKey())
		return false;
	auto itc = constBegin();
	for (auto it = other.constBegin(); it != other.constEnd(); ++it, ++itc)
		if (it.key() != itc.key() || it.value() != itc.value())
			return false;
	return true;
}
#endif

template <typename KTYPE, typename TYPE>
TYPE& OrderedTimeMap<KTYPE, TYPE>::valueNearPos(KTYPE key, int pos)
{
	if (pos < count_ && pos >= 0)
	{
		auto& data = dataAt(pos);
		if (data.time == key)
			return data.value;
		int p = key > data.time ? 1 : -1;
		int pos2 = pos;
		do
		{
			pos2 += p;
			auto& data2 = dataAt(pos2);
			if (data.time == key)
			{
				DWLOG(QString("Промах key %1 pos %2 pos2 %3").arg(key).arg(pos).arg(pos2));
				return data2.value;
			}
			else if (p*(data2.time - key) > 0)
				break;

		} while(pos2 >=0 && pos2 < count_);
	}
	DWLOG("Промах valueNearPos");
	return emptyVal;
}

template <typename KTYPE, typename TYPE>
TYPE& OrderedTimeMap<KTYPE, TYPE>::operator [](KTYPE key)
{
    if (key > lastKey_)
		return this->insert(key, TYPE());
	auto it = find(key);
	if (it == constEnd())
		return this->insert(key, TYPE());
	return it.value();
}

template <typename KTYPE, typename TYPE>
typename OrderedTimeMap<KTYPE, TYPE>::iterator OrderedTimeMap<KTYPE, TYPE>::find(KTYPE key)
{
    auto it = lowerBound(key);
    if (it == constEnd() || it.key() == key)
        return it;
    return constEnd();
}

template <typename KTYPE, typename TYPE>
typename OrderedTimeMap<KTYPE, TYPE>::iterator OrderedTimeMap<KTYPE, TYPE>::lowerBound(KTYPE key) const
{
    if (!count_ || key > lastKey_)
        return constEnd();
    if (key <= firstKey_)
        return iterator(this, 0);
    if (key == lastKey_)
        return iterator(this, count_-1);

    int begin = 0;
    int end = count_-1;
#ifdef FIND2
	KTYPE beginKey = firstKey_, endKey = lastKey_;
#endif
	while (begin + 1 < end) // магия. 2 элемента - уже выход
    {
#ifdef FIND2
        int pos = begin + (end-begin)*float(key-beginKey)/(endKey-beginKey);
        if (pos <= begin)
            pos = begin+1;
        else if (pos >= end)
            pos = end-1;
#else
	auto pos = (end+begin)/2;
#endif
        auto& atval = dataAt(pos);
        if (atval.time == key)
            return iterator(this, pos);
#ifdef FIND2
        if (key > atval.time)
        {
            begin = pos;
            beginKey = atval.time;
        }
        else
        {
            end = pos;
            endKey = atval.time;
        }
#else
        key > atval.time ? begin = pos : end = pos;
#endif
    }
    if (end - begin == 1)
        return iterator(this, end);
    return constEnd();
}

#ifdef QLIST_H
template <typename KTYPE, typename TYPE>
QList<KTYPE> OrderedTimeMap<KTYPE, TYPE>::keys() const
{
	QList<KTYPE> res;
    for (auto it = constBegin(); it != constEnd(); ++it)
		res.append(it.key());
    return res;
}
#endif

} // Smitto::

#ifdef MYDWLOG
#undef DWLOG
#undef MYDWLOG
#endif
