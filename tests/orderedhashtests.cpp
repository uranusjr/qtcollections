#include "orderedhashtests.h"

OrderedHashTests::OrderedHashTests() : QObject()
{
}

void OrderedHashTests::init()
{
    hash = qtcollections::OrderedHash<int, QString>();
}

void OrderedHashTests::testCopyConstructor()
{
    hash.insert(1, "one");
    auto copied = qtcollections::OrderedHash<int, QString>(hash);
    hash.insert(2, "two");

    QCOMPARE(hash.size(), 2);
    QCOMPARE(copied.size(), 1);
}

void OrderedHashTests::testInitializerListConstructor()
{
    hash.insert(1, "one");
    hash.insert(2, "two");

    qtcollections::OrderedHash<int, QString> expected({
        {1, "one"}, {2, "two"},
    });
    QCOMPARE(hash, expected);
}

void OrderedHashTests::testAssignmentOperator()
{
    hash.insert(1, "one");
    hash.insert(2, "two");

    auto copied = hash;
    qtcollections::OrderedHash<int, QString> expected({
        {1, "one"}, {2, "two"},
    });
    QCOMPARE(copied, expected);
}

void OrderedHashTests::testEqualityOperator()
{
    hash.insert(1, "one");
    auto other = qtcollections::OrderedHash<int, QString>();
    QCOMPARE(hash == other, false);

    other.insert(1, "one");
    QVERIFY(hash == other);
}

void OrderedHashTests::testInequalityOperator()
{
    hash.insert(1, "one");
    auto other = qtcollections::OrderedHash<int, QString>();
    QVERIFY(hash != other);

    other.insert(1, "one");
    QCOMPARE(hash != other, false);
}

void OrderedHashTests::testSize()
{
    QCOMPARE(hash.size(), 0);

    hash.insert(1, "one");
    QCOMPARE(hash.size(), 1);
}

void OrderedHashTests::testIsEmpty()
{
    QVERIFY(hash.isEmpty());

    hash.insert(1, "one");
    QVERIFY(!hash.isEmpty());
}

void OrderedHashTests::testClear()
{
    hash.insert(1, "one");
    QVERIFY(!hash.isEmpty());

    hash.clear();
    QVERIFY(hash.isEmpty());
}

void OrderedHashTests::testRemove()
{
    hash.insert(1, "one");
    hash.insert(2, "two");
    QVERIFY(!hash.isEmpty());

    QCOMPARE(hash.remove(3), 0);
    QVERIFY(!hash.isEmpty());

    QCOMPARE(hash.remove(1), 1);
    QCOMPARE(hash.remove(1), 0);

    QCOMPARE(hash.remove(2), 1);
    QVERIFY(hash.isEmpty());
}

void OrderedHashTests::testTake()
{
    hash.insert(1, "one");
    hash.insert(2, "two");
    QVERIFY(!hash.isEmpty());

    QCOMPARE(hash.take(3), QString());
    QVERIFY(!hash.isEmpty());

    QCOMPARE(hash.take(1), QString("one"));
    QCOMPARE(hash.size(), 1);

    QCOMPARE(hash.take(1), QString());
    QCOMPARE(hash.size(), 1);

    QCOMPARE(hash.take(2), QString("two"));
    QVERIFY(hash.isEmpty());
}

void OrderedHashTests::testContains()
{
    QVERIFY(!hash.contains(1));

    hash.insert(1, "one");
    QVERIFY(hash.contains(1));

    hash.remove(1);
    QVERIFY(!hash.contains(1));
}

void OrderedHashTests::testKey()
{
    hash.insert(1, "one");
    hash.insert(2, "one");
    hash.insert(3, "one");

    QCOMPARE(hash.key("one"), 1);
    QCOMPARE(hash.key("two"), 0);
}

void OrderedHashTests::testKeyDefault()
{
    hash.insert(1, "one");
    hash.insert(2, "one");
    hash.insert(3, "one");

    QCOMPARE(hash.key("one", -1), 1);
    QCOMPARE(hash.key("two", -1), -1);
}

void OrderedHashTests::testValue()
{
    hash.insert(1, "nil");
    hash.insert(1, "one");

    QCOMPARE(hash.value(1), QString("one"));
    QCOMPARE(hash.value(2), QString());
}

void OrderedHashTests::testValueDefault()
{
    hash.insert(1, "non");
    hash.insert(1, "one");

    QCOMPARE(hash.value(1, "nil"), QString("one"));
    QCOMPARE(hash.value(2, "nil"), QString("nil"));
}

void OrderedHashTests::testBracketOperator()
{
    hash.insert(1, "non");
    hash.insert(1, "one");

    QCOMPARE(hash[1], QString("one"));
    QCOMPARE(hash[2], QString());
}

void OrderedHashTests::testKeys()
{
    hash.insert(1, "one");
    hash.insert(2, "two");
    hash.insert(3, "one");

    QCOMPARE(hash.keys(), QList<int>() << 1 << 2 << 3);
}

void OrderedHashTests::testKeysForValue()
{
    hash.insert(1, "one");
    hash.insert(2, "two");
    hash.insert(3, "one");

    QCOMPARE(hash.keys("one"), QList<int>() << 1 << 3);
}

void OrderedHashTests::testValues()
{
    hash.insert(1, "one");
    hash.insert(2, "two");
    hash.insert(3, "one");

    QCOMPARE(hash.values(), QList<QString>() << "one" << "two" << "one");
}

void OrderedHashTests::testEmpty()
{
    QVERIFY(hash.empty());

    hash.insert(1, "one");
    QVERIFY(!hash.empty());
}

void OrderedHashTests::testCount()
{
    QCOMPARE(hash.count(), 0);

    hash.insert(1, "one");
    QCOMPARE(hash.count(), 1);
}

void OrderedHashTests::testFind()
{
    QCOMPARE(hash.find(1), hash.end());

    hash.insert(1, "one");
    QCOMPARE(hash.find(1).key(), 1);

    hash.insert(2, "one");
    QCOMPARE(hash.find(1).key(), 1);
    QCOMPARE(hash.find(2).key(), 2);
    QCOMPARE(hash.find(3), hash.end());
}

void OrderedHashTests::testFindConst()
{
    qtcollections::OrderedHash<int, QString>::const_iterator i;

    i = hash.find(1);
    QCOMPARE(i, hash.constEnd());

    hash.insert(1, "one");
    i = hash.find(1);
    QCOMPARE(i.key(), 1);

    hash.insert(2, "one");

    i = hash.find(1);
    QCOMPARE(i.key(), 1);

    i = hash.find(2);
    QCOMPARE(i.key(), 2);

    i = hash.find(3);
    QCOMPARE(i, hash.constEnd());
}

void OrderedHashTests::testConstFind()
{
    QCOMPARE(hash.constFind(1), hash.constEnd());

    hash.insert(1, "one");
    QCOMPARE(hash.constFind(1).key(), 1);

    hash.insert(2, "one");
    QCOMPARE(hash.constFind(1).key(), 1);
    QCOMPARE(hash.constFind(2).key(), 2);
    QCOMPARE(hash.constFind(3), hash.constEnd());
}

void OrderedHashTests::testErase()
{
    hash.insert(1, "one");
    hash.insert(2, "one");
    hash.insert(3, "one");
    QCOMPARE(hash.size(), 3);
    QCOMPARE(hash.find(2) + 1, hash.find(3));

    auto i = hash.erase(hash.find(2));
    QCOMPARE(hash.size(), 2);
    QCOMPARE(i, hash.find(3));

    hash.insert(2, "two");
    QCOMPARE(hash.find(2) - 1, hash.find(3));
}

void OrderedHashTests::testInsert()
{
    hash.insert(1, "one");
    QCOMPARE(hash.size(), 1);

    hash.insert(1, "non");
    QCOMPARE(hash.size(), 1);

    hash.insert(2, "two");
    QCOMPARE(hash.size(), 2);
}

void OrderedHashTests::testToHash()
{
    hash.insert(1, "one");
    hash.insert(3, "one");
    hash.insert(2, "two");

    auto actual = hash.toHash();
    QHash<int, QString> expected({{1, "one"}, {2, "two"}, {3, "one"}});
    QCOMPARE(actual, expected);

    hash.insert(4, "four");
    QCOMPARE(actual, expected);
}

void OrderedHashTests::testFirstKey()
{
    hash.insert(1, "one");
    hash.insert(2, "two");
    hash.insert(3, "one");

    QCOMPARE(hash.firstKey(), 1);
}

void OrderedHashTests::testLastKey()
{
    hash.insert(1, "one");
    hash.insert(3, "one");
    hash.insert(2, "two");

    QCOMPARE(hash.lastKey(), 2);

    hash.remove(3);
    QCOMPARE(hash.lastKey(), 2);
}

void OrderedHashTests::testTakeFirst()
{
    hash.insert(1, "one");
    hash.insert(3, "one");
    hash.insert(2, "two");
    QCOMPARE(hash.size(), 3);

    auto expected = QPair<int, QString>(1, "one");
    QCOMPARE(hash.takeFirst(), expected);
    QCOMPARE(hash.size(), 2);
}

void OrderedHashTests::testTakeLast()
{
    hash.insert(1, "one");
    hash.insert(2, "two");
    hash.insert(3, "one");
    QCOMPARE(hash.size(), 3);

    auto expected = QPair<int, QString>(3, "one");
    QCOMPARE(hash.takeLast(), expected);
    QCOMPARE(hash.size(), 2);
}

void OrderedHashTests::testFirst()
{
    hash.insert(1, "one");
    hash.insert(3, "three");
    hash.insert(2, "two");

    QCOMPARE(hash.first(), QString("one"));

    hash.remove(3);
    QCOMPARE(hash.first(), QString("one"));
}

void OrderedHashTests::testLast()
{
    hash.insert(1, "one");
    hash.insert(3, "one");
    hash.insert(2, "two");

    QCOMPARE(hash.last(), QString("two"));

    hash.remove(3);
    QCOMPARE(hash.last(), QString("two"));
}

void OrderedHashTests::testRemoveFirst()
{
    hash.insert(1, "one");
    hash.insert(3, "one");
    hash.insert(2, "two");

    hash.removeFirst();
    QCOMPARE(hash, decltype(hash)({{3, "one"}, {2, "two"}}));

    hash.removeFirst();
    QCOMPARE(hash, decltype(hash)({{2, "two"}}));
}

void OrderedHashTests::testRemoveLast()
{
    hash.insert(1, "one");
    hash.insert(3, "one");
    hash.insert(2, "two");

    hash.removeLast();
    QCOMPARE(hash, decltype(hash)({{1, "one"}, {3, "one"}}));

    hash.removeLast();
    QCOMPARE(hash, decltype(hash)({{1, "one"}}));
}

void OrderedHashTests::testPopFront()
{
    hash.insert(1, "one");
    hash.insert(3, "one");
    hash.insert(2, "two");

    hash.pop_front();
    QCOMPARE(hash, decltype(hash)({{3, "one"}, {2, "two"}}));

    hash.pop_front();
    QCOMPARE(hash, decltype(hash)({{2, "two"}}));
}

void OrderedHashTests::testPopBack()
{
    hash.insert(1, "one");
    hash.insert(3, "one");
    hash.insert(2, "two");

    hash.pop_back();
    QCOMPARE(hash, decltype(hash)({{1, "one"}, {3, "one"}}));

    hash.pop_back();
    QCOMPARE(hash, decltype(hash)({{1, "one"}}));
}

void OrderedHashTests::testConstIteration()
{
    hash.insert(1, "one");
    auto it = hash.constBegin();

    QCOMPARE(it.key(), 1);
    QCOMPARE(it.value(), QString("one"));
    QCOMPARE(*it, QString("one"));

    it++;
    QCOMPARE(it, hash.constEnd());
}

void OrderedHashTests::testForeach()
{
    auto keys = QList<int>() << 1 << 2 << 3 << 4;
    auto comp = QHash<int, QString>({
        {1, "one"}, {2, "two"}, {3, "three"}, {1, "four"},
    });
    foreach (int key, keys)
        hash.insert(key, comp.value(key));

    auto kit = keys.constBegin();
    foreach (const QString &value, hash)
    {
        QCOMPARE(value, comp.value(*kit));
        kit++;
    }
}

void ContainedOrderedHashTests::init()
{
    hash = qtcollections::OrderedHash<int, QString>({{1, "one"}, {2, "two"}});
}

void ContainedOrderedHashTests::testBracketOperatorConst() const
{
    QCOMPARE(hash[1], QString("one"));
    QCOMPARE(hash[3], QString());
}

void ContainedOrderedHashTests::testFirst() const
{
    QCOMPARE(hash.first(), QString("one"));
}

void ContainedOrderedHashTests::testLast() const
{
    QCOMPARE(hash.last(), QString("two"));
}
