//
// Created by Ignas on 5/8/2019.
//

#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H

#include <iostream>
#include <algorithm>
#include <memory>
#include <cstring>
#include <cmath>



template <class T>
class Vector {

public:
    typedef T* iterator;
    typedef  const T* const_iterator;
    typedef size_t size_type;
    typedef T value_type;

    Vector() { create(); }
    Vector(iterator first, iterator last) {
        create(first, last);
    }
    Vector(const Vector& v) {create(v.begin(), v.end());}
    explicit Vector(size_type n, const T& val = T{}) { create(n, val); }

    Vector& operator=(const Vector& rhs) {
        if (&rhs != this) {
            uncreate();

            create(rhs.begin(), rhs.end());
        }
        return *this;
    }

    ~Vector() { uncreate(); }

    size_type size() const { return  avail - data; }

    T& operator[](size_type i) { return  data[i];}
    const T& operator[](size_type i) const { return  data[i];}

    iterator begin() { return data;}
    const_iterator begin() const {return data;}
    iterator end() { return avail;}
    const_iterator end() const { return avail;}

    bool empty() {
        return size() == 0;
    }

    iterator insert (iterator position, const value_type& val) {
        size_type index = position-begin();

        if (avail == limit)
            grow();

        iterator pos = &data[index];

        std::move(pos, avail++, pos+1);

        *pos = val;


        return &data[0];

    }

    size_type capacity() {
        return limit-data;
    }

    void resize(size_type size, value_type val = {}) {

        unsigned int currSize = this->size();

        if (size == currSize) {
            return;
        }

        iterator new_data = alloc.allocate(size);

        iterator new_avail = std::copy(data, data+size, new_data);

        if (size > currSize) {
            std::uninitialized_fill(new_data+currSize, new_avail, val);
        }

        uncreate();

        data = new_data;
        avail = new_avail;
        limit = new_avail;
    }

    void shrink_to_fit() {

        if (limit == avail) {
            return;
        }

        iterator it = limit;
        while (it != avail) {
            alloc.destroy(--it);
        }

        alloc.deallocate(avail, limit - avail);

        limit = avail;
    }

    iterator erase(iterator it) {

        if (it > avail) {
            throw std::out_of_range("Out of range");
        }

        std::move(it + 1, avail--, it);

        return it;

    }

    void erase (iterator first, iterator last) {
        if (first > avail || last > avail) {
            throw std::out_of_range("Out of range");
        }
        size_type range = last - first;

        std::move(last+1, avail, first);

        avail -= (range+1);
    }

     void reserve(size_type size) {
        if (size <= capacity()) {
            return;
        }

         iterator new_data = alloc.allocate(size);
         iterator new_avail = std::uninitialized_copy(data, avail, new_data);

         uncreate();

         data = new_data;
         avail = new_avail;
         limit = data + size;
    }


    T& at(size_type pos) {
        if (pos >= size()) {
            throw std::out_of_range("Out of range");
        }

        return data[pos];
    }

    T& front() {
        return *begin();
    }

    T& back() {
        return *end();
    }

    T& front() const {
        return *begin();
    }

    T& back() const {
        return *end();
    }

    void push_back(const T& val) {
        if (avail == limit)
            grow();
        unchecked_append(val);
    }

    void pop_back() {
        iterator it = avail;
        alloc.destroy(--it);
        avail = it;
    }

    void clear()  {
        size_type prev_capacity = capacity();
        iterator new_data = alloc.allocate(prev_capacity);
        uncreate();

        limit = new_data + prev_capacity;
        data = avail = new_data;
    }


private:
    iterator data;
    iterator avail;
    iterator limit;

    std::allocator<T> alloc;

    void create() {
        data = avail = limit = nullptr;
    }

    void create(size_type n, const T& val) {
        data = alloc.allocate(n);
        limit = avail = data + n;
        std::uninitialized_fill(data, limit, val);
    }

    void create(const_iterator i, const_iterator j) {
        data = alloc.allocate(j - i);
        limit = avail = std::uninitialized_copy(i, j, data);

    }

    void uncreate() {
        if (data) {
            iterator it = avail;
            while (it != data) {
                alloc.destroy(--it);
            }

            alloc.deallocate(data, limit - data);
        }
        data = limit = avail = nullptr;
    }

    void grow() {
        size_type new_size = std::max(2 * (limit - data), ptrdiff_t(1));

        iterator new_data = alloc.allocate(new_size);
        iterator new_avail = std::uninitialized_copy(data, avail, new_data);

        uncreate();

        data = new_data;
        avail = new_avail;
        limit = data + new_size;
    }

    void unchecked_append(const T& val) {
        alloc.construct(avail++, val);
    }

};

#endif //VECTOR_VECTOR_H
