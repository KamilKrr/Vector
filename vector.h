#ifndef VECTOR_H
#define VECTOR_H
#include<iostream>

template<typename T>
class Vector {
public:
	class ConstIterator;
	class Iterator;
    using value_type = T;
	using size_type = size_t;
	using difference_type = ptrdiff_t;
	using reference = value_type&;
    using pointer = value_type*;
	using const_pointer = const value_type*;
    using const_reference = const value_type&;
	using iterator = Vector::Iterator;
	using const_iterator = Vector::ConstIterator;
	

private:
    size_t max_sz;
    size_t sz;
    pointer values;

public:

class Iterator {
	public: 
		using value_type = Vector::value_type;
		using reference = Vector::reference;
		using pointer = Vector::pointer;
		using difference_type = Vector::difference_type;
		using iterator_category = std::forward_iterator_tag;

	private:
		pointer ptr;
		long availible_increments;
	public:
		Iterator() : ptr{nullptr}, availible_increments{-1}{};
		Iterator(pointer ptr) : ptr{ptr}, availible_increments{0} {};
		Iterator(pointer ptr, long availible_increments) : ptr{ptr}, availible_increments{availible_increments} {};
		reference operator*() {
			if(availible_increments <= 0) throw std::runtime_error("out of bounds");
			return *ptr;
		}
		pointer operator->() {
			if(availible_increments <= 0) throw std::runtime_error("out of bounds");
			return ptr;
		}
		bool operator==(const const_iterator& rop) const {
			return static_cast<const_iterator>(*this) == rop;
		}
		bool operator!=(const const_iterator& rop) const {
			return !(*this == rop);
		}
        iterator& operator++() {
			if(availible_increments <= 0) return *this;
            ptr++;
			availible_increments--;
            return *this;
        }
        iterator operator++(int) {
			if(availible_increments <= 0) return *this;
            return iterator(ptr++, availible_increments--);
        }
        operator const_iterator() const {
            return ConstIterator(ptr, availible_increments);
        }
};
class ConstIterator {
	public: 
		using value_type = Vector::value_type;
		using reference = Vector::const_reference;
		using pointer = Vector::const_pointer;
		using difference_type = Vector::difference_type;
		using iterator_category = std::forward_iterator_tag;
	private:
		pointer ptr;
		long availible_increments;
	public:
		ConstIterator() : ptr{nullptr}, availible_increments{-1} {};
		ConstIterator(pointer ptr) : ptr{ptr}, availible_increments{0} {};
		ConstIterator(pointer ptr, long availible_increments) : ptr{ptr}, availible_increments{availible_increments} {};
		reference operator*() {
			if(availible_increments <= 0) throw std::runtime_error("out of bounds");
			return *ptr;
		}
		pointer operator->() {
			if(availible_increments <= 0) throw std::runtime_error("out of bounds");
			return ptr;
		}
		bool operator==(const const_iterator& rop) const {
			return this->ptr == rop.ptr;
		}
		bool operator!=(const const_iterator& rop) const {
			return !(*this == rop);
		}
        const_iterator& operator++() {
			if(availible_increments <= 0) return *this;
            ptr++;
			availible_increments--;
            return *this;
        }
        const_iterator operator++(int) {
			if(availible_increments <= 0) return *this;
            return const_iterator(ptr++, availible_increments--);
        }
        friend Vector::difference_type operator-(const Vector::ConstIterator& lop, const Vector::ConstIterator& rop) {
            return lop.ptr - rop.ptr;
        }
};
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
    Vector(const Vector& src) {
        max_sz = src.max_sz;
        sz = src.sz;
        values = new value_type[max_sz];
        for (size_t i{0}; i < sz; ++i)
            values[i] = src.values[i];
    }
    Vector(std::initializer_list<value_type> list) {
        max_sz = list.size();
        sz = max_sz;
        values = new value_type[max_sz];

        size_t i{0};
        for(auto v : list) {
            values[i++] = v;
        }
    }
    ~Vector() {
        delete[] values;
    }
    Vector& operator=(Vector src) {
        std::swap(sz, src.sz);
        std::swap(max_sz, src.max_sz);
        std::swap(values, src.values);
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
    void clear() {
        sz = 0;
    }
    std::ostream& print(std::ostream & o) const {
        for (size_t i{0}; i < sz; ++i)
            o << values[i] << '\n';
        return o;
    }
    size_t size() const {
        return sz;
    }
    size_t capacity() const {
        return max_sz;
    }
    bool empty() const {
        return sz == 0;
    }
    void shrink_to_fit() {
        if(max_sz > sz){
            value_type* new_values = new value_type[sz];
            for (size_t i{0}; i < sz; ++i)
                new_values[i] = values[i];
            max_sz = sz;
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
    void pop_back() {
        if(empty())
            throw std::runtime_error ("pop_back failed: vector cannot be empty");
        
        sz--;
    }
    value_type& operator[](size_t index) {
        if(index < 0)
            throw std::out_of_range ("index cannot be negative");
        if(index >= sz)
            throw std::out_of_range ("index out of bounds");

        return values[index];
    }
    const value_type& operator[](size_t index) const {
        if(index < 0)
            throw std::out_of_range ("index cannot be negative");
        if(index >= sz)
            throw std::out_of_range ("index out of bounds");

        return values[index];
    }

	iterator begin() {
		return iterator(values, sz);
	}

	iterator end() {
		return iterator(values+sz, -1);
	}

    const_iterator begin() const {
		return const_iterator(values, sz);
	}

	const_iterator end() const {
		return const_iterator(values+sz, -1);
	}

    iterator insert(const_iterator pos, const_reference val) {
        auto diff = pos-begin();
        if (diff < 0 ||static_cast<size_type>(diff) > sz)
            throw std::runtime_error("Iterator out of bounds");
        size_type current{static_cast<size_type>(diff)};
        if (sz >= max_sz)
            reserve(max_sz * 2 + 1);
        for (auto i {sz}; i-- > current;)
            values[i+1] = values[i];
        values[current] = val;
        ++sz;
        return iterator{values+current, static_cast<long>(sz-1-current)};
    }

    iterator erase(const_iterator pos) {
        auto diff = pos-begin();
        if (diff < 0 ||static_cast<size_type>(diff) >= sz)
            throw std::runtime_error("Iterator out of bounds");
        size_type current{static_cast<size_type>(diff)};
        for (auto i{current}; i < sz - 1; ++i)
            values[i] = values[i + 1];
        --sz;
        return iterator{values+current, static_cast<long>(sz-1-current)};
    }

    friend std::ostream& operator<<(std::ostream& o, const Vector& v){
		return v.print(o);
	}
};

#endif
