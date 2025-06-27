#include <iostream>

#include "tinyvec.hpp"

int main() {
  std::cout << "\nTesting general stuff\n";
  tinyvec<int> tv{1};
  std::cout << tv << "\n";
  tv.push_back(2);
  std::cout << tv << "\n";
  int last = tv.pop_back();
  std::cout << "tv.pop_back() " << last << " tv " << tv << "\n";
  tv.push_back(3);
  tv.push_back(4);
  tv.push_back(5);
  std::cout << tv << "\n";
  for (int i = 6; i <= 10; ++i) {
    tv.push_back(i);
  }
  std::cout << tv << "\n";

  // Testing copy assignment.
  std::cout << "\nTesting copy assignment\n";
  tinyvec<int> a{69};
  tinyvec<int> b{420};
  std::cout << "a:" << a << " b:" << b << " - Going to do a = b\n";
  a = b;
  std::cout << "a:" << a << " b:" << b << "\n";
  b[0] = 69;
  std::cout << "after |b[0] = 69| : " << "a: " << a << " b: " << b << "\n";

  // Testing move assignemnt
  std::cout << "\nTesting move assignment\n";
  tinyvec<int> ma1{1, 2};
  std::cout << "before move - ma1:" << ma1 << "\n";
  ma1 = tinyvec<int>{3, 4};
  std::cout << "after move - ma1:" << ma1 << "\n";
  tinyvec<int> mb1{1, 2};
  tinyvec<int> mb2{3, 4};
  std::cout << "before move - mb1:" << mb1 << " mb2:" << mb2 << "\n";
  mb1 = std::move(mb2);
  std::cout << "after move - mb1:" << mb1 << " mb2:" << mb2 << "\n";

  // Testing initialization lists
  std::cout << "\nTesting initialization list\n";
  tinyvec<int> multi{1, 2, 3};
  std::cout << multi << "\n";

  std::cout << "\nTesting misc : will throw an error!\n";
  std::cout << "calling pop_back() on empty tinyvec\n";
  tinyvec<int> empty;
  int z = empty.pop_back();
  std::cout << "z= " << z << "\n";
  return 0;
}