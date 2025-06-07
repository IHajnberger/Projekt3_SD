#ifndef Cuckohash
#define Ccuckohash

#include <vector>
#include <stdexcept>

class CuckooHashTable 
{
private:
    struct Entry 
    {
        int key;
        int value;
        bool isEmpty;
        Entry() : key(-1), value(-1), isEmpty(true) {}
        Entry(int k, int v, bool e) : key(k), value(v), isEmpty(e) {}
    };

    std::vector<Entry> table1;
    std::vector<Entry> table2;
    int capacity;
    void rehash();
    int hash1(int key) const;
    int hash2(int key) const;

public:
    explicit CuckooHashTable(int size);
    void insert(int key, int value);
    int search(int key) const;
    void remove(int key);
};

#endif 