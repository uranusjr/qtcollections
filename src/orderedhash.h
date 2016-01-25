#ifndef QTCOLLECTIONS_ORDEREDHASH_H
#define QTCOLLECTIONS_ORDEREDHASH_H

#ifdef Q_COMPILER_INITIALIZER_LISTS
#include <initializer_list>
#endif
#include <QHash>
#include <QLinkedList>
#include <QPair>
#include <QScopedPointer>
#include "qtcollections_global.h"

namespace qtcollections
{

template <typename Key, typename T>
struct QTCOLLECTIONS_SHARED_EXPORT OrderedHashData
{
    typedef typename QLinkedList<Key>::iterator KeyIterator;
    QHash<Key, T> hash;
    QLinkedList<Key> keys;
    QHash<Key, KeyIterator> lookup;

    OrderedHashData() {}
    OrderedHashData(const OrderedHashData &o) : hash(o.hash), keys(o.keys)
    {
        for (KeyIterator i = keys.begin(); i != keys.end(); i++)
            lookup.insert(*i, i);
    }

    void reserve(int size)
    {
        hash.reserve(size);
        lookup.reserve(size);
    }

    void clear()
    {
        hash.clear();
        keys.clear();
        lookup.clear();
    }

    void erase(const KeyIterator &it)
    {
        Key key = *it;
        keys.erase(it);
        hash.remove(key);
        lookup.remove(key);
    }

    QPair<Key, T> takeFirst()
    {
        const Key &key = keys.takeFirst();
        const T &value = hash.value(key);
        hash.remove(key);
        lookup.remove(key);
        return QPair<Key, T>(key, value);
    }

    QPair<Key, T> takeLast()
    {
        const Key &key = keys.takeLast();
        const T &value = hash.value(key);
        hash.remove(key);
        lookup.remove(key);
        return QPair<Key, T>(key, value);
    }
};

template <typename Key, typename T>
class QTCOLLECTIONS_SHARED_EXPORT OrderedHash
{
    typedef OrderedHashData<Key, T> Data;
    typedef typename QLinkedList<Key>::iterator KeyIterator;
    QScopedPointer<Data> d;

public:
    inline OrderedHash() : d(new Data()) {}
    inline OrderedHash(const OrderedHash &other) : d(new Data(*other.d)) {}
#ifdef Q_COMPILER_INITIALIZER_LISTS
    inline OrderedHash(std::initializer_list<std::pair<Key,T> > list);
#endif
    inline OrderedHash &operator=(const OrderedHash &other) {
        d.reset(new Data(*other.d));
        return *this;
    }
    // TODO: Move semantics if Q_COMPILER_RVALUE_REFS.

    inline int capacity() const { return d->hash.capacity(); }
    void reserve(int size) { return d->reserve(size); }
    inline void squeeze() { d->reserve(1); }

    void swap(OrderedHash &other) { qSwap(d, other.d); }

    bool operator==(const OrderedHash &other) const;
    bool operator!=(const OrderedHash &other) const;

    inline int size() const { return d->hash.size(); }
    inline bool isEmpty() const { return d->hash.isEmpty(); }

    void clear();
    int remove(const Key &key);
    T take(const Key &key);

    bool contains(const Key &key) const { return d->hash.contains(key); }
    const Key key(const T &value) const { return key(value, Key()); }
    const Key key(const T &value, const Key &defaultKey) const;
    const T value(const Key &key) const { return d->hash.value(key); }
    const T value(const Key &key, const T &defaultValue) const
        { return d->hash.value(key, defaultValue); }
    T &operator[](const Key &key) { return d->hash[key]; }
    const T operator[](const Key &key) const { return d->hash[key]; }

    QList<Key> keys() const;
    QList<Key> keys(const T &value) const;
    QList<T> values() const;

    class const_iterator;

    class iterator
    {
        friend class const_iterator;
        friend class OrderedHash;
        typedef OrderedHashData<Key, T> HashData;

        KeyIterator i;
        HashData *d;

    public:
        inline iterator() : d(0) {}
        inline iterator(KeyIterator i, const QScopedPointer<HashData> &d) :
            i(i), d(d.data()) {}

        inline const Key &key() const { return *i; }
        inline T &value() const { return d->hash[*i]; }
        inline T &operator*() const { return value(); }
        inline T &operator->() const { return value(); }

        inline bool operator==(const iterator &o) const
            { return i == o.i && d == o.d; }
        inline bool operator!=(const iterator &o) const
            { return !(*this == o); }

        inline iterator &operator++() {
            ++i;
            return *this;
        }
        inline iterator operator++(int) {
            iterator r = *this;
            i++;
            return r;
        }
        inline iterator &operator--() {
            --i;
            return *this;
        }
        inline iterator operator--(int) {
            iterator r = *this;
            i--;
            return r;
        }
        inline iterator operator+(int j) const {
            iterator r = *this;
            if (j > 0) while (j > 0) { ++r ; j--; }
            else if (j < 0) while (j < 0) { --r; j++; }
            return r;
        }
        inline iterator operator-(int j) const {
            iterator r = *this;
            if (j > 0) while (j > 0) { --r ; j--; }
            else if (j < 0) while (j < 0) { ++r; j++; }
            return r;
        }
        inline iterator &operator+=(int j) { return *this = *this + j; }
        inline iterator &operator-=(int j) { return *this = *this - j; }

#ifndef QT_STRICT_ITERATORS
    public:
        inline bool operator==(const const_iterator &o) const
            { return i == o.i; }
        inline bool operator!=(const const_iterator &o) const
            { return i != o.i; }
#endif
    };
    friend class iterator;

    class const_iterator
    {
        friend class iterator;
        typedef typename QLinkedList<Key>::const_iterator KeyIterator;
        typedef OrderedHashData<Key, T> HashData;

        KeyIterator i;
        HashData *d;

    public:
        inline const_iterator() : d(0) {}
        inline const_iterator(
                KeyIterator i, const QScopedPointer<HashData> &d) :
            i(i), d(d.data()) {}

#ifdef QT_STRICT_ITERATORS
        explicit
#endif
        inline const_iterator(const iterator &o) : i(o.i), d(o.d) {}

        inline const Key &key() const { return *i; }
        inline T &value() const { return d->hash[*i]; }
        inline T &operator*() const { return value(); }
        inline T &operator->() const { return value(); }

        inline bool operator==(const const_iterator &o) const
            { return i == o.i && d == o.d; }
        inline bool operator!=(const const_iterator &o) const
            { return !(*this == o); }

        inline const_iterator &operator++() {
            ++i;
            return *this;
        }
        inline const_iterator operator++(int) {
            const_iterator r = *this;
            i++;
            return r;
        }
        inline const_iterator &operator--() {
            --i;
            return *this;
        }
        inline const_iterator operator--(int) {
            const_iterator r = *this;
            i--;
            return r;
        }
        inline const_iterator operator+(int j) const {
            const_iterator r = *this;
            i = i + j;
            return r;
        }
        inline const_iterator operator-(int j) const {
            const_iterator r = *this;
            i = i - j;
            return r;
        }
        inline const_iterator &operator+=(int j) { return *this = *this + j; }
        inline const_iterator &operator-=(int j) { return *this = *this - j; }
    };
    friend class const_iterator;

    // STL-style iteration.
    inline iterator begin()
        { return iterator(d->keys.begin(), d); }
    inline const_iterator begin() const
        { return const_iterator(d->keys.begin(), d); }
    inline const_iterator cbegin() const
        { return const_iterator(d->keys.cbegin(), d); }
    inline const_iterator constBegin() const
        { return const_iterator(d->keys.constBegin(), d); }
    inline iterator end()
        { return iterator(d->keys.end(), d); }
    inline const_iterator end() const
        { return const_iterator(d->keys.end(), d); }
    inline const_iterator cend() const
        { return const_iterator(d->keys.cend(), d); }
    inline const_iterator constEnd() const
        { return const_iterator(d->keys.constEnd(), d); }

    // STL compatibility.
    typedef T mapped_type;
    typedef Key key_type;
    typedef qptrdiff difference_type;
    typedef int size_type;
    inline bool empty() const { return isEmpty(); }

    // Qt Core compatibility.
    typedef iterator Iterator;
    typedef const_iterator ConstIterator;
    inline int count() const { return d->hash.count(); }
    iterator find(const Key &key)
        { return iterator(d->lookup.value(key, d->keys.end()), d); }
    const_iterator find(const Key &key) const
        { return const_iterator(d->lookup.value(key, d->keys.end()), d); }
    const_iterator constFind(const Key &key) const
        { return const_iterator(d->lookup.value(key, d->keys.end()), d); }
    iterator erase(iterator it);

    // Map interface.
    iterator insert(const Key &key, const T &value);
    QHash<Key, T> toHash() const { return d->hash; }
    const Key &firstKey() const { return d->keys.first(); }
    const Key &lastKey() const { return d->keys.last(); }
    QPair<Key, T> takeFirst() { return d->takeFirst(); }
    QPair<Key, T> takeLast() { return d->takeLast(); }

    // Sequence interface.
    T &first() { return d->hash[d->keys.first()]; }
    const T &first() const { return d->hash[d->keys.first()]; }
    T &last() { return d->hash[d->keys.last()]; }
    const T &last() const { return d->hash[d->keys.last()]; }
    void removeFirst() { d->takeFirst(); }
    void removeLast() { d->takeLast(); }

    // Sequence interface, STL-style.
    void pop_front() { d->takeFirst(); }
    void pop_back() { d->takeLast(); }
};

#ifdef Q_COMPILER_INITIALIZER_LISTS
template <typename Key, typename T>
OrderedHash<Key, T>::OrderedHash(
        std::initializer_list< std::pair<Key, T> > list) :
    d(new Data())
{
    typedef typename std::initializer_list<std::pair<Key,T> >::const_iterator
            InitListConstIterator;
    for (InitListConstIterator it = list.begin(); it != list.end(); ++it)
        insert(it->first, it->second);
}
#endif

template <typename Key, typename T>
bool OrderedHash<Key, T>::operator==(const OrderedHash &other) const
{
    if (d == other.d)
        return true;
    return d->hash == other.d->hash && d->keys == other.d->keys;
}

template <typename Key, typename T>
bool OrderedHash<Key, T>::operator!=(const OrderedHash &other) const
{
    return !(*this == other);
}

template <typename Key, typename T>
void OrderedHash<Key, T>::clear()
{
    d->clear();
}

template <typename Key, typename T>
int OrderedHash<Key, T>::remove(const Key &key)
{
    int r = d->hash.remove(key);
    if (r)
        d->keys.erase(d->lookup.take(key));
    return r;
}

template <typename Key, typename T>
T OrderedHash<Key, T>::take(const Key &key)
{
    if (d->hash.contains(key))
        d->keys.erase(d->lookup.take(key));
    return d->hash.take(key);
}

template <typename Key, typename T>
const Key OrderedHash<Key, T>::key(const T &value, const Key &defaultKey) const
{
    foreach (const Key &key, d->keys)
    {
        if (d->hash.value(key) == value)
            return key;
    }
    return defaultKey;
}

template <typename Key, typename T>
QList<Key> OrderedHash<Key, T>::keys() const
{
    QList<Key> keys;
    keys.reserve(d->keys.size());
    foreach (const Key &key, d->keys)
        keys.append(key);
    return keys;
}

template <typename Key, typename T>
QList<Key> OrderedHash<Key, T>::keys(const T &value) const
{
    QList<Key> keys;
    keys.reserve(d->keys.size());
    foreach (const Key &key, d->keys)
    {
        if (d->hash.value(key) == value)
            keys.append(key);
    }
    return keys;
}

template <typename Key, typename T>
QList<T> OrderedHash<Key, T>::values() const
{
    QList<T> values;
    values.reserve(d->keys.size());
    foreach (const Key &key, d->keys)
        values.append(d->hash.value(key));
    return values;
}

template <typename Key, typename T>
typename OrderedHash<Key, T>::iterator OrderedHash<Key, T>::erase(
        OrderedHash<Key, T>::iterator it)
{
    Q_ASSERT_X(it.d == d.data(), "qtcollections::OrderedHash::erase",
               "The specified iterator argument 'it' is invalid");
    if (it == end())
        return it;
    iterator next = it + 1;
    d->erase(it.i);
    return next;
}

template <typename Key, typename T>
typename OrderedHash<Key, T>::iterator OrderedHash<Key, T>::insert(
        const Key &key, const T &value)
{
    bool existed = d->hash.contains(key);
    d->hash.insert(key, value);
    if (existed)
        return iterator(d->lookup.value(key), d);

    KeyIterator kit = d->keys.insert(d->keys.end(), key);
    d->lookup.insert(key, kit);
    return iterator(kit, d);
}


}   // namespace qtcollections

#endif // QTCOLLECTIONS_ORDEREDHASH_H
