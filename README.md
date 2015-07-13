to_string.cpp
====

cpp is trash


```c++
class Foo{
public:
  int v;
  
  std::string to_string(){
    return "Foo (v : " + to_string(v) + ")";
  }
};
```
```c++
Foo f;

f.v = 14;

std::cout<< to_string(f) <<std::endl; // Foo(v : 14)

```
