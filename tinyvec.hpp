#pragma once

#include <algorithm>
#include <cstddef>
#include <format>
#include <iostream>
#include <memory>
#include <ostream>
#include <string>
#include <utility>

template <typename T, typename Allocator = std::allocator<T>>
class tinyvec {
 public:
  using value_type = T;
  using allocator_type = Allocator;
  using size_type = size_t;

  tinyvec() : _data(nullptr), _size(0), _capacity(0), _allocator(Allocator()) {
    std::println("[tinyvec] : default constructor");
  };

  tinyvec(T val)
      : _data(nullptr), _size(0), _capacity(0), _allocator(Allocator()) {
    std::println("[tinyvec] : calling on |T val| constructor");
    push_back(val);
  };

  explicit tinyvec(const Allocator& alloc)
      : _size(0), _capacity(0), _allocator(alloc), _data(nullptr) {}

  tinyvec(std::initializer_list<T> init)
      : _size(init.size()), _capacity(init.size()), _allocator(Allocator()) {
    std::println("[tinyvec] : initializer list constructor");
    _data = _allocator.allocate(init.size());  //_data(new T[init.size()]),
    std::copy(init.begin(), init.end(), _data);
  }

  tinyvec(const tinyvec& other)
      : _size(other._size),
        _capacity(other._capacity),
        _allocator(other._allocator) {
    if (_capacity > 0) {
      _data = _allocator.allocate(_capacity);
      std::copy(other._data, other._data + _size, _data);
    } else {
      _data = nullptr;
    }
  };

  tinyvec(tinyvec&& other) noexcept {
    if (this != &other) {
      if (_data && _capacity > 0) {
        _allocator.deallocate(_data, _capacity);
      }
      _data = other._data;
      _size = other._size;
      _capacity = other._capacity;
      other._data = nullptr;
      other._size = 0;
      other._capacity = 0;
    }
  }

  ~tinyvec() {
    clear();
    if (_data) {
      _allocator.deallocate(_data, _capacity);
    }
  };

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

  void clear() {
    for (size_type i = 0; i < _size; ++i) {
      std::destroy_at(_data + i);
    }
    _size = 0;
  }

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
      if (_data && _capacity > 0) {
        _allocator.deallocate(_data, _capacity);
      }
      _data = _allocator.allocate(other._capacity);
      std::copy(other._data, other._data + other._size, _data);
      _size = other._size;
      _capacity = other._capacity;
    }
    return *this;
  };

  tinyvec& operator=(tinyvec<T, Allocator>&& other) noexcept {
    if (this != &other) {
      if (_data && _capacity > 0) {
        _allocator.deallocate(_data, _capacity);
      }
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
  T* _data;
  size_type _size;
  size_type _capacity;
  Allocator _allocator;

  void resize() {
    size_type new_capacity = (_capacity == 0 ? 1 : _capacity) * 2;
    T* data = _allocator.allocate(new_capacity);

    for (size_type i = 0; i < _size; ++i) {
      data[i] = std::move_if_noexcept(_data[i]);
    }

    if (_data && _capacity > 0) {
      _allocator.deallocate(_data, _capacity);
    }

    _capacity = new_capacity;
    _data = data;
  };
};

//
// "Friend" << method, outside class.
//
template <typename T, typename A>
std::ostream& operator<<(std::ostream& os, const tinyvec<T, A>& vec) {
  os << "[";
  for (size_t i = 0; i < vec.size(); ++i) {
    os << vec[i];
    if (i != vec.size() - 1) os << ", ";
  }
  os << "]";
  return os;
}

// To be able to do:
// |tinyvec<T> tv{T};|
// |std::println("{}", tv);|
template <typename T, typename A>
struct std::formatter<tinyvec<T, A>> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }

  auto format(const tinyvec<T, A>& obj, std::format_context& ctx) const {
    static_assert(std::formattable<T, char>,
                  "tinyvec<T, A> requires T to be formattable");

    size_t sizeMinusOne = obj.size() - 1;

    std::string s = "[";
    for (size_t i = 0; i < obj.size(); ++i) {
      if (i < sizeMinusOne) {
        s += std::format("{}, ", obj[i]);
      } else {
        s += std::format("{}", obj[i]);
      }
    }
    s += "]";

    return std::format_to(ctx.out(), "{}", s);
  }
};