# tvec
Implement vector

Just trying to learn!

# Usage

```c++
// tinyvec<T> v{T};
tinyvec<int> myInts{1, 2, 3};
myInts.push_back(4); // [1,2,3,4]
int fourth = myInts.pop_back(); // [1,2,3] -> 4 
std::cout << "My Ints: " << myInts << "\n";
```

# Compile

1. Configure

From root of project:

```shell
cmake -S . -B build
```

2. Build

From root of project

```shell
cmake --build build
```

3. Run `main.cpp`

From root of project

```shell
./build/main
```