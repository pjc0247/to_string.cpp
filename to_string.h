#pragma once

#include <string>

template <typename T, bool A> 
struct get_to_string_ret_type{
	enum{value = false};
};
template <typename T> 
struct get_to_string_ret_type<T, true>{
	enum{value = std::is_same<std::string,  decltype(((T*)nullptr)->to_string()) >::value};
};

class pod_defaults{
public:

	template <typename T>
	struct cvt{
		/* nothing -> deduction failure */
	};

	template <>
	struct cvt<int>{
		static std::string to_string(int n){
			return "int";
		}
	};
	template <>
	struct cvt<float>{
		static std::string to_string(int n){
			return "float";
		}
	};
};

template <typename T> 
struct pod_convertible{
	typedef char yes;
    typedef long no;

    template <typename C> static yes test( decltype(&pod_defaults::cvt<C>::to_string) ) ;
    template <typename C> static no test(...);

public:
	enum{value = sizeof(test<T>(0)) == sizeof(yes)};
};


template <typename T>
struct has_to_string{
public:
    typedef char yes;
    typedef long no;

    template <typename C> static yes test( decltype(&C::to_string) ) ;
    template <typename C> static no test(...);

public:
    enum{value = get_to_string_ret_type<Hello, sizeof(test<T>(0)) == sizeof(yes) >::value};
};


template <typename T>
struct is_string_convertible {
	enum{value = has_to_string<T>::value || pod_convertible<T>::value};
};



template <typename T>
typename std::enable_if<has_to_string<T>::value, std::string>::type
to_string(T o){
	return o.to_string();
}

template <typename T>
typename std::enable_if<(!has_to_string<T>::value) && pod_convertible<T>::value, std::string>::type
to_string(T o){
	return pod_defaults::cvt<T>::to_string(o);
}

template <typename T>
typename std::enable_if<(!has_to_string<T>::value) && (!pod_convertible<T>::value), std::string>::type
to_string(T o){
	char tmp[128];
	sprintf_s(tmp, "#<%s %p>", typeid(T).name(), &o);
	return tmp;
}
