#include <iostream>

/*
                =================================
                | std::string_view class (C++17)|
                =================================
*/

/*
  #include <string>
  #include <string_view>

  // `std::string_view` class does have
  // all of the const member functions of std::string class
  // in its interface.

  class String_View_Impl1 {
  private:
    const char* mp_start;
    std::size_t m_strlen;
  };

  class String_View_Impl2 {
  private:
    const char* mp_start;
    const char* mp_end;
  };

  void func(const std::string& ref_str) 
  {}

  void foo(std::string_view sv) 
  {}
  // only pointer member variable of std::string_view object
  // will be copied.

  int main()
  {
    std::string str{ "hello world" };

    func(str);  
    // reference semantics -> no copying

    func("hello world");
    // "hello world" is a string literal
    // that will be copied to the memory allocated in heap.

    // temp std::string object will be constructed,
    // with the string literal "hello world" 
    // to bind the reference parameter of the "func" function
  }
*/

/*
  #include <string>
  #include <string_view>

  void func(const std::string& str)
  {
    auto new_str = str.substr(10, 4500);
    // "func" is using the string for reading purpose
    // but "substr" member function will copy the substring
    // to a new std::string object.
    // It is very expensive operation.
  }

  void func_efficient(const std::string& str)
  {
    std::string_view sv = str;
    // "sv" is now pointing to the same memory location
    // with the "str" object.

    auto new_sv = sv.substr(10, 4500);
    // "new_sv" is a string_view object
    // that is pointing to the same memory location
    // with the "str" object's (10, 4500) substring.
  }
*/

/*
  #include <cstddef>      // std::size_t
  #include <string_view>

  int main()
  {
    std::cout << "sizeof(char*) = " 
              << sizeof(char*) << '\n';
    // output -> sizeof(char*) = 8

    std::cout << "sizeof(std::size_t) = " 
              << sizeof(std::size_t) << '\n';
    // output -> sizeof(std::size_t) = 8
    
    std::cout << "sizeof(std::string_view) = " 
              << sizeof(std::string_view) << '\n';
    // output -> sizeof(std::string_view) = 16
  }
*/

/*
  #include <string>
  #include <string_view>
  #include <cstddef>    // std::size_t

  int main()
  {
    std::cout << std::boolalpha;

    // --------------------------------------------

    auto p_str = new std::string{ "hello world" };
    std::string_view sv(*p_str);

    // both "p_str" and "sv" 
    // are pointing to the same memory location

    // --------------------------------------------

    std::cout << "|" << sv << "|\n";  
    // output -> |hello world|
    std::cout << sv.front() << '\n';  
    // output -> h
    std::cout << sv.back() << '\n';   
    // output -> d

    // --------------------------------------------

    std::cout << "sv.length() = " << sv.length() << '\n';
    // output -> sv.length() = 11
    std::cout << "sv.size() = " << sv.size() << '\n';
    // output -> sv.size() = 11

    for (std::size_t idx{}; idx != sv.size(); ++idx)
      std::cout << sv[idx] << " ";
    // output -> h e l l o   w o r l d

    std::cout << '\n';

    // --------------------------------------------

    delete p_str;
    // because of the delete(free) operation
    // "sv" object's pointer that is pointing the string literal
    // will become a dangling pointer.

    std::cout << "|" << sv << "|\n";  // undefined behaviour(UB)
    // trying to use the dangling pointer

    // --------------------------------------------
  }
*/

/*
  #include <string>
  #include <string_view>

  int main()
  {
    // --------------------------------------------

    std::string str{ "hello world" };
    std::string_view sv = str;

    std::cout << "|" << sv << "|\n";
    // output -> |hello world|

    // --------------------------------------------

    str += ", galaxy, universe.";
    // reallocation can be happen in this operation
    // if the current capacity of the "str" object 
    // is not enough to hold the new string literal
    // that will be added.

    std::cout << "|" << str << "|\n";
    // output -> |hello world, galaxy, universe.|

    std::cout << "|" << sv << "|\n";  // undefined behaviour(UB)
    // if reallocation happened
    // because of "sv" object is still pointing 
    // to the old memory location, dereferencing it
    // will cause undefined behaviour(UB)

    // --------------------------------------------
  }
*/

/*
  #include <string>
  #include <string_view>

  std::string get_str()
  {
    return "hello world";
    // temp std::string object will be constructed
    // for the return value of the function.
    // When the function's scope ends
    // temp object's destructor will be called.
  }

  int main()
  {
    // --------------------------------------------

    const auto& r = get_str();   // VALID
    // temp string object's(constructed in "get_str" function) 
    // life will extend.

    // const LValue reference can bind to PR value expression

    // --------------------------------------------

    std::string& str_ref = get_str();   // syntax error
    // error: cannot bind non-const lvalue reference of type 
    // 'std::string&' to an rvalue of type 'std::string'

    // LValue reference can not bind to PR value expression

    // --------------------------------------------

    std::string_view sv = get_str();
    // string_view object's pointer(s) 
    // is pointing to temp std::string object
    // which will be destroyed at the end of the function.
    // so string_view object's pointer(s) will become dangling.

    std::cout << sv << '\n';  // undefined behaviour(UB)

    // --------------------------------------------
  }
*/

/*
  #include <string_view>

  int main()
  {
    // --------------------------------------------

    char str[] = "hello world";
    // "str" is a C-style array(NTBS)

    std::cout << '|' << str << "|\n"; 
    // output -> |hello world|

    // --------------------------------------------

    std::string_view sv(str, 5);

    std::cout << sv << '\n';            // output -> hello
    std::cout << sv.length() << '\n';   // output -> 5
    std::cout << sv.front() << '\n';    // output -> h
    std::cout << sv.back() << '\n';     // output -> o

    // --------------------------------------------

    std::cout << sv.data() << '\n'; 
    // output -> hello world

    // even if "sv"'s length is 5,
    // "data" member function will print the whole string
    // until it finds the NULL('\0') character.
    // which is the end of the string.
    // 'h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0')

    // --------------------------------------------
  }
*/

/*
  #include <string_view>
  #include <vector>

  int main()
  {
    std::vector<char> cvec{ 'h', 'e', 'l', 'l', 'o' };
    // there is no NULL character in "cvec"

    std::string_view sv(cvec.data(), 5);
    std::cout << "|" << sv << "|\n";  // output -> |hello|

    std::cout << "|" << sv.data() << "|\n"; 
    // undefined behaviour(UB)
    // "data" member function will print the whole string
    // until it finds the NULL('\0') character.
    // There is no NULL character so it will cause UB.
  }
*/

/*
  #include <string_view>

  int main()
  {
    std::cout << std::boolalpha;

    std::string_view sv;

    std::cout << "sv.empty() = " << sv.empty() << '\n';  
    // output -> is empty? true
    std::cout << sv.length() << '\n'; 
    // output -> 0
    std::cout << sv.size() << '\n';
    // output -> 0
    std::cout << (sv.data() == nullptr) << '\n';
    // output -> true
  }
*/

/*
  #include <string>
  #include <array>    // std::size
  #include <string_view>

  int main()
  {
    char c_arr[] = "hello world";
    std::string str{ "hello galaxy" };
    std::array<char, 5> arr{ 'u', 'n', 'i', 't', 'y' };

    // --------------------------------------------

    std::string_view sv1;

    std::cout << "sv1.length() = " << sv1.length() 
              << " sv1 = |" << sv1 << "|\n";
    // output -> sv1.length() = 0 sv1 = ||

    // --------------------------------------------

    std::string_view sv2 = "hello universe";

    std::cout << "sv2.length() = " << sv2.length() 
              << " sv2 = |" << sv2 << "|\n";
    // output -> sv2.length() = 14 sv2 = |hello universe|

    // --------------------------------------------

    std::string_view sv3 = { c_arr, 5 };

    std::cout << "sv3.length() = " << sv3.length() 
              << " sv3 = |" << sv3 << "|\n";
    // output -> sv3.length() = 5 sv3 = |hello|

    // --------------------------------------------

    std::string_view sv4{ str };

    std::cout << "sv4.length() = " << sv4.length()
              << " sv4 = |" << sv4 << "|\n";
    // output -> sv4.length() = 12 sv4 = |hello galaxy|

    // --------------------------------------------

    std::string_view sv5{ str.data() + 6, 6};

    std::cout << "sv5.length() = " << sv5.length()
              << " sv5 = |" << sv5 << "|\n";
    // output -> sv5.length() = 6 sv5 = |galaxy|

    // --------------------------------------------

    std::string_view sv6{ arr.data(), std::size(arr)};

    std::cout << "sv6.length() = " << sv6.length()
              << " sv6 = |" << sv6 << "|\n";
    // output -> sv6.length() = 5 sv6 = |unity|

    // --------------------------------------------

    std::string_view sv7{ c_arr + 6, c_arr + 9 };

    std::cout << "sv7.length() = " << sv7.length() 
              << " sv7 = |" << sv7 << "|\n";
    // output -> sv7.length() = 3 sv7 = |wor|

    // --------------------------------------------

    std::string_view sv8{ str.begin() + 6, str.end()};

    std::cout << "sv8.length() = " << sv8.length() 
              << " sv8 = |" << sv8 << "|\n";
    // output -> sv8.length() = 6 sv8 = |galaxy|
    // range constructor C++20

    // --------------------------------------------
  }
*/

/*
  #include <string>
  #include <string_view>

  void func(std::string)
  {}

  int main()
  {
    std::string str1{ "istanbul" };
    std::string str2{ "izmir" };
    std::string_view sv1{ "world" };

    // --------------------------------------------

    // std::string str3 = sv1;  // syntax error
    // error: conversion from 'std::string_view' to 
    // non-scalar type 'std::string' requested

    // --------------------------------------------

    std::string str4{ sv1 };   // VALID
    // explicit std::string constructor that have 
    // a std::string_view paramater

    // --------------------------------------------

    using basic_str_view_t = 
      std::basic_string_view<char, std::char_traits<char>>;

    sv1 = str2;
    sv1 = str2.operator basic_str_view_t();
    // Those 2 lines are equivalent.

    // function that converts std::string object to 
    // std::string_view object

    // --------------------------------------------

    using namespace std::string_view_literals;

    auto sv2 = "hello world"sv;

    func(sv2);  // syntax error
    // error: could not convert 'sv2' from 
    // 'std::basic_string_view<char>' to 'std::string' 

    func(std::string{ sv2 });   // VALID

    // --------------------------------------------
  }
*/

/*
  #include <string_view>
  #include <string>

  std::string func_1(std::string_view sv)
  {
    return sv;  // syntax error
    // error: could not convert 'sv' 
    // from 'std::string_view' to 'std::string'

    // std::string class has an EXPLICIT constructor
    // that takes a std::string_view object as a parameter.
  }

  std::string func_2(std::string_view sv)
  {
    return std::string{ sv };  // VALID
    // calling std::string's EXPLICIT constructor
  }

  std::string func_3(std::string_view sv)
  {
    return sv.data();  // VALID
    // "data" member function returns a const char* 
    // which can be passed to std::string's 
    // NON-EXPLICIT constructor
  }

  void foo(std::string)
  {}

  int main()
  {
    std::string_view sv("hello world");

    // --------------------------------------------

    foo(sv);                      // syntax error
    std::string str1 = sv;        // syntax error

    // --------------------------------------------

    std::string str2{ sv };       // VALID 
    // explicit std::string(std::string_view) constructor

    // --------------------------------------------

    std::string str3 = sv.data(); // VALID 
    // std::string(const char*) constructor

    // --------------------------------------------

    foo(std::string{ sv });       // VALID
    // explicit std::string(std::string_view) constructor

    // --------------------------------------------

    foo(sv.data());               // VALID
    // std::string(const char*) constructor

    // --------------------------------------------
  }
*/

/*
  #include <string_view>

  int main()
  {
    char c_arr[] = "hello world";

    std::string_view sv{ c_arr };   
    // char[12] will decay to char* implicitly
    // and the pointer will be passed to the constructor

    c_arr[1] = 'a';
    std::cout << "|" << sv << "|\n";
    // output -> |hallo world|
  }
*/

/*
  #include <string>
  #include <string_view>

  int main()
  {
    std::string str{ "hello world" };
    std::string_view sv{ str };

    std::cout << "[" << sv << "]\n";
    // output -> [hello world]

    // --------------------------------------------

    str.front() = '_';
    str.back() = '_';

    std::cout << "[" << sv << "]\n";    // VALID
    // output -> [_ello worl_]

    // because of "str" object's size is not changed
    // "sv" object's pointer is still pointing 
    // to the valid memory location.

    // --------------------------------------------

    str.append(500, 'A');  
    // reallocation can be happen

    std::cout << "[" << sv << "]\n";  // undefined behaviour(UB)

    // because of str object's size is changed
    // which can cause reallocation
    // and "sv" object's pointer is still pointing
    // to the old memory location.
    // pointer is now pointing to the invalid memory location.
    // dereferencing it will cause UB.

    // --------------------------------------------
  }
*/

/*
  #include <string_view>
  #include <string>       // std::begin, std::end
  #include <algorithm>    // std::reverse

  std::string_view get_reverse(std::string str)
  {
    std::reverse(std::begin(str), std::end(str));
    return str;
  }

  // returning a std::string_view object
  // that is pointing to a temporary std::string object "str"
  // that will be destroyed at the end of the function.
  // so when the function's scope ends
  // std::string_view object's pointer(s) will become dangling.

  int main()
  {
    auto sv = get_reverse("hello world"); 

    std::cout << sv << '\n';  // undefined behaviour(UB)
    // trying to use the dangling pointer
  }
*/

/*
  // "remove_prefix" member function changes
  //  the data member start pointer of the std::string_view object

  // "remove_suffix" member function changes 
  // the data member end pointer or data member size 
  // of the std::string_view object

  #include <string_view>

  int main()
  {
    // --------------------------------------------

    std::string_view sv("hello world");

    std::cout << "sv.length() = " << sv.length() 
              << ", sv = |" << sv << "|\n";
    // output -> sv.length() = 11, sv = |hello world|

    // --------------------------------------------

    sv.remove_prefix(6);

    std::cout << "sv.length() = " << sv.length() 
              << ", sv = |" << sv << "|\n";
    // output -> sv.length() = 5, sv = |world|

    // --------------------------------------------

    sv.remove_suffix(2);

    std::cout << "sv.length() = " << sv.length() 
              << ", sv = |" << sv << "|\n";
    // output -> sv.length() = 3, sv = |wor|

    // --------------------------------------------
  }
*/

/*
  #include <string_view>
  #include <exception>    // std::exception

  int main()
  {
    std::string_view sv("hello world");

    auto ch1 = sv[20];  // no exception will be thrown

    try {
      auto ch2 = sv.at(20);  // exception will be thrown
    }
    catch (const std::exception& ex)
    {
      std::cout << "exception caught : " << ex.what() << '\n';
    }
    // output -> 
    // exception caught : basic_string_view::at: __pos 
    // (which is 20) >= this->size() (which is 11)
  }
*/

/*
  #include <string_view>
  #include <string>
  #include <algorithm>  // std::min

  int main()
  {
    std::string str{ "         ________________" };
    std::string_view sv{ str };

    sv.remove_prefix(std::min(sv.find_first_not_of(" "), 
                              sv.size()));

    // if the string contains only space characters
    // "find_first_not_of" member function will return 
    // std::string::npos(biggest possible value for std::size_t)
    // so 2nd argument "sv.size()" will be chosen by "std::min"
    // else "find_first_not_of" will get chosen
    // because it must be smaller than "sv.size()"

    std::cout << "|" << str << "|\n";
    // output -> |         ________________|

    std::cout << "|" << sv << "|\n";
    // output -> |________________|
  }
*/

/*
  #include <string_view>
  #include <cstring>    // std::strlen

  int main()
  {
    // --------------------------------------------

    std::string_view sv{ "programming" };

    std::cout << "sv = '" << sv 
              << "', std::strlen(sv.data()) = " 
              << std::strlen(sv.data()) << '\n';
    // output -> sv = 'programming', std::strlen(sv.data()) = 11

    // --------------------------------------------

    sv.remove_prefix(3);
    sv.remove_suffix(4);


    std::cout << "sv = '" << sv 
              << "', std::strlen(sv.data()) = " 
              << std::strlen(sv.data()) << '\n';
     // output -> sv = 'gram', std::strlen(sv.data()) = 8

    // "std::strlen" function will check the NULL character
    // when counting the length of the string.

    // becuse of "sv.remove_prefix(3)" "sv" object's
    // data member start pointer is now pointing 
    // to the 4th character('g) of the string literal.

    // Even "sv"'s size = 4, 
    // NULL character is still at the end of the string literal.
    // so "std::strlen" function will count the length
    // of the string until it finds the NULL character.

    // --------------------------------------------

    std::cout << "sv.data() = " << sv.data() << '\n';
    // output -> sv.data() = gramming

    // "data" member function will print the whole string
    // until it finds the NULL('\0') character.

    std::cout << "sv = |" << sv << "|\n";
    // output -> sv = |gram|

    // --------------------------------------------
  }
*/

/*
  #include <string_view>

  int main()
  {
    // --------------------------------------------

    char c_arr[] = { 'a', 'b', 'c', 'd', '\0', '\0' , '\0' };

    std::cout << "c_arr = |" << c_arr 
              << "|, sizeof c_arr = " << sizeof c_arr << '\n';
    // output -> c_arr = |abcd|, sizeof c_arr = 7

    // --------------------------------------------

    std::string_view sv(c_arr, sizeof c_arr);

    auto trim_idx = sv.find('\0');
    std::cout << "trim_idx = " << trim_idx << '\n';
    // output -> trim_idx = 4

    if (trim_idx != sv.npos)
      sv.remove_suffix(sv.size() - trim_idx);

    std::cout << "sv = |" << sv 
              << "|, sv.size() = " << sv.size();
    // output -> sv = |abcd|, sv.size() = 4

    // --------------------------------------------
  }
*/

/*
  #include <string_view>

  int main()
  {
    std::string_view sv{ "hello_world" };

    sv.remove_prefix(5);
    sv.remove_suffix(8);

    std::cout << "(" << sv << ")";  // undefined behaviour(UB)
  }
*/

/*
  // "starts_with" and "ends_with" member functions
  // since C++20

  #include <string_view>

  int main()
  {
    std::cout << std::boolalpha;

    std::string_view sv{ "hello world we are live again" };

    std::cout << sv.length() << '\n';
    // output -> 29

    // --------------------------------------------

    std::cout << sv.substr(0, sv.find(' ')) << '\n';
    // output -> hello

    // --------------------------------------------

    std::cout << (sv == "hello galaxy") << '\n';
    // output -> false

    // --------------------------------------------

    std::cout << sv.starts_with("hello") << '\n';
    // output -> true
    std::cout << sv.ends_with("galaxy") << '\n';
    // output -> false

    // --------------------------------------------

    std::cout << '|' << sv << "|";
    // output -> |hello world we are live again|

    // --------------------------------------------
  }
*/