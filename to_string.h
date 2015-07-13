#pragma once

#include <string>

class defaults{
public:

	template <typename T>
	struct cvt{
		/* nothing -> deduction failure */
	};

	template <>
	struct cvt<int>{
		static std::string to_string(int n){
			char b[32];
			sprintf_s(b, "%d", n);
			return b;
		}
	};
	template <>
	struct cvt<float>{
		static std::string to_string(int n){
			char b[32];
			sprintf_s(b, "%f", n);
			return b;
		}
	};
};

template <typename T> 
struct is_default_convertible{
	typedef char yes;
    typedef long no;

    template <typename C> static yes test( decltype(&defaults::cvt<C>::to_string) ) ;
    template <typename C> static no test(...);

public:
	enum{value = sizeof(test<T>(0)) == sizeof(yes)};
};

template <typename T, bool A> 
struct get_to_string_ret_type{
	enum{value = false};
};
template <typename T> 
struct get_to_string_ret_type<T, true>{
	enum{value = std::is_same<std::string,  decltype(((T*)nullptr)->to_string()) >::value};
};

template <typename T>
struct has_to_string{
public:
    typedef char yes;
    typedef long no;

    template <typename C> static yes test( decltype(&C::to_string) ) ;
    template <typename C> static no test(...);

public:
   /* to_string 메소드가 있는지 검사한다 ->
    * to_string 메소드 리턴형이 std::string인지 검사한다. */
    enum{value = get_to_string_ret_type<Hello, sizeof(test<T>(0)) == sizeof(yes) >::value};
};


template <typename T>
struct is_string_convertible {
    enum{value = has_to_string<T>::value || default_convertible<T>::value};
};



/* to_string메소드가 있는 경우 */
template <typename T>
typename std::enable_if<has_to_string<T>::value, std::string>::type
to_string(T o){
	return o.to_string();
}

/* to_string이 없지만, 기본형 타입 변환이 가능한 경우 */
template <typename T>
typename std::enable_if<(!has_to_string<T>::value) && default_convertible<T>::value, std::string>::type
to_string(T o){
	return defaults::cvt<T>::to_string(o);
}

/* to_string이 없고, 기본형 타입도 아닌 경우 */
template <typename T>
typename std::enable_if<(!has_to_string<T>::value) && (!default_convertible<T>::value), std::string>::type
to_string(T o){
	char tmp[128];
	sprintf_s(tmp, "#<%s %p>", typeid(T).name(), &o);
	return tmp;
}
