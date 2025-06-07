#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <random>
#include <algorithm>
#include "Cuckoo_hash.hpp"
#include "robinhood.hpp"
#include "open_adressing.hpp"
using namespace std;
std::vector<int> unique_keys(int n) 
{
    std::vector<int> keys(n);
    for (int i = 0; i < n; ++i) keys[i] = i;
    std::shuffle(keys.begin(), keys.end(), std::mt19937(std::random_device{}()));
    return keys;
}

int main() 
{
    std::vector<int> sizes = {500, 1000, 5000, 10000, 50000, 100000, 500000, 1000000};
    std::vector<double> fills = {0, 0.25, 0.5, 0.75, 0.99, 0.997};
    // 0% i 25% - przypadki optymistyczne
    // 50% i 75% - przypadki średnie
    // 99% i 99.7% - przypadki pesymistyczne
    int powtorzenia = 100;
    std::ofstream wyniki("wyniki.txt");

    for (int size : sizes) {
        for (double fill : fills) {
            int n = static_cast<int>(size * fill);
            std::vector<int> keys = unique_keys(n);
            CuckooHashTable cuckoo(size);
            for (int i = 0; i < n; ++i) cuckoo.insert(keys[i], keys[i] * 10);

            long long total_insert = 0, total_remove = 0;
            for (int i = 0; i < powtorzenia; ++i) 
            {
                int test_key = size + i; 
                // Insert test
                auto start = std::chrono::high_resolution_clock::now();
                cuckoo.insert(test_key, test_key * 10);
                auto end = std::chrono::high_resolution_clock::now();
                total_insert += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
                cuckoo.remove(test_key);
                // Remove test
                cuckoo.insert(test_key, test_key * 10);
                start = std::chrono::high_resolution_clock::now();
                cuckoo.remove(test_key);
                end = std::chrono::high_resolution_clock::now();
                total_remove += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            }
            wyniki << "[Cuckoo] Rozmiar: " << size << ", Zapełnienie: " << (fill * 100) << "%\n";
            wyniki << "  Średni czas insert: " << total_insert / powtorzenia << " ns\n";
            wyniki << "  Średni czas remove: " << total_remove / powtorzenia << " ns\n";

            RobinHoodHashTable robin(size);
            for (int i = 0; i < n; ++i) robin.insert(keys[i], keys[i] * 10);

            total_insert = 0; total_remove = 0;
            for (int i = 0; i < powtorzenia; ++i) 
            {
                int test_key = size + i;
                auto start = std::chrono::high_resolution_clock::now();
                robin.insert(test_key, test_key * 10);
                auto end = std::chrono::high_resolution_clock::now();
                total_insert += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
                robin.remove(test_key);
                robin.insert(test_key, test_key * 10);
                start = std::chrono::high_resolution_clock::now();
                robin.remove(test_key);
                end = std::chrono::high_resolution_clock::now();
                total_remove += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            }
            wyniki << "[RobinHood] Rozmiar: " << size << ", Zapełnienie: " << (fill * 100) << "%\n";
            wyniki << "  Średni czas insert: " << total_insert / powtorzenia << " ns\n";
            wyniki << "  Średni czas remove: " << total_remove / powtorzenia << " ns\n";

            OpenAddressingHashTable open(size);
            for (int i = 0; i < n; ++i) open.insert(keys[i], keys[i] * 10);

            total_insert = 0; total_remove = 0;
            for (int i = 0; i < powtorzenia; ++i)
            {
                int test_key = size + i;
                auto start = std::chrono::high_resolution_clock::now();
                open.insert(test_key, test_key * 10);
                auto end = std::chrono::high_resolution_clock::now();
                total_insert += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
                open.remove(test_key);
                open.insert(test_key, test_key * 10);
                start = std::chrono::high_resolution_clock::now();
                open.remove(test_key);
                end = std::chrono::high_resolution_clock::now();
                total_remove += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            }
            wyniki << "[OpenAddressing] Rozmiar: " << size << ", Zapełnienie: " << (fill * 100) << "%\n";
            wyniki << "  Średni czas insert: " << total_insert / powtorzenia << " ns\n";
            wyniki << "  Średni czas remove: " << total_remove / powtorzenia << " ns\n";
        }
    }
    cout<<"Testy przeprowadzone pomyslnie - calosc testu w pliku wyniki.txt"<<endl;
    wyniki.close();
    return 0;
}