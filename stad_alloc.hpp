#include <print>

template <typename T>
struct stad_alloc {
  using value_type = T;

  stad_alloc() { std::println("[stad_alloc] Default stad_alloc<{}>", typeid(T).name()); }

  stad_alloc(const stad_alloc&) noexcept { std::println("[stad_alloc] Copy constructor called"); }

  template <typename U>
  stad_alloc(const stad_alloc<U>&) {
    std::println("[stad_alloc] Rebinding stad_alloc from <{}> to <{}>", typeid(U).name(),
                 typeid(T).name());
  }

  T* allocate(std::size_t n) {
    std::println("[stad_alloc] Allocating {} obbjects of type {}", n, typeid(T).name());
    return static_cast<T*>(operator new(n * sizeof(T)));
  }

  void deallocate(T* p, std::size_t n) {
    std::println("[stad_alloc] Deallocating {} objects of type {}", n, typeid(T).name());
    operator delete(p);
  }

  template <typename U>
  bool operator==(const stad_alloc<U>&) const noexcept {
    return true;
  }

  template <typename U>
  bool operator!=(const stad_alloc<U>&) const noexcept {
    return false;
  }
};
