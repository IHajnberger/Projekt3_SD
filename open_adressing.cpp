#include "open_adressing.hpp"

OpenAddressingHashTable::OpenAddressingHashTable(int cap)
    : table(cap), capacity(cap), size(0) {}

int OpenAddressingHashTable::hash(int key) const 
{
    return key % capacity;
}
int OpenAddressingHashTable::probe(int hashValue, int i) const 
{
    return (hashValue + i) % capacity;
}

void OpenAddressingHashTable::insert(int key, int value) 
{
    int hashValue = hash(key);
    for (int i = 0; i < capacity; ++i) {
        int idx = probe(hashValue, i);
        if (table[idx].isEmpty || table[idx].isDeleted || table[idx].key == key) 
        {
            table[idx] = Entry(key, value);
            table[idx].isDeleted = false;
            table[idx].isEmpty = false;
            return;
        }
    }
    throw std::runtime_error("Hash table is full");
}

int OpenAddressingHashTable::search(int key) const 
{
    int hashValue = hash(key);
    for (int i = 0; i < capacity; ++i) 
    {
        int idx = probe(hashValue, i);
        if (table[idx].isEmpty) break;
        if (!table[idx].isDeleted && table[idx].key == key) 
        {
            return table[idx].value;
        }
    }
    throw std::runtime_error("Key not found");
}

void OpenAddressingHashTable::remove(int key) 
{
    int hashValue = hash(key);
    for (int i = 0; i < capacity; ++i) {
        int idx = probe(hashValue, i);
        if (table[idx].isEmpty) break;
        if (!table[idx].isDeleted && table[idx].key == key) 
        {
            table[idx].isDeleted = true;
            return;
        }
    }
    throw std::runtime_error("Key not found");
}