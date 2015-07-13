to_string.cpp
====

cpp is trash


Usage (for Custom Classes)
----
```c++
class Foo{
public:
  int v;
  
  std::string to_string(){
    return "Foo (v : " + ::to_string(v) + ")";
  }
};
```
```c++
Foo f;

f.v = 14;

std::cout<< to_string(f) <<std::endl; // Foo(v : 14)
```

Usage (for Fundamental types)
----
```c++
int a = 1;

std::cout<< to_string(a) <<std::endl;
```

is_string_convertible
----
```c++
cout<< is_string_convertible<Foo>::value; // true
cout<< is_string_convertible<Bar>::value; // false
```
