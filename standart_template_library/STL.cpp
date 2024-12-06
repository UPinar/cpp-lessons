#include <iostream>

/*
                ===================================
                | Standart Template Library (STL) |
                ===================================
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
          --------------------------------------------------
          | std::bind function adaptor (function template) |
          --------------------------------------------------
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

    // ----------------------------------------------------

    // class member functions is not same, different syntax

    // ----------------------------------------------------
  }
*/

// -----------------------------------------------------
// -----------------------------------------------------
// -----------------------------------------------------
// -----------------------------------------------------
// -----------------------------------------------------

/*
  // how structure binding is working

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

// -------------------------------------------------------
// -------------------------------------------------------
// -------------------------------------------------------
// -------------------------------------------------------
// -------------------------------------------------------

// TODO : CONTINUE FIXING FROM HERE

// std::function son ornek member function pointerlar
// ile alakali, sonradan duzenleme yapilabilir.

/*
                    ----------------------------
                    | member function pointers |
                    ----------------------------
*/

/*
  class Myclass {
  public:
    static int foo(int);
    int baz(int);
  };

  int bar(int);

  int main()
  {
    auto f = [](int a) {return a * 5; };

    int(*fp)(int);

    fp = &bar;
    fp = &Myclass::foo;	// static member function
    fp = f;				// stateless lambda

    fp = &Myclass::baz;	// syntax error.
    // non-static member functions does have this pointer(hidden parameter)

    auto fp1 = &Myclass::baz;
    int(Myclass::* fp1)(int) = &Myclass::baz;
    // These 2 lines are same
  }
*/

/*
  int foo(int);

  using ftype = int (*)(int);

  int main()
  {
    auto fp1 = &foo;
    auto fp2 = foo;
    int (*fp3)(int) = &foo;
    ftype fp4 = &foo;
    // Those 4 lines are same.
  }
*/

/*
  int f1(int);
  int f2(int);
  int f3(int);
  int f4(int);
  int f5(int);

  using fptype = int (*)(int);

  int main()
  {
    fptype fp_arr[] = { f1, f2, f3, f4, f5 };
  }
*/

/*
  int f1(int);
  int f2(int);
  int f3(int);
  int f4(int);
  int f5(int);

  using fptype = int (*)(int);

  int main()
  {
    auto f = f1;
    // type deduction for auto is int(*)(int) which is a function pointer

    auto& r = f1;
    // type deduction for auto is int(int) which is a function itself.
    int(&r2)(int) = f1;	// same line as [auto& r = f1]
  }
*/

/*
  // there is no type difference between global foo() and static member bar() functions.
  // static member functions did not have this pointer.

  #include <type_traits>

  int foo(int);

  class Myclass {
  public:
    static int bar(int);
  };

  int main()
  {
    auto f1 = foo;
    auto f2 = Myclass::bar;

    std::is_same_v<decltype(f1), decltype(f2)>;	// true[compile time]
  }
*/

/*
  int foo(int);

  class Myclass {
  public:
    int bar(int);
    double baz(int, int);
  };

  int main()
  {
    auto f1 = foo;

    int(*f2)(int) = Myclass::bar;	// syntax error
    // non-static member functions are not implicitly convert
    // from function to function pointer.

    int(Myclass::* f2)(int) = &Myclass::bar;
    double (Myclass::* f3)(int, int) = &Myclass::baz;
  }
*/

/*
  class Myclass {
  public:
    int foo(int);
    int bar(int);
    int baz(int);
  };

  using mftype = int (Myclass::*)(int);

  int main()
  {
    int(Myclass:: * mf_arr2[3])(int) = {
      &Myclass::bar,
      &Myclass::foo,
      &Myclass::baz,
    };

    mftype mf_arr2[] = {
      &Myclass::bar,
      &Myclass::foo,
      &Myclass::baz, };
  }
*/

/*
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
    Myclass m;

    std::cout << "&m = " << &m << '\n';
    m.foo(45);

    // output ->
    //	&m = 00BCF9E7
    //	int Myclass::foo(int x)
    //	x = 45
    //	this = 00BCF9E7

    auto fp = &Myclass::foo;
    // int (Myclass:: * fp)(int) = &Myclass::foo;

    // [.*] -> member function pointer selection operator
    (m.*fp)(34);
    // output ->
    //	int Myclass::foo(int x)
    //	x = 34
    //	this = 00BCF9E7
  }
*/

/*
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
    Myclass m;
    Myclass* p{ &m };

    auto fp = &Myclass::foo;

    ((*p).*fp)(34);	// verbose
    // can be used to call a member function if we have a pointer to an object.
    // output ->
    //	int Myclass::foo(int x)
    //	x = 34
    //	this = 007AFD57

    (p->*fp)(44);
    // output ->
    //	int Myclass::foo(int x)
    //	x = 44
    //	this = 007AFD57
  }
*/

/*
  #include <functional>

  int sum(int x, int y, int z)
  {
    std::cout << "sum(int, int, int)\n";
    return x + y + z;
  }

  int main()
  {
    auto result = std::invoke(sum, 10, 20, 30);
    // output -> sum(int, int, int)

    std::cout << "std::invoke(sum, 10, 20, 30) = " << result << '\n';
    // output -> std::invoke(sum, 10, 20, 30) = 60
  }
*/

/*
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
    using namespace std;

    Myclass m;
    cout << "&m = " << &m << '\n';
    // output -> &m = 004FFB93

    invoke(&Myclass::foo, m, 12);
    // output ->
    //	int Myclass::foo(int x)
    //	x = 12
    //	this = 004FFB93

    auto fptr = &Myclass::foo;
    invoke(fptr, m, 13);
    // output ->
    //	int Myclass::foo(int x)
    //	x = 13
    //	this = 004FFB93

    Myclass* ptr{ &m };
    invoke(fptr, ptr, 14);
    // output ->
    //	int Myclass::foo(int x)
    //	x = 14
    //	this = 004FFB93
  }
*/

/*
  class Myclass {
  public:
    int foo(int x);
    int bar(int x);
    int baz(int x);
  };

  void g(Myclass m, int val, int (Myclass::*fp)(int))
  {
    (m.*fp)(val);
  }

  int main()
  {
    Myclass mx;

    g(mx, 20, &Myclass::baz);
    g(mx, 20, &Myclass::bar);
    g(mx, 20, &Myclass::foo);
    // client can declare which member function will be called.
  }
*/

/*
  #include <functional>

  class Myclass {
  public:
    int foo(int x)
    {
      std::cout << "Myclass::foo(int)\n";
      return 1;
    }
    int bar(int x)
    {
      std::cout << "Myclass::bar(int)\n";
      return 2;
    }
    int baz(int x)
    {
      std::cout << "Myclass::baz(int)\n";
      return 3;
    }
  };


  int main()
  {
    Myclass mx;

    using ftype = int(Myclass::*)(int);

    ftype arr[] = {
      &Myclass::foo,
      &Myclass::bar,
      &Myclass::baz,
    };

    for (auto fp : arr)
    {
      (mx.*fp)(12);
      std::invoke(fp, mx, 13);
      // Those 2 lines acts same
    }
    // output ->
    //	Myclass::foo(int)
    //	Myclass::bar(int)
    //	Myclass::baz(int)
  }
*/

/*
  class Myclass {
  public:
    int foo(int x)
    {
      std::cout << "Myclass::foo(int)\n";
      return 1;
    }
    int bar(int x)
    {
      std::cout << "Myclass::bar(int)\n";
      return 2;
    }

    void func()
    {
      ((*this).*mfp)(10);
    }

    void set_mfp(int (Myclass::* f)(int))
    {
      mfp = f;
    }
  private:
    int (Myclass::* mfp)(int) {&Myclass::foo};
  };


  int main()
  {
    Myclass mx;
    mx.func();	// output -> Myclass::foo(int)

    mx.set_mfp(&Myclass::bar);
    mx.func();	// output -> Myclass::bar(int)
  }
*/

/*
  ------------------------
  | data member pointers |
  ------------------------
*/

/*
  #include <functional>

  struct Point {
    int mx, my, mz;
  };

  int main()
  {
    Point p = { 35, 56, 90 };
    auto x = &p.my;
    // x's type is int* (pointer to int)

    auto dmptr = &Point::mx;			// data member pointer
    //int Point::* dmptr = &Point::mx;
    // Those 2 lines are same.

    std::cout << p.*dmptr << '\n';	// output -> 35

    p.*dmptr = 90;	// [p.*dmptr] is an L value expression
    std::cout << "p.mx = " << p.mx << '\n';	// output -> p.mx = 90

    std::invoke(dmptr, p) = 888;
    std::cout << "p.mx = " << p.mx << '\n';	// output -> p.mx = 888
  }
*/

/*
  #include <functional>

  struct Point {
    int mx, my, mz;
  };

  void func(Point& p, int Point::*mp)
  {
    p.*mp = 555;
  }

  int main()
  {
    Point mypoint = { 44, 77, 99 };

    func(mypoint, &Point::mx);
    func(mypoint, &Point::my);
    func(mypoint, &Point::mz);
    // client can declare which data member will be used.
  }
*/

/*
  #include <functional>

  int main()
  {
    using namespace std;

    function<double(double)> f;

    cout << (f ? "not empty" : "empty") << '\n';	// output -> empty

    f = [](double dval) {return dval * dval; };
    cout << (f ? "not empty" : "empty") << '\n';	// output -> not empty
  }
*/

/*
  #include <functional>

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
    using namespace std;

    function<void(Myclass&, int)> f1 = &Myclass::foo;
    function<void(Myclass*, int)> f2 = &Myclass::foo;

    Myclass m;
    cout << "&m = " << &m << '\n';	// output -> &m = 00AFF687

    f1(m, 10);
    f2(&m, 22);
    // output ->
    //	void Myclass::foo(int x) x = 10
    //	this = 00AFF687
    //	void Myclass::foo(int x) x = 22
    //	this = 00AFF687
  }
*/

/*
  #include <functional>

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
    using namespace std;

    auto fn = mem_fn(&Myclass::foo);

    Myclass m;
    cout << "&m = " << &m << '\n';	// output -> &m = 00F3FA3B

    fn(m, 12);
    // output ->
    //	Myclass::foo(int x) x = 12
    //	this = 00F3FA3B
  }
*/

/*
  #include <vector>
  #include <string>
  #include <algorithm>
  #include <functional>

  int main()
  {
    using namespace std;

    vector<string> svec{ "hello", "world", "we", "are", "live", "from", "izmir" };
    vector<size_t> len_vec(7);
    vector<size_t> len_vec2(7);

    transform(svec.begin(), svec.end(), len_vec.begin(), mem_fn(&string::size));
    // every string object in svec will call its size() member function

    transform(svec.begin(), svec.end(), len_vec2.begin(),
                [](const string& str) {return str.size(); });
    // can be done by a lamda expression too..

    for (auto len : len_vec)
      cout << len << ' ';
    cout << '\n';
    // output -> 5 5 2 3 4 4 5

    for (auto len : len_vec2)
      cout << len << ' ';
    cout << '\n';
    // output -> 5 5 2 3 4 4 5
  }
*/

/*
  #include <functional>

  bool is_even(int x)
  {
    return x % 2 == 0;
  }

  int main()
  {
    using namespace std;

    int ival{ 34546 };
    cout << boolalpha;

    cout << is_even(ival) << '\n' << is_even(ival + 1) << '\n';
    // output ->
    //	true
    //	false

    auto fn = not_fn(is_even);
    cout << fn(ival) << '\n' << fn(ival + 1) << '\n';
    // output ->
    //	false
    //	true

    // not_fn adaptor gets a callable as a parameter and returns a callable.
    // the callable that not_fn() returns, will have a logical not of the result that it normally returns.
    // is_even(1) normally returns false but not_fn(is_even)(1) returns true
  }
*/

/*
  #include <algorithm>
  #include <functional>
  #include <random>
  #include <vector>

  bool is_even(int x)
  {
    return x % 2 == 0;
  }

  int main()
  {
    using namespace std;

    mt19937 eng;
    uniform_int_distribution dist{ 0, 10000 };

    vector<int> ivec(5000);
    generate(ivec.begin(), ivec.end(), [&] {return dist(eng); });

    cout << "count of odd : " <<
      count_if(ivec.begin(), ivec.end(), [](int x) { return !is_even(x); }) << '\n';
    // output -> count of odd : 2475

    cout << "count of odd : " <<
      count_if(ivec.begin(), ivec.end(), not_fn(is_even)) << '\n';
    // output -> count of odd : 2475
  }
*/

/*
  ------------------------------
  | std::move_iterator adaptor |
  ------------------------------
*/

/*
  #include <string>
  #include <vector>
  #include <iterator>

  class Myclass {
  public:
    Myclass() = default;
    Myclass(const Myclass&)
    {
      std::cout << "copy ctor\n";
    }
    Myclass(Myclass&&)
    {
      std::cout << "move ctor\n";
    }
    Myclass& operator=(const Myclass&)
    {
      std::cout << "copy assignment\n";
      return *this;
    }
    Myclass& operator=(Myclass&&)
    {
      std::cout << "move assignment\n";
      return *this;
    }
  };

  template <typename Iter>
  std::move_iterator<Iter> MakeMoveIterator(Iter it)
  {
    return std::move_iterator<Iter>{it};
  }

  int main()
  {
    using namespace std;

    vector<string> svec{ "hello_world", "we_are_live", "from_Izmir" };

    auto iter = svec.begin();
    auto s = *iter;	// copy ctor
    cout << "length = " << svec[0].length() << '\n'; // output -> length = 11
    // did not moved, it is copied.

    auto s2 = std::move(*iter);
    cout << "length = " << svec[0].length() << '\n'; // output -> length = 0
    // it is moved

    *iter = "hello world";
    for (auto str : svec)
      cout << str << ' ';
    cout << '\n';
    // output -> hello world we_are_live from_Izmir

    move_iterator<vector<string>::iterator> move_iter{ svec.begin() };
    auto s3 = *move_iter;
    cout << "length = " << svec[0].length() << '\n'; // output -> length = 0
    // element is moved.


    vector<Myclass> my_vec(100);
    move_iterator <vector<Myclass>::iterator> vec_iter{ my_vec.begin() };
    Myclass x = *vec_iter;	// output -> move ctor

    auto iter_end = MakeMoveIterator(my_vec.end());
    // iter_end's type is std::move_iterator<std::vector<Myclass>::iterator>

    auto s4 = *make_move_iterator(my_vec.begin());	// output -> move ctor
    // STL make_move_iterator function template
  }
*/

/*
  #include <vector>
  #include <iterator>
  #include <algorithm>

  class Myclass {
  public:
    Myclass() = default;

    Myclass(const Myclass&)
    {
      std::cout << "copy ctor\n";
    }
    Myclass(Myclass&&)
    {
      std::cout << "move ctor\n";
    }
    Myclass& operator=(const Myclass&)
    {
      std::cout << "copy assignment\n";
      return *this;
    }
    Myclass& operator=(Myclass&&)
    {
      std::cout << "move assignment\n";
      return *this;
    }
  };

  int main()
  {
    using namespace std;

    vector<Myclass> x(10);
    vector<Myclass> y(10);

    copy(x.begin(), x.end(), y.begin());
    // copy assignment will be called for 10 times

    copy(make_move_iterator(x.begin()), make_move_iterator(x.end()), y.begin());
    // move assignment will be called for 10 times

    std::move(x.begin(), x.end(), y.begin());
    // move assignment will be called for 10 times
    // std::move() is an STL algorithm in <algorithm> header
  }
*/

/*
  --------------
  | std::tuple |
  --------------
*/

/*
  #include <tuple>
  #include <string>

  enum {age, wage, name};

  int main()
  {
    using namespace std;

    tuple<int, double, string> tx{ 12, 4.5, "hello"};
    tuple{ 12, 4.5, "hello" };	// CTAD(C++17)

    get<0>(tx) = 16;
    // returns a reference to 0'th index element in tx tuple

    cout << get<0>(tx) << '\n';	// output -> 16

    get<2>(tx) += " world";
    cout << get<2>(tx) << '\n';	// output -> hello world

    get<3>(tx);					// syntax error
    // will be a compile time error not run-time error.

    int index = 2;
    get<index>(tx);				// syntax error
    // compile time error nttp has to be constant expression

    const int c_index = 1;
    get<c_index>(tx);			// legal

    get<double>(tx) = 10.2;
    cout << get<1>(tx) << '\n';	// output -> 10.2


    tuple tx2{ 12, 4.5, 44 };
    get<int>(tx2) = 17;			// ambiguity error
    // there are 2 int in tx2 tuple.


    get<wage>(tx) = 99.9;
    cout << get<1>(tx) << '\n';	// output -> 99.9
  }
*/

/*
  #include <tuple>

  template <typename ...Args>
  auto MakeTuple(Args&& ...args)
  {
    return std::tuple(std::forward<Args>(args)...) {};
  }

  int main()
  {
    using namespace std;
    auto tp = make_tuple(12, 6.76, "Hello world"s);
    // tp's type is std::tuple<int, double, std::string>

    auto tp2 = MakeTuple(12, 6.76, 9L);
    // tp2's type is std::tuple<int, double, long>
  }
*/

/*
  #include <tuple>
  #include <string>

  using namespace std;

  auto foo()
  {
    return tuple{ 82, 5.3, string{"live izmir"} };
  }

  int main()
  {
    tuple tx{ 12, 8.2, string{"hello world"} };

    auto& [age, height, name] = tx;
    // structured binding

    age = 28;
    cout << get<0>(tx) << '\n';	// output -> 28

    auto [x, y, z] = foo();

    std::cout << z << '\n';		// output -> live izmir
  }
*/

/*
  #include <tuple>
  #include <string>
  #include <vector>

  using Person = std::tuple<int, double, std::string>;

  int main()
  {
    using namespace std;
    vector<Person> pvec{ {10, 2.3, "hello"}, {99,6.3, "world"} };

    pvec.emplace_back(18, 8.5, "izmir");

    for (auto item : pvec)
    {
      cout << get<0>(item) << ' ';
      cout << get<1>(item) << ' ';
      cout << get<2>(item) << '\n';
    }
    // output ->
    //	10 2.3 hello
    //	99 6.3 world
    //	18 8.5 izmir

    // using structured binding
    for (const auto& [x, y, z] : pvec)
    {
      cout << x << ' ';
      cout << y << ' ';
      cout << z << '\n';
    }
    // output ->
    //	10 2.3 hello
    //	99 6.3 world
    //	18 8.5 izmir
  }
*/

/*
  // comparison in tuple

  #include <tuple>
  #include <random>
  #include <algorithm>
  #include <vector>

  using My_tuple = std::tuple<int, int, int>;

  int main()
  {
    using namespace std;

    vector<My_tuple> tvec;

    mt19937 eng;
    uniform_int_distribution dist1{ 0, 10 };
    uniform_int_distribution dist2{ 0, 20 };
    uniform_int_distribution dist3{ 0, 30 };

    for (int i = 0; i < 1000; ++i)
    {
      tvec.emplace_back(dist1(eng), dist2(eng), dist3(eng));
    }

    sort(tvec.begin(), tvec.end());

    for (const auto& [x, y, z] : tvec)
    {
      cout << x << ' ';
      cout << y << ' ';
      cout << z << '\n';
    }

    // output ->
    //	0 0 4
    //	0 0 9
    //	0 0 12
    //	0 0 18
    //	0 0 18
    //	0 0 30
    //	0 1 2
    //	0 1 7
    //	0 1 21
    //	0 1 27
    //	0 2 0
    //	0 2 1
    //	0 2 12
    //	0 2 24
  }
*/

/*
  #include <tuple>

  std::tuple<int, std::string, double> foo()
  {
    return { 99, "yes", 15.3 };
  }

  int main()
  {
    using namespace std;

    int x{};
    string str{};
    double d{};

    auto tp = tie(x, str, d);
    // tp's type is std::tuple<int&, std::string&, double&>

    tie(x, str, d) = foo();
    // tp = foo();

    cout << x << '\n';		// output -> 99
    cout << str << '\n';	// output -> yes
    cout << d << '\n';		// output -> 15.3
  }
*/

/*
  #include <tuple>
  #include <utility>

  int main()
  {
    int x = 10;
    int y = 34;

    std::tie(y, x) = std::pair{ x,y };

    std::cout << "x = " << x << '\n';	// output -> x = 34
    std::cout << "y = " << y << '\n';	// output -> y = 10
  }
*/

/*
  #include <tuple>
  #include <string>

  std::tuple<int, double, std::string> foo();

  int main()
  {
    using namespace std;

    int ival{};
    double dval{};
    string str{};

    tie(std::ignore, dval, str) = foo();
    // we can use std::ignore if we do not want to use that variable.

    auto [_, dval, str] = foo();
    // we do need to crate a variable even if
    // we are not going to use it in structured binding.

    auto [_, k, l] = foo();	// syntax error
    // we already used a variable called '_'

    auto [__, x, y] = foo();
  }
*/

/*
  #include <tuple>

  int main()
  {
    using namespace std;

    int x = 1, y = 2, z = 3;

    //	int temp = x;
    //	x = y;
    //	y = z;
    //	z = temp;
    // instead of this code we can use std::tie

    tie(x, y, z) = tuple{ y, z, x };
    cout << x << y << z << '\n';	// output -> 231
  }
*/

/*
  #include <tuple>

  class Date {
  public:
    Date(int y, int m, int d) : m_year{ y }, m_mon{ m }, m_day{ d } {}

    friend bool operator<(const Date& d1, const Date& d2)
    {
      return std::tuple(d1.m_year, d1.m_mon, d1.m_day) < std::tuple(d2.m_year, d2.m_mon, d2.m_day);
      // In tuple, comparison starts from first elem,
      // if same then second, still same then third ...
    }
  private:
    int m_year;
    int m_mon;
    int m_day;
  };
*/

/*
  --------------
  | std::apply |
  --------------
*/

/*
  #include <tuple>

  void print(int x, int y, int z)
  {
    std::cout << x << ' ' << y << ' ' << z << '\n';
  }

  void double_it(int& x, int& y, int& z)
  {
    x *= 2;
    y *= 2;
    z *= 2;
  }

  int main()
  {
    using namespace std;

    tuple tx{ 4,6,9 };

    apply(print, tx);							// output -> 4 6 9
    print(get<0>(tx), get<1>(tx), get<2>(tx));	// output -> 4 6 9
    // Those 2 lines acts like same.

    apply(double_it, tx);
    apply(print, tx);							// output -> 8 12 18
  }
*/

/*
  #include <tuple>

  template <typename ...Ts>
  std::ostream& operator<<(std::ostream& os, const std::tuple<Ts...>& tx)
  {
    std::apply
    (
      [&os](const Ts& ...tupleArgs)
      {
        os << '[';
        std::size_t n{ 0 };
        ((os << tupleArgs << (++n != sizeof...(Ts) ? ", " : "")), ...);	// binary fold expression
        os << ']';
      }, tx
    );
    return os;
  }

  int main()
  {
    std::cout << std::tuple{ 43, 5.6, "hello", 'A' } << '\n';
  }
*/

/*
  // tuple_size and tuple_element are meta functions in tuple interface

  #include <tuple>
  #include <array>

  using tp_type = std::tuple<int, double, long>;
  using arr_type = std::array<double, 5>;

  int main()
  {
    using namespace std;

    constexpr auto val = tuple_size<tp_type>::value;
    constexpr auto val2 = tuple_size_v<tp_type>;		// variable template
    // Those 2 lines are same
    // vals value is equal to element count in tuple

    constexpr auto val3 = tuple_size_v<arr_type>;
    // val3 equals to 5

    // tuple_size can be used for std::pair, std::array and std::tuple.(tuple interface)

    tuple_element<1, tp_type>::type x{};	// x's type is double
    tuple_element_t<0, tp_type> y{};		// y's type is int
    // alias template
  }
*/

/*
  ----------------------------
  | sorted ranged algorithms |
  ----------------------------
*/

/*
  #include <vector>
  #include <string>
  #include "../headers/nutility.h"

  int main()
  {
    using namespace std;

    vector<string> svec;

    for (int i = 0; i < 5; ++i) {
      auto town = rtown();
      auto iter = lower_bound(svec.begin(), svec.end(), town);

      svec.insert(iter, std::move(town));
      print(svec);
    }
    // output ->
    //	sivas
    //	sivas tunceli
    //	kirikkale sivas tunceli
    //	elazig kirikkale sivas tunceli
    //	denizli elazig kirikkale sivas tunceli
  }
*/

/*
  #include <vector>
  #include <string>
  #include "../headers/nutility.h"

  int main()
  {
    using namespace std;

    vector<string> svec{"aaa", "bbb", "ccc", "ddd", "ddd", "ddd", "eee"};

    auto [iter_lower, iter_upper] = equal_range(svec.begin(), svec.end(), "ddd");

    cout << "index lower_bound = " << distance(svec.begin(), iter_lower) << '\n';
    cout << "index upper_bound = " << distance(svec.begin(), iter_upper) << '\n';
    // output ->
    //	index lower_bound = 3
    //	index upper_bound = 6
  }
*/

/*
  #include <vector>
  #include <list>
  #include "../headers/nutility.h"

  int main()
  {
    using namespace std;

    vector<int> ivec;
    list<int> ilist;

    rfill(ivec, 20, Irand{ 0, 100 });
    rfill(ilist, 20, Irand{ 0, 100 });

    sort(ivec.begin(), ivec.end());
    ilist.sort();

    print(ivec);
    // output -> 4 11 11 13 16 20 26 27 32 34 37 37 68 69 78 82 84 94 97 99
    print(ilist);
    // output -> 6 9 11 15 28 29 32 37 45 49 56 62 65 68 70 72 75 93 94 96

    // vector and list both have
    set_intersection(ivec.begin(), ivec.end(), ilist.begin(), ilist.end(), ostream_iterator<int>{cout, " "});
    // output -> 11 32 37 68 94
    std::cout << '\n';

    // all of the vector and list have
    set_union(ivec.begin(), ivec.end(), ilist.begin(), ilist.end(), ostream_iterator<int>{cout, " "});
    // output -> 4 6 9 11 11 13 15 16 20 26 27 28 29 32 34 37
    //				37 45 49 56 62 65 68 69 70 72 75 78 82 84 93 94 96 97 99
    std::cout << '\n';

    // vector have but list does not have
    set_difference(ivec.begin(), ivec.end(), ilist.begin(), ilist.end(), ostream_iterator<int>{cout, " "});
    // output -> 4 11 13 16 20 26 27 34 37 69 78 82 84 97 99
    std::cout << '\n';

    // (all of the vector and list have) - (vector and list both have)
    set_symmetric_difference(ivec.begin(), ivec.end(), ilist.begin(), ilist.end(), ostream_iterator<int>{cout, " "});
    // output -> 4 6 9 11 13 15 16 20 26 27 28 29 34 37
    //				45 49 56 62 65 69 70 72 75 78 82 84 93 96 97 99
  }
*/

/*
  #include <vector>
  #include <algorithm>

  int main()
  {
    using namespace std;

    vector<int> ivec{ 2, 5, 7, 9, 13, 45, 89, 90, 123, 567 };
    vector<int> ivec_2{ -2, 5, -7, 9, -13, -45, -89, 90, -123, 567 };

    int ival{45};
    if (binary_search(ivec.begin(), ivec.end(), ival))
      cout << "the value : " << ival << " is exists in vector\n";
    else
      cout << "the value : " << ival << " is not exists in vector\n";
    // output -> the value : 45 is exists in vector

    if (binary_search(ivec.begin(), ivec.end(), ival, [](int x, int y) {
      return abs(x) < abs(y);
      }))
      cout << "the value : " << ival << " is exists in vector\n";
    else
      cout << "the value : " << ival << " is not exists in vector\n";
    // the value : 45 is exists in vector
    // (-45) exists in the vector not 45.
  }
*/

/*
  ------------------------------
  | structured binding / C++17 |
  ------------------------------
  generally used for tuple-like classes
*/

/*
  int main()
  {
    using namespace std;

    int ar[] = { 3, 6, 9 };
    auto [x, y, z] = ar;
    cout << x << y << z << '\n';	// output -> 369

    x += 2;	// x is not a reference to ar[0]
    cout << ar[0] << '\n';			// output -> 3

    auto& [k, l, m] = ar;
    ++k;	// k is a reference to ar[0] because of auto&
    cout << ar[0] << '\n';			// output -> 4

    ar[0] = ar[1] = ar[2] = 0;
    cout << x << y << z << '\n';	// output -> 569
    cout << k << l << m << '\n';	// output -> 000
  }
*/

/*
  int main()
  {
    using namespace std;

    int ar[] = { 3, 6, 9 };
    int ar2[] = { 1, 2, 3 };

    auto [x, y, _] = ar;
    auto [a, b, _] = ar2;
    // error C2374: '_': redefinition; multiple initialization
    // error C2386: '_': a symbol with this name already exists in the current scope
  }
*/

/*
  #include <string>

  struct Mystruct {
    int a, b;
    std::string str;
  };

  Mystruct foo()
  {
    return { 4, 6, "hello world" };
  }

  int main()
  {
    using namespace std;

    auto [a, b, name] = foo();

    cout << name << " " << a << " " << b << '\n';
    // output -> hello world 4 6
  }
*/

/*
  #include <string>

  class Myclass {
  public:
    Myclass(int x, int y, std::string s) : a(x), b(y), str(s) {}
  private:
    friend void func();
    int a, b;
    std::string str;
  };

  Myclass foo()
  {
    return { 4, 6, "hello world" };
  }

  void func()
  {
    auto [a, b, str] = foo();	// valid after C++17
  }

  int main()
  {
    using namespace std;

    auto [a, b, name] = foo();	// syntax error
    // because of data members of class is in private section.
    // Error E2845	cannot bind to non - public member "Myclass::a"
  }
*/

/*
  #include <string>

  struct Mystruct {
    int a, b;
    std::string str;
  };

  Mystruct foo()
  {
    return { 4, 6, "hello world" };
  }

  int main()
  {
    using namespace std;

    auto [a, b, str] = foo();

    auto fn = [=]() { return a + b; };
    // capturing structure binding object in lambda expressions
    // is not valid before C++20.
  }
*/

/*
  #include <array>
  #include <tuple>

  int main()
  {
    using namespace std;

    array<int, 3> ar{ 1, 5, 9 };
    auto [x, y, z] = ar;
    // array is applicable to tuple-like api
    //	1. tuple_element
    //	2. tuple_size
    //	3. get() function template

    tuple_element<1, decltype(ar)>::type;	// type int
    tuple_element_t<1, decltype(ar)>;		// type int

    using tp = tuple<int, double, long, long long>;
    tuple_element_t<2, tp>;					// type long

    using mypair = pair<int, double>;

    tuple_size<decltype(ar)>::value;	// size_t 3 unsigned int
    tuple_size<tp>::value;				// size_t 4 unsigned int
    tuple_size_v<mypair>;				// size_t 2 unsigned int

    tp x{0,2.3,10L, 11LL};

    get<0>(ar);
  }
*/

/*
  #include <string>

  class Person {
  public:
    Person(std::string name, std::string surname) :
      m_name{std::move(name)}, m_surname{std::move(surname)} {}

    std::string get_name() const { return m_name; }
    std::string get_surname() const { return m_surname; }

    std::string m_name;
    std::string m_surname;
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

  template <std::size_t n>
  auto get(const Person& p)
  {
    if constexpr (n == 0)
      return p.get_name();
    else if constexpr (n == 1)
      return p.get_surname();
  }

  int main()
  {
    using namespace std;

    Person per{ "Hello", "World" };
    auto [x, y] = per;

    std::cout << x << ' ' << y << '\n';
  }
*/

/*
  #include <type_traits>

  struct Mystruct {
    int a[5]{};
    double b[10]{};
  };

  int main()
  {
    Mystruct ms;

    auto [p1, p2] {ms};

    std::cout << sizeof(p1) << ' ' << sizeof(p2) << '\n';
    // output -> 20 80

    constexpr auto b = std::is_same_v<decltype(p1), int[5]>;
    // b is true

    // arrays are not decaying to pointers.
  }
*/

/*
  struct Mystruct {
    Mystruct() = default;
    Mystruct(const Mystruct&) {
      std::cout << "Mystruct copy ctor\n";
    }

    ~Mystruct()
    {
      std::cout << "D";
    }
    int a{}, b{}, c{};
  };

  int main()
  {
    Mystruct ms;

    auto [x, y, z] = ms;
    // output -> Mystruct copy ctor
    // compiler will copy Mystruct class object then use its data members
    // in structured binding as structure binding objects.

    // output -> DD
    // because of Mystruct object has been copied, at the end of the main scope
    // they both will be destroyed.
  }
*/

/*
  struct Mystruct {
    int a[5]{};
    double b[10]{};
  };

  int main()
  {
    Mystruct ms;

    auto [p1, p2] {ms};
    // because of Mystruct will be copied.
    // p1 and p2 are the data members of copied Mystruct.
    // which are int[5] and double[10]
  }
*/

/*
  struct Mystruct {
    int a{}, b{};
  };

  int main()
  {
    Mystruct ms;

    // both are universal references and reference collapsion rule applied.
    auto&& [x, y] = ms;				// & - && -> &
    auto&& [a, b] = Mystruct{};		// && - && -> &&
  }
*/

/*
  struct Mystruct {
    char str[20]{ "hello" };
    int a{};
  };

  int main()
  {
    Mystruct ms;

    auto [a, s] = ms;
    // s's type is char[20]
    auto b = s;
    // b's type is char* because of array decays to pointer
  }
*/

/*
  ------------------
  | decltype(auto) |
  ------------------
*/

/*
  template <typename T>
  decltype(auto) foo(T& x)
  {
    return x;
    // x's type is int&
    // decltype(auto)'s type is same as decltype(x)'s type which is int&
  }

  decltype(auto) bar(int x)
  {
    return (x);		// Undefined Behaviour
    // x's type is int
    // decltype(x)'s type is int
    // decltype((x))'s type is int&
    // decltype(auto)'s type(return type) will be int&

    // after scope ends x will be destroyed,
    // and the reference to x will become dangling.
  }

  int main()
  {
    int y = 10;
    double l = 2.3;

    decltype(y);
    decltype(auto) x = y;
    decltype(auto) z = (y);
    decltype(auto) t = std::move(y);

    // when we apply decltype() to y, (y), std::move(y)
    // which type we get will be the type of decltype(auto)
    // decltype(y) -> int					-> decltype(auto) -- x -> int
    // decltype((y)) -> int&				-> decltype(auto) -- z -> int&
    // decltype(std::move(y)) -> int&&		-> decltype(auto) -- t -> int&&
  }
*/

/*
  ------------------------------
  | std::bitset class template |
  ------------------------------
  // generally used in embedded system and system programming
*/

/*
  template <std::size_t n>	// NTTP(Non Type Template Parameter)
  class Bitset {

  };
  // zero cost abstraction will be applied.
*/

/*
  #include <bitset>

  int main()
  {
    using namespace std;

    bitset<8> bs;
    cout << bs << '\n';	// output -> 00000000
    // inserter function

    bitset<32> bs2(872345u);
    cout << bs2 << '\n';	// output -> 00000000000011010100111110011001

    bitset<8> bs3("11111111");
    cout << bs3 << '\n';	// output -> 11111111
  }
*/

/*
  #include <bitset>

  int main()
  {
    using namespace std;

    bitset<8> bs("11111111");
    cout << bs << '\n';	// output -> 11111111

    bs[7] = 0;
    cout << bs << '\n';	// output -> 01111111

    bs.operator[](4) = 0;
    // returns a proxy class which have
    // flip(), operator bool(), operator=() and operator~() member functions.
    cout << bs << '\n';	// output -> 01101111

    bs[6] = false;
    cout << bs << '\n';	// output -> 00101111

    bs[5] = bs[6];
    cout << bs << '\n';	// output -> 00001111

    bs[3] = bs.operator[](3).operator~();
    cout << bs << '\n';	// output -> 00000111

    // operator bool() function
    cout << bs[4] << '\n';								// output -> 0
    cout << bs.operator[](4).operator bool() << '\n';	// output -> 0
    // Those 2 lines are same
  }
*/

/*
  #include <bitset>

  int main()
  {
    using namespace std;

    bitset<16> bs("010101101010011");

    auto x = bs[5];
    // x's type is not bool -> its type is a proxy class type.

    auto y = bs[5].operator bool();
    // y's type is bool.
  }
*/

/*
  #include <bitset>

  int main()
  {
    using namespace std;

    constexpr bitset<8> bs1("00101000");
    constexpr bitset<8> bs2("00000000");
    constexpr bitset<8> bs3;
    constexpr bitset<8> bs4("11111111");

    // any() member function returns true if any bit is set.
    // returns false if all bits are not set.
    constexpr bool a = bs1.any();	// a -> true
    constexpr bool b = bs2.any();	// b -> false
    constexpr bool c = bs3.any();	// c -> false

    // none() member function returns false if any bit is set.
    // returns true if all bits are not set.
    constexpr bool d = bs1.none();	// d -> false
    constexpr bool e = bs2.none();	// e -> true
    constexpr bool f = bs3.none();	// f -> true

    // all() member function returns if all bits are set.
    constexpr bool g = bs4.all();	// g -> true
    constexpr bool h = bs1.all();	// h -> false

    // count() member function returns(size_t) how many bits are set.
    constexpr size_t set_bit_count1 = bs1.count();	// 2
    constexpr size_t set_bit_count2 = bs4.count();	// 8
    constexpr size_t set_bit_count3 = bs3.count();	// 0

    // set() member function returns *this
    // if no argument sets all bits.
    bitset<8> bs5;
    bitset<8> bs6("00001111");
    bs5.set();
    bs6.set();
    cout << bs5 << '\n';	// output -> 11111111
    cout << bs6 << '\n';	// output -> 11111111

    // set(size_t, bool = true)
    bitset<8> bs7("00001111");
    bs7.set(7, 1);
    bs7.set(6);
    bs7.set(0, 0);
    cout << bs7 << '\n';	// output -> 11001110


    bitset<8> bs8;	// defalt initialize all bits are not set.
    bs8 = ~bs8;
    //	bs8 = bs8.operator~();
    // Those 2 lines are same.
    cout << bs8 << '\n';	// output -> 11111111

    // reset() member function
    bs8.reset(3);
    cout << bs8 << '\n';	// output -> 11110111
    bs8.reset();
    cout << bs8 << '\n';	// output -> 00000000

    // flip() member function
    bitset<8> bs9;
    bs9.flip();
    cout << bs9 << '\n';	// output -> 11111111
    bs9.flip(3);
    cout << bs9 << '\n';	// output -> 11110111
  }
*/

/*
  #include <bitset>

  int main()
  {
    using namespace std;

    bitset<32> bx{ 87345u };
    bitset<32> by{ 803459344u };

    cout << bx << '\n';
    cout << by << '\n';
    cout << (bx & by) << '\n';
    // output ->
    //	00000000000000010101010100110001
    //	00101111111000111101000100010000
    //	00000000000000010101000100010000

    cout << bx << '\n';
    cout << by << '\n';
    cout << (bx | by) << '\n';

    // output ->
    //	00000000000000010101010100110001
    //	00101111111000111101000100010000
    //	00101111111000111101010100110001

    cout << bx << '\n';
    cout << by << '\n';
    cout << (bx ^ by) << '\n';

    // output ->
    //	00000000000000010101010100110001
    //	00101111111000111101000100010000
    //	00101111111000101000010000100001
  }
*/

/*
  #include <bitset>

  int main()
  {
    using namespace std;

    bitset<8> bx{ "00001111"};

    cout << bx << '\n';	// output -> 00001111
    bx <<= 3;
    cout << bx << '\n';	// output -> 01111000

    bx.set();
    cout << bx << 5 << '\n';	// output -> 111111115

    cout << (bx << 5) << '\n';	// output -> 11100000
    // operator<<(cout, bx.operator<<(5))
    // Those 2 lines are same.
  }
*/

/*
  #include <bitset>

  int main()
  {
    try
    {
      std::bitset<16> bs{ "1010001020100101" };
    }
    catch (const std::exception& ex)
    {
      std::cout << "exception caught : " << ex.what() << '\n';
      // output -> exception caught : invalid bitset char
    }
  }
*/

/*
  #include <bitset>
  #include <algorithm>

  int main()
  {
    using namespace std;

    bitset<16> bs{ 2362369 };

    auto str = bs.to_string();

    copy(str.begin(), str.end(), ostream_iterator<char>{cout, " "});
    // output -> 0 0 0 0 1 1 0 0 0 0 0 0 0 0 0 1
  }
*/

/*
  #include <bitset>
  #include <algorithm>

  int main()
  {
    using namespace std;

    bitset<16> bs{ "110100101001011" };

    auto ux = bs.to_ulong();

    cout << ux << '\n';	// output -> 26955
  }
*/

/*
  #include <bitset>
  #include <set>

  int main()
  {
    using namespace std;

    bitset<32> bs1{ "110100101001" };
    bitset<32> bs2{ "111100101001" };

    auto bs3 = bs1 == bs2;
    // operator==() and operator!=() are overloaded functions
    auto bs4 = bs1 < bs2;	// syntax error
    // operator<(), operator>(), operator<=()...
    // comparison functions are not overloaded.

    set<bitset<16>> myset;
    myset.insert(8712);	// syntax error
    // C2678 binary '<': no operator found which takes a left - hand operand of type 'const _Ty'
    // (or there is no acceptable conversion)

    // set containers 2nd template parameter is Comparator parameter
    // default comparator argument = less<bitset<16>>
  }
*/

/*
  #include <bitset>
  #include <set>

  int main()
  {
    using namespace std;

    auto fcmp = [](bitset<16> x, bitset<16> y) {
      return x.to_ulong() < y.to_ulong();
    };

    set<bitset<16>, decltype(fcmp)> myset;
    myset.insert(8172);
    myset.insert(3456);
    myset.insert(121);
    myset.insert(254);
    myset.insert(29054);

    for (auto bs : myset){
      cout << bs << ' ' << bs.to_ulong() <<  '\n';
    }
    // output ->
    //	0000000001111001 121
    //	0000000011111110 254
    //	0000110110000000 3456
    //	0001111111101100 8172
    //	0111000101111110 29054
  }
*/

/*
  ---------------------------
  | dynamic storage objects |
  ---------------------------
*/

/*
  // C code
  #include <cstdlib>

  struct Window {
    int a, b, c;
  };

  int main()
  {
    //	struct Window* pd = malloc(sizeof(struct Window));
    // legal in C -> implicit conversion from void* to Window*,  not legal in C++

    struct Window* pd = (Window*)malloc(sizeof(struct Window));

    if (!pd)	// controlling if we allocate a memory. If not returns a null pointer.
    {
      // we allocate the memory but now every data member of Window object
      // have indeterminate(garbage) values in it.
    }

    pd->a = 10;
    pd->b = 11;
    pd->c = 12;

    free(pd);
    // when our job is finished we use free() function
  }
*/

/*
  #include <string>

  int main()
  {
    using namespace std;

    string* p1 = new string;
    auto p2 = new string;
    // Those 2 lines are same
    // dynamic storage objects have been default initialized.

    new string{};	// value initialized

    auto p3 = new string(12, 'a');
    // 2 memory allocation happens in heap.
    // 1. storage of string object (memory allocation) [sizeof(string)]
    // 2. storage that string object holds ("aaaaaaaaaaaaa") (resource allocation)
  }
*/

/*
  class Myclass {
  public:
    Myclass()
    {
      std::cout << "default ctor\n";
    }
    Myclass(int)
    {
      std::cout << "Myclass(int)\n";
    }
    Myclass(int, int)
    {
      std::cout << "Myclass(int, int)\n";
    }
    ~Myclass()
    {
      std::cout << "destructor\n";
    }
  private:
    unsigned char buf[1024]{};
  };

  void* operator new(size_t);	// operator new function
  // same signature as malloc() function
  // if succeeds returns a void*, if not throw a bad_alloc exception
  // we are NOT overloading new operator, we are overloading operator new() function.

  int main()
  {
    std::cout << "sizeof(Myclass) = " << sizeof(Myclass) << '\n';
    // output -> sizeof(Myclass) = 1024

    Myclass* p1 = new Myclass;
    // output -> default ctor	-> default initialization
    Myclass* p2 = new Myclass();
    // output -> default ctor	-> value initialization
    Myclass* p3 = new Myclass{};
    // output -> default ctor	-> value initialization
    Myclass* p4 = new Myclass{ 12 };
    // output -> Myclass(int)
    Myclass* p4 = new Myclass{ 12, 56 };
    // output -> Myclass(int, int)

    // No destructor have been called for p1, p2, p3, p4, p5

    // PSEUDO CODE
    // operator new function have been called for new Myclass; statement
    //		void* vp = operator new(sizeof(Myclass));
        // operator new() function have been called.
    //		try {
    //			new (vp)Myclass;	-> ctor has been called.
    //		}
    //		catch (...) {
    //			operator delete(vp);
    //		}
  }
*/

/*
  #include <vector>

  class Myclass {
  public:
    Myclass()
    {
      std::cout << "default ctor\n";
    }
    ~Myclass()
    {
      std::cout << "destructor\n";
    }
  private:
    unsigned char buf[1024 * 1024]{};
  };

  int main()
  {
    using namespace std;

    vector<void*> vec;

    int i;

    try
    {
      for (i = 0; i < 10000; ++i)
      {
        vec.push_back(operator new(sizeof(Myclass)));
      }
    }
    catch (const std::exception& ex)
    {
      std::cout << "exception caught : " << ex.what() << '\n';
      cout << "i = " << i << '\n';
    }
    // output ->
    //	exception caught : bad allocation
    //	i = 1864
    // operator new() function throw an exception
  }
*/

/*
  class Myclass {
  public:
    Myclass()
    {
      std::cout << "default ctor\n";
    }
    ~Myclass()
    {
      std::cout << "destructor\n";
    }
  private:
    unsigned char buf[1024 * 1024]{};
  };

  int main()
  {
    using namespace std;

    auto p = new Myclass;

    delete p;
    // PSEUDO CODE for delete expression
    //		p->~Myclass();
    //		operator delete(p);
    // gave back the memory which have allocated with operator new()
  }
*/

/*
  #include <cstdlib>

  class Myclass {
  public:
    Myclass()
    {
      std::cout << "default ctor, this = " << this << '\n';
    }
    ~Myclass()
    {
      std::cout << "destructor gave back resources. this = " << this << '\n';
    }
  private:
    unsigned char buf[1024]{};
  };

  void* operator new(std::size_t sz)
  {
    std::cout << "operator new function called for the size of : " << sz << '\n';

    void* vp = std::malloc(sz);

    if (!vp) {
      throw std::bad_alloc{};
    }

    std::cout << "the address of allocated block is : " << vp << '\n';
    return vp;
  }

  void operator delete(void* vp) noexcept
  {
    if (!vp) return;
    std::cout << "operator delete function called for the address of : " << vp << '\n';
    std::free(vp);
  }

  int main()
  {
    auto p = new Myclass;
    // output ->
    //	operator new function called for the size of : 1024
    //	the address of allocated block is : 00000296B1191AC0
    //	default ctor, this = 00000296B1191AC0

    std::cout << "object will be destroyed\n";

    delete p;
    // output ->
    //	destructor gave back resources. this = 00000296B1191AC0
    //	operator delete function called for the address of : 00000296B1191AC0

    std::cout << "main continiues..\n";
  }
*/

/*
  class Myclass {
  public:
    Myclass()
    {
      std::cout << "default ctor... this = " << this << '\n';
    }
    ~Myclass()
    {
      std::cout << "destructor... this = " << this << '\n';
    }
  private:
    unsigned char buf[256]{};
  };

  int main()
  {
    using namespace std;

    Myclass* p = new Myclass[5];	// array new
    // output ->
    //	default ctor... this = 0167A814
    //	default ctor... this = 0167A914
    //	default ctor... this = 0167AA14
    //	default ctor... this = 0167AB14
    //	default ctor... this = 0167AC14

    delete[] p;						// array delete
    // output ->
    //	destructor... this = 0167AC14
    //	destructor... this = 0167AB14
    //	destructor... this = 0167AA14
    //	destructor... this = 0167A914
    //	destructor... this = 0167A814
  }
*/

/*
  class Myclass {
  public:
    Myclass()
    {
      std::cout << "default ctor... this = " << this << '\n';
    }
    ~Myclass()
    {
      std::cout << "destructor... this = " << this << '\n';
    }
  private:
    unsigned char buf[256]{};
  };

  int main()
  {
    using namespace std;

    const Myclass* p1 = new const Myclass;
    auto p2 = new const Myclass;
    // Those 2 lines are same.
  }
*/

/*
  class Myclass {
  public:
    Myclass()
    {
      std::cout << "default ctor... this = " << this << '\n';
    }
    ~Myclass()
    {
      std::cout << "destructor... this = " << this << '\n';
    }
  private:
    unsigned char buf[256]{};
  };

  int main()
  {
    using namespace std;

    Myclass* p = new Myclass;

    delete p;
    // p is dangling pointer now.

    delete p;	// double deletion

    Myclass m1;
    p = &m1;
  }
*/

/*
  // Mental model for how memory allocation throw a bad_alloc exception

  #include <cstdlib>

  using new_handler = void(*)();

  new_handler gfp = nullptr;

  new_handler get_new_handler()
  {
    return gfp;
  }
  new_handler set_new_handler(new_handler f)
  {
    auto temp_new_handler = gfp;
    gfp = f;
    return temp_new_handler;
  }

  void* operator new(size_t sz)
  {
    for (;;)
    {
      void* vp = malloc(sz);
      if (vp) {
        return vp;
      }

      auto fp = get_new_handler();

      // controlling if fp is nullptr or is there any other handler assigned to it.
      if (!fp) {
        throw std::bad_alloc{};
      }
      else
        fp();
      // if operator new has been failed and we already assigned another handler
      // our handler function will be called.
    }
  }
*/

/*
  #include <new>
  #include <vector>

  void first_handler()
  {
    static int cnt{};
    std::cout << "first_handler has been called for " << ++cnt << " times.\n";
  }

  struct Myclass {
    unsigned char buff[2048 * 2048]{};
  };

  int main()
  {
    //	std::set_new_handler(&first_handler);

    std::vector<Myclass*> myvec;

    try
    {
      for (int i = 0; i < 10000; ++i) {
        if (i % 100 == 0)
        {
          std::cout << i << '\n';
        }
        myvec.push_back(new Myclass);
      }
    }
    catch (const std::exception& ex)
    {
      std::cout << "exception caught: " << ex.what() << '\n';
    }
    // output ->
    //	0
    //	100
    //	200
    //	300
    //	400
    //	exception caught : bad allocation
  }
*/

/*
  a function saved to set_new_handler can do these.

  1) can run a code that makes possible to allocate a memory.
  2) can run some code then throw bad_alloc or
    another exception that inherited from bad_alloc.
  3) can set nullptr -> set_new_handler(nullptr) ->
    cause function to throw bad_alloc exception
  4) can set another handler -> set_new_handler(another_handler)
*/

/*
  // 2) can run some code then throw bad_alloc or
  //	another exception that inherited from bad_alloc.

  #include <new>
  #include <vector>

  void first_handler()
  {
    static int cnt{};
    std::cout << "first_handler has been called for " << ++cnt << " times.\n";
    if (cnt == 5)
      throw std::bad_alloc{};
  }

  struct Myclass {
    unsigned char buff[2048 * 2048]{};
  };

  int main()
  {
    std::set_new_handler(&first_handler);

    std::vector<Myclass*> myvec;

    for (int i = 0; i < 10000; ++i) {
      if (i % 100 == 0)
      {
        std::cout << i << '\n';
      }
      myvec.push_back(new Myclass);
    }
    // output ->
    //	0
    //	100
    //	200
    //	300
    //	400
    //	first_handler has been called for 1 times.
    //	first_handler has been called for 2 times.
    //	first_handler has been called for 3 times.
    //	first_handler has been called for 4 times.
    //	first_handler has been called for 5 times.
    //	exception caught : bad allocation
  }
*/

/*
  // 3) can set nullptr -> set_new_handler(nullptr) ->
  // cause function to throw bad_alloc exception

  #include <new>
  #include <vector>

  void first_handler()
  {
    static int cnt{};
    std::cout << "first_handler has been called for " << ++cnt << " times.\n";
    if (cnt == 3)
      std::set_new_handler(nullptr);
  }

  struct Myclass {
    unsigned char buff[2048 * 2048]{};
  };

  int main()
  {
    std::set_new_handler(&first_handler);

    std::vector<Myclass*> myvec;

    try
    {
      for (int i = 0; i < 10000; ++i) {
        if (i % 100 == 0)
        {
          std::cout << i << '\n';
        }
        myvec.push_back(new Myclass);
      }
    }
    catch (const std::exception& ex)
    {
      std::cout << "exception caught: " << ex.what() << '\n';
    }
    // output ->
    //	0
    //	100
    //	200
    //	300
    //	400
    //	first_handler has been called for 1 times.
    //	first_handler has been called for 2 times.
    //	first_handler has been called for 3 times.
    //	exception caught : bad allocation
  }
*/

/*
  //	4) can set another handler->set_new_handler(another_handler)

  #include <new>
  #include <vector>

  void second_handler()
  {
    static int cnt{};
    std::cout << "second_handler has been called for " << ++cnt << " times.\n";
    if (cnt == 3)
      std::set_new_handler(nullptr);
  }

  void first_handler()
  {
    static int cnt{};
    std::cout << "first_handler has been called for " << ++cnt << " times.\n";
    if (cnt == 3)
      std::set_new_handler(&second_handler);
  }

  struct Myclass {
    unsigned char buff[2048 * 2048]{};
  };

  int main()
  {
    std::set_new_handler(&first_handler);

    std::vector<Myclass*> myvec;

    try
    {
      for (int i = 0; i < 10000; ++i) {
        if (i % 100 == 0)
        {
          std::cout << i << '\n';
        }
        myvec.push_back(new Myclass);
      }
    }
    catch (const std::exception& ex)
    {
      std::cout << "exception caught: " << ex.what() << '\n';
    }
    // output ->
    //	0
    //	100
    //	200
    //	300
    //	400
    //	first_handler has been called for 1 times.
    //	first_handler has been called for 2 times.
    //	first_handler has been called for 3 times.
    //	second_handler has been called for 1 times.
    //	second_handler has been called for 2 times.
    //	second_handler has been called for 3 times.
    //	exception caught : bad allocation
  }
*/

/*
  -----------------------------
  | placement new expressions |
  -----------------------------
*/

/*
  #include <cstdlib>

  class Myclass {
  private:
    unsigned char buf[1024]{};
  };

  void* operator new(std::size_t, int x, int y)
  {
    std::cout << "x = " << x << " y = " << y << '\n';
    return malloc(1000);
  }

  int main()
  {
    auto p = new(111, 555)Myclass;
    // output -> x = 111 y = 555
    // we can send more information to operator new function overload.
  }
*/

/*
  // CAN NOT BE OVERLOADED
  //	void* operator new(std::size_t, void* vp)
  //	{
  //		return vp;
  //	}

  class Myclass {
  public:
    Myclass()
    {
      std::cout << "Myclass default ctor this = " << this << '\n';
    }
    ~Myclass()
    {

    }
  private:
    unsigned char buf[1024]{};
  };

  int main()
  {
    unsigned char buffer[1024];

    std::cout << "address of buffer array = " <<  static_cast<void*>(buffer) << '\n';

    Myclass* p = new(buffer)Myclass;
    // in this statement we are sending &buffer as void* to operator new function.
    // void* operator new(std::size_t, void* vp) -> second param vp -> will be &buffer

    // because of operator new function returns vp(&buffer),
    // Myclass object will be constructed in the address that we want(in stack in this case).

    // output ->
    //	address of buffer array = 00000021FC2FF530
    //	Myclass default ctor this = 00000021FC2FF530

    delete p;	// Undefined behaviour
    // because of Myclass is constructed in stack[did not memory allocate with malloc]
    // because buffer arrays address is in stack.
    // calling operator delete() function will be undefined behaviour.
    // in this case we need to call ~Myclass() destructor by its name.

    p->~Myclass();
  }
*/

/*
  class Myclass {
    char mbuff[1024 * 1024];
  };

  int main()
  {
    using namespace std;

    new(nothrow) Myclass;
    // if it fails it is not throwing an exception, it retuns a nullptr

    Myclass* p = new(nothrow) Myclass;

    if (!p) {
      //...
    }
  }
*/

/*
  -----------------------------------------------------------------------------------
  | overloading operator new() and operator delete() functions as a member function |
  -----------------------------------------------------------------------------------
*/

/*
  class Myclass {
  public:
    void* operator new(std::size_t n)
    {
      this;
      // using this keyword is a syntax error -> static member function
    }
  private:
    char buf[1024]{};
  };

  int main()
  {
    auto p = new Myclass;
    // if operator new() function was not a static member function
    // it would need a Myclass object to call that non-static member function.
    // but we need to allocate memory before creating Myclass object.
    // that is why operator new() function is by default a static member function.
  }
*/

/*
  class Myclass {
  public:
    static void* operator new(std::size_t n)
    {
      return nullptr;
    }
    // we can also use static keyword in the function decleration of definition.
  private:
    char buf[1024]{};
  };

  int main()
  {
    auto p = new Myclass;
  }
*/

/*
  #include <cstdlib>

  class Myclass {
  public:
    Myclass()
    {
      std::cout << "default ctor this = " << this << '\n';
    }

    ~Myclass()
    {
      std::cout << "destructor this = " << this << '\n';
    }

    static void* operator new(std::size_t n)
    {
      std::cout << "Myclass::operator new\n";
      std::cout << "n = " << n << '\n';
      void* vp = std::malloc(n);

      if (!vp) {
        throw std::bad_alloc{};
      }

      std::cout << "address : " << vp << '\n';
      return vp;
    }

    static void operator delete(void* vp)
    {
      std::cout << "Myclass::operator delete vp = " << vp << '\n';
      std::free(vp);
    }

  private:
    char buf[1024]{};
  };

  int main()
  {
    Myclass* p = new Myclass;
    delete p;
    //	Myclass::operator new
    //	n = 1024
    //	address : 01034B08
    //	default ctor this = 01034B08
    //	destructor this = 01034B08
    //	Myclass::operator delete vp = 01034B08
  }
*/

/*
  #include <cstdlib>

  class Myclass {
  public:
    static void* operator new(std::size_t n)
    {
      std::cout << "Myclass::operator new\n";
      void* vp = std::malloc(n);

      if (!vp) {
        throw std::bad_alloc{};
      }
      return vp;
    }
    static void operator delete(void* vp)
    {
      std::cout << "Myclass::operator delete\n";
      std::free(vp);
    }

  private:
    char buf[1024]{};
  };

  int main()
  {
    // even if our class has an operator new() or operator delete() static member functions
    // we can call standart libraries functions by using ::(unary scope resolution operator).
    Myclass* p = ::new Myclass;
    ::delete p;
    // output -> empty
  }
*/