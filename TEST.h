#pragma once

#include <iterator>

template<typename T>
class Iterator : public std::iterator<std::random_access_iterator_tag, T>
{
public:
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using difference_type = std::ptrdiff_t;

    Iterator(T* ptr) : m_ptr(ptr) {}
    Iterator(const Iterator& other) : m_ptr(other.m_ptr) {}

    Iterator& operator=(const Iterator& other)
    {
        m_ptr = other.m_ptr;
        return *this;
    }

    Iterator& operator++()
    {
        ++m_ptr;
        return *this;
    }

    Iterator& operator--()
    {
        --m_ptr;
        return *this;
    }

    Iterator operator++(int)
    {
        Iterator tmp(*this);
        operator++();
        return tmp;
    }

    Iterator operator--(int)
    {
        Iterator tmp(*this);
        operator--();
        return tmp;
    }

    Iterator operator+(difference_type n) const
    {
        Iterator tmp(*this);
        return tmp += n;
    }

    Iterator& operator+=(difference_type n)
    {
        m_ptr += n;
        return *this;
    }

    Iterator operator-(difference_type n) const
    {
        Iterator tmp(*this);
        return tmp -= n;
    }

    Iterator& operator-=(difference_type n)
    {
        m_ptr -= n;
        return *this;
    }

    difference_type operator-(const Iterator& other) const
    {
        return m_ptr - other.m_ptr;
    }

    reference operator*() const
    {
        return *m_ptr;
    }

    pointer operator->() const
    {
        return m_ptr;
    }

    reference operator[](difference_type n) const
    {
        return *(m_ptr + n);
    }

    bool operator==(const Iterator& other) const
    {
        return m_ptr == other.m_ptr;
    }

    bool operator!=(const Iterator& other) const
    {
        return m_ptr != other.m_ptr;
    }

    bool operator<(const Iterator& other) const
    {
        return m_ptr < other.m_ptr;
    }

    bool operator<=(const Iterator& other) const
    {
        return m_ptr <= other.m_ptr;
    }

    bool operator>(const Iterator& other) const
    {
        return m_ptr > other.m_ptr;
    }

    bool operator>=(const Iterator& other) const
    {
        return m_ptr >= other.m_ptr;
    }

    T* data() const
    {
        return m_ptr;
    }

    private:
        T* m_ptr;
};

template<typename T>
Iterator<T> operator+(typename Iterator<T>::difference_type n, const Iterator<T>& it)
{
    return it + n;
}

