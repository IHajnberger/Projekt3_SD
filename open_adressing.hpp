#ifndef Open_adressing
#define Open_adressing

#include <vector>
#include <stdexcept>

class OpenAddressingHashTable 
{
private:
    struct Entry 
    {
        int key;
        int value;
        bool isEmpty;
        bool isDeleted;
        Entry() : key(-1), value(-1), isEmpty(true), isDeleted(false) {}
        Entry(int k, int v) : key(k), value(v), isEmpty(false), isDeleted(false) {}
    };

    std::vector<Entry> table;
    int capacity;
    int size;

    int hash(int key) const;
    int probe(int hashValue, int i) const;

public:
    explicit OpenAddressingHashTable(int cap);
    void insert(int key, int value);
    int search(int key) const;
    void remove(int key);
};

#endif 