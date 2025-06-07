#include "cuckoo_hash.hpp"
#include <algorithm>
#include <stdexcept>

CuckooHashTable::CuckooHashTable(int size)
    : table1(size), table2(size), capacity(size) {}

int CuckooHashTable::hash1(int key) const 
{
    return key % capacity;
}

int CuckooHashTable::hash2(int key) const 
{
    return (key / 7) % capacity;
}

void CuckooHashTable::rehash() 
{
    int oldCapacity = capacity;
    capacity *= 2;
    std::vector<Entry> newTable1(capacity);
    std::vector<Entry> newTable2(capacity);
    std::swap(table1, newTable1);
    std::swap(table2, newTable2);

  for (int i = 0; i < oldCapacity; i++) 
  {
        if (!newTable1[i].isEmpty) 
        {
            insert(newTable1[i].key, newTable1[i].value);
        }
        if (!newTable2[i].isEmpty) 
        {
            insert(newTable2[i].key, newTable2[i].value);
        }
    }
}

void CuckooHashTable::insert(int key, int value) 
{
    int index1 = hash1(key);
    int index2 = hash2(key);
    int loopCount = 0;
    int maxLoops = capacity * 2;

        while (loopCount < maxLoops) 
        {
        if (table1[index1].isEmpty) 
        {
            table1[index1] = Entry(key, value, false);
            return;
        }

        std::swap(key, table1[index1].key);
        std::swap(value, table1[index1].value);

        index2 = hash2(key);
        if (table2[index2].isEmpty) 
        {
            table2[index2] = Entry(key, value, false);
            return;
        }

        std::swap(key, table2[index2].key);
        std::swap(value, table2[index2].value);

        index1 = hash1(key);
        loopCount++;
    }

    rehash();
    insert(key, value);
}

int CuckooHashTable::search(int key) const 
{
    int index1 = hash1(key);
    int index2 = hash2(key);

    if (!table1[index1].isEmpty && table1[index1].key == key) 
    {
        return table1[index1].value;
    }
    if (!table2[index2].isEmpty && table2[index2].key == key) 
    {
        return table2[index2].value;
    }
  return -1;;
}

void CuckooHashTable::remove(int key) 
{
    int index1 = hash1(key);
    int index2 = hash2(key);

    if (!table1[index1].isEmpty && table1[index1].key == key) 
    {
        table1[index1] = Entry();
        return;
    }
    if (!table2[index2].isEmpty && table2[index2].key == key) 
    {
        table2[index2] = Entry();
        return;
    }
}