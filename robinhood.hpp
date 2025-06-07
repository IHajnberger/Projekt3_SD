#ifndef RobinHood
#define RobinHood

#include <vector>

class RobinHoodHashTable 
{
private:
    struct Entry 
    {
        int key;
        int value;
        int probeLength;
        bool isEmpty;
        Entry() : key(-1), value(-1), probeLength(0), isEmpty(true) {}
        Entry(int k, int v, int p, bool e) : key(k), value(v), probeLength(p), isEmpty(e) {}
    };

    std::vector<Entry> table;
    int capacity;
    int hashFunction(int key) const;

public:
    explicit RobinHoodHashTable(int size);
    void insert(int key, int value);
    int search(int key) const;
    void remove(int key);
};

#endif 
