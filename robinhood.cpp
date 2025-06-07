#include "robinhood.hpp"
#include <stdexcept>
#include <algorithm>

RobinHoodHashTable::RobinHoodHashTable(int size)
    : table(size), capacity(size) {}

int RobinHoodHashTable::hashFunction(int key) const 
{
    return key % capacity;
}

void RobinHoodHashTable::insert(int key, int value) 
{
    int idx = hashFunction(key);
    int probeLen = 0;
    Entry newEntry(key, value, probeLen, false);

    while (true) {
        if (table[idx].isEmpty) 
        {
            newEntry.probeLength = probeLen;
            table[idx] = newEntry;
            return;
        }
        if (table[idx].key == key) 
        {
            table[idx].value = value;
            return;
        }
        if (table[idx].probeLength < probeLen) 
        {
            std::swap(table[idx], newEntry);
        }
        idx = (idx + 1) % capacity;
        probeLen++;
        newEntry.probeLength = probeLen;
        if (probeLen >= capacity) {
            throw std::overflow_error("Hash table is full");
        }
    }
}

int RobinHoodHashTable::search(int key) const 
{
    int idx = hashFunction(key);
    int probeLen = 0;
    while (!table[idx].isEmpty && probeLen < capacity) 
    {
        if (table[idx].key == key) 
        {
            return table[idx].value;
        }
        if (table[idx].probeLength < probeLen) 
        {
            break;
        }
        idx = (idx + 1) % capacity;
        probeLen++;
    }
    throw std::runtime_error("Key not found");
}

void RobinHoodHashTable::remove(int key) 
{
    int idx = hashFunction(key);
    int probeLen = 0;
    while (!table[idx].isEmpty && probeLen < capacity) 
    {
        if (table[idx].key == key) {
            table[idx].isEmpty = true;
            int nextIdx = (idx + 1) % capacity;
            while (!table[nextIdx].isEmpty && table[nextIdx].probeLength > 0) 
            {
                table[idx] = table[nextIdx];
                table[idx].probeLength--;
                table[nextIdx].isEmpty = true;
                idx = nextIdx;
                nextIdx = (idx + 1) % capacity;
            }
            return;
        }
        if (table[idx].probeLength < probeLen) 
        {
            break;
        }
        idx = (idx + 1) % capacity;
        probeLen++;
    }
    throw std::runtime_error("Key not found");
}