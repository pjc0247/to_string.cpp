to_string.cpp
====

cpp is trash


Usage
----
* for Custom Classes
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

* for Fundamental types
```c++
int a = 1;

std::cout<< to_string(a) <<std::endl;
```

* for STL containers
```c++
std::vector<int> v({1,2,3,4});

std::cout<< to_string(v); // [1, 2, 3, 4]

std::map<std::string, std::string> m({{"name", "park"}, {"nickname", "jo"}});

std::cout<< to_string(m); // {name : park, nickname : jo}

std::map<std::string, std::vector<std::string>> m2({
		{"fruits", {"apple", "banana", "orange"}},
		{"colors", {"yellow", "red", "blue"}}
	});
std::cout<< to_string(m2); // {fruits : [apple, banana, orange], colors : [yellow, red, blue]}
```

* for initializer-lists
```c++
std::cout<< to_string({1,2,3,4});

std::cout<< to_string({{1,2}, {3,4}}); //not implemented yet
```

is_string_convertible
----
```c++
cout<< is_string_convertible<Foo>::value; // true
cout<< is_string_convertible<Bar>::value; // false
```
