#ifndef VECTOR_H
#define VECTOR_H
#include <cstddef>
#include <iostream>
using namespace std;

class Vector {
public:
    using value_type = double;
    using pointer = value_type*;
    using const_reference = const value_type&;

private:
    size_t max_sz;
    size_t sz;
    pointer values;

public:
    Vector() {
        max_sz = 0;
        sz = 0;
        values = nullptr;
    }
    Vector(size_t n) {
        max_sz = n;
        values = new value_type[max_sz];
        sz = 0;
    }
    ~Vector() {
        delete[] values;
    }
    Vector(const Vector& src) {
        max_sz = src.max_sz;
        sz = src.sz;
        values = new value_type[max_sz];
        for (size_t i{0}; i < sz; ++i)
            values[i] = src.values[i];
    }
    Vector& operator=(Vector src) {
        swap(sz, src.sz);
        swap(max_sz, src.max_sz);
        swap(values, src.values);
        return *this;
    }
    void reserve(size_t n) {
        if (n > max_sz) {
            value_type* new_values = new value_type[n];
            for (size_t i{0}; i < sz; ++i)
                new_values[i] = values[i];
            max_sz = n;
            delete[] values;
            values = new_values;
        }
    }
    void push_back(const_reference val) {
        if (sz >= max_sz) {
            reserve(2*max_sz+1);
        }
        values[sz++] = val;
    }
    void clear() {
        sz = 0;
    }
    ostream& print(ostream & o) {
        for (size_t i{0}; i < sz; ++i)
            o << values[i] << '\n';
        return o;
    }
};

#endif