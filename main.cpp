#include <iostream>
#include <print>
#include <vector>

#include "stad_alloc.hpp"
#include "tinyvec.hpp"

int main() {
  std::println("\n~~~ Testing general stuff ~~~\n");
  tinyvec<int> tv{1};
  std::println("{}", tv);
  tv.push_back(2);
  std::println("{}", tv);
  int last = tv.pop_back();
  std::println("tv.pop_back()={} tv={}", last, tv);
  tv.push_back(3);
  tv.push_back(4);
  tv.push_back(5);
  std::println("{}", tv);
  for (int i = 6; i <= 10; ++i) {
    tv.push_back(i);
  }
  std::cout << tv << "\n";

  // Testing copy assignment.
  std::println("\n~~~ Testing copy assignment ~~~\n");
  tinyvec<int> a{69};
  tinyvec<int> b{420};
  std::println("a={} b={} - About to do |a = b|", a, b);
  a = b;
  std::println("a={} b={}", a, b);
  b[0] = 69;
  std::println("after |b[0]=69| : a={} b={}", a, b);

  // Testing move assignemnt
  std::println("\n~~~ Testing move assignment ~~~\n");
  tinyvec<int> ma1{1, 2};
  std::println("before move - ma1={}", ma1);
  ma1 = tinyvec<int>{3, 4};
  std::println("after move - ma1={}", ma1);
  tinyvec<int> mb1{1, 2};
  tinyvec<int> mb2{3, 4};
  std::println("before move - mb1={} mb2={}", mb1, mb2);
  mb1 = std::move(mb2);
  std::println("after move - mb1={} mb2={}", mb1, mb2);

  // Testing initialization lists
  std::println("\n~~~ Testing initialization list ~~~\n");
  tinyvec<int> multi{1, 2, 3};
  std::println("{}", multi);

  // Using tinyvec with custom allocator
  std::println(
      "\n~~~ Testing |tinyvec| with custom allocator |stad_alloc| ~~~\n");
  tinyvec<int, stad_alloc<int>> tvstad{1};
  std::println("{}", tvstad);
  tinyvec<int, stad_alloc<int>> tvstad_a{1};
  tinyvec<int, stad_alloc<int>> tvstad_b{2};
  std::println("\nbefore copy | tvstad_a={} tvstad_b={}", tvstad_a, tvstad_b);
  tvstad_a = tvstad_b;
  std::println("after copy | tvstad_a={} tvstad_b={}\n", tvstad_a, tvstad_b);
  tinyvec<int, stad_alloc<int>> tvstad_mv_a{1};
  tinyvec<int, stad_alloc<int>> tvstad_mv_b{2};
  std::println("\nbefore move | tvstad_mv_a={} tvstad_mv_b={}", tvstad_mv_a,
               tvstad_mv_b);
  tvstad_mv_a = std::move(tvstad_mv_b);
  std::println("after move | tvstad_mv_a={} tvstad_mv_b={}", tvstad_mv_a,
               tvstad_mv_b);

  // Using std::vector with custom allocator
  std::println(
      "\n~~~ Testing |std::vector| with custom allocator |stad_alloc| ~~~\n");
  std::vector<int, stad_alloc<int>> vecstad{1};
  std::println("{}", vecstad);

  std::println("\n~~~ Testing misc : will throw an error! ~~~\n");
  std::println("calling pop_back() on empty tinyvec\n");
  tinyvec<int> empty;
  int z = empty.pop_back();
  std::println("z= {}", z);
  return 0;
}