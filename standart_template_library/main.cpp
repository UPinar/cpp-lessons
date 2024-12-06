#include <iostream>

/*
                ===================================
                | Standart Template Library (STL) |
                ===================================
*/

/*
                  <---- check stl_general.png ---->
*/

/*
          ------------------------------------------------
          | standart function objects(standart functors) |
          ------------------------------------------------
*/

/*
  #include <functional>  // std::less

  // mental model for std::sort algorithm
  template <typename RanIt, typename BinaryPred>
  void Sort(RanIt iter_beg, RanIt iter_end, BinaryPred fn)
  {
    while (iter_beg != iter_end) 
      fn(*iter_beg, *(iter_beg + 1));

    // if std::less sent as a callable(BinaryPred)
    // it will use less comparison

    // if std::greater sent as a callable(BinaryPred)
    // it will use greater comparison
  }

  // mental model for std::less function object implementation
  template <typename T>
  struct Less {
    bool operator()(const T& t1, const T& t2) const
    {
      return t1 < t2;
    }
  };

  int main()
  {
    std::cout << std::boolalpha;

    int x = 11, y = 22;

    // ----------------------------------------------

    std::cout << (x < y) << '\n'; 
    // output -> true

    // ----------------------------------------------

    std::cout << Less<int>{}(x, y) << '\n';
    // output -> true
    // "Less<int>{}" is a temporary object

    // ----------------------------------------------

    Less<int> less_1;
    std::cout << less_1(x, y) << '\n';
    // output -> true

    // ----------------------------------------------
  }
*/

/*
  #include <functional> 
  // std::less, std::greater, std::plus, std::multiplies

  // std::less function object implementation
  template <typename T>
  struct Less {
    bool operator()(const T& t1, const T& t2) const
    {
      return t1 < t2;
    }
  };

  // std::greater function object implementation
  template <typename T>
  struct Greater {
    bool operator()(const T& t1, const T& t2) const
    {
      return t1 > t2;
    }
  };

  // std::plus function object implementation
  template <typename T>
  struct Plus {
    T operator()(const T& t1, const T& t2) const
    {
      return t1 + t2;
    }
  };

  // std::multiplies function object implementation
  template <typename T>
  struct Multiplies {
    T operator()(const T& t1, const T& t2) const
    {
      return t1 * t2;
    }
  };
*/

/*
  #include <functional>
  // std::less, std::greater, std::greater_equal,
  // std::plus, std::multiplies
  #include <vector>
  #include <string>
  #include <algorithm>  // std::sort

  int main()
  {
    std::cout << std::boolalpha;

    // -------------------------------------------------

    std::cout << std::less<int>()(11, 22) << '\n';           
    // output -> true
    std::cout << std::greater<int>()(11, 22) << '\n';
    // output -> false
    std::cout << std::greater_equal<int>()(11, 22) << '\n';
    // output -> false
    std::cout << std::plus<int>()(11, 22) << '\n';
    // output -> 33
    std::cout << std::multiplies<int>()(11, 22) << '\n';
    // output -> 242

    // -------------------------------------------------

    std::vector<std::string> svec{ 
      "yes", "no", "in", "out", "up", "down", 
      "war", "peace", "black", "white" };

    std::sort(svec.begin(), svec.end());
    std::sort(svec.begin(), svec.end(), std::less<std::string>{});
    // Those 2 lines are equivalent.
    // default binary predicate argument is std::less

    for (auto elem : svec)
      std::cout << elem << ' ';
    // output -> black down in no out peace up war white yes

    std::cout << '\n';
    
    // -------------------------------------------------

    sort(svec.begin(), svec.end(), std::greater<std::string>{});

    for (auto elem : svec)
      std::cout << elem << ' ';
    // output -> yes white war up peace out no in down black
    
    // -------------------------------------------------
  }
*/

/*
  #include <algorithm>  // std::max_element, std::sort
  #include <iterator>   // std::distance
  #include <vector>
  #include <functional> // std::greater

  // function implementation
  bool less_abs(int a, int b)
  {
    return std::abs(a) < std::abs(b);
  }

  // function object implementation
  struct Greater_Abs {
    bool operator()(int a, int b) const
    {
      return std::abs(a) > std::abs(b);
    }
  };

  int main()
  {
    using namespace std;

    // --------------------------------------------------------

    vector<int> ivec{ 12, 5, 84, 293, 1092, 283, 63, 28, 34 };

    auto iter = std::max_element(ivec.begin(), ivec.end());
    // default std::less function object(functor class)
    // used as a binary predicate

    cout  << "max element = " << *iter 
          << ", index = " << std::distance(ivec.begin(), iter) 
          << '\n';
    // output -> max element = 1092, index = 4

    // --------------------------------------------------------

    ivec = { 12, -1435, -84, 293, 1092, -283, 63, 28, -34 };
    iter = max_element(ivec.begin(), ivec.end(), less_abs);
    // "less_abs" function used as a binary predicate

    cout  << "max = " << *iter 
          << ", index = " << std::distance(ivec.begin(), iter) 
          << '\n';
    // output -> max = -1435, index = 1

    // --------------------------------------------------------

    std::sort(ivec.begin(), ivec.end(), std::greater{});
    // "std::greater" function object(functor class) 
    // used as a binary predicate

    for (auto elem : ivec)
      cout << elem << ' ';
    // output -> 1092 293 63 28 12 -34 -84 -283 -1435
    
    std::cout << '\n';

    // ---------------------------------------------------------- 

    std::sort(ivec.begin(), ivec.end(), less_abs);
    // "less_abs" function used as a binary predicate

    for (auto elem : ivec)
      cout << elem << ' ';
    // output -> 12 28 -34 63 -84 -283 293 1092 -1435

    std::cout << '\n';

    // ---------------------------------------------------------- 

    std::sort(ivec.begin(), ivec.end(), Greater_Abs{});
    // "Greater_Abs" function object(functor class)
    // used as a binary predicate

    for (auto elem : ivec)
      cout << elem << ' ';
    // output -> -1435 1092 293 -283 -84 63 -34 28 12
    std::cout << '\n';

    // ---------------------------------------------------------- 

    std::sort(ivec.begin(), ivec.end(), [](int a, int b) {
        return std::abs(a) < std::abs(b);
      });
    // lambda expression used as a binary predicate

    for (auto elem : ivec)
      cout << elem << ' ';
    // output -> 12 28 -34 63 -84 -283 293 1092 -1435
    std::cout << '\n';

    // ---------------------------------------------------------- 
  }
*/

/*
  #include <vector>
  #include <functional>   // std::negate, std::plus, std::multiplies
  #include <algorithm>    // std::transform
  #include <list>
  #include <iterator>     // std::back_inserter

  int main()
  {
    using namespace std;

    // ---------------------------------------------------------

    vector<int> ivec{ 11, -22, -33, 44, -55, 66, -77, -88, 99 };

    std::transform( ivec.begin(), ivec.end(),   // source
                    ivec.begin(),               // destination
                    std::negate<int>{});        // binary pred
    // "std::negate" function object(functor class)
    // used as a binary predicate

    for (auto elem : ivec)
      cout << elem << ' ';
    // output -> -11 22 33 -44 55 -66 77 88 -99

    cout << '\n';

    // ---------------------------------------------------------

    vector<int> ivec2{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    vector<int> ivec3{ 10, 20, 30, 40, 50, 60, 70, 80, 90 };
    list<int> ilist;

    std::transform( ivec2.begin(), ivec2.end(),   // source_1
                    ivec3.begin(),                // source_2
                    std::back_inserter(ilist),    // destination
                    std::plus{});                 // binary pred
    // "std::plus" function object(functor class) 
    // used as a binary predicate

    for (auto elem : ilist)
      cout << elem << ' ';
    // output -> 11 22 33 44 55 66 77 88 99

    std::cout << '\n';

    // ---------------------------------------------------------

    ilist.clear();

    std::transform( ivec3.begin(), ivec3.end(),        // source_1
                    ivec2.begin(),                     // source_2
                    std::back_inserter(ilist),         // destination
                    [](int a, int b) { return a - b; } // binary pred
                  );
    // lambda expression used as a binary predicate

    for (auto elem : ilist)
      cout << elem << ' ';
    // output -> 9 18 27 36 45 54 63 72 81

    cout << '\n';

    // ---------------------------------------------------------

    ilist.clear();

    std::transform( ivec2.begin(), ivec2.end(),   // source_1
                    ivec3.begin(),                // source_2
                    std::back_inserter(ilist),    // destination
                    std::multiplies{});           // binary pred
    // "std::multiplies" function object(functor class)
    // used as a binary predicate

    for (auto elem : ilist)
      cout << elem << ' ';
    // output -> 10 40 90 160 250 360 490 640 810  

    // ---------------------------------------------------------
  }
*/

/*
  #include <vector>
  #include <algorithm>    // std::sort
  #include <functional>   // std::greater

  int main()
  {

    std::vector<int> ivec1{ 43, 3, -5, 78, 23, -44, -12, 90, 21 };
    std::vector<int> ivec2{ 43, 3, -5, 78, 23, -44, -12, 90, 21 };

    // ------------------------------------------------------

    std::sort(ivec1.begin(), ivec1.end(), std::greater{});
    // "std::greater" functional object(functor class) 
    // used as a binary predicate

    for (auto elem : ivec1)
      std::cout << elem << ' ';
    // output -> 90 78 43 23 21 3 -5 -12 -44

    std::cout << '\n';

    // ------------------------------------------------------

    std::sort(ivec2.rbegin(), ivec2.rend());
    // default arguent "std::less" functional object
    // used as a binary predicate

    for (auto elem : ivec1)
      std::cout << elem << ' ';
    // output -> 90 78 43 23 21 3 -5 -12 -44

    std::cout << '\n';

    // ------------------------------------------------------
  }
*/

/*
                  ------------------------------
                  | lambda expressions (C++11) |
                  ------------------------------
*/

/*
  - compiler is generating a temporary object,
    when lambda expression is used.
  - temproray object is called "closure object".
  - type of the closure object is a class type 
    called "closure type".
  - for every lambda expression, compiler will generate
    different closure types.
  - lambda expression's is value category is 
    PRValue(R) because of it is a temporary object.
*/

/*
  // compiler generated closure type
  class xyz_11 {
  public:
    void operator()() const{}
  };

  int main()
  {
    [](){};     
    // lambda expression.

    [](){}();  
    // temp object created from lambda expression
  }
*/

/*
  --------------------------------------------------------------

  [] -> stateless lambda (no capture clause)
    stateless lambda, does not have non-static member function

  --------------------------------------------------------------

  "()" operator call function's parameter paranthesis
  
  []()        
    lambda expression that its operator call function 
    does not have a parameter.
  []    
    lambda expression that its operator call function 
    does not have a parameter.
  [](int x, int y)
    lambda expression that its operator call function 
    has 2 parameters.

  --------------------------------------------------------------

  "{}" operator call function's main block

  [](){}

  --------------------------------------------------------------
*/

/*
  class xyz_11 {
  public:
    int operator()(int val) const
    {
      return val * val;
    }
  };

  int main()
  {
    [](int x) { return x * x; };
    // compiler generated closure type and 
    // "xyz_11" class type are equivalent.
  
    // compiler will use type deduction to find out 
    // the return type of the lamda expression's 
    // operator call function's return type.

    // if there is no return value, 
    // return type will be void.
  }
*/

/*
  #include <type_traits>

  int main()
  {
    // -----------------------------------------------------

    auto fn = [](int x) { return x * x; };
    // fn's type is a class type (functor object)

    std::cout << fn(12) << '\n';  
    // output -> 144
    std::cout << fn(5) << '\n'; 
    // output -> 25

    // -----------------------------------------------------

    auto ival = [](int x) { return x * x; }(10);
    std::cout << "ival = " << ival << '\n';
    // output -> ival = 100

    // -----------------------------------------------------

    auto fn1 = [](int x) { return x * x; };
    auto fn2 = [](int x) { return x * x; };

    constexpr bool b1 = std::is_same_v< decltype(fn1), 
                                        decltype(fn2)>;
    // b1 -> false

    //for every lambda expression, 
    // compiler will generate different closure types,
    // even if they have the same structure.

    // -----------------------------------------------------
  }
*/

/*
  #include <vector>
  #include <algorithm>  // std::find_if
  #include <iterator>   // std::distance

  bool mod_5(int x)
  {
    return x % 5 == 0;
  }

  int main()
  {
    std::vector<int> ivec{ 3, 11, 8, 5, 1, 6, 10, 7, 4, 2 };

    // ------------------------------------------------------

    if (auto iter_found = 
          std::find_if( ivec.begin(), ivec.end(), 
                        [](int x) { return x % 5 == 0; });
        iter_found != ivec.end()) 
    {
      std::cout << "found = " << *iter_found 
                << ", index = " 
                << std::distance(ivec.begin(), iter_found)
                << '\n';
    } 
    // output -> found = 5, index = 3
    // using lambda expression as a callable

    // ------------------------------------------------------

    if (auto iter_found = 
          std::find_if(ivec.begin(), ivec.end(), &mod_5);
        iter_found != ivec.end()) 
    {
      std::cout << "found = " << *iter_found 
                << ", index = " 
                << std::distance(ivec.begin(), iter_found)
                << '\n';
    }
    // output -> found = 5, index = 3
    // using global function as a callable

    // ------------------------------------------------------
  }
*/

/*
  #include <cmath>  // std::abs

  template <typename T>
  class Myclass {};

  int main()
  {
    Myclass<decltype([](int x, int y) {
              return std::abs(x) < std::abs(y); 
            })> mx;

    // closure type can is being used 
    // as an explicit template argument
  }
*/

/*
  []()mutable{}
  []()-> int {}
  []()noexcept{}
  []()constexpr{}

  - parameter paranthesis is not need when it does not have
    any parameter variables.

  - when those are being used,
    - "mutable" keyword
    - trailing return type
    - "noexcept" specifier
    - "constexpr" keyword

  (since C++23, parameter paranthesis becomes optional)
*/

/*
  int main()
  {
    // ------------------------------------------------

    auto fn = [](){ std::cout << "hello world\n"; };
    // "fn" is a functor class

    fn(); 
    // output -> hello
    // class object's operator call function is called

    // ------------------------------------------------

    [](){ std::cout << "hello galaxy\n"; }();
    // output -> hello galaxy

    // ------------------------------------------------
  }
*/

/*
  int g_ival = 11;  // non-static global variable
  // (static storage duration)

  int main()
  {
    int ival = 22;  // non-static local variable
    // (automatic storage duration)
    static int s_ival = 33; // static local variable
    // (static storage duration)

    []() {
      ++ival;     // syntax error
      // error: 'ival' is not captured
      // local variables are not visible in class scope

      ++g_ival;   // VALID
      ++s_ival;   // VALID
      // static storage duration objects are visible  
      // in class scope
    }(); 
  }
*/

/*
  #include <string>

  class xyz_111 {
  private:
    int m_ival;
  public:
    xyz_111(int x) : m_ival(x) {}

    bool operator()(int val)const
    {
      return val % m_ival == 0;
    }
  };

  int main()
  {
    std::cout << std::boolalpha;

    int ival = 11;
    std::string str{ "hello world" };
    double dval = 4.5;

    // -------------------------------------------------------

    std::cout << xyz_111(ival)(22) << '\n';
    // output -> true
    std::cout << xyz_111(ival)(15) << '\n';
    // output -> false
    
    // -------------------------------------------------------

    std::cout << [ival](int x){ return x % ival == 0; }(33) 
              << '\n';
    // output -> true
    std::cout << [ival](int x){ return x % ival == 0; }(15) 
              << '\n';
    // output -> false

    // capturing local variable "ival" in capture clause
    // (copy capture)

    // -------------------------------------------------------

    [ival, str, dval](){}();
    // capturing multiple local variables in capture clause
    // (copy capture)

    // -------------------------------------------------------

    [=](){}();
    // capturing all local variables int capture clause
    // (copy capture)

    auto fn = [=](){ return ival * dval; }();
    std::cout << fn << '\n';  // output -> 49.5

    // -------------------------------------------------------
  }
*/

/*
  #include <random>

  class compiler_gen_1 {
  private:
    int m_x;
  public:
    compiler_gen_1(int x) : m_x(x) {}

    void operator()(int val) const
    {
      m_x += val; // syntax error
      // error: assignment of member 'compiler_gen_1::m_x' 
      // in read-only object

      // assigning to a data member of a class object
      // in a const member function is not allowed.
    }
  };

  class compiler_gen_2 {
  private:
    std::mt19937 m_eng;
  public:
    int foo() const
    {
      m_eng();  // syntax error
      //  error: no match for call to '(const std::mt19937) ()'
      
      // calling non-const member function
      // with const object is not allowed.
    }
  };

  int main()
  {

    int ival = 5;

    // ---------------------------------------------------------

    auto fn_1 = [ival](int x){ return ival += x; }; 
    // syntax error
    // error: assignment of read-only variable 'ival'

    // compiler generated closure type will have a 
    // data member "ival", and const operator call member function.

    // inside const member function, changing the value of
    // data member is not allowed.

    // ---------------------------------------------------------

    auto fn_2 = [ival](int x)mutable { return ival += x; }; 

    // when "mutable" keyword is used in lambda expression,
    // compiler generated closure type will have a
    // NON-const operator call member function.

    // inside NON-const member function, changing the value of
    // data member is allowed.

    // ---------------------------------------------------------

    std::mt19937 eng;
    auto fn_3 = [eng](){ return eng(); }; 
    // syntax error
    // error: no match for call to '(const std::mt19937)()'

    // inside const member function, calling non-const member
    // function of an object is not allowed.

    // ---------------------------------------------------------

    auto fn_4 = [eng]()mutable { return eng(); };

    // when "mutable" keyword is used in lambda expression,
    // compiler generated closure type will have a
    // NON-const operator call member function.

    // inside NON-const member function, calling non-const member
    // function of an object is allowed.

    // ---------------------------------------------------------
  }
*/

/*
  class compiler_gen_1 {
  private:
    int m_x;
  public:
    compiler_gen_1(int val) : m_x(val) {}
    void foo(int i){ m_x *= i; }
  };

  class compiler_gen_2 {
  private:
    int& mr_x;
  public:
    compiler_gen_2(int& val) : mr_x(val) {}
    void foo(int i) const { mr_x *= i; }
    // changing the object that reference binds to
    // inside a const member function is NOT syntax error in.
  };

  int main()
  {
    int ival = 5;

    // --------------------------------------------------

    compiler_gen_1 gen(ival);
    gen.foo(20);
    std::cout << "ival = " << ival << '\n';
    // output -> ival = 5

    // --------------------------------------------------

    compiler_gen_2 gen2(ival);
    gen2.foo(20);
    std::cout << "ival = " << ival << '\n';
    // ouput -> ival = 100

    // --------------------------------------------------

    ival = 5;

    auto fn = [ival](int val)mutable { ival *= val; };
    // "ival" local variable captured by copy semantics. 

    fn(10);

    std::cout << "ival = " << ival << '\n';
    // output -> ival = 5
    // "ival" that is captured in lambda expression 
    // is a copy of the original "ival" variable.

    // --------------------------------------------------

    auto fn_2 = [&ival](int i) { ival *= i; };
    // "ival" local variable captured by reference semantics.

    fn_2(20);
    std::cout << "ival = " << ival << '\n';
    // output -> ival = 100

    // --------------------------------------------------
  }
*/

/*
  #include <string>

  int main()
  {
    int ival = 10;
    double dval = 4.5;
    std::string str{ "hello" };

    // ----------------------------------------------------

    [&ival, &str, &dval](){}();
    // local variables are captured by reference semantics.

    // ----------------------------------------------------

    [&](){}();
    // capturing all local variables by reference semantics.

    // ----------------------------------------------------

    [&ival, &dval, str](){}();
    // "ival" and "dval" local variables are captured 
    // by reference semantics. 
    // "str" local variable is copy captured.

    // ----------------------------------------------------

    [=, &dval](){}();
    // "dval" local variable is captured by reference semantics.
    // all other local variables are copy captured.

    // ----------------------------------------------------

    [&, dval](){}();
    // "dval" local variable is copy captured.
    // all other local variables are captured 
    // by reference semantics.

    // ----------------------------------------------------

    auto fn = [std::cout](){}();  // syntax error
    // error: capture of non-variable 'std'

    // static storage dureation objects can not be captured
    // in capture clause.

    // ----------------------------------------------------
  }
*/

/*
  int main()
  {
    // ------------------------------------------------

    auto fn_1 = [](int x){ return x + 5; };
    auto fn_2 = [](int x)-> double{ return x + 5; };

    auto ival = fn_1(20);
    auto dval = fn_2(20);

    // ------------------------------------------------

    auto fn_3 = [](int x) {
          if (x > 10)
            return x + 5;
          else
            return x * 1.4;   // // syntax error
        };
    // error: inconsistent types 'int' and 'double' 
    // deduced for lambda return type

    // return type can both be deduce to int or double.
    // so it will be syntax error.
    // in this scenario, better using trailing return type.

    // ------------------------------------------------

    auto fn_4 = [](int x)->double {
                    if (x > 10)
                      return x + 5;
                    else
                      return x * 1.4;
                  };
    // return type will be deduce to 'double'.

    // ------------------------------------------------
  }
*/

/*
  void foo()noexcept; // no-throw guarantee

  int main()
  {
    auto fn_1 = [](){};
    auto fn_2 = []()noexcept{};


    constexpr bool b1 = noexcept(fn_1());   // b1 -> false
    // fn_1 functor class's operator call function
    // does not giving no-throw guarantee.

    constexpr bool b2 = noexcept(fn_2());   // b2 -> true
    // fn_2 functor class's operator call function
    // giving no-throw guarantee.
  }
*/

/*
  // in constexpr functions body, 
  // static storage duration objects can not be used.

  #include <array>

  int main()
  {
    // ---------------------------------------------

    auto fn_1 = [](int x){ return x * 5; };

    constexpr auto val = fn_1(12);  // val -> 60
    // "fn_1(12)" is a constant expression.

    // ---------------------------------------------

    auto fn_2 = [](int x) {
        static int s_ival = 10;
        return x * s_ival;
      };

    constexpr auto val2 = fn_2(5);  // syntax error
    // error: 
    //  'main()::<lambda(int)>' called in a constant expression
    //  's_ival' defined 'static' in 'constexpr' context

    // "fn_2(5)" is NOT a constant expression.

    // ---------------------------------------------

    std::array<int, fn_1(20)> ar_1; // VALID

    std::array<int, fn_2(20)> ar_2;  // syntax error
    // error: 
    //  'main()::<lambda(int)>' called in a constant expression

    // ---------------------------------------------
  }
*/

/*
  int main()
  {
    // ----------------------------------------------------

    auto fn_1 = [](int x) constexpr {
          static int s_ival = 11;   // syntax error
          return x * s_ival;
        };

    // when "constexpr" keyword added in lambda expression,
    // if there is any statement inside function body 
    // that violates constexpr rules, it will become syntax error.

    // ----------------------------------------------------

    auto fn_2 = [](int x) {
        static int s_ival = 11;
        return x * s_ival;
      };
    // NOT syntax error

    // this lambda expression can not be used,  
    // any context that requires constant expression.

    // ----------------------------------------------------
  }
*/

/*
                  ---------------------------------
                  | generalized lambda expression |
                  ---------------------------------
*/

/*
  #include <string>

  class Myclass {
  public:
    template <typename T>
    T operator()(T x){ return x; }
  };

  // compiler will generate a closure type like
  // below for "fn" lambda expression in main block scope.
  class compiler_gen {
  public:
    template <typename T>
    auto operator()(T x){ return x + x; }
  };

  int main()
  {
    // ----------------------------------------------

    Myclass m1;
    m1(12);   // passing `int` argument
    m1(6.2);  // passing `double` argument

    // ----------------------------------------------

    auto fn = [](auto x){ return x + x; };

    std::string str{ "hello world" };

    std::cout << fn(12) << '\n';  
    // output -> 24
    std::cout << fn(6.2) << '\n';
    // output -> 12.4
    std::cout << fn(str) << '\n';
    // output -> hello worldhello world

    // ----------------------------------------------
  }
*/

/*
  #include <list>
  #include <vector>

  int main()
  {
    auto get_container_size = 
      [](const auto& con) { return con.size(); };

    std::vector<int> ivec(20);
    std::list<double> dlist(50);

    std::cout << "size of ivec = " 
              << get_container_size(ivec) << '\n';
    // output -> size of ivec = 20
    std::cout << "size of dlist = " 
              << get_container_size(dlist) << '\n';
    // output -> size of dlist = 50
  }
*/

/*
  #include <algorithm>    // std::sort, std::for_each
  #include <memory>       // std::shared_ptr, std::make_shared
  #include <vector>
  #include <string>

  using namespace std;

  void f1(vector<shared_ptr<string>>& svec)
  {
    std::sort(begin(svec), end(svec),       // source
              []( const shared_ptr<string>& sptr_1,
                  const shared_ptr<string>& sptr_2){ 
                return *sptr_1 < *sptr_2;   // predicate
              });

    std::for_each(begin(svec), end(svec), 
                  [](const shared_ptr<string>& sptr){ 
                    cout << *sptr << ' '; 
                  });

    std::cout << '\n';
  }

  void f2(vector<shared_ptr<string>>& svec)
  {
    std::sort(begin(svec), end(svec), 
              [](const auto& s_ptr1, const auto& s_ptr2){ 
                return *s_ptr1 > *s_ptr2;  
              });

    std::for_each(begin(svec), end(svec), 
                  [](const auto& sptr){ 
                    cout << *sptr << ' '; 
                  });
  }

  int main()
  {
    vector<shared_ptr<string>> svec;

    svec.emplace_back(new string{ "cccc" });
    svec.push_back(make_shared<string>("bbbbb"));
    svec.emplace_back(new string{ "aaaa" });

    f1(svec);
    // output -> aaaa bbbbb cccc
    f2(svec);
    // output -> cccc bbbbb aaaa
  }
*/

/*
  #include <cstdio>     // std::putchar
  #include <vector>
  #include <algorithm>  // std::for_each

  void func(int) { std::putchar('I'); }
  void func(double) { std::putchar('D'); }
  void func(long) { std::putchar('L'); }

  int main()
  {
    std::vector<int> ivec(22);
    std::vector<double> dvec(11);

    // -----------------------------------------------------

    for_each(ivec.begin(), ivec.end(), func); // syntax error
    // error: no matching function for call to 
    // 'for_each( std::vector<int>::iterator, 
    //            std::vector<int>::iterator, 
    //            <unresolved overloaded function type>)'

    // which "func" overload will be called is not known.

    // -----------------------------------------------------

    for_each(ivec.begin(), ivec.end(), (void(*)(int))func);
    // output -> IIIIIIIIIIIIIIIIIIIIII
    // casting func's address to a void(*)(int) function pointer 

    std::cout << '\n';

    // -----------------------------------------------------

    for_each(ivec.begin(), ivec.end(), (void(*)(long))func);
    // output -> LLLLLLLLLLLLLLLLLLLLLL
    // casting func's address to a void(*)(long) function pointer 

    std::cout << '\n';

    // -----------------------------------------------------

    for_each(ivec.begin(), ivec.end(), [](auto x){ func(x); });
    // output -> IIIIIIIIIIIIIIIIIIIIII
    // "x" will deduce to "int", when *iter was passed to 
    // lambda function so func(int) overload will be called.

    std::cout << '\n';

    // -----------------------------------------------------

    for_each(dvec.begin(), dvec.end(), [](auto x){ func(x); });
    // output -> DDDDDDDDDDD

    // "x" will deduce to "double" when *iter was passed to
    // lambda function, so func(double) overload will be called.

    // -----------------------------------------------------
  }
*/

/*
  #include <initializer_list>
  #include <utility>            // std::forward

  template <typename ...Args>
  void print(Args&&... args)
  {
    std::initializer_list<int>{
      ((std::cout << std::forward<Args>(args) << '\n'), 0)...};
  }

  int main()
  {
    auto fn = [](auto&&... args) {
      print(std::forward<decltype(args)>(args)...);
    };
    // arguments will be perfect forwarded to "print" function.

    fn(12, 3.4, 4.5f, "hello world");
    // output ->
    //  12
    //  3.4
    //  4.5
    //  hello world
  }
*/

/*
                  -------------------------------
                  | lambda init capture (C++14) |
                  -------------------------------
*/

/*
  // compiler generated closure type 
  // for "fn_1" and "fn_2" lambda expressions
  class compiler_gen_1_2 {
  private:
    int m_val;
  public:
    compiler_gen_1_2(int x) : m_val{ x * 6 } {}
  };

  // compiler generated closure type
  // for "fn_3" lambda expression
  class compiler_gen_3 {
  private:
    int m_val;
  public:
    compiler_gen_3(int x) : m_val{ m_val * 6 } {}
  };

  int main()
  {
    int ival = 10;

    // -------------------------------------------------------

    auto fn_1 = [x = ival * 6](int a) { return x + a; };
    std::cout << fn_1(20) << '\n';  // output -> 80

    auto fn_2 = [ival](int a){ return (ival * 6) + a; };
    std::cout << fn_2(20) << '\n';  // output -> 80

    // -------------------------------------------------------

    auto fn_3 = [ival = ival * 6](int a){ return ival + a; };
    std::cout << fn_3(20) << '\n';  // output -> 80

    // [ival = ival * 6] ---> [data member = local variable * 6]

    // -------------------------------------------------------
  }
*/

/*
  int main()
  {
    int x = 10;

    auto fn_1 = [&val = x](int a) {
      val = 2;
    };

    auto fn_2 = [&x = x](int a) {
      x = 2;  // data member "x"
    };
    // "fn_1" and "fn_2" lambda expressions are equivalent.
  }
*/

/*
  // lamba init capture is used for move-only types.

  #include <utility>  // std::move
  #include <memory>   // std::unique_ptr
  #include <string>

  class Myclass {
  public:
    Myclass() = default;
    Myclass(Myclass&&)
    {
      std::cout << 
        "Myclass::Myclass(Myclass&&) - move constructor\n";
    }
    // copy members are implicitly deleted 
    // because of move constructor is user declared to be defined.
  };

  int main()
  {
    Myclass mx;

    auto fn_1 = [cap = std::move(mx)]() {};
    // output -> Myclass::Myclass(Myclass&&) - move constructor

    // "mx" object is moved to "cap" object.
    // "mx" is in moved-from state

    // ----------------------------------------------

    std::unique_ptr<std::string> uptr{ 
        new std::string{"hello world"} };

    std::cout << (uptr ? "not empty" : "empty") << '\n';
    // output -> not empty
    
    auto fn_2 = [cap_uptr = std::move(uptr)]() {
          std::cout << *cap_uptr << '\n';
        };

    fn_2();   // output -> hello world
    // uptr is in moved-from state.

    std::cout << (uptr ? "not empty" : "empty") << '\n';
    // output -> empty

    // ----------------------------------------------
  }
*/

/*
  int main()
  {
    auto fn = [](int x){ return x * x; };  
    // stateless lambda

    // ---------------------------------------------------

    decltype(fn) fn_2;  // VALID since C++20
    // default constructor of "[](int x)->int" 
    // it is a implicitly deleted before C++20,
    // since C++20 it is not deleted.

    // ---------------------------------------------------

    auto fn_3 = fn;   
    // VALID - copy constructor is NOT deleted.

    // ---------------------------------------------------

    fn_3 = fn_2;  // VALID since C++20
    // copy assingment operator is NOT deleted since C++20

    // ---------------------------------------------------
    // ---------------------------------------------------

    int ival = 20;
    auto fn_4 = [ival](int x){ return x * ival; };
    //  stateful lambda

    decltype(fn_4) fn_5;  // syntax error
    // error: 
    //  use of deleted function 'main()::<lambda(int)>::<lambda>()'
    
    // if lambda expression is a stateful lambda,
    // it is still a syntax error.

    // ---------------------------------------------------
  }
*/

/*
  // implicit conversion from stateless lambda to
  // function pointer is allowed.

  using cmp_fn = int(*)(int);

  class compiler_gen {
  public:
    int operator()(int x)const
    {
      return x * 6;
    }

    operator cmp_fn() const
    {
      // function that lets implicit conversion 
      // from closure object to cmp_fn(function pointer) type.
      return operator()
    }
  };

  int main()
  {
    // ---------------------------------------------------

    int (*fp1)(int) = [](int x){ return x * 6; };
    // stateless lambda
    // impiicit conversion from closure object to function pointer

    std::cout << fp1(20) << '\n'; // output -> 120

    // ---------------------------------------------------

    compiler_gen cg1;
    int (*fp2)(int) = cg1;
    std::cout << fp2(20) << '\n'; // output -> 120

    // ---------------------------------------------------

    auto fn_1 = [](int x) { return x * 11; };
    auto fn_2 = [](int x) { return x * 22; };

    int(*fp3)(int) = fn_1;
    fp3 = fn_2;

    // ---------------------------------------------------
  }
*/

/*
  // implicit conversion from stateful lambda to 
  // function pointer is not allowed.

  int main()
  {
    int ival = 55;

    auto fn_1 = [ival](int x){ return x * ival; };
    auto fn_2 = [ival](int x){ return x * ival * 2; };
    // stateful lambda

    int (*fp)(int) = fn_1;  // syntax error
    // error: cannot convert 'main()::<lambda(int)>' to 
    //  'int (*)(int)' in initialization

    fp = fn_2;              // syntax error
    // error: cannot convert 'main()::<lambda(int)>' to 
    //  'int (*)(int)' in assignment
  }
*/

/*
                      -------------------------
                      | positive lambda idiom |
                      -------------------------
*/

/*
  int foo(int) {}

  class AClass {
  public:
    operator int() const;
  };

  using fptr = int(*)(int);

  class BClass {
  public:
    operator fptr() const;
  };

  int main()
  {
    // ----------------------------------------------

    int ival = 10;
    int* ip1 = &ival;
    auto ip2 = +ip1;
    // "+p" expression's data type is "int*"

    // ----------------------------------------------

    int(*fp1)(int) = &foo;
    int(*fp2)(int) = +fp1; 
    // "+fp1" expression's data type is "int(*)(int)"

    // ----------------------------------------------

    AClass a1;
    +a1;
    // to become an operand of unary sign(+) operator,
    // AClass will implicitly convert to int
    // by calling its operator int() const member function.

    // ----------------------------------------------

    BClass b1;
    +b1;
    +b1.operator fptr();
    // These 2 lines are equivalent.

    // to become an operand of unary sign(+) operator,
    // BClass will implicitly convert to function pointer.
    // by calling its operator fptr() const member function.

    // BClass can convert to function pointer 
    // which can be an operand of sign + operator.

    // ----------------------------------------------
  }
*/

/*
  template <typename Callable>
  void func(Callable fn)
  {
    std::cout << fn(111) << '\n';
  }

  int main()
  {
    // ---------------------------------------------
    
    auto fn = [](int x){ return x * 5; };
    // fn's type is closure type

    auto fp = +[](int x) { return x * 5; };
    // fp's type is int(*)(int)

    // ---------------------------------------------

    func([](int x){ return x * 5; });   // output -> 555
    // sending closure type as an argument.

    func(+[](int x){ return x * 6; });  // output -> 666
    // sending function pointer as an argument
  }
*/

/*
  ----------------------------------------------------------------
  | Immediately Invoked Function(Lambda) Expression [IIFE] idiom |
  ----------------------------------------------------------------
*/

/*
  - general purpose of IIFE idiom is 
    assignment to const variables.
*/

/*
  int main()
  {
    // ------------------------------------------------

    int ival = 10;

    [ival](int y){ return ival * y; }(10);
    // lambda's operator call function can be called immediately.

    // ------------------------------------------------

    int a = 5, b = 7, c = 9;

    const int c_ival = [=](int val){ return a * b + 3; }(c);
    // copy capturing all local variables
    // and sending c as an argument to lambda expression.

    std::cout << "c_ival = " << c_ival << '\n';
    // output -> c_ival = 38

    // ------------------------------------------------
  }
*/

/*
  auto foo()
  {
    return [](int val){ return val * 5; };
  }
  // function's return type is closure type

  int main()
  {
    auto fn = foo();

    std::cout << "fn(11) = " << fn(11) << '\n';
    // output -> fn(11) = 55
  }
*/

/*
  auto foo(int x)
  {
    return [x](int val) {return val * x; };
  }

  int main()
  {
    auto fn = foo(11);

    std::cout << fn(22) << '\n';  
    // output -> 242

    std::cout << foo(11)(22) << '\n';
    // output -> 242
  }
*/

/*
  auto foo(int x)
  {
    return [&x](int val){ return val * x; };
  }

  int main()
  {
    auto fn = foo(20);
    // closure objects data member(int&) will bind to 
    // foo function's parameter variable x.

    // After "foo" function's execution, 
    // parameter variable "x"'s life will be ended and 
    // closure object's data member will become dangling reference

    std::cout << fn(34) << '\n';  // undefined behaviour(UB)
  }
*/

/*
                  -----------------------------
                  | std::hash function object |
                  -----------------------------
*/

/*
  In unordered containers, keys need to be hashed to an index.

  key can be 
    - phone number
    - date
    - address
    - ...

  hashing key(phone number) to index 
    (0531-111-11-11) ---> index 0
    (0532-222-22-22) ---> index 1
    ...

  Hashing                 : converting a key to an index
  Hasher / Hash function  : function that convert a key to an index

  - better hash function means less collision between indexes.
  - in standart library, if there is a collision between indexes
    it will transfer that index to a list container.
*/

/*
  // std::hash is a class template (function object class)

  #include <string>   // std::hash 

  int main()
  {
    std::cout << std::hash<std::string>{}("hello worlc") << '\n';	
    // output -> 3046853591255510168
    std::cout << std::hash<std::string>{}("hello world") << '\n';
    // output -> 5577293430985752569

    // return type of the "operator()" member function 
    // of std::hash class template is `std::size_t`
  }
*/

/*
  #include "../headers/nutility.h"
  #include <string>     // std::hash
  #include <cstddef>    // std::size_t

  int main()
  {
    std::string str_city{};
    for (std::size_t i = 0; i < 10; ++i)
    {
      str_city = rtown();
      std::cout << "key = " << str_city << ", hash = " 
                << std::hash<std::string>{}(str_city) << '\n';
    }
    // output ->
    //  key = van, hash = 1263615577688186006
    //  key = hakkari, hash = 14763395533960259727
    //  key = bingol, hash = 5984918586931409758
    //  key = antalya, hash = 5992998171556963400
    //  key = mugla, hash = 17921419194443234248
    //  key = siirt, hash = 6510389844421836500
    //  key = kastamonu, hash = 2571461943374302701
    //  key = van, hash = 1263615577688186006
    //  key = elazig, hash = 13546496586208094739
    //  key = tokat, hash = 15927138287924965727

    // same keys will hashed to same index, i.e check "van"
  }
*/

/*
                    --------------------------
                    | std::reference_wrapper |
                    --------------------------
*/

/*
  template <typename T>
  class ReferenceWrapper {
  public:
    ReferenceWrapper(T& val) : m_p{ &val } {}
    ReferenceWrapper operator=(T& val) 
    { 
      m_p = &val; 
      return *this;
    }

    operator T&() { return *m_p; }
    T& get() { return *m_p; }
  private:
    T* m_p;
  };

  int main()
  {
    int ival{};
    ReferenceWrapper<int> rw{ ival };

    int ival2 = rw;
    int ival3 = rw.operator int &();
    // Those 2 lines are equivalent.

    int ival4 = 10;
    rw = ival4;
    rw.operator=(ival4);
    // Those 2 lines are equivalent.
  }
*/

/*
  #include <functional>   
  // std::reference_wrapper, std::ref, std::cref

  template <typename T>
  std::reference_wrapper<T> Ref(T& val)
  {
    return std::reference_wrapper<T>{ val };
  }

  int main()
  {
    int ival = 10;
    std::reference_wrapper<int> ref_wrap{ ival };

    // ----------------------------------------------------

    std::cout << ref_wrap.operator int& () << '\n';
    // output -> 10
    std::cout << ref_wrap << '\n';
    // output -> 10

    // ----------------------------------------------------

    ref_wrap.get() = 45;    
    // returns reference to the object

    std::cout << "ival = " << ival << '\n';
    // output -> x = 45

    // ----------------------------------------------------

    int ival2 = 55;
    ref_wrap = ival2;

    std::cout << "ref_wrap = " << ref_wrap << '\n';
    // output -> ref_wrap = 55

    // ----------------------------------------------------

    auto ref_wrap_2 = Ref(ival);
    // ref_wrap_2's type is std::reference_wrapper<int>

    // ----------------------------------------------------

    ival = 10;
    auto r1 = std::ref(ival);
    // r1's type is std::reference_wrapper<int>

    ++r1;
    std::cout << "ival = " << ival << '\n';
    // output -> ival = 11

    r1.get() = 15;
    std::cout << "ival = " << ival << '\n';
    // output -> ival = 15

    // ----------------------------------------------------

    ival = 10;
    auto r2 = std::cref(ival);
    // r2's type is std::reference_wrapper<const int>

    ++r2;           // syntax error
    // error: no match for 'operator++' 
    //  (operand type is 'std::reference_wrapper<const int>')

    r2.get() = 15;  // syntax error
    // error: assignment of read-only location 
    //  'r2.std::reference_wrapper<const int>::get()'

    // ----------------------------------------------------
  }
*/

/*
  #include <functional> // std::ref

  template <typename T>
  void func(T x)
  {
    std::cout << typeid(x).name() << '\n';
  }

  class Myclass {
    unsigned char m_buffer[4096]{};
  };

  int main()
  {
    Myclass mx;

    std::cout << "sizeof(Myclass) = " << sizeof(Myclass) << '\n';
    // output -> 4096

    func(mx);
    // output -> class Myclass

    func(std::ref(mx));
    // output -> class std::reference_wrapper<class Myclass>

    func<Myclass&>(mx);
    // output -> class Myclass
    // can also be used instead of std:ref()
  }
*/

/*
  #include <functional>   // std::reference_wrapper
  #include <vector>

  int main()
  {
    int x = 10, y = 20, z = 30;

    // -------------------------------------------------------
    
    std::vector<int&> iref_vec { x, y, z }; // syntax error
    //  error: forming pointer to reference type 'int&'

    // containers CAN NOT hold references.

    // -------------------------------------------------------

    std::vector<std::reference_wrapper<int>> irefwrap_vec{ 
      x, y, z };

    ++irefwrap_vec[0];
    ++irefwrap_vec[1];
    ++irefwrap_vec[2];

    std::cout << "x = " << x << '\n'; // output -> x = 11
    std::cout << "y = " << y << '\n'; // output -> y = 21
    std::cout << "z = " << z << '\n'; // output -> z = 31

    // -------------------------------------------------------
  }
*/

/*
  #include <list>
  #include <vector>
  #include <functional>   // std::reference_wrapper
  #include <algorithm>    // std::sort

  int main()
  {
    std::list<int> i_list{ 33, 77, 55, 22, 99  };
    std::vector<std::reference_wrapper<int>> irefwrap_vec { 
      i_list.begin(), i_list.end() };

    std::sort(irefwrap_vec.begin(), irefwrap_vec.end());
    // element's values will be sorted in irefwrap_vec
    // but it will not change the order of elements in i_list.

    for (auto elem : i_list)
      std::cout << elem << ' ';
    // output -> 33 77 55 22 99

    std::cout << '\n';

    for (auto elem : irefwrap_vec)
      std::cout << elem << ' ';
    // output -> 22 33 55 77 99
  }
*/

/*
  #include <random>       // std::mt19937
  #include <functional>   // std::ref
  #include <algorithm>
  #include <vector>

  template <typename T>
  void func(T){}

  template <typename ForIt, typename Fn>
  void Generate(ForIt iter_beg, ForIt iter_end, Fn fn)
  {
    while (iter_beg != iter_end)
      *iter_beg++ = fn();
  }

  int main()
  {
    // ------------------------------------------------
    std::mt19937 eng;
    std::cout << "sizeof(eng) = " << sizeof(eng) << '\n';
    // output -> sizeof(eng) = 2504

    func(std::ref(eng));
    // because of std::mt19937 is a large object,
    // it is better to wrap it with std::ref()
    // when it is passed to a function.

    // ------------------------------------------------

    std::vector<unsigned int> ivec(1000);

    Generate(ivec.begin(), ivec.end(), eng);
    // std::mt19937 object will be copied to Generate function

    Generate(ivec.begin(), ivec.end(), std::ref(eng));
    // reference semantics will be used.
    // ------------------------------------------------
  }
*/

/*
  #include <utility>      // std::pair, std::make_pair
  #include <functional>   // std::ref

  int main()
  {
    int x = 0, y = 0;

    // ------------------------------------------------------

    std::pair<int, int> ii_pair1{ x, y };
    ii_pair1.first = 111;
    ii_pair1.second = 111;

    std::cout << "x = " << x << '\n';   // output -> x = 0
    std::cout << "y = " << y << '\n';   // output -> y = 0

    // x and y has been copied to std::pair(ii_pair1) 
    // so their values did not change
    // copied values are changed.

    // ------------------------------------------------------

    std::pair<int&, int&> ii_pair2{ x, y };
    ii_pair2.first = 222;
    ii_pair2.second = 222;

    std::cout << "x = " << x << '\n';   // output -> x = 222
    std::cout << "y = " << y << '\n';   // output -> y = 222

    // ii_pair2 is holding references to x and y
    // so their values are changed.

    // ------------------------------------------------------

    auto ii_pair3 = std::make_pair(x, y);   
    // std::pair<int,int>

    ii_pair3.first = 333;
    ii_pair3.second = 333;

    std::cout << "x = " << x << '\n';   // output -> x = 222
    std::cout << "y = " << y << '\n';   // output -> y = 222


    // x and y will be deduce to int
    // so their values are copied to std::pair(ii_pair3)
    // so their values did not change.

    // ------------------------------------------------------

    auto ii_pair4 = std::make_pair(std::ref(x), std::ref(y)); 
    // std::pair<int&, int&>

    ii_pair4.first = 444;
    ii_pair4.second = 444;

    std::cout << "x = " << x << '\n';   // output -> x = 444
    std::cout << "y = " << y << '\n';   // output -> y = 444

    // ------------------------------------------------------
  }
*/

/*
                    ----------------------------
                    | member function pointers |
                    ----------------------------
*/

/*
  class Myclass {
  public:
    static int static_member_func(int);
    int non_static_member_func(int);
  };

  int non_static_global_func(int);

  int main()
  {
    int(*fp)(int);

    // -----------------------------------------------

    fp = &non_static_global_func;         // VALID
    fp = &Myclass::static_member_func;    // VALID
    
    auto stateless_lambda = [](int a){ return a * 5; };
    fp = stateless_lambda;                // VALID

    // -----------------------------------------------

    fp = &Myclass::non_static_member_func;    // syntax error
    // error: cannot convert 'int (Myclass::*)(int)' 
    // to 'int (*)(int)' in assignment

    // non-static member functions have `this` pointer parameter
    // (hidden parameter)

    // -----------------------------------------------

    auto fp1 = &Myclass::non_static_member_func;
    int(Myclass::* fp2)(int) = &Myclass::non_static_member_func;
    // Those 2 lines are equivalent.

    // -----------------------------------------------
  }
*/

/*
  int foo(int);

  using fp_type = int (*)(int);

  int main()
  {
    auto fp1          = &foo;
    auto fp2          = foo;
    int (*fp3)(int)   = &foo;
    fp_type fp4       = &foo;
    // Those 4 lines are equivalent.
  }
*/

/*
  int f1(int);
  int f2(int);
  int f3(int);
  int f4(int);
  int f5(int);

  using fp_type = int(*)(int);

  int main()
  {
    fp_type fp_arr[] = { f1, f2, f3, f4, f5 };
  }
*/

/*
  int func_1(int);

  int main()
  {
    // ----------------------------------------------

    auto fp1 = func_1;
    int(*fp2)(int) = func_1;
    // Those 2 lines are equivalent.

    // type deduction for auto, will be `int(*)(int)` type
    // which is a function pointer type.

    // ----------------------------------------------

    auto& fn1 = func_1;
    int(&fn2)(int) = func_1;
    // Those 2 lines are equivalent.

    // type deduction for auto will be `int(int)` type 
    // which is a function type.

    // ----------------------------------------------
  }
*/

/*
  // there is no type difference between 
  // "non_static_global_func" and "static_member_func"
  // because static member functions did not have `this` 
  // pointer as its hidden parameter.

  #include <type_traits>    // std::is_same

  int non_static_global_func(int);

  class Myclass {
  public:
    static int static_member_func(int);
  };

  int main()
  {
    auto fp_1 = non_static_global_func;
    auto fp_2 = Myclass::static_member_func;

    constexpr bool b1 = std::is_same_v< decltype(fp_1), 
                                        decltype(fp_2)>;
    // b1 -> true
  }
*/

/*
  class Myclass {
  public:
    int func1(int);           // non-static member function
    double func2(int, int);   // non-static member function
  };

  int main()
  {
    int(Myclass::*m_fp1)(int) = &Myclass::func1;
    double(Myclass::* m_fp2)(int, int) = &Myclass::func2;
  }
*/

/*
  class Myclass {
  public:
    int func_1(int);    // non-static member function
    int func_2(int);    // non-static member function
    int func_3(int);    // non-static member function
  };

  using m_fp_type = int(Myclass::*)(int);

  int main()
  {
    int(Myclass::*m_fparr[3])(int) = {
      &Myclass::func_1,
      &Myclass::func_2,
      &Myclass::func_3,
    };

    m_fp_type m_fparr2[] = {
      &Myclass::func_1,
      &Myclass::func_2,
      &Myclass::func_3, 
    };

    // Those 2 arrays are equivalent.
  }
*/

/*
  #include <cstdio>    // std::puts, std::printf

  class Myclass {
  public:
    // non-static member function
    int func(int val)    
    {
      std::puts("int Myclass::foo(int val)");
      std::printf("val = %d\n", val);
      std::cout << "this = " << this << '\n';
      return val;
    }
  };

  int main()
  {
    Myclass mx;
    std::cout << "&mx = " << &mx << '\n';
    // output -> &mx = 0x9f0fdffa2f

    // ----------------------------------------------

    mx.func(11);
    // output ->
    //  int Myclass::foo(int val)
    //  val = 11
    //  this = 0x9f0fdffa2f

    // ----------------------------------------------

    auto member_fp = &Myclass::func;
    // int (Myclass::*member_fp)(int) = &Myclass::func;

    // .* -> member function pointer selection operator
    (mx.*member_fp)(22);
    //  int Myclass::foo(int val)
    //  val = 22
    //  this = 0x9f0fdffa2f

    // ----------------------------------------------
  }
*/

/*
  #include <cstdio>    // std::puts, std::printf

  class Myclass {
  public:
    int foo(int x)
    {
      std::puts("int Myclass::foo(int x)");
      std::printf("x = %d\n", x);
      std::cout << "this = " << this << '\n';
      return x;
    }
  };

  int main()
  {
    Myclass mx;
    Myclass* p_mx{ &mx };

    // -----------------------------------------

    auto member_fp = &Myclass::foo;

    ((*p_mx).*member_fp)(11);
    // output ->
    //  int Myclass::foo(int x)
    //  x = 11
    //  this = 0x4ac5ffa07

    (p_mx->*member_fp)(22);
    // output ->
    //  int Myclass::foo(int x)
    //  x = 22
    //  this = 0x4ac5ffa07

    // -----------------------------------------
  }
*/

/*
  class Myclass {
  public:
    void func_1(int x)
    {
      std::cout << "Myclass::func_1(int x), x = " 
                << x << '\n';
    }
    void func_2(int x)
    {
      std::cout << "Myclass::func_2(int x), x = " 
                << x << '\n';
    }

    void func()
    {
      ((*this).*mp_memberfn)(11);
    }

    void set_member_fp(void(Myclass::*member_fn)(int))
    {
      mp_memberfn = member_fn;
    }
  private:
    void (Myclass::*mp_memberfn)(int){ &Myclass::func_1 };
  };

  int main()
  {
    Myclass mx;
    mx.func();  
    // output -> Myclass::func_1(int x), x = 11

    mx.set_member_fp(&Myclass::func_2);
    mx.func();  
    // output -> Myclass::func_2(int x), x = 11
  }
*/

/*
                      ------------------------
                      | data member pointers |
                      ------------------------
*/

/*
  #include <functional>   // std::invoke

  struct Point {
    int m_x, m_y;
  };

  int main()
  {
    Point px = { 11, 22 };

    // ----------------------------------------------

    auto i_ptr = &px.m_x;
    // `i_ptr`'s type is int*

    // ----------------------------------------------

    // data member pointer
    auto dm_ptr1 = &Point::m_x;      
    int Point::* dm_ptr2 = &Point::m_y;
    // Those 2 lines are equivalent.

    // ----------------------------------------------

    std::cout << "px.*dm_ptr1 = " << px.*dm_ptr1 << '\n'; 
    // output -> px.*dm_ptr1 = 11
    std::cout << "px.m_x = " << px.m_x << '\n'; 
    // output -> px.m_x = 11

    px.*dm_ptr1 = 90;
    // "px.*dm_ptr1" is an LValue expression

    std::cout << "px.m_x = " << px.m_x << '\n'; 
    // output -> p.mx = 90

    // -------------------------------------------

    std::invoke(dm_ptr2, px) = 888;
    std::cout << "px.m_y = " << px.m_y << '\n'; 
    // output -> px.m_y = 888

    // -------------------------------------------
  }
*/

/*
  struct Point {
    int m_x, m_y;
  };

  void func(Point& px, int Point::*dm_ptr)
  {
    px.*dm_ptr = 99;
  }

  int main()
  {
    Point p1 = { 11, 22 };

    // --------------------------------------------

    std::cout << "p1.m_x = " << p1.m_x << '\n';
    // output -> p1.m_x = 11
    
    func(p1, &Point::m_x);

    std::cout << "p1.m_x = " << p1.m_x << '\n';
    // output -> p1.m_x = 99

    // --------------------------------------------

    std::cout << "p1.m_y = " << p1.m_y << '\n';
    // output -> p1.m_y = 22

    func(p1, &Point::m_y);

    std::cout << "p1.m_y = " << p1.m_y << '\n';
    // output -> p1.m_y = 99

    // --------------------------------------------
  }
*/

/*
                  --------------------------------
                  | std::function class template |
                  --------------------------------
*/

/*
  #include <functional>   
  // std::function, std::bind, std::placeholders

  int sum(int x, int y)
  {
    std::cout << "::sum()\n";
    return x + y;
  }

  int foo(int a, int b, int c)
  {
    std::cout << "::foo()\n";
    return a * b * c;
  }

  class Functor {
  public:
    int operator()(int a, int b)const
    {
      std::cout << "Functor::operator()\n";
      return a * b;
    }
  };

  int main()
  {
    using namespace std::placeholders;

    auto callable_1 = [](int x, int y){ return x * x + y * y; };
    auto callable_2 = std::bind(foo, _1, _2, 400);

    // -------------------------------------------------

    std::function<int(int, int)> fn_1{ sum };
    std::cout << fn_1(11, 22) << '\n';  
    // output ->
    //  ::sum()
    //  33

    // -------------------------------------------------

    std::function<int(int, int)> fn_2{ Functor{} };
    std::cout << fn_2(11, 22) << '\n';
    // output ->
    //  Functor::operator()
    //  242 

    // -------------------------------------------------

    std::function<int(int, int)> fn_3{ callable_1 };
    std::cout << fn_3(11, 22) << '\n';
    // output -> 605

    // -------------------------------------------------

    std::function<int(int, int)> fn_4{ callable_2 };
    std::cout << fn_4(11, 22) << '\n';
    // output ->
    //  ::foo()
    //  96800

    // -------------------------------------------------

    std::function<int(int, int)> fn5{ 
                    [](int a, int b){ return a - b; } };

    std::cout << fn5(11, 22) << '\n';
    // output -> -11

    // -------------------------------------------------
  }
*/

/*
  #include <functional>   // std::function, std::bind
  #include <vector>

  // generic callback structure.
  void func(std::function<int(int, int)> fn)
  {
    fn(10, 20);
  }

  int sum(int x, int y)
  {
    return x + y;
  }

  class Functor {
  public:
    int operator()(int a, int b) const
    {
      return a * b;
    }
  };

  int foo(int a, int b, int c)
  {
    return a * b * c;
  }

  using func_t = std::function<int(int, int)>;

  int main()
  {
    using namespace std::placeholders;

    std::vector<std::function<int(int, int)>> fn_vec1;
    std::vector<func_t> fn_vec2;
    // Those 2 lines are equivalent.

    // --------------------------------------------------

    fn_vec1.push_back(sum);
    fn_vec1.push_back(Functor{});
    fn_vec1.push_back([](int a, int b){return a * b - 1; });
    fn_vec1.push_back(std::bind(foo, 10, _1, _2));

    for (auto& fn : fn_vec1)
      std::cout << fn(10, 20) << '\n';
    // output ->
    //  30
    //  200
    //  199
    //  2000

    // --------------------------------------------------
  }
*/

/*
  #include <functional>   // std::function

  int foo(int, int)
  {
    std::cout << "::foo called\n";
    return 1;
  }

  int bar(int, int)
  {
    std::cout << "::bar called\n";
    return 2;
  }

  struct Functor {
    int operator()(int, int)
    {
      std::cout << "Functor::operator() called\n";
      return 3;
    }
  };

  int main()
  {

    std::function fn{ foo };    // CTAD(C++17)
    fn(11, 22);   
    // output -> ::foo called

    fn = bar;
    fn(11, 22);   
    // output -> ::bar called

    fn = Functor{};
    fn(11, 22);   
    // output -> Functor::operator() called

    fn = [](int a, int b) {
      std::cout << "lambda expression\n";
      return 4;
      };
    fn(11, 22);  
     // output -> lambda exprssion
  }
*/

/*
  #include <functional>   
  // std::function, std::bad_function_call

  int main()
  {
    std::function<int(int, int)> fn;  // default initialization
    // default constructor will be called.
    // "fn" is not wrapping any function when default constructed 
    // so calling fn() will throw an exception.

    try
    {
      fn(12, 56);
    }
    catch (const std::bad_function_call& ex)
    {
      std::cout << "exception caught: " << ex.what() << '\n';
    }
    // output -> exception caught: bad_function_call
  }
*/

/*
  #include <functional>   // std::function

  void foo(int, int)
  {
    std::cout << "::foo called\n";
  }

  int main()
  {
    std::function<void(int, int)> fn;

    // ----------------------------------------------------
    
    if (fn)
    {
      std::cout << "there is a callable can be invoked.\n";
      fn(10, 20);
    }
    else
    {
      std::cout << "there is no wrapped callable.\n";
    }
    // output -> there is no wrapped callable.

    // ----------------------------------------------------

    fn = foo;

    if (fn) {
      std::cout << "there is a callable can be invoked.\n";
      fn(10, 20);
    }
    else {
      std::cout << "there is no wrapped callable.\n";
    }
    // output -> 
    //  there is a callable can be invoked.
    //  ::foo called

    // ----------------------------------------------------
  }
*/

/*
  #include <functional>   // std::function

  int bar(int x)
  {
    return x * 6;
  }

  std::function<int(int)> func_1()
  {
    return [](int x){ return x * 5; };
  }
    
  std::function<int(int)> func_2()
  {
    return bar;
  }

  int main()
  {
    std::cout << func_1()(11) << '\n';  // output -> 55
    std::cout << func_2()(11) << '\n';  // output -> 66  
  }
*/

/*
  #include <vector>
  #include <functional>   // std::function

  void foo(int (*fp)(int, int));
  int bar(int, int);

  using fn_type = int(*)(int);

  int func_1(int);
  int func_2(int);
  int func_3(int);

  using fn_type_generic = std::function<int(int)>;

  int main()
  {
    foo(bar);
    foo(&bar);
    // Those 2 lines are equivalent.
    // because of function to function pointer conversion.

    std::vector<fn_type> fn_vec1{ func_1, func_2, func_3 };
    std::vector<fn_type> fn_vec2{ &func_1, &func_2, &func_3 };
    std::vector fn_vec3{ func_1, func_2, func_3 };  // CTAD(C++17)
    std::vector<fn_type_generic> fn_vec4{ func_1, func_2, func_3 };
    // Those 4 lines are equivalent.
  }
*/

/*
  #include <functional>   // std::function

  int main()
  {
    std::function<double(double)> fn;

    std::cout << (fn ? "not empty" : "empty") << '\n';	
    // output -> empty

    fn = [](double dval){ return dval * dval; };
    std::cout << (fn ? "not empty" : "empty") << '\n';
    // output -> not empty
  }
*/

/*
  #include <functional>   // std::function

  class Myclass {
  public:
    void foo(int x)
    {
      std::cout << "void Myclass::foo(int x) x = " << x << '\n';
      std::cout << "this = " << this << '\n';
    }
  };

  int main()
  {
    std::function<void(Myclass&, int)> fn_1 = &Myclass::foo;
    std::function<void(Myclass*, int)> fn_2 = &Myclass::foo;

    Myclass mx;
    std::cout << "&mx = " << &mx << '\n';
    // output -> &mx = 0x81ebdffc1f

    fn_1(mx, 11);
    // output ->
    //  void Myclass::foo(int x) x = 11
    //  this = 0x81ebdffc1f

    fn_2(&mx, 22);
    // output ->
    //  void Myclass::foo(int x) x = 22
    //  this = 0x81ebdffc1f
  }
*/

/*
                          ---------------
                          | std::invoke |
                          ---------------
*/

/*
  #include <functional>   // std::invoke

  int sum(int x, int y, int z)
  {
    std::cout << "::sum(int, int, int)\n";
    return x + y + z;
  }

  int main()
  {
    auto result = std::invoke(sum, 10, 20, 30);
    // output -> ::sum(int, int, int)

    std::cout << "std::invoke(sum, 10, 20, 30) = " 
              << result << '\n';
    // output -> std::invoke(sum, 10, 20, 30) = 60
  }
*/

/*
  #include <cstdio>       // std::puts, std::printf
  #include <functional>   // std::invoke

  class Myclass {
  public:
    int foo(int x)
    {
      std::puts("int Myclass::foo(int x)");
      std::printf("x = %d\n", x);
      std::cout << "this = " << this << '\n';
      return x;
    }
  };

  int main()
  {

    Myclass mx;
    std::cout << "&mx = " << &mx << '\n';
    // output -> &mx = 0x3363bffe4b

    // -------------------------------------------

    std::invoke(&Myclass::foo, mx, 11);  
    // output ->
    //  int Myclass::foo(int x)
    //  x = 11
    //  this = 0x3363bffe4b

    // passing class object as a second argument
    // this pointer will be extracted from that object

    // -------------------------------------------

    auto member_fp = &Myclass::foo;
    std::invoke(member_fp, mx, 22);
    // output ->
    //  int Myclass::foo(int x)
    //  x = 22
    //  this = 0x3363bffe4b

    // passing `this` pointer as a second argument

    // -------------------------------------------

    Myclass* p_mx{ &mx };
    std::invoke(member_fp, p_mx, 33);
    // output ->
    //  int Myclass::foo(int x)
    //  x = 33
    //  this = 0x3363bffe4b

    // passing a pointer to the object
    // this pointer will be extracted from that pointer

    // -------------------------------------------
  }
*/

/*
  class Myclass {
  public:
    void func_1(int x)
    {
      std::cout << "Myclass::func_1(int x), x = " 
                << x << '\n';
    }
    void func_2(int x)
    {
      std::cout << "Myclass::func_2(int x), x = " 
                << x << '\n';
    }
    void func_3(int x)
    {
      std::cout << "Myclass::func_3(int x), x = " 
                << x << '\n';
    }
  };

  void g_func(Myclass mx, int val, void(Myclass::*member_fp)(int))
  {
    (mx.*member_fp)(val);
  }

  int main()
  {
    Myclass mx;

    g_func(mx, 11, &Myclass::func_1);
    // output -> Myclass::func_1(int x), x = 11
    g_func(mx, 22, &Myclass::func_2);
    // output -> Myclass::func_2(int x), x = 22
    g_func(mx, 33, &Myclass::func_3);
    // output -> Myclass::func_3(int x), x = 33
  }
*/

/*
  #include <functional>   // std::invoke

  class Myclass {
  public:
    void func_1(int x)
    {
      std::cout << "Myclass::func_1(int x), x = " 
                << x << '\n';
    }
    void func_2(int x)
    {
      std::cout << "Myclass::func_2(int x), x = " 
                << x << '\n';
    }
    void func_3(int x)
    {
      std::cout << "Myclass::func_3(int x), x = " 
                << x << '\n';
    }
  };

  int main()
  {
    Myclass mx;

    using member_fp_type = void(Myclass::*)(int);

    member_fp_type member_fp_arr[] = {
      &Myclass::func_1,
      &Myclass::func_2,
      &Myclass::func_3,
    };

    for (auto member_fp : member_fp_arr) {
      (mx.*member_fp)(11);
      std::invoke(member_fp, mx, 22);
      // Those 2 lines are equivalent.
    }
    // output ->
    //  Myclass::func_1(int x), x = 11
    //  Myclass::func_1(int x), x = 22
    //  Myclass::func_2(int x), x = 11
    //  Myclass::func_2(int x), x = 22
    //  Myclass::func_3(int x), x = 11
    //  Myclass::func_3(int x), x = 22
  }
*/  

/*
                        ---------------------
                        | function adaptors |
                        ---------------------
*/

/*
                  ---------------------------------
                  | std::bind (function template) |
                  ---------------------------------
*/

/*
  #include <functional>   // std::bind, std::placeholders

  void foo(int x, int y, int z)
  {
    std::cout << "x = " << x << '\n';
    std::cout << "y = " << y << '\n';
    std::cout << "z = " << z << '\n';
    std::cout << "------------------\n";
  }

  int main()
  {
    // std::bind function's first parameter is a callable 
    // its return type is also a callable
    auto fn = std::bind(foo, 10, 20, 30);
    fn();
    // output ->
    //	x = 10
    //	y = 20
    //	z = 30

    using namespace std::placeholders;
    // std::placeholders is a nested namespace.

    // -------------------------------------------------

    auto fn_1 = std::bind(foo, 11, 22, _1);
    fn_1(333);
    // output ->
    //  x = 11
    //  y = 22
    //  z = 333

    // -------------------------------------------------

    auto fn_2 = std::bind(foo, _1, 22, 33);
    fn_2(111);
    // output ->
    //  x = 111
    //  y = 22
    //  z = 33

    // -------------------------------------------------

    auto fn_3 = std::bind(foo, _1, _2, 33);
    fn_3(111, 222);
    // output ->
    //  x = 111
    //  y = 222
    //  z = 333

    // -------------------------------------------------

    auto fn_4 = bind(foo, _1, 22, _2);
    fn_4(111, 333);
    // output ->
    //  x = 111
    //  y = 22
    //  z = 333

    // -------------------------------------------------

    auto f5 = std::bind(foo, _1, _1, _1);
    f5(111);
    // output ->
    //  x = 111
    //  y = 111
    //  z = 111

    // -------------------------------------------------

    auto fn_6 = std::bind(foo, _3, _1, _2);
    fn_6(22, 33, 11);
    // output ->
    //  x = 11
    //  y = 22
    //  z = 33

    // -------------------------------------------------
  }
*/

/*
  #include <vector>
  #include <random>  
  // std::mt19937, std::uniform_int_distribution
  #include <algorithm>  // std::generate, std::copy_if
  #include <functional> 
  // std::bind, std::greater, std::placeholders
  #include <iterator>   // std::back_inserter

  int main()
  {
    std::vector<int> ivec(15);

    std::mt19937 eng;
    std::uniform_int_distribution dist{ 0, 100 };

    std::generate(ivec.begin(), ivec.end(), 
                  [&](){ return dist(eng); });

    for (auto elem : ivec)
      std::cout << elem << ' ';
    // output -> 82 13 91 84 12 97 92 22 63 31 9 55 28 19 55
    std::cout << '\n';

    // -------------------------------------------------

    std::vector<int> dest_vec1;

    const int val_greater = 70;
    auto callable = std::bind(std::greater<int>{}, 
                        std::placeholders::_1, 
                        val_greater);

    std::copy_if( ivec.begin(), ivec.end(), 
                  std::back_inserter(dest_vec1), 
                  callable);
    // callable(*iter) inside copy_if algorithm

    for (auto elem : dest_vec1)
      std::cout << elem << ' ';
    // output -> 82 91 84 97 92
    std::cout << '\n';

    // -------------------------------------------------

    // using lambda expression instead of std::bind
    // for callable

    std::vector<int> dest_vec2;

    std::copy_if( ivec.begin(), ivec.end(), 
                  std::back_inserter(dest_vec2),
                  [val_greater](int i){ return i > val_greater; });

    for (auto elem : dest_vec2)
      std::cout << elem << ' ';
    // output -> 82 91 84 97 92

    // -------------------------------------------------
  }
*/

/*
  #include <functional>   // std::bind, std::placeholders

  void foo(int x, int y, int z)
  {
    std::cout << "x = " << x << '\n';
    std::cout << "y = " << y << '\n';
    std::cout << "z = " << z << '\n';
  }

  int main()
  {
    using namespace std::placeholders;

    // std::bind can be called similar like  
    // instantly invoke lambda expression

    std::bind(foo, 11, _2, _1)(33, 22);
    // output ->
    //  x = 11
    //  y = 22
    //  z = 33
  }
*/

/*
  #include <functional>   // std::bind, std::placeholders

  class Functor {
  public:
    int operator()(int x, int y) const
    {
      return x * x + y * y;
    }
  };

  class Myclass {
  public:
    void foo(int x) const
    {
      std::cout << "x = " << x << '\n';
    }
  };

  int main()
  {
    using namespace std::placeholders;

    // --------------------------------------------------

    auto fn_1 = std::bind(Functor{}, _1, 4);
    auto sum_square = fn_1(3);

    std::cout << "sum_square = " << sum_square << '\n';
    // output -> sum_square = 25

    // --------------------------------------------------

    auto fn_2 = std::bind([](int a, int b){ return a * b; }, 
                          std::placeholders::_1, 4);
    int multiply_val = fn_2(3);

    std::cout << "multiply_val = " << multiply_val << '\n';
    // output -> multiply_val = 12

    // --------------------------------------------------

    Myclass mx;
    auto fn_3 = std::bind(&Myclass::foo, mx, 30);
    fn_3();   // output -> x = 30

    // if a member function wants to be called with std::bind
    // 2nd parameter should be an object or a pointer to an object
    // of that class.

    // --------------------------------------------------

    auto fn_4 = std::bind(&Myclass::foo, _1, 40);
    fn_4(mx);   // output -> x = 40

    // --------------------------------------------------

    Myclass* p_mx{ &mx };
    auto fn_5 = std::bind(&Myclass::foo, p_mx, 50);
    fn_5();     // output -> x = 50

    // --------------------------------------------------
  }
*/

/*
  #include <functional>   
  // std::bind, std::ref, std::placeholders

  void foo(int& i_ref) { ++i_ref; }
  void bar(std::ostream& os, int x) { os << ++x << '\n'; }

  int main()
  {
    int x{ 30 };
    std::cout << "x = " << x << '\n';   // output -> x = 30

    // -----------------------------------------------------

    auto fn_1 = std::bind(foo, x);
    fn_1();

    std::cout << "x = " << x << '\n';   // output -> x = 30
    // std::bind will copy the variable x
    // and foo function's parameter will bind to that copy
    // so x will not be changed.

    // -----------------------------------------------------

    auto fn_2 = std::bind(foo, std::ref(x));
    fn_2();

    std::cout << "x = " << x << '\n';   // output -> x = 31
    // sending reference of "x" to std::bind
    // so foo function's parameter will bind to that reference
    // which means parameter will bind to "x"
    // so x will be changed.

    // -----------------------------------------------------

    auto fn_3 = std::bind(bar, 
                          std::cout, 
                          std::placeholders::_1); // syntax error
    
    // because of std::ostream class is not copyable
    // it will cause a syntax error.

    // -----------------------------------------------------

    auto fn_4 = std::bind(bar, 
                          std::ref(std::cout), 
                          std::placeholders::_1); // VALID
    fn_4(x);  // output -> 32

    // bar function's parameter will bind to global "std::cout"
    // object.

    // -----------------------------------------------------
  }
*/

/*
                          ---------------
                          | std::mem_fn |
                          ---------------
*/

/*
  https://en.cppreference.com/w/cpp/utility/functional/mem_fn
*/

/*
  #include <functional>   // std::mem_fn

  class Myclass {
  public:
    void foo(int x)
    {
      std::cout << "Myclass::foo(int x) x = " << x << '\n';
      std::cout << "this = " << this << '\n';
    }
  };

  int main()
  {
    auto fn = std::mem_fn(&Myclass::foo);

    Myclass mx;
    std::cout << "&mx = " << &mx << '\n';
    // output -> &mx = 0x66771ffb8f

    fn(mx, 11);
    // output ->
    //  Myclass::foo(int x) x = 11
    //  this = 0x66771ffb8f
  }
*/

/*
  #include <vector>
  #include <string>
  #include <cstddef>      // std::size_t
  #include <algorithm>    // std::transform
  #include <functional>   // std::mem_fn

  int main()
  {
    std::vector<std::string> svec{ 
      "hello", "world", "we", "are", "live", "from", "izmir" };

    std::vector<std::size_t> len_vec1(7);
    std::vector<std::size_t> len_vec2(7);

    // --------------------------------------------------

    std::transform( svec.begin(), svec.end(), 
                    len_vec1.begin(), 
                    std::mem_fn(&std::string::size));

    // every std::string object in svec 
    // will call its "size" member function

    for (auto elem : len_vec1)
      std::cout << elem << ' ';
    // output -> 5 5 2 3 4 4 5

    std::cout << '\n';

    // --------------------------------------------------

    std::transform( svec.begin(), svec.end(), 
                    len_vec2.begin(),
                    [](const std::string& str){
                      return str.size(); 
                    });

    // every std::string object in svec 
    // will call its "size" member function

    for (auto elem : len_vec2)
      std::cout << elem << ' ';
    // output -> 5 5 2 3 4 4 5

    // --------------------------------------------------
  }
*/

/*
                          ---------------
                          | std::not_fn |
                          ---------------
*/

/*
  https://en.cppreference.com/w/cpp/utility/functional/not_fn
*/

/*
  #include <functional>   // std::not_fn

  bool is_even(int x)
  {
    return x % 2 == 0;
  }

  int main()
  {
    std::cout << std::boolalpha;

    int ival{ 11111 };

    // ------------------------------------------

    std::cout << is_even(ival) << '\n';       // output -> false
    std::cout << is_even(ival + 1) << '\n';   // output -> true

    // ------------------------------------------

    auto not_fn1 = std::not_fn(is_even);

    std::cout << not_fn1(ival) << '\n';       // output -> true
    std::cout << not_fn1(ival + 1) << '\n';   // output -> false

    // ------------------------------------------

    // `std::not_fn` function adaptor gets a callable 
    // as a parameter and returns a callable.

    // the callable that `std::not_fn` returns, 
    // will be the logical not value of the result 
    // that it normally returns.

    // is_even(1)               returns false  
    // std::not_fn(is_even)(1)  returns true

    // ------------------------------------------
  }
*/

/*
  #include <vector>
  #include <random>     
  // std::mt19937, std::uniform_int_distribution  
  #include <algorithm>      // std::generate, std::count_if
  #include <functional>     // std::not_fn

  bool is_even(int x)
  {
    return x % 2 == 0;
  }

  int main()
  {
    std::mt19937 eng;
    std::uniform_int_distribution dist{ 0, 10000 };

    std::vector<int> ivec(5000);
    std::generate(ivec.begin(), ivec.end(), 
                  [&]{ return dist(eng); });

    // -----------------------------------------------

    std::cout << "odd count = " <<
      std::count_if(ivec.begin(), ivec.end(), 
                  [](int x){ return !is_even(x); }) << '\n';
    // output -> odd count = 2475

    // -----------------------------------------------

    std::cout << "odd count = " <<
      std::count_if(ivec.begin(), ivec.end(), 
                    std::not_fn(is_even)) << '\n';
    // output -> odd count = 2475

    // -----------------------------------------------
  }
*/