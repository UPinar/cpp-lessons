#include <iostream>

/*
                        ==================
                        | <tuple> module |
                        ==================
*/

/*
  #include <tuple>    // std::get(tuple)
  #include <string>

  enum { age, wage, name };

  int main()
  {
    std::tuple<int, double, std::string> t1{ 12, 4.5, "hello" };
    std::tuple t2{ 12, 4.5, "hello" };
    // Those 2 lines are equivalent.

    // ----------------------------------------------

    std::get<0>(t1) = 16;
    // returns a reference to 0'th index element in tx tuple

    std::cout << "std::get<0>(t1) = " 
              << std::get<0>(t1) << '\n'; 
    // output -> std::get<0>(t1) = 16

    // ----------------------------------------------

    std::get<2>(t1) += " world";

    std::cout << "std::get<2>(t1) = " 
              << std::get<2>(t1) << '\n';
    // output -> hello world

    // ----------------------------------------------

    std::get<3>(t1);    // compile time error
    // error: static assertion failed: 
    //  tuple index must be in range

    // ----------------------------------------------

    int idx = 2;
    std::get<idx>(t1);  // syntax error
    // error: the value of 'idx' 
    //  is not usable in a constant expression

    // NTTP has to be a constant expression

    // ----------------------------------------------

    const int c_idx = 1;
    std::get<c_idx>(t1);  // VALID

    std::cout << "std::get<c_idx>(t1) = " 
              << std::get<c_idx>(t1) << '\n';
    // output -> std::get<c_idx>(t1) = 4.5

    // ----------------------------------------------

    std::get<double>(t1) = 11.1;

    std::cout << "std::get<double>(t1) = " 
              << std::get<double>(t1) << '\n';
    // output -> std::get<double>(t1) = 11.1

    // ----------------------------------------------

    std::tuple t3{ 11, 22, 33.3 };

    std::get<int>(t3) = 17;   // ambiguity error
    //  error: static assertion failed: 
    //  the type T in std::get<T> must occur exactly once 
    //  in the tuple

    // ----------------------------------------------

    std::get<wage>(t1) = 99.9;

    std::cout << "std::get<wage>(t1) = " 
              << std::get<wage>(t1) << '\n';
    // output -> std::get<wage>(t1) = 99.9

    std::cout << "std::get<1>(t1) = " 
              << std::get<1>(t1) << '\n';
    // output -> std::get<1>(t1) = 99.9

    // ----------------------------------------------
  }
*/

/*
  #include <tuple>    // std::make_tuple
  #include <utility>  // std::forward

  template <typename ...Args>
  auto Make_Tuple(Args&&... args)
  {
    return std::tuple(std::forward<Args>(args)...);
  }

  int main()
  {
    using namespace std::string_literals;

    auto tp1 = std::make_tuple(11, 22.2 , "hello world"s);
    // tp's type is std::tuple<int, double, std::string>

    auto tp2 = Make_Tuple(33, 44.4, 99999L);
    // tp2's type is std::tuple<int, double, long>
  }
*/

/*
  #include <tuple>    // std::get(tuple)
  #include <string>

  auto foo()
  {
    return std::tuple{ 11, 22.2, std::string{ "hello universe" }};
  }

  int main()
  {
    std::tuple t1{ 22, 88.8, std::string{ "hello world"} };

    auto& [age, wage, str] = t1;
    age = 33;

    std::cout << "std::get<0>(t1) = " 
              << std::get<0>(t1) << '\n';
    // output -> std::get<0>(t1) = 33

    // -------------------------------------------------

    auto [x, y, z] = foo();

    z = "hello galaxy";
    std::cout << z << '\n';   // output -> hello galaxy

    // -------------------------------------------------
  }
*/

/*
  #include <tuple>    // std::get(tuple)
  #include <string>
  #include <vector>

  using Person_t = std::tuple<int, double, std::string>;

  int main()
  {
    std::vector<Person_t> per_vec{ 
      {10, 2.3, "hello"}, 
      {99, 6.3, "world"} };

    per_vec.emplace_back(18, 8.5, "izmir");

    // ----------------------------------------------

    for (auto per : per_vec) {
      std::cout << get<0>(per) << ' ';
      std::cout << get<1>(per) << ' ';
      std::cout << get<2>(per) << '\n';
    }
    // output ->
    //  10 2.3 hello
    //  99 6.3 world
    //  18 8.5 izmir

    // ----------------------------------------------

    // using structured binding
    for (const auto& [x, y, z] : per_vec) {
      std::cout << x << ' ';
      std::cout << y << ' ';
      std::cout << z << '\n';
    }
    // output ->
    //	10 2.3 hello
    //	99 6.3 world
    //	18 8.5 izmir

    // ----------------------------------------------
  }
*/

/*
  // comparison in std::tuple

  #include <tuple>
  #include <random>
  // std::mt19937, std::uniform_int_distribution
  #include <algorithm>    // std::sort
  #include <vector>

  using Tuple_t = std::tuple<int, int, int>;

  int main()
  {
    using namespace std;

    std::vector<Tuple_t> tx_vec;

    std::mt19937 eng;
    std::uniform_int_distribution dist1{ 0, 10 };
    std::uniform_int_distribution dist2{ 0, 20 };
    std::uniform_int_distribution dist3{ 0, 30 };

    for (int i = 0; i < 1000; ++i)
      tx_vec.emplace_back(dist1(eng), dist2(eng), dist3(eng));
    
    std::sort(tx_vec.begin(), tx_vec.end());

    for (const auto& [x, y, z] : tx_vec)
    {
      cout << x << ' ';
      cout << y << ' ';
      cout << z << '\n';
    }

    // output ->
    //  ...
    //  0 17 0
    //  0 17 8
    //  0 17 13
    //  0 17 17
    //  0 18 0
    //  0 18 4
    //  0 18 7
    //  0 19 1
    //  0 19 5
    //  0 19 8
    //  0 19 13
    //  0 19 17
    //  0 20 3
    //  0 20 9
    //  0 20 12
    //  0 20 21
    //  0 20 22
    //  1 0 17
    //  1 0 19
    //  1 1 3
    //  1 1 5
    //  1 1 6
    //  ...
  }
*/

/*
  #include <tuple>

  class Date {
  private:
    int m_year;
    int m_mon;
    int m_day;

  public:
    Date(int y, int m, int d) : 
      m_year{ y }, m_mon{ m }, m_day{ d } {}

    friend bool operator<(const Date& d1, const Date& d2)
    {
      return  std::tuple(d1.m_year, d1.m_mon, d1.m_day) < 
              std::tuple(d2.m_year, d2.m_mon, d2.m_day);
      // comparison goes from 1st, 2nd and 3rd element
    }
  };
*/

/*
  #include <tuple>    // std::tie
  #include <string>

  std::tuple<int, std::string, double> foo()
  {
    return { 99, "hello world", 15.3 };
  }

  int main()
  {
    int ival{};
    std::string str{};
    double dval{};

    // -------------------------------------------------

    auto t1 = std::tie(ival, str, dval);
    // t1's type is std::tuple<int&, std::string&, double&>

    std::tie(ival, str, dval) = foo();
    //  t1 = foo();
    // Those 2 lines are equivalent.

    std::cout << ival << '\n';    // output -> 99
    std::cout << str << '\n';     // output -> hello world
    std::cout << dval << '\n';    // output -> 15.3

    // -------------------------------------------------
  }
*/

/*
  #include <tuple>      // std::tie
  #include <utility>    // std::pair

  int main()
  {
    int ival_1 = 11;
    int ival_2 = 22;

    std::tie(ival_2, ival_1) = std::pair{ ival_1, ival_2 };

    std::cout << "ival_1 = " << ival_1 << '\n';
    // output -> x = 22
    std::cout << "ival_2 = " << ival_2 << '\n';
    // output -> y = 11
  }
*/

/*
  #include <tuple>    // std::ignore, std::tie
  #include <string>

  std::tuple<int, double, std::string> foo();

  int main()
  {
    int ival{};
    double dval{};
    std::string str{};

    // ---------------------------------------------

    std::tie(std::ignore, dval, str) = foo();
    // std::ignore is being used to ignore foo function's 
    // return type tuple's first element.

    // ---------------------------------------------

    auto [_, dval2, str2] = foo();
    // placeholder '_' is being used to ignore foo function's
    // std::ignore can not be used in structured binding.

    // ---------------------------------------------
  }
*/

/*
  #include <tuple>    // std::tie

  int main()
  {
    int x = 11, y = 22, z = 33;

    //  int temp = x;
    //  x = y;
    //  y = z;
    //  z = temp;
    // instead of this code std::tie can be used.

    std::tie(x, y, z) = std::tuple{ y, z, x };

    std::cout << "x = " << x << '\n';   // output -> x = 22
    std::cout << "y = " << y << '\n';   // output -> y = 33
    std::cout << "z = " << z << '\n';   // output -> z = 11
  }
*/

/*
                          --------------
                          | std::apply |
                          --------------
*/

/*
  #include <tuple>    // std::apply, std::get(tuple)

  void print(int x, int y, int z)
  {
    std::cout << "x = " << x << ' ' 
              << "y = " << y << ' '
              << "z = " << z << '\n';
  }

  void double_all(int& x, int& y, int& z)
  {
    x *= 2;
    y *= 2;
    z *= 2;
  }

  int main()
  {
    std::tuple tx{ 11, 22, 33 };

    // ---------------------------------------------

    std::apply(print, tx);
    // output -> x = 11 y = 22 z = 33

    print(std::get<0>(tx), std::get<1>(tx), std::get<2>(tx));
    // output -> x = 11 y = 22 z = 33

    // Those 2 lines are equivalent.

    // ---------------------------------------------

    std::apply(double_all, tx);
    std::apply(print, tx);
    // output -> x = 22 y = 44 z = 66

    // ---------------------------------------------
  }
*/

/*
  #include <tuple>    // std::apply

  template <typename ...Ts>
  std::ostream& operator<<( std::ostream& os, 
                            const std::tuple<Ts...>& tx)
  {
    std::apply
    (
      [&os](const Ts&... tuple_args)
      {
        std::size_t N{ 0 };
        
        os << '[';

        ((os  << tuple_args 
              << (++N != sizeof...(Ts) ? ", " : "")), ...);
        // binary fold expression on comma 

        os << ']';
      }, tx
    );
    return os;
  }

  int main()
  {
    std::cout << std::tuple{ 43, 5.6, "hello", 'A' } << '\n';
    // output -> [43, 5.6, hello, A]

    std::cout << std::tuple{ 11, 5.5, "hello world" } << '\n';
    // output -> [11, 5.5, hello world]
  }
*/

/*
  // std::tuple_size and std::tuple_element are meta functions.

  #include <tuple>    // std::tuple_size, std::tuple_element
  #include <array>

  using tp_type1 = std::tuple<int, double, long>;
  using tp_type2 = std::tuple<int, double, long, float>;

  using arr_type = std::array<double, 5>;

  int main()
  {
    // --------------------------------------------------

    constexpr auto val1 = std::tuple_size<tp_type1>::value;
    // val1 -> 3
    constexpr auto val2 = std::tuple_size_v<tp_type2>;
    // val2 -> 4

    // "std::tuple_size_v" is a variable template

    // --------------------------------------------------

    constexpr auto val3 = std::tuple_size_v<arr_type>;
    // val3 -> 5

    // std::tuple_size can be used with (tuple interface) types
    //  - std::pair
    //  - std::array
    //  - std::tuple

    // --------------------------------------------------

    std::tuple_element<0, tp_type1>::type ival{};   // int 
    std::tuple_element_t<1, tp_type2> dval{};       // double
    // "std::tuple_element_t" is an alias template

    std::tuple_element_t<3, tp_type2> fval{};       // float

    std::tuple_element<2, arr_type>::type dval2{};   // double

    // --------------------------------------------------
  }
*/

/*
                ------------------------------
                | structured binding (C++17) |
                ------------------------------
*/

/*
  - generally used with std::tuple, std::pair, std::array
    (tuple-like classes)
*/

/*
  int main()
  {
    int i_arr[] = { 11, 22, 33 };

    auto [x, y, z] = i_arr;

    std::cout << "x = " << x << '\n'; // output -> x = 11
    std::cout << "y = " << y << '\n'; // output -> y = 22
    std::cout << "z = " << z << '\n'; // output -> z = 33

    x += 2;   
    // x is NOT a reference to i_arr[0] becuase of `auto`
    std::cout << i_arr[0] << '\n';    // output -> 11

    // ---------------------------------------------------

    auto& [k, l, m] = i_arr;

    ++k;  
    // k is a reference to i_arr[0] because of `auto&`
    std::cout << i_arr[0] << '\n';    // output -> 12

    // ---------------------------------------------------

    i_arr[0] = i_arr[1] = i_arr[2] = 0;

    std::cout << "x = " << x << '\n'; // output -> x = 11
    std::cout << "y = " << y << '\n'; // output -> y = 22
    std::cout << "z = " << z << '\n'; // output -> z = 33

    std::cout << "k = " << k << '\n'; // output -> k = 0
    std::cout << "l = " << l << '\n'; // output -> l = 0
    std::cout << "m = " << m << '\n'; // output -> m = 0
    
    // ---------------------------------------------------
  }
*/

/*
  // how structured binding is working

  #include <string>

  struct Person {
    std::string m_name{ "world" };
    std::string m_surname{ "universe" };
    int m_no = 346283;
  };

  Person foo()
  {
    Person person1;
    person1.m_name += "_galaxy";
    return person1;
  }

  int main()
  {
    auto [name, surname, no] = foo();

    // auto compiler_gen_object = foo();
    // std::string name         = compiler_gen_object.m_name;
    // std::string surname      = compiler_gen_object.m_surname;
    // int no                   = compiler_gen_object.m_no;

    std::cout << "name = " << name << '\n';
    std::cout << "surname = " << surname << '\n';
    std::cout << "no = " << no << '\n';
    // output ->
    //  name = world_galaxy
    //  surname = universe
    //  no = 346283
  }
*/

/*
  #include <string>

  struct Mystruct {
    int m_a, m_b;
    std::string m_str;
  };

  Mystruct foo()
  {
    return { 11, 22, "hello world" };
  }

  int main()
  {
    auto [x, y, str] = foo();

    std::cout << "x = " << x << '\n'; 
    // output -> x = 11
    std::cout << "y = " << y << '\n'; 
    // output -> y = 22
    std::cout << "str = " << str << '\n'; 
    // output -> str = hello world
  }
*/

/*
  #include <string>

  class Myclass {
  private:
    int m_a, m_b;
    std::string m_str;
    friend void func();   // friend function
    
  public:
    Myclass(int x, int y, std::string s) 
      : m_a(x), m_b(y), m_str(s) {}
  };

  Myclass foo()
  {
    return { 11, 22, "hello world" };
  }

  void func()
  {
    auto [a, b, str] = foo();   // VALID since C++17
  }

  int main()
  {
    auto [a, b, name] = foo();    // syntax error
    // error: cannot decompose inaccessible member 
    // 'Myclass::m_a' of 'Myclass'
  }
*/

/*
  #include <string>

  struct Mystruct {
    int m_a, m_b;
    std::string m_str;
  };

  Mystruct foo()
  {
    return { 11, 22, "hello world" };
  }

  int main()
  {
    auto [a, b, str] = foo();

    auto fn = [=](){ return a + b; };
    // capturing structure binding objects 
    // in lambda expressions is VALID since C++20
  }
*/

/*
  // std::array have a tuple interface which have
  //  - std::tuple_element
  //  - std::tuple_size
  //  - std::get(array) function template

  #include <array>
  // std::tuple_element<std::array>, std::tuple_size<std::array>
  #include <tuple>
  // std::tuple_size<std::tuple>, std::tuple_element<std::tuple>
  #include <utility>  
  // std::pair, std::tuple_element<std::pair>
  // std::tuple_size<std::pair>

  int main()
  {

    std::array<int, 3> i_arr3{ 11, 22, 33 };
    auto [x, y, z] = i_arr3;

    std::get<0>(i_arr3);

    // ------------------------------------------------

    std::tuple_element<1, decltype(i_arr3)>::type;  // int
    std::tuple_element_t<1, decltype(i_arr3)>;      // int
    // Those 2 lines are equivalent.

    // ------------------------------------------------

    using tp_type = std::tuple<int, double, long, long long>;
    std::tuple_element_t<2, tp_type>; // long

    // ------------------------------------------------

    using p_type = std::pair<int, double>;

    std::tuple_size<decltype(i_arr3)>::value;   // 3
    std::tuple_size<tp_type>::value;            // 4
    std::tuple_size_v<p_type>;                  // 2

    // ------------------------------------------------
  }
*/

/*
  // creating a tuple-like class

  #include <string>
  #include <tuple>    // std::tuple_element, std::tuple_size
  #include <utility>  // std::move
  #include <cstddef>  // std::size_t

  class Person {
  private:
    std::string m_name;
    std::string m_surname;

  public:
    Person(std::string name, std::string surname) :
      m_name{ std::move(name) }, 
      m_surname{ std::move(surname) } 
    {}

    std::string get_name() const { return m_name; }
    std::string get_surname() const { return m_surname; }
  };

  template <>
  struct std::tuple_element<0, Person> {
    using type = std::string;
  };

  template <>
  struct std::tuple_element<1, Person> {
    using type = std::string;
  };

  template <>
  struct std::tuple_size<Person> {
    constexpr static std::size_t value = 2;
  };

  template <std::size_t N>
  auto get(const Person& p)
  {
    if constexpr (N == 0)
      return p.get_name();
    else if constexpr (N == 1)
      return p.get_surname();
  }

  int main()
  {
    Person per{ "hello", "world" };
    auto [x, y] = per;

    std::cout << "x = " << x << '\n';   // output -> x = Hello
    std::cout << "y = " << y << '\n';   // output -> y = World
  }
*/

/*
  #include <type_traits>  // std::is_same

  struct Mystruct {
    int m_iarr[5]{};
    double m_darr[10]{};
  };

  int main()
  {
    Mystruct ms;

    auto [i_arr, d_arr] = ms;

    std::cout << "sizeof(i_arr) = " << sizeof(i_arr) << '\n';
    // output -> sizeof(i_arr) = 20
    std::cout << "sizeof(d_arr) = " << sizeof(d_arr) << '\n';
    // output -> sizeof(d_arr) = 80

    // -----------------------------------------------------

    // array will not decay to pointer

    constexpr auto b1 = std::is_same_v<decltype(i_arr), int[5]>;
    // b1 -> true

    constexpr bool b2 = std::is_same_v<decltype(i_arr), int*>;
    // b2 -> false

    // -----------------------------------------------------
  }
*/

/*
  struct Mystruct {
    int m_a{}, m_b{}, m_c{};

    Mystruct() 
    {
      std::cout << "Mystruct()\n";
    }
    ~Mystruct()
    {
      std::cout << "~Mystruct()\n";
    }
    Mystruct(const Mystruct&) 
    {
      std::cout << "Mystruct(const Mystruct&)\n";
    }
  };

  int main()
  {
    Mystruct mx;

    auto [x, y, z] = mx;

    // compiler will copy Mystruct object 
    // and will use its data members in structured binding
    // as structured binding objects.
  }
  // output -> 
  //  Mystruct()
  //  Mystruct(const Mystruct&)
  //  ~Mystruct()
  //  ~Mystruct()
*/


/*
  struct Mystruct {
    int m_iarr[5]{};
    double m_darr[10]{};
  };

  int main()
  {
    Mystruct mx;

    auto [arr1, arr2]{ mx };
    // m_iarr and m_darr will be copied 
    // when Mystruct object is copied.
    // arr1 and arr2 are data members of the copied object.
  }
*/

/*
  struct Mystruct {
    int m_a{}, m_b{};
  };

  int main()
  {
    Mystruct mx;

    // --------------------------------------------------

    auto&& [x, y] = mx;
    // && - & -> &      (reference collapsing)

    // --------------------------------------------------

    auto&& [a, b] = Mystruct{};
    // && - && -> &&    (reference collapsing)

    // --------------------------------------------------
  }
*/

/*
  struct Mystruct {
    int m_a{};
    char m_str[20]{ "hello world" };
  };

  int main()
  {
    Mystruct ms;

    auto [ival, str] = ms;
    // str's type is char[20]  (no array decay)

    auto copied_str = str;
    // "copied_str"'s type is char*
    // char[20] will decay to char* (array decay)
  }
*/