#pragma once

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <ostream>
#include <utility>

template <typename T>
class tinyvec {
 public:
  tinyvec<T>() : _data(nullptr), _size(0), _capacity(0){};

  tinyvec<T>(T val) : tinyvec<T>() { push_back(val); };

  tinyvec(std::initializer_list<T> init)
      : _data(new T[init.size()]), _size(init.size()), _capacity(init.size()) {
    std::copy(init.begin(), init.end(), _data);
  }

  tinyvec<T>(const tinyvec<T>& other)
      : _size(other._size), _capacity(other._capacity) {
    if (_capacity > 0) {
      _data = new T[_capacity];
      std::copy(other._data, other._data + _size, _data);
    } else {
      _data = nullptr;
    }
  };

  tinyvec(tinyvec<T>&& other) noexcept
      : _data(other._data), _size(other._size), _capacity(other._capacity) {
    other._data = nullptr;
    other._size = 0;
    other._capacity = 0;
  }

  ~tinyvec<T>() { delete[] _data; };

  size_t size() const { return _size; };

  size_t capacity() const { return _capacity; };

  void push_back(const T& val) {
    if (_size >= _capacity) {
      resize();
    }
    _data[_size] = val;
    _size++;
  };

  void push_back(T&& val) {
    if (_size >= _capacity) {
      resize();
    }
    _data[_size] = std::move(val);
    _size++;
  };

  T pop_back() {
    if (_size == 0) {
      throw std::out_of_range("tinyvec::pop_back() called on empty tinyvec");
    }
    _size--;
    return std::move(_data[_size]);
  };

  T& operator[](size_t index) {
    if (index >= _size) {
      throw std::out_of_range("index out of bounds");
    }
    return _data[index];
  };

  const T& operator[](size_t index) const {
    if (index >= _size) {
      throw std::out_of_range("index out of bounds");
    }
    return _data[index];
  };

  tinyvec& operator=(const tinyvec& other) noexcept {
    if (this != &other) {
      T* newData = new T[other._capacity];
      std::copy(other._data, other._data + other._size, newData);
      delete[] _data;
      _data = newData;
      _size = other._size;
      _capacity = other._capacity;
    }
    return *this;
  };

  tinyvec<T>& operator=(tinyvec<T>&& other) noexcept {
    if (this != &other) {
      delete[] _data;
      _data = other._data;
      _size = other._size;
      _capacity = other._capacity;

      other._data = nullptr;
      other._size = 0;
      other._capacity = 0;
    }
    return *this;
  }

 private:
  void resize() {
    size_t cap = (_capacity == 0 ? 1 : _capacity) * 2;
    T* data = new T[cap];

    for (size_t i = 0; i < _size; ++i) {
      data[i] = std::move_if_noexcept(_data[i]);
    }

    delete[] _data;  // deallocate old array
    _capacity = cap;
    _data = data;
  };

  T* _data;
  size_t _size;
  size_t _capacity;
};

//
// "Friend" << method, outside class.
//
template <typename T>
std::ostream& operator<<(std::ostream& os, const tinyvec<T>& vec) {
  os << "[";
  for (size_t i = 0; i < vec.size(); ++i) {
    os << vec[i];
    if (i != vec.size() - 1) os << ", ";
  }
  os << "]";
  return os;
}