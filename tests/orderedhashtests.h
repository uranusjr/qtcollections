#ifndef ORDEREDHASHTESTS_H
#define ORDEREDHASHTESTS_H

#include <QtTest>
#include "orderedhash.h"

class OrderedHashTests : public QObject
{
    Q_OBJECT

public:
    OrderedHashTests();

private slots:
    // Implicitly tests the assignment operator.
    void init();
    void testCopyConstructor();
    void testInitializerListConstructor();
    void testAssignmentOperator();

    // testSwap();

    void testEqualityOperator();
    void testInequalityOperator();

    void testSize();
    void testIsEmpty();

    void testClear();
    void testRemove();
    void testTake();

    void testContains();
    void testKey();
    void testKeyDefault();
    void testValue();
    void testValueDefault();
    void testBracketOperator();

    void testKeys();
    void testKeysForValue();
    void testValues();

    // Tests for iterator.

    // Tests for const_iterator.

    void testEmpty();
    void testCount();
    void testFind();
    void testFindConst();
    void testConstFind();
    void testErase();

    void testInsert();
    void testToHash();
    void testFirstKey();
    void testLastKey();
    void testTakeFirst();
    void testTakeLast();

    void testFirst();
    void testLast();

    void testRemoveFirst();
    void testRemoveLast();

    void testPopFront();
    void testPopBack();

    void testConstIteration();
    void testForeach();

private:
    // Implicitly tests the default constructor.
    qtcollections::OrderedHash<int, QString> hash;
};


class ContainedOrderedHashTests : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void testBracketOperatorConst() const;
    void testFirst() const;
    void testLast() const;

private:
    qtcollections::OrderedHash<int, QString> hash;
};


#endif  // ORDEREDHASHTESTS_H

