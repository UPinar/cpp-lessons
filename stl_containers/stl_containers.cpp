#include <iostream>

/*
                      ==================
                      | STL Containers |
                      ==================
*/

/*
  sequence containers
  ----------------------------------
  C Arrays
  std::vector
  std::deque
  std::list
  std::forward_list         (C++11)
  std::string
  std::array                (C++11)

  associative containers
  ----------------------------------
  std::set
  std::multiset
  std::map
  std::multimap

  unordered associative containers
  ----------------------------------
  std::unordered_set        (C++11)
  std::unordered_multiset   (C++11)
  std::unordered_map        (C++11)
  std::unordered_multimap   (C++11)
*/

/*
  -----------------------------------------------------------

  -> C arrays are fixed arrays.
  -> std::vector is a dynamic array.
  -> std::deque is double ended queue. (vector of vectors)
  -> std::list is doubly linked list.
  -> std::forward_list is linked list
  -> std::string is a dynamic array.
  -> std::array is C array wrapper.

  -----------------------------------------------------------

  -> std::set is a binary tree of unique keys.
  -> std::multiset is a binary tree of non-unique keys. 
  -> std::map is holding [unique key - value] pairs. 
  -> std::multimap is holding [non-unique key - value] pairs.

  -----------------------------------------------------------

  -> search in assosiative containers           -> O(log n) 
      those are binary search trees.
  -> search in unordered associative containers -> O(1) 
      those are hash tables.

  -----------------------------------------------------------
*/

/*
  container adaptors
  -----------------------
  std::stack          -> stack interface. Last In First Out(LIFO)
  std::queue          -> tail interface.  First In First Out(FIFO)
  std::priority_queue -> high priority first out.
*/

/*
  // mental model for containers

  template <typename T>
  class Vector {
  public:
    // constiner member functions
    void push_back(const T&);
    void push_back(T&&);
    void pop_back();
    std::size_t size()const;
    bool empty()const;

    // nested type iterator interface
    class iterator {
    public:
      T& operator*();
      iterator& operator++();
      iterator& operator--();
      T* operator->();
      bool operator==(iterator)const;
      bool operator!=(iterator)const;
    };

    iterator insert(iterator, const T& val);
    iterator erase(iterator);

    iterator begin(); 
    // returns first elements position
    iterator end();   
    // returns sentinel position (last element + 1)
  };
*/

/*
  template <typename Container>
  void func(Container& c)
  {
    auto iter = c.begin();      
    // all containers have "begin" member function.
    typename C::iterator iter;
    // all containers have an 'iterator' nested type.
    typename C::value_type;
    // all containers have 'value_type' nested type.
  }
*/

/*
  template <typename Iter>
  void func(Iter beg, Iter end)
  {
    typename Iter::value_type;
    // all iterator type have a 'value_type' nested type.
  }
*/

/*
  #include <vector>
  int main()
  {
    std::vector<int>::value_type;             // int
    std::vector<int*>::iterator::value_type;  // int*

    // - containers 
    // - 'iterator' nested type of containers
    //    have a 'value_type' nested type

    std::vector<int>::pointer;          // int*
    std::vector<int>::reference;        // int&
  }
*/

/*
  - In sequence containers elements 
    CAN BE add to a specific index.
  - In associative containers elements 
    CAN NOT be added to a random index.

  Standart Library containers have common functions,
    - empty   -> returns true if container is empty
    - clear   -> deletes all elements from the container
    - size    -> returns count of elements in the container

  Sequence containers in Standart Library have common functions,
    - front   -> returns the first element of container
    - back()  -> returns the last element of container
    - resize  -> change the size of the container
*/

/*
  // containers have common nested types,
  // i.e. "size_type", "value_type", "pointer", "reference"...

  #include <vector>
  #include <list>
  #include <map>
  #include <forward_list>
  #include <set>

  int main()
  {
    // --------------------------------------------------

    std::vector<int>::size_type vec_size{};
    std::list<int>::size_type list_size{};
    std::map<int, int>::size_type map_size{};
    std::set<int>::size_type  set_size{};
    std::forward_list<int>::size_type forward_list_size{};

    // --------------------------------------------------

    std::vector<int>::value_type ival{};
    // std::vector<int>::value_type -> int 

    std::list<double>::value_type dval{};
    // std::list<double>::value_type -> double

    std::map<int, double>::value_type pair_int_double{};	
    // std::map<int, double>::value_type -> 
    //    std::pair<const int, double>

    // --------------------------------------------------

    std::vector<int>::pointer i_ptr{};
    // std::vector<int>::pointer -> int*

    int i1 = 10;
    std::vector<int>::reference i_ref = i1;
    // std::vector<int>::reference -> int&

    // --------------------------------------------------
  }
*/

/*
  #include <vector>
  #include <iterator>   // std::iterator_traits

  // Question :
  // what if C style array's sent to "func_1"
  // std::begin(arr), std::end(arr)
  // Answer :
  // C style array does not have a "value_type"
  // so it will be a syntax error.

  template <typename InIter>
  void func_1(InIter iter_beg, InIter iter_end)
  {
    typename InIter::value_type x{};
  }

  // for the problem above std::iterator_traits 
  // class template will be used.
  template <typename InIter>
  void func_2(InIter iter_beg, InIter iter_end)
  {
    typename std::iterator_traits<InIter>::value_type x{};
  }

  // -----------------------------------------------------

  // primary template for Iterator_Traits 
  template <typename Iter>
  struct Iterator_Traits {
    using value_type = typename Iter::value_type;
    using pointer = typename Iter::pointer;
    using reference = typename Iter::reference;
  };

  // partial specialization for pointer type
  template <typename T>
  struct Iterator_Traits<T*> {
    using value_type = T;
    using pointer = T*;
  };

  // because of C array will decay to pointer 
  // it will choose the partial specialization
  // so value_type will become int.

  // -----------------------------------------------------

  int main()
  {
    std::vector<int> ivec(100);
    int i_arr[5] = { 11, 22, 33, 44, 55 };

    // ---------------------------------------------

    func_1(ivec.begin(), ivec.end());           // VALID
    func_1(std::begin(i_arr), std::end(i_arr)); // syntax error
    // error: 'int*' is not a class, struct, or union type
    func_1(i_arr, i_arr + 5);                   // syntax error
    // error: 'int*' is not a class, struct, or union type

    // ---------------------------------------------

    func_2(ivec.begin(), ivec.end());           // VALID
    func_2(std::begin(i_arr), std::end(i_arr)); // VALID
    func_2(i_arr, i_arr + 5);                   // VALID 

    // ---------------------------------------------
  }
*/

/*
                  -------------------------
                  | std::vector container |
                  -------------------------
*/


/*
  - in std::vector all index's can be reached in constant time
    using pointer arithmetics because std::vector is 
    a sequence container.

  - when adding an element at the end of the std::vector 
    sometimes reallocation will be needed, 
    other times O(1), 
    so it was called amortized constant time.
*/

/*
  #include <vector>
  #include <memory>   // std::allocator

  template <typename T, typename A = std::allocator<T>>
  class Vector {};

  int main()
  {
    std::cout << std::boolalpha;

    // -----------------------------------------------

    std::vector<int, std::allocator<int>> ivec1;
    std::vector<int> ivec2;
    // Those 2 lines are equivalent

    // -----------------------------------------------

    std::vector<int> ivec;  // default initialization

    std::cout << "ivec.size() = " << ivec.size() << '\n';
    // output -> ivec.size() = 0
    std::cout << "ivec.empty() = " << ivec.empty() << '\n';
    // output -> ivec.empty() = true

    // -----------------------------------------------
  }
*/

/*
  // insert functions of std::vector, 
  // are increasing the size of the container.

  // remove functions of std::vector, 
  // are decreasing the size of the container.

  #include <vector>

  int main()
  {
    std::vector<int> ivec;

    // insert functions of std::vector
    ivec.push_back(10);
    ivec.emplace_back(10);
    ivec.insert(ivec.begin(), 5);

    // remove functions of std::vector
    ivec.pop_back();
    ivec.erase(ivec.begin());
  }
*/

/*
  #include <utility>  // std::forward

  // mental model for insert functions of std::vector
  template <typename T>
  class Vector {
  public:
    // const L value reference parameter
    void push_back(const T&);

    // R value reference parameter
    void push_back(T&&);       

    // universal reference parameter
    template <typename ...Args>
    void emplace_back(Args&&... args) 
    {
      new(address) T(std::forward<Args>(args)...);
      // address in std::vector 
      // that the object will be constructed.
    }
  };
*/

/*
  #include <vector>

  class Myclass {
  public:
    Myclass() 
    {
      std::cout << "Myclass::Myclass() : default constructor\n";
    }

    Myclass(int, int, int)
    {
      std::cout << "Myclass::Myclass(int, int, int)\n";
    }

    Myclass(const Myclass&)
    {
      std::cout << 
        "Myclass::Myclass(const Myclass&) : copy constructor\n";
    }

    Myclass(Myclass&&)
    {
      std::cout << 
        "Myclass::Myclass(Myclass&&) : move constructor\n";
    }
  };

  int main()
  {
    std::vector<Myclass> m_vec;
    m_vec.reserve(100);

    // ----------------------------------------------------

    Myclass m1;
    m_vec.push_back(m1);
    // output ->
    //  Myclass::Myclass() : default constructor
    //  Myclass::Myclass(const Myclass&) : copy constructor

    // default constructor for m1 object
    // copy constructor for copying m1 object to std::vector

    // ----------------------------------------------------

    m_vec.push_back(Myclass{});
    // output ->
    //  Myclass::Myclass() : default constructor
    //  Myclass::Myclass(Myclass&&) : move constructor

    // default constructor for temporary Myclass{} object
    // move constructor for moving temporary object to std::vector

    // ----------------------------------------------------

    m_vec.emplace_back();
    // output -> Myclass::Myclass() : default constructor 

    // Myclass object will directly constructed in std::vector
    // because of no arguments has been pass to "emplace_back"
    // function, default constructor of Myclass will be called.

    // ----------------------------------------------------

    m_vec.emplace_back(11, 22, 33);
    // output -> Myclass::Myclass(int, int, int)

    // arguments of the "emplace_back" will be 
    // perfect forwarded to Myclass(int, int, int) constructor

    // ----------------------------------------------------
  }
*/

/*
  #include <vector>
  #include <string>
  #include <utility>  // std::move

  int main()
  {
    std::vector<int> ivec;

    // -----------------------------------------------

    // std::vector class's member functions

    auto iter_1 = ivec.begin();    // iterator
    auto iter_2 = ivec.cbegin();   // const iterator
    auto iter_3 = ivec.rbegin();   // reverse iterator
    auto iter_4 = ivec.crbegin();  // const reverse iterator

    // -----------------------------------------------

    // global functions (generally used for C style arrays)

    auto iter_5 = std::begin(ivec);   // iterator
    auto iter_6 = std::cbegin(ivec);  // const iterator
    auto iter_7 = std::rbegin(ivec);  // reverse iterator
    auto iter_8 = std::crbegin(ivec); // const reverse iterator

    // -----------------------------------------------

    int i_arr[]{ 11, 22, 33, 44, 55 };
    std::crbegin(i_arr);

    // -----------------------------------------------

    // all containers have default constructor

    std::vector<int> ivec1;    // default initialization
    // std::vector classes default constructor will be called
    std::vector<int> ivec2{};  // value initialization
    // std::vector classes default constructor will be called

    std::vector<int> ivec3();
    // this is a function declaration not a variable definition
    // most vexing parse 

    // -----------------------------------------------

    std::vector<std::string> svec_1{ 
      "istanbul", "ankara", "izmir", "bursa", "eskisehir" };

    auto svec_2 = svec_1;
    auto svec_3{ svec_1 };
    // std::vector classes copy constructor will be called.

    std::cout << "svec_1.capacity() = " 
              << svec_1.capacity() << '\n';
    // output -> svec_1.capacity() = 5

    std::cout << "svec_2.capacity() = "
              << svec_2.capacity() << '\n';
    // output -> svec_2.capacity() = 5

    std::cout << "svec_3.capacity() = "
              << svec_3.capacity() << '\n';
    // output -> svec_3.capacity() = 5

    // -----------------------------------------------

    auto svec_4 = std::move(svec_1);
    // std::vector classes move constructor will be called.
    // "svec" will become moved-from state. 
    // like default initialized state for std::vector class

    std::cout << "svec_4.capacity() = "
          << svec_4.capacity() << '\n';
    // output -> svec_4.capacity() = 5

    std::cout << "svec_1.capacity() = "
      << svec_1.capacity() << '\n';
    // output -> svec_1.capacity() = 0
    
    // -----------------------------------------------
  }
*/

/*
  #include <vector>
  #include <type_traits>  // std::is_same

  class Myclass {
  public:
    Myclass(int);
  };

  int main()
  {
    // --------------------------------------------------

    std::vector<std::string> svec(100);   
    // fill constructor
    // there are 100 default constructed 
    // "std::string" objects in "svec"

    std::vector<Myclass> m_vec(100);  // syntax error
    // error: no matching function for call to 'Myclass::Myclass()'

    // because of there is user-defined 
    // Myclass::Myclass(int) constructor,  
    // Myclass's default constructor is not declared.

    // --------------------------------------------------

    std::vector<std::string> svec_2(10, "xyz");
    // fill constructor

    std::cout << "svec_2.size() = " << svec_2.size() << '\n';
    // output -> svec_2.size() = 10

    for (auto elem : svec_2)
      std::cout << elem << ' '; 
    // output -> xyz xyz xyz xyz xyz xyz xyz xyz xyz xyz
    std::cout << '\n';

    // --------------------------------------------------

    std::vector<int> ivec(20);
    // fill constructor
    std::cout << "ivec.size = " << ivec.size() << '\n';
    // output -> ivec.size = 20

    std::vector<int> ivec_2{ 20 };
    // std::initializer_list parameter constructor
    std::cout << "ivec_2.size() = " << ivec_2.size() << '\n';
    // output -> ivec_2.size() = 1

    // --------------------------------------------------

    std::vector<int> ivec_3(10, 11);
    // fill constructor

    std::cout << "ivec_3.size() = " << ivec_3.size() << '\n';
    // output -> ivec_3.size() = 10

    for (auto elem : ivec_3)
      std::cout << elem << ' ';
    // output -> 11 11 11 11 11 11 11 11 11 11
    std::cout << '\n';


    std::vector<int> ivec_4{ 10, 11 };
    // std::initializer_list parameter constructor

    std::cout << "ivec_4.size() = " << ivec_4.size() << '\n';	
    // output -> ivec_4.size() = 2

    for (auto elem : ivec_4)
      std::cout << elem << ' ';
    // output -> 10 11
    std::cout << '\n';

    // --------------------------------------------------

    std::vector<int> ivec_5{ 11, 22, 33, 44, 55 }; 

    std::vector ivec_6{ 11, 22, 33, 44, 55 }; 
    // CTAD(Class Template Argument Deduction)

    constexpr bool b1 = 
      std::is_same_v<decltype(ivec_5), decltype(ivec_6)>;
    // b1 -> true

    // --------------------------------------------------
  }
*/

/*
  #include <vector>
  #include <list>
  #include <string>
  #include <cstddef>  // std::size_t

  int main()
  {
    std::list<int> ilist{ 11, 22, 33, 44, 55, 66, 77 };

    // ---------------------------------------------------

    // std::vector<int> ivec{ ilist };  // syntax error
    // error: no matching function for call to 
    // 'std::vector<int>::vector(
    //      <brace-enclosed initializer list>)'

    // assigning different containers to each other
    // is syntax error

    // ---------------------------------------------------

    std::vector<int> ivec_2{ ilist.begin(), ilist.end() };
    // range parameter constructor 

    std::cout << "ivec_2.size() = " 
              << ivec_2.size() << '\n';
    // output -> ivec_2.size() = 7

    for (auto elem : ivec_2)
      std::cout << elem << ' '; 
    // output -> 11 22 33 44 55 66 77
    std::cout << '\n';

    // ---------------------------------------------------

    std::vector<double> dvec{ ilist.begin(), ilist.end() };
    // range parameter constructor

    std::cout << "dvec.size() = " 
              << dvec.size() << '\n';
    // output -> dvec.size() = 7

    for (auto elem : dvec)
      std::cout << elem << ' '; 
    // output -> 11 22 33 44 55 66 77
    std::cout << '\n';

    // ---------------------------------------------------

    std::list<const char*> cstr_list{ 
      "world", "universe", "galaxy" };

    std::vector<std::string> svec{ 
      cstr_list.begin(), cstr_list.end() };
    // range parameter constructor

    std::cout << "svec.size() = " 
              << svec.size() << '\n';
    // output -> svec.size() = 3

    for (auto elem : svec)
      std::cout << elem << ' ';
    // output -> world universe galaxy
    std::cout << '\n';

    // ---------------------------------------------------

    int i_arr[]{ 111, 222, 333, 444, 555 };

    std::size_t i_arr_size = sizeof(i_arr) / sizeof(*i_arr);

    std::vector<int> ivec_3{ i_arr, i_arr + i_arr_size };
    // range parameter constructor

    std::cout << "ivec_3.size() = " 
              << ivec_3.size() << '\n';
    // output -> ivec_3.size() = 5

    for (auto elem : ivec_3)
      std::cout << elem << ' ';
    // output -> 111 222 333 444 555
    std::cout << '\n';

    // ---------------------------------------------------

    std::vector<int> ivec_4{ std::begin(i_arr), std::end(i_arr)};
    // range parameter constructor

    std::cout << "ivec_4.size() = " 
              << ivec_4.size() << '\n';
    // output -> ivec_4.size() = 5

    for (auto elem : ivec_4)
      std::cout << elem << ' ';
    // output -> 111 222 333 444 555
    std::cout << '\n';

    // ---------------------------------------------------
  }
*/

/*
  std::vector container constructors
  ----------------------------------
  - copy constructor
  - move constructor
  - default constructor
  - (std::size_t)             -> fill constructor
  - (std::size_t, T)          -> fill constructor
  - (std::initializer_list)   -> initializer_list cosntructor
  - (iter_beg, iter_end)      -> range constructor
*/

/*
  // global "std::size" and "std::empty" functions

  #include <vector>   // std::size, std::empty

  int main()
  {
    std::vector<int> ivec;


    std::cout << "std::size(ivec) = " 
              << std::size(ivec) << '\n';
    // output -> std::size(ivec) = 0

    std::cout << "std::empty(ivec) = " 
              << std::empty(ivec) << '\n';
    // output -> std::empty(ivec) = 1
  }
*/

/*
  // global "std::data" function template
  // returns a pointer to the block of memory 
  // containing the elements of the range. 

  #include <vector>   // std::data

  int main()
  {
    std::vector<int> ivec(10);

    auto ivec_ptr_1 = std::data(ivec);
    auto ivec_ptr_2 = ivec.data();

    std::cout << "&ivec[0] = " << &ivec[0] << '\n';
    // output -> &ivec[0] = 0x2297f322b80
    std::cout << "ivec_ptr_1 = " << ivec_ptr_1 << '\n';
    // output -> ivec_ptr_1 = 0x2297f322b80
    std::cout << "ivec_ptr_2 = " << ivec_ptr_2 << '\n';
    // output -> ivec_ptr_2 = 0x2297f322b80
  }
*/

/*
  #include <vector>

  int main()
  {
    std::vector<int> ivec(20);

    auto current_capacity = ivec.capacity();
    int reallocation_count{};

    while (ivec.size() < 2000) 
    {
      ivec.push_back(1);
      // when size reaches to capacity
      // reallocation will occur
      // (implementation defined - 1.5x or 2x the capacity)

      if (ivec.capacity() != current_capacity) 
      {
        std::cout << "reallocation_count = "
                  << ++reallocation_count
                  << ", size = " << ivec.size();

        std::cout << ", new capacity = " 
                  << ivec.capacity() << '\n';

        current_capacity = ivec.capacity();
      }
    }
    // output ->
    //  reallocation_count = 1, size = 21, new capacity = 40
    //  reallocation_count = 2, size = 41, new capacity = 80
    //  reallocation_count = 3, size = 81, new capacity = 160
    //  reallocation_count = 4, size = 161, new capacity = 320
    //  reallocation_count = 5, size = 321, new capacity = 640
    //  reallocation_count = 6, size = 641, new capacity = 1280
    //  reallocation_count = 7, size = 1281, new capacity = 2560
  }
*/

/*
  #include <vector>

  int main()
  {
    std::vector<int> ivec(20);
    ivec.reserve(1200);   
    // std::vector containers "reserve" member function 

    auto current_capacity = ivec.capacity();
    int reallocation_count{};

    while (ivec.size() < 2'000) 
    {
      ivec.push_back(1);

      if (ivec.capacity() != current_capacity)
      {
        std::cout << "reallocation_count = "
                  << ++reallocation_count
                  << ", size = " << ivec.size();

        std::cout << ", new capacity = " 
                  << ivec.capacity() << '\n';

        current_capacity = ivec.capacity();
      }
    }
    // output ->
    //  reallocation_count = 1, size = 1201, new capacity = 2400
  }
*/

/*
  #include <vector>

  int main()
  {
    // -----------------------------------------------------

    std::vector<int> ivec(100'000, 5);
    std::cout << "ivec.size() = " 
              << ivec.size() 
              << ", ivec.capacity() = " 
              << ivec.capacity() << '\n';
    // output -> ivec.size() = 100000, ivec.capacity() = 100000

    ivec.resize(10);
    std::cout << "ivec.size() = " 
              << ivec.size() 
              << ", ivec.capacity() = " 
              << ivec.capacity() << '\n';
    // output -> ivec.size() = 10, ivec.capacity() = 100000

    ivec.shrink_to_fit();
    std::cout << "ivec.size() = " 
          << ivec.size() 
          << ", ivec.capacity() = " 
          << ivec.capacity() << '\n';
    // output -> ivec.size() = 10, ivec.capacity() = 10

    // -----------------------------------------------------
    // -----------------------------------------------------

    // before "shrink_to_fit" member function, 
    // "swap" member function is being used.

    std::vector<int> ivec2(200'000, 5);
    ivec2.resize(10);

    std::cout << "ivec2.size() = " 
        << ivec2.size() 
        << ", ivec2.capacity() = " 
        << ivec2.capacity() << '\n';
    // output -> ivec2.size() = 10, ivec2.capacity() = 10


    std::vector<int>{ ivec2 }.swap(ivec2);
    // std::vector class has a constructor,
    // "vector( const vector& other )"
    // temporary object is being created and 
    // "swap" member function is being called.

    std::cout << "ivec2.size() = " 
        << ivec2.size() 
        << ", ivec2.capacity() = " 
        << ivec2.capacity() << '\n';
    // output -> ivec2.size() = 10, ivec2.capacity() = 10
    
    // -----------------------------------------------------
  }
*/

/*
  #include <vector>
  #include <string>

  int main()
  {
    std::vector<int> ivec{ 11, 22, 33, 44, 55 };
      
    // --------------------------------------------------

    // compiler written range based for loop -> Scenario_1 
    for (auto elem : ivec);

    for (auto it = ivec.begin(); it != ivec.end(); ++it) 
      auto elem = *it;
    
    // --------------------------------------------------

    // compiler written range based for loop -> Scenario_2
    for (const auto elem : ivec);

    for (auto c_it = ivec.begin(); c_it != ivec.end(); ++c_it)
      const auto elem = *c_it;

    // --------------------------------------------------

    // compiler written range based for loop -> Scenario_3
    for (const auto& elem : ivec);

    for (auto it = ivec.begin(); it != ivec.end(); ++it)
      const auto& elem = *it;
  
    // --------------------------------------------------

    // compiler written range based for loop -> Scenario_4
    for (auto&& elem : ivec) {}

    for (auto it = ivec.begin(); it != ivec.end(); ++it) 
      auto&& elem = *it;
    
    // --------------------------------------------------
  }
*/

/*
  #include <vector>
  #include <string>
  #include <algorithm>  // std::copy
  #include <iterator>   // std::back_inserter

  int main()
  {
    std::vector<int> ivec{ 11, 22, 33, 44, 55 };
    // "front" and "back" member functions 
    // are reaching first and the last elements 
    // of the std::vector with reference semantics.

    ivec.front() += 99;
    ivec.back() += 9999;

    for (auto elem : ivec)
      std::cout << elem << ' ';
    // output -> 110 22 33 44 10054

    // ----------------------------------------------------
    
    std::vector<std::string> svec;

    auto beg_iter = svec.begin();   // NOT undefined behaviour
    auto end_iter = svec.end();     // NOT undefined behaviour

    *beg_iter;      // undefined behaviour(UB)
    *end_iter;      // undefined behaviour(UB)

    bool b1 = (beg_iter == end_iter);
    // NOT undefined behaviour result is true

    std::distance(beg_iter, end_iter);
    // NOT undefined behaviour result is 0

    // ----------------------------------------------------

    std::vector<int> ivec_x;
    std::vector<int> ivec_y;

    std::copy(ivec_x.begin(), ivec_x.end(),   // source
              std::back_inserter(ivec_y));    // destination
    // NOT undefined behaviour 
    // because can not get into while loop in 
    // std::copy function.

    // ----------------------------------------------------
  }
*/

/*
  #include <vector>

  int main()
  {
    std::vector<int> ivec(5, 11);

    // --------------------------------------------------

    std::cout << "ivec.size() = " 
              << ivec.size() 
              << ", ivec.capacity() = " 
              << ivec.capacity() << '\n';
    // output -> ivec.size() = 5, ivec.capacity() = 5

    for (auto elem : ivec)
      std::cout << elem << ' ';
    // output -> 11 11 11 11 11
    std::cout << '\n';

    // --------------------------------------------------

    ivec.resize(10);
    std::cout << "ivec.size() = " 
          << ivec.size() 
          << ", ivec.capacity() = " 
          << ivec.capacity() << '\n';
    // output -> ivec.size() = 10, ivec.capacity() = 10

    for (auto elem : ivec)
      std::cout << elem << ' ';
    // output -> 11 11 11 11 11 0 0 0 0 0
    std::cout << '\n';

    // --------------------------------------------------

    ivec.resize(15, 22);
    std::cout << "ivec.size() = " 
          << ivec.size() 
          << ", ivec.capacity() = " 
          << ivec.capacity() << '\n';
    // output -> ivec.size() = 15, ivec.capacity() = 20

    for (auto elem : ivec)
      std::cout << elem << ' ';
    // output -> 11 11 11 11 11 0 0 0 0 0 22 22 22 22 22
    std::cout << '\n';

    // --------------------------------------------------

    // deleting elements from container 
    // with "resize" member function.

    ivec.resize(3);
    std::cout << "ivec.size() = " 
          << ivec.size() 
          << ", ivec.capacity() = " 
          << ivec.capacity() << '\n';
    // output -> ivec.size() = 3, ivec.capacity() = 20

    for (auto elem : ivec)
      std::cout << elem << ' ';
    // output -> 11 11 11
    std::cout << '\n';

    // --------------------------------------------------

    // deleting every element in container
    // with "resize(0)" is valid but better using
    // "clear member function"

    ivec.resize(0);
    std::cout << "ivec.size() = " 
          << ivec.size() 
          << ", ivec.capacity() = " 
          << ivec.capacity() << '\n';
    // output -> ivec.size() = 0, ivec.capacity() = 20

    for (auto elem : ivec)
      std::cout << elem << ' ';
    // output -> 

    // --------------------------------------------------
  }
*/

/*
  #include <vector>

  int main()
  {
    std::vector<int> ivec;
    ivec.reserve(10);

    for (int i = 0; i < 10; ++i)
      ivec.push_back(i);

    for (auto elem : ivec)
      std::cout << elem << ' ';
    // output -> 0 1 2 3 4 5 6 7 8 9
  }
*/

/*
  #include <vector>
  #include <string>
  #include <cstddef>  // std::size_t
  #include <utility>  // std::move

  int main()
  {
    std::vector<std::string> svec{ 
      "istanbul", "ankara", "izmir", "eskisehir", "rize" };
      
    std::vector<std::string> dest_vec;

    for (std::size_t i{}; i < svec.size(); ++i)
      dest_vec.push_back(std::move(svec[i]));


    std::cout << "svec.size() = " << svec.size() << '\n';
    // output -> svec.size() = 5

    // svec container's size is 5 but std::string objects 
    // in svec container are in moved-from state.

    for (const auto& str : svec) 
      std::cout << str.size() << ' ';
    // output -> 0 0 0 0 0   
    
    // (std::string's "size" member function )
  }
*/

/*
  #include <vector>
  #include <string>

  int main()
  {
    std::vector<std::string> svec{ 
      "istanbul", "ankara", "izmir", "eskisehir" };

    for (auto str : svec)
      std::cout << str << ' ';
    // output -> istanbul ankara izmir eskisehir
    std::cout << '\n';

    // -------------------------------------------------

    svec = { "samsun", "erzurum", "sivas" };
    // std::initializer list assignment

    for (auto str : svec)
      std::cout << str << ' ';
    // output -> samsun erzurum sivas
  }
*/

/*
  #include <vector>
  #include <list>
  #include <string>

  int main()
  {
    std::list<std::string> slist{ 
      "istanbul", "ankara", "izmir", "eskisehir" };

    std::vector<std::string> svec;

    // -----------------------------------------------

    svec.assign(slist.begin(), slist.end());
    // assing member function with range parameters

    for (auto str : svec)
      std::cout << str << ' ';
    std::cout << '\n';
    // output -> istanbul ankara izmir eskisehir

    // -----------------------------------------------

    svec.assign(5, "universe");
    // assign member function with fill parameters

    for (auto str : svec)
      std::cout << str << ' ';
    // output -> universe universe universe universe universe
    std::cout << '\n';

    // -----------------------------------------------
  }
*/

/*
  // insert member functions of std::vector are returning
  // an iterator (inserted element(s) address)

  #include <vector>
  #include <iterator>   // std::next

  int main()
  {
    std::vector<int> ivec{ 
      11, 22, 33, 44, 55, 66, 77, 88, 99 };

    // ----------------------------------------------------

    ivec.insert(ivec.begin(), 999);
    // inserting element to the beginning of the container

    for (auto elem : ivec)
      std::cout << elem << ' ';
    // output -> 999 11 22 33 44 55 66 77 88 99
    std::cout << '\n';

    // ----------------------------------------------------

    ivec.insert(ivec.begin() + 1, 777);
    ivec.insert(std::next(ivec.begin()), 777);
    // Those 2 lines are equivalent.
    // inserting element to the 2nd position in container

    for (auto elem : ivec)
      std::cout << elem << ' ';
    // output -> 999 777 777 11 22 33 44 55 66 77 88 99
    std::cout << '\n';

    // ----------------------------------------------------

    ivec.insert(ivec.end(), 111);
    ivec.push_back(111);
    // Those 2 lines are equivalent.
    // inserting element to the end of the container

    for (auto elem : ivec)
      std::cout << elem << ' ';
    // output -> 999 777 777 11 22 33 44 55 66 77 88 99 111 111
    std::cout << '\n';

    // ----------------------------------------------------
  }
*/

/*
  #include <vector>
  #include <list>

  int main()
  {
    std::vector<int> ivec{ 11, 22, 33, 44, 55 };

    // ----------------------------------------------------

    ivec.insert(ivec.begin(), { 66, 77, 88, 99 });
    // inserting std::initializer_list to the beginning 
    // of the container

    for (auto elem : ivec)
      std::cout << elem << ' ';
    // output -> 66 77 88 99 11 22 33 44 55
    std::cout << '\n';

    // ----------------------------------------------------

    ivec.insert(ivec.begin(), 3 , 222);
    // inserting 3 elements with value 222 to the beginning

    for (auto elem : ivec)
      std::cout << elem << ' ';
    // output -> 222 222 222 66 77 88 99 11 22 33 44 55
    std::cout << '\n';

    // ----------------------------------------------------

    std::list<int> ilist{ 20, 30, 40 };
    ivec.insert(ivec.begin(), ilist.begin(), ilist.end());
    // inserting elements from list container to the beginning
    // of the vector container

    for (auto elem : ivec)
      std::cout << elem << ' ';
    // output -> 20 30 40 222 222 222 66 77 88 99 11 22 33 44 55

    // ----------------------------------------------------
  }
*/

/*
  #include <vector>
  #include <list>
  #include <string>
  #include <iterator>   // std::distance

  int main()
  {
    std::vector<int> ivec{ 11, 22, 33, 44, 55 };

    // -------------------------------------------------

    auto iter_added = ivec.insert(ivec.begin() + 1, 88);

    std::cout << *iter_added << '\n';	
    // output -> 88
    std::cout << std::distance(ivec.begin(), iter_added) << '\n';
    // output -> 1

    // -------------------------------------------------

    iter_added = ivec.insert(ivec.begin() + 1, { 55, 66, 77 });
    std::cout << *iter_added << '\n';	
    // output -> 55
    std::cout << std::distance(ivec.begin(), iter_added) << '\n';
    // output -> 1

    // 3 elements from std::initializer_list added 
    // and an iterator to a first element added is returned.

    // -------------------------------------------------

    std::vector<std::string> svec{ "hello", "world" };

    svec.emplace(svec.begin() + 1, 10, 'T');
    // (20, 'T') parameters will be pass 
    // to std::string's constructor
    // which will be constructed in 2nd position of the vector.

    for (auto str : svec)
      std::cout << str << ' ';
    // output -> hello TTTTTTTTTT world
    std::cout << '\n';

    // -------------------------------------------------

    // C_string("istanbul") parameter will be pass to 
    // std::string(const char*) constructor 
    // which will be constructed at end of the vector.

    svec.emplace_back("istanbul");
    for (auto str : svec)
      std::cout << str << ' ';
    // output -> hello TTTTTTTTTT world istanbul
    
    // -------------------------------------------------
  }
*/

/*
  // "pop_back" member function is constant time operation O(1)
  // "pop_back" member function will return void

  #include <vector>

  int main()
  {
    std::vector<int> ivec{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    while (!ivec.empty())
    {
      for (auto elem : ivec)
        std::cout << elem << ' ';
      std::cout << '\n';

      ivec.pop_back();
    }
    // output ->
    //  1 2 3 4 5 6 7 8 9
    //  1 2 3 4 5 6 7 8
    //  1 2 3 4 5 6 7
    //  1 2 3 4 5 6
    //  1 2 3 4 5
    //  1 2 3 4
    //  1 2 3
    //  1 2
    //  1
  }
*/

/*
  #include <vector>
  #include <iterator>   // std::prev

  int main()
  {
    std::vector<int> ivec{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    for (auto elem : ivec)
      std::cout << elem << ' ';
    // output -> 1 2 3 4 5 6 7 8 9
    std::cout << '\n';

    // -------------------------------------------------

    auto iter_deleted = ivec.erase(ivec.begin());

    for (auto elem : ivec)
      std::cout << elem << ' ';
    // output -> 2 3 4 5 6 7 8 9
    std::cout << '\n';

    std::cout << "iterator position after deletion  = " 
              << *iter_deleted << '\n';
    // output -> iterator position after deletion  = 2

    // -------------------------------------------------

    ivec.erase(std::prev(ivec.end()));

    for (auto elem : ivec)
      std::cout << elem << ' ';
    // output -> 2 3 4 5 6 7 8
    std::cout << '\n';

    // -------------------------------------------------

    ivec = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    while (!ivec.empty()) 
    {
      for (auto i : ivec) 
        std::cout << i << ' ';
      std::cout << '\n';
      
      ivec.erase(ivec.begin());
    }
    // output ->
    //  1 2 3 4 5 6 7 8 9
    //  2 3 4 5 6 7 8 9
    //  3 4 5 6 7 8 9
    //  4 5 6 7 8 9
    //  5 6 7 8 9
    //  6 7 8 9
    //  7 8 9
    //  8 9
    //  9

    // -------------------------------------------------
  }
*/

/*
  #include <vector>
  #include <iterator>  // std::next, std::prev

  int main()
  {
    using namespace std;

    vector<int> ivec{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    
    // -----------------------------------------------------

    ivec.erase(ivec.begin(), ivec.begin() + 3);
    // range parameter "erase" member function

    for (auto i : ivec) 
      std::cout << i << ' ';
    // output -> 4 5 6 7 8 9
    std::cout << '\n';

    // -----------------------------------------------------

    ivec.erase(ivec.begin(), std::next(ivec.begin(), 3));
    // range parameter "erase" member function
    
    for (auto i : ivec) 
      std::cout << i << ' ';
    // output -> 7 8 9
    std::cout << '\n';

    // -----------------------------------------------------

    // deleting only first and the last element from the vector

    ivec = { 11, 22, 33, 44, 55, 66, 77, 88, 99 };

    ivec.erase(std::next(ivec.begin()), std::prev(ivec.end()));
    for (auto i : ivec) 
      std::cout << i << ' ';
    // output -> 11 99
    std::cout << '\n';

    // -----------------------------------------------------
  }
*/

/*
  // erasing all elements from the container

  #include <vector>

  int main()
  {
    // ------------------------------------------------

    std::vector<int> ivec = { 11, 22, 33, 44, 55, 66, 77, 88, 99 };
    std::cout << "ivec.size() = " << ivec.size() << '\n';
    // output -> ivec.size() = 9

    ivec.clear();
    // "clear" member function does not have a return type

    std::cout << "ivec.size() = " << ivec.size() << '\n';
    // output -> ivec.size() = 0

    // ------------------------------------------------

    ivec = { 11, 22, 33, 44, 55, 66, 77, 88, 99 };
    std::cout << "ivec.size() = " << ivec.size() << '\n';
    // output -> ivec.size() = 9

    ivec.erase(ivec.begin(), ivec.end());
    // "erase" member function with range parameter
    std::cout << "ivec.size() = " << ivec.size() << '\n';
    // output -> ivec.size() = 0

    // ------------------------------------------------

    ivec = { 11, 22, 33, 44, 55, 66, 77, 88, 99 };
    std::cout << "ivec.size() = " << ivec.size() << '\n';
    // output -> ivec.size() = 9

    ivec.resize(0);
    // "resize" member function with "0" as an argument. 
    std::cout << "ivec.size() = " << ivec.size() << '\n';
    // output -> ivec.size() = 0

    // ------------------------------------------------

    ivec = { 11, 22, 33, 44, 55, 66, 77, 88, 99 };
    std::cout << "ivec.size() = " << ivec.size() << '\n';
    // output -> ivec.size() = 9

    ivec = {};    
    // using empty initalizer list
    std::cout << "ivec.size() = " << ivec.size() << '\n';
    // output -> ivec.size() = 0

    // ------------------------------------------------

    ivec = { 11, 22, 33, 44, 55, 66, 77, 88, 99 };
    std::cout << "ivec.size() = " << ivec.size() << '\n';
    // output -> ivec.size() = 9

    ivec = std::vector<int>{};    
    // passing empty temporary std::vector object
    // to copy asssignment operator function
    std::cout << "ivec.size() = " << ivec.size() << '\n';
    // output -> ivec.size() = 0

    // ------------------------------------------------
  }
*/

/*
  #include <vector>
  #include <string>
  #include <utility>  // std::swap

  int main()
  {

    std::vector<std::string> svec_1(100'000, "hello");
    std::vector<std::string> svec_2(100'000, "world");

    svec_1.swap(svec_2);
    // swap member function of std::vector class
    std::swap(svec_2, svec_1);
    // global std::swap function 

    // pointers of the containers will be swapped.
  }
*/

/*
  std::vector<bool> is a partial specialization.
    - not holding bool variables, holding bits.
    - so 10k bool variables can be stored in 1250 bytes.
*/

/*
  #include <vector>

  int main()
  {
    std::vector<int> ivec;
    std::vector<bool> bvec;

    // -------------------------------------------------

    ivec.flip();  // syntax error
    // error: 'class std::vector<int>' has no member named 'flip'
    
    // std::vector<int> specialization does not have 
    // "flip" member function in its interface.

    bvec.flip();
    // std::vector<bool> specialization does have
    // "flip" member function in its interface.

    // -------------------------------------------------

    bvec.data();  // syntax error
    // error: use of deleted function 
    // 'void std::vector<bool, _Alloc>::data()

    // std::vector<bool> partial specialization's 
    // "data" member function is deleted.
    // because of it is not holding bool variables
    // returning bool* is not possible.

    ivec.data();
    // std::vector<int> specialization 
    // does have "data" member function which is returning int* 

    // -------------------------------------------------
  }
*/

/*
  #include <vector>
  #include <cstdio>   // std::printf

  void print_array(const int* p_arr, size_t arr_size)
  {
    while (arr_size--)
      std::printf("%d ", *p_arr++);
  }

  int main()
  {
    std::vector<int> ivec{ 
        11, 22, 33, 44, 55, 66, 77, 88, 99 };

    print_array(ivec.data(), ivec.size());
    // output -> 11 22 33 44 55 66 77 88 99

    // "data" member function can be passed to C api functions
  }
*/

/*
  #include <vector>

  int main()
  {
    std::vector<bool> ivec{ 
      false, false, false, false, false, false, false, false };

    // -----------------------------------------------------

    // operator[] function of 
    // std::vector<bool> partial specialization 
    // is returning a proxy class.

    ivec[2] = true;
    ivec[2].operator=(true);
    // Those 2 lines are equivalent.

    // -----------------------------------------------------

    auto proxy_class = ivec[3];
    // "proxy_class"'s type is std::vector<bool>::reference
    proxy_class = true;

    // -----------------------------------------------------

    for (const auto& val : ivec)
      std::cout << val << ' ';
    // output -> 0 0 1 1 0 0 0 0
  }
*/

/*
  // primary template for Vector
  template <typename T, typename A>
  class Vector {};

  // partial specialization for Vector<bool, A>
  template <typename A>
  class Vector<bool, A> {};
  
  // mental model for std::vector::reference proxy class
  // in std::vector<bool> partial specialization
  class BVector {
  private:
    unsigned char m_buffer[1000]{};   // 8000 bits
  public:
    class Reference {};
    Reference& operator[](size_t N);  // returning bits
  };
*/

/*
                      ------------------------
                      | std::deque container |
                      ------------------------
*/

/*
  - std::deque(double ended queue) contains different chunk blocks.

  - reaching an element with an index operator is a constant time.
  - first need to reach the chunk that holds the element 
    of that index, then reaching the exact element.

  i.e. 
    100 elements in deque container. 10 element in each chunk.
    if index 95 wanted, first need to reach the 10th chunk then 
    the 6th element in that chunk.

  - chunks are not contigious
  - for every chunk, memory allocation needed.
  - all chunk address's are stored in a pointer array
    in implementation of std::deque container.
  - it's iterator type is std::random_access_iterator

  -------------------------------------------------------------
  differences between std::vector and std::deque containers

  - "push_front" is also a CONSTANT TIME operation like
    "push_back" operation.
    different chunks have been used for "push_front" and 
    "push_back" operations.

  - std::deque<bool> holds bool values, std::vector<bool> 
    DID NOT hold bool values.

  - std::deque have "push_front", "pop_front", "emplace_front"
    member functions.

  - std::deque does not have "data" member function, 
    because of chunks are not contigious.

  -------------------------------------------------------------

  - if an insertion operation WON'T be done to corners(first or last)
    all iterators and references will become INVALID.
  - if an insertion operation WILL be done to corners(first or last)
    all iterators will become INVALID, but references are still VALID.
  
  - if a remove operation WON'T be done to corners(first or last)
    all iterators and references will become INVALID.
  - if a remove operation WILL be done to corners(first or last)
    iterators and references will become INVALID 
    for ONLY deleted elements.

  -------------------------------------------------------------
*/

/*
  #include <deque>
  #include <string>

  int main()
  {
    std::deque<std::string> s_deque { 
      "hello", " world", "galaxy", "universe", 
      "we", "are", "live", "from", "Istanbul" };

    auto iter = s_deque.begin() + 3;
    auto& ref = s_deque[3];

    std::cout << "*iter = " << *iter << '\n';
    // output -> *iter = universe
    std::cout << "ref = " << ref << '\n';
    // output -> ref = universe

    // ---------------------------------------------------

    s_deque.insert(s_deque.begin() + 1, "Izmir");
    // insertion to 2nd position with insert() member function.
    // insertion to NOT corners(first or last)

    // iterators and references will become INVALID

    std::cout << "*iter = " << *iter << '\n'; 
    // undefined behaviour(UB).
    // dereferecing an INVALID iterator

    std::cout << "ref = " << ref << '\n';
    // undefined behaviour(UB).
    // dereferecing an INVALID reference

    // ---------------------------------------------------
  }
*/

/*
  #include <deque>
  #include <string>

  int main()
  {
    using namespace std;

    std::deque<std::string> s_deque { 
      "hello", " world", "galaxy", "universe", 
      "we", "are", "live", "from", "Istanbul" };

    auto iter = s_deque.begin() + 3;
    auto& ref = s_deque[3];

    std::cout << "*iter = " << *iter << '\n';
    // output -> *iter = universe
    std::cout << "ref = " << ref << '\n';
    // output -> ref = universe

    // -------------------------------------------------

    s_deque.push_front("Izmir");
    // insertion to 1st position with "push_front" member function.
    // insertion to corners(first or last)

    // iterators will become INVALID, 
    // but references are still VALID.

    std::cout << "ref = " << ref << '\n';   // VALID
    // output -> ref = universe

    std::cout << "*iter = " << *iter << '\n'; 
    // undefined behaviour(UB).
    // dereferecing an INVALID iterator

    // -------------------------------------------------
  }
*/

/*
  #include <deque>
  #include <string>

  int main()
  {
    std::deque<std::string> s_deque { 
      "hello", " world", "galaxy", "universe", 
      "we", "are", "live", "from", "Istanbul" };

    auto iter = s_deque.begin() + 3;
    auto ptr  = &s_deque[3];

    std::cout << *iter << " - " << *ptr << '\n';
    // output -> universe - universe

    for (int i = 0; i < 3; ++i) 
    {
      s_deque.pop_front();
      s_deque.pop_back();
      std::cout << *iter << " - " << *ptr << '\n';
    }
    // output ->
    //  universe - universe
    //  universe - universe
    //  universe - universe

    // remove operation is done to corners(first or last) position
    // with "pop_front" and "pop_back" member functions.
    // so only iterators and references become invalid 
    // for deleted elements.
    // because of the index 3 is not deleted, 
    // iterator and reference to itself is still VALID
  }
*/

/*
                      -----------------------
                      | std::list container |
                      -----------------------
*/

/*
  advantages :
  ------------
  - to a known address, insertion and deletion operations 
    is O(1) a constant time operation.
  - because of elements are being hold in nodes(structure), 
    which have pointer data members,
    swapping large objects will not copy the whole object,
    only will copy the data member pointers.
  - std::list, std::forward_list containers 
    have "reverse" member function which std::vector does not have.
  - splice operations can be done with list containers, 
    getting a node from one list and adding it to another list.

  disadvantages :
  ---------------
  - every insertion operation will allocate dynamic memory.
    in std::vector container, with "reserve" function
    reallocation cost can be omitted. 
    each malloc operation -> (object memory + overhead)
*/

/*
  - std::list containers iterator type is 
    "std::bidirectional_iterator"
*/

/*
  #include <list>

  template <typename T, typename A = std::allocator<T>>
  class List {};

  int main()
  {
    std::list<int> ilist(10);

    ilist.reverse();
    ilist.sort();
    ilist.unique();
    ilist.merge();
    ilist.remove();
    ilist.remove_if();
    ilist.splice();
    // member functions of std::list container
  }
*/

/*
  #include <list>
  #include <functional>   // std::greater(function object)

  int main()
  {
    std::list<int> ilist{ 1, 15, 6, 2, 19, 86, 97, 32, 12, 28 };

    // ---------------------------------------------------------

    for (auto elem : ilist)
      std::cout << elem << ' ';
    // output -> 1 15 6 2 19 86 97 32 12 28
    std::cout << '\n';

    // ---------------------------------------------------------

    ilist.reverse();

    for (auto elem : ilist)
      std::cout << elem << ' ';
    // output -> 28 12 32 97 86 19 2 6 15 1
    std::cout << '\n';

    // ---------------------------------------------------------

    ilist.sort(); 
    // default predicate is "std::less{}"

    for (auto elem : ilist)
      std::cout << elem << ' ';
    // output -> 1 2 6 12 15 19 28 32 86 97
    std::cout << '\n';

    // ---------------------------------------------------------

    ilist.sort(std::greater{});

    for (auto elem : ilist)
      std::cout << elem << ' ';
    // output -> 97 86 32 28 19 15 12 6 2 1
    std::cout << '\n';

    // ---------------------------------------------------------

    ilist.push_front(32);

    for (auto elem : ilist)
      std::cout << elem << ' ';
    // output -> 32 97 86 32 28 19 15 12 6 2 1
    std::cout << '\n';

    // ---------------------------------------------------------

    auto N_removed = ilist.remove(32);

    for (auto elem : ilist)
      std::cout << elem << ' ';
    // output -> 97 86 28 19 15 12 6 2 1
    std::cout << '\n';

    std::cout << "removed '32' count = " << N_removed << '\n';
    // output -> removed '32' count = 2

    // ---------------------------------------------------------

    ilist.remove_if([](int val){ return val % 2 == 0; });

    for (auto elem : ilist)
      std::cout << elem << ' ';
    // output -> 97 19 15 1
    std::cout << '\n';

    // ---------------------------------------------------------
  }
*/

/*
  #include <list>
  #include <random>       
  // std::mt19937, std::uniform_int_distribution
  #include <algorithm>    // std::generate

  void print_list(std::ostream& os, std::list<int>& list)
  {
    for (auto elem : list)
      os << elem << ' ';
    os << '\n';
  }

  int main()
  {
    std::list<int> ilist1(10);
    std::list<int> ilist2(10);

    std::mt19937 eng;
    std::uniform_int_distribution dist{ 0,1000 };

    std::generate(ilist1.begin(), ilist1.end(), 
                  [&](){ return dist(eng); });
    std::generate(ilist2.begin(), ilist2.end(), 
                  [&](){ return dist(eng); });

    ilist1.sort();  
    ilist2.sort();
    // default predicate is std::less{}

    std::cout << "ilist1 = ";
    print_list(std::cout, ilist1);
    // output -> ilist1 = 127 135 221 308 632 815 835 906 914 969

    std::cout << "ilist2 = ";
    print_list(std::cout, ilist2);
    // output -> ilist2 = 97 188 278 547 547 958 965 968 993 997

    // -------------------------------------------------------

    ilist1.merge(ilist2);

    std::cout << "ilist1.size() = " << ilist1.size() << '\n';
    // output -> ilist1.size() = 20
    std::cout << "ilist2.size() = " << ilist2.size() << '\n';
    // output -> ilist2.size() = 0

    std::cout << "ilist1 = ";
    print_list(std::cout, ilist1);
    // output -> 
    //  ilist1 =  97 127 135 188 221 278 308 547 547 632
    //            815 835 906 914 958 965 968 969 993 997

    std::cout << "ilist2 = ";
    print_list(std::cout, ilist2);
    // output -> ilist2 = 

    // lists are still in sorted order after "merge" operation.

    // -------------------------------------------------------
  }
*/

/*
  #include <list>
  #include <functional>   // std::greater
  #include <random>       
  // std::mt19937, std::uniform_int_distribution
  #include <algorithm>    // std::generate

  void print_list(std::ostream& os, std::list<int>& list)
  {
    for (auto elem : list)
      os << elem << ' ';
    os << '\n';
  }

  int main()
  {
    std::list<int> ilist1(10);
    std::list<int> ilist2(10);

    std::mt19937 eng;
    std::uniform_int_distribution dist{ 0,1000 };

    std::generate(ilist1.begin(), ilist1.end(), 
                  [&](){ return dist(eng); });
    std::generate(ilist2.begin(), ilist2.end(), 
                  [&](){ return dist(eng); });

    ilist1.sort(std::greater{});  
    ilist2.sort(std::greater{});

    std::cout << "ilist1 = ";
    print_list(std::cout, ilist1);
    // output -> ilist1 = 969 914 906 835 815 632 308 221 135 127

    std::cout << "ilist2 = ";
    print_list(std::cout, ilist2);
    // output -> ilist2 = 997 993 968 965 958 547 547 278 188 97

    // -------------------------------------------------------

    ilist2.merge(ilist1, std::greater{});

    std::cout << "ilist1.size() = " << ilist1.size() << '\n';
    // output -> ilist1.size() = 0
    std::cout << "ilist2.size() = " << ilist2.size() << '\n';
    // output -> ilist2.size() = 20

    std::cout << "ilist1 = ";
    print_list(std::cout, ilist1);
    // output -> ilist1 = 

    std::cout << "ilist2 = ";
    print_list(std::cout, ilist2);
    // output -> 
    //  ilist2 =  997 993 969 968 965 958 914 906 835 815 
    //            632 547 547 308 278 221 188 135 127 97

    // -------------------------------------------------------
  }
*/

/*
  #include <list>
  #include <algorithm>  // std::generate
  #include <iterator>   // std::next, std::prev

  void print_container(const auto& con)
  {
    for (auto elem : con)
      std::cout << elem << ' ';
    std::cout << '\n';
  }

  void refresh_containers(auto& con_1, auto& con_2)
  {
    con_1 = { 1, 2, 3, 4, 5 };
    con_2 = { 6, 7, 8, 9, 10 };
  }

  int main()
  {
    using namespace std;

    std::list<int> ilist1{ 1, 2, 3, 4, 5 };
    std::list<int> ilist2{ 6, 7, 8, 9, 10 };

    // ----------------------------------------------------

    ilist1.splice(ilist1.begin(), ilist2);

    std::cout << "ilist1.size() = " << ilist1.size() << '\n';
    // output -> ilist1.size() = 10
    std::cout << "ilist2.size() = " << ilist2.size() << '\n';
    // output -> ilist2.size() = 0

    print_container(ilist1);  // output -> 6 7 8 9 10 1 2 3 4 5

    // ----------------------------------------------------

    refresh_containers(ilist1, ilist2);
    
    ilist1.splice(ilist1.end(), ilist2);

    std::cout << "ilist1.size() = " << ilist1.size() << '\n';
    // output -> ilist1.size() = 10
    std::cout << "ilist2.size() = " << ilist2.size() << '\n';
    // output -> ilist2.size() = 0

    print_container(ilist1);  // output -> 1 2 3 4 5 6 7 8 9 10

    // ----------------------------------------------------

    refresh_containers(ilist1, ilist2);

    ilist1.splice(std::prev(ilist1.end()), ilist2);

    std::cout << "ilist1.size() = " << ilist1.size() << '\n';
    // output -> ilist1.size() = 10
    std::cout << "ilist2.size() = " << ilist2.size() << '\n';
    // output -> ilist2.size() = 0

    print_container(ilist1);  // output -> 1 2 3 4 6 7 8 9 10 5

    // ----------------------------------------------------

    refresh_containers(ilist1, ilist2);

    // ilist1 = { 1, 2, 3, 4, 5 }
    // ilist2 = { 6, 7, 8, 9, 10 }

    ilist1.splice(std::next(ilist1.begin(), 2), 
                  ilist2, std::next(ilist2.begin()));

    std::cout << "ilist1.size() = " << ilist1.size() << '\n';
    // output -> ilist1.size() = 6
    std::cout << "ilist2.size() = " << ilist2.size() << '\n';
    // output -> ilist2.size() = 4

    print_container(ilist1);  // output -> 1 2 7 3 4 5
    print_container(ilist2);  // output -> 6 8 9 10

    // ----------------------------------------------------

    refresh_containers(ilist1, ilist2);

    // ilist1 = { 1, 2, 3, 4, 5 }
    // ilist2 = { 6, 7, 8, 9, 10 }

    ilist1.splice(std::next(ilist1.begin()), 
                  ilist2, 
                  ilist2.begin(), std::next(ilist2.begin(), 3));

    std::cout << "ilist1.size() = " << ilist1.size() << '\n';
    // output -> ilist1.size() = 8
    std::cout << "ilist2.size() = " << ilist2.size() << '\n';
    // output -> ilist2.size() = 2

    print_container(ilist1);  // output -> 1 6 7 8 2 3 4 5
    print_container(ilist2);  // output -> 9 10

    // ----------------------------------------------------
  }
*/

/*
  #include <list>
  #include <random>
  // std::mt19937, std::uniform_int_distribution
  #include <algorithm>  // std::generate

  void print_container(const auto& con)
  {
    for (auto elem : con)
      std::cout << elem << ' ';
    std::cout << '\n';
  }

  int main()
  {
    std::mt19937 eng;
    std::uniform_int_distribution dist{ 0, 1000 };

    std::list<int> ilist1(50);
    std::generate(ilist1.begin(), ilist1.end(), 
                  [&](){ return dist(eng); });

    print_container(ilist1);
    // output ->
    //  815 135 906 835 127 969 914 221 632 308 97 
    //  547 278 188 547 993 958 997 965 968 157 726 
    //  971 982 958 109 485 798 801 297 142 4 422 112 
    //  916 640 792 879 960 504 656 798 35 361 849 
    //  212 934 682 679 399

    // ----------------------------------------------------

    ilist1.unique([](int x, int y){ return x % 2 == y % 2; });

    std::cout << "ilist1.size() = " << ilist1.size() << '\n';	
    // output -> x.size() = 25

    print_container(ilist1);
    // output ->
    //  815 906 835 914 221 632 97 278 547 958 
    //  997 968 157 726 971 982 109 798 801 142 
    //  879 960 35 212 679

    // ----------------------------------------------------

    ilist1.resize(50);
    std::generate(ilist1.begin(), ilist1.end(), 
                  [&](){ return dist(eng); });

    std::cout << "ilist1.size() = " << ilist1.size() << '\n';	
    // output -> x.size() = 50

    print_container(ilist1);
    // output ->
    //  758 741 743 475 392 422 656 174 171 
    //  302 706 798 31 316 277 873 46 149 97 
    //  995 824 822 695 125 317 764 951 491 34 
    //  664 439 126 381 210 766 51 795 36 187 
    //  409 490 458 446 488 646 794 710 921 755 808

    // ----------------------------------------------------

    auto deleted_elem_count = 
      ilist1.unique([](int x, int y){ return x % 10 == y % 10; });

    std::cout << "ilist1.size() = " << ilist1.size() << '\n';	
    // output -> x.size() = 46

    std::cout << "deleted element count = " 
              << deleted_elem_count << '\n';	
    // output -> deleted element count = 4

    print_container(ilist1);
    // output ->
    //  758 741 743 475 392 656 174 171 302 
    // 706 798 31 316 277 873 46 149 97 995 
    // 824 822 695 317 764 951 34 439 126 381 
    // 210 766 51 795 36 187 409 490 458 446 
    // 488 646 794 710 921 755 808

    // ----------------------------------------------------
  }
*/

/*
                  -------------------------------
                  | std::forward_list container |
                  -------------------------------
*/

/*
  ---------------------------------------------------------

  std::forward_list's iterator type is "std::forward_iterator"

  ---------------------------------------------------------

  example forward_list :  12 -> 4 -> 43 -> 7

  if a node wanted to insert, after to 2nd node(4),
  need to have an iterator to node(12)

  if 3rd node(43) wanted to delete, 
  need to have an iterator to node(4)
  because when 3rd node(43) is deleted,
  2nd node(4) next pointer should be changed to 7.
  so because of the iterator type is forward_iterator,
  accessing to the previous node is not possible.
  so having an iterator to the previous node is a must.

  ---------------------------------------------------------

  - std::forward_list class's interface has only 1 pointer
    to the beginning of the list.
  - because of there is no size data member or a pointer 
    to the end of the list, calculating the size of the list 
    is an O(n) operation (traversing the list from the beginning)

  - STL container's "size" member functions are guaranteed to be 
    O(1) operation, so std::forward_list does not have a "size"
    member function.

  ---------------------------------------------------------
*/

/*
  #include <forward_list>
  #include <iterator>   // std::distance, std::advance

  int main()
  {
    std::forward_list<int> ilist{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    std::cout << "size = " 
              << std::distance(ilist.begin(), ilist.end()) << '\n';
    // output -> size = 9
    // std::distance algorithm is O(n) operation.

    // ---------------------------------------------------

    auto iter1 = ilist.end();

    --iter1; // syntax error
    // error: no match for 'operator--' 
    //  (operand type is 'std::_Fwd_list_iterator<int>')

    // ---------------------------------------------------

    auto iter2 = ilist.begin();
    ++iter2;  // VALID

    std::cout << *iter2 << '\n';  // output -> 2

    // ---------------------------------------------------

    auto iter3 = ilist.begin();
    std::advance(iter3, 3);

    std::cout << *iter3 << '\n';  // output -> 4

    // ---------------------------------------------------
  }
*/

/*
  #include <forward_list>
  #include <iterator>   // std::next

  void print_container(const auto& con)
  {
    for (auto elem : con)
      std::cout << elem << ' ';
    std::cout << '\n';
  }

  int main()
  {
    std::forward_list<int> ilist { 
      11, 22, 33, 44, 55, 66, 77, 88, 99 };

    // -------------------------------------------------

    auto iter = std::next(ilist.begin());
    std::cout << "*iter = " << *iter << '\n';
    // output -> *iter = 22

    // -------------------------------------------------

    ilist.insert_after(iter, -11);
    print_container(ilist);
    // output -> 11 22 -11 33 44 55 66 77 88 99
    std::cout << "*iter = " << *iter << '\n';
    // output -> *iter = 22

    // -------------------------------------------------

    ilist.erase_after(iter);
    print_container(ilist);
    // output -> 11 22 33 44 55 66 77 88 99

    // -------------------------------------------------

    ilist.insert_after(iter, { 444, 555, 666 });
    print_container(ilist);
    // output -> 11 22 444 555 666 33 44 55 66 77 88 99
    std::cout << "*iter = " << *iter << '\n';
    // output -> *iter = 22

    // -------------------------------------------------

    ilist.erase_after(iter, std::next(iter, 4));
    print_container(ilist);
    // output -> 11 22 33 44 55 66 77 88 99

    // -------------------------------------------------

    ilist.insert_after(ilist.begin(), { 444, 555, 666 });
    print_container(ilist);
    // output -> 11 444 555 666 22 33 44 55 66 77 88 99

    // -------------------------------------------------

    ilist.erase_after(ilist.begin(), 
                      std::next(ilist.begin(), 4));
    print_container(ilist);
    // output -> 11 22 33 44 55 66 77 88 99

    // -------------------------------------------------

    ilist.insert_after(ilist.before_begin(), { 444, 555, 666 });
    print_container(ilist);
    // output -> 444 555 666 11 22 33 44 55 66 77 88 99

    // -------------------------------------------------

    ilist.erase_after(ilist.before_begin(), 
                      std::next(ilist.begin(), 3));
    print_container(ilist);
    // output -> 11 22 33 44 55 66 77 88 99

    // -------------------------------------------------
  }
*/

/*
  #include <forward_list>
  #include <iterator>   // std::next

  void print_container(const auto& con)
  {
    int mod_counter = 1;
    for (const auto& elem : con)
    {
      if (mod_counter % 10 == 0)
        std::cout << elem << '\n'; 
      else
        std::cout << elem << ' ';

      ++mod_counter;
    }

    std::cout << '\n';
  }

  int main()
  {
    std::forward_list<int> ilist;

    for (int i = 0; i < 100; ++i)
      ilist.push_front(++i);

    print_container(ilist);
    // output ->
    //  99 97 95 93 91 89 87 85 83 81
    //  79 77 75 73 71 69 67 65 63 61
    //  59 57 55 53 51 49 47 45 43 41
    //  39 37 35 33 31 29 27 25 23 21
    //  19 17 15 13 11 9 7 5 3 1

    // ----------------------------------------------------

    int deleted_elem_val = 59;
    // need to find the previous node of (59) which is (61)

    auto iter = ilist.before_begin();

    while (std::next(iter) != ilist.end()) 
    {
      if (*std::next(iter) == deleted_elem_val) {
        ilist.erase_after(iter);
        break;
      }
      ++iter;
    }

    print_container(ilist);
    // output ->
    //  99 97 95 93 91 89 87 85 83 81
    //  79 77 75 73 71 69 67 65 63 61
    //  57 55 53 51 49 47 45 43 41 39
    //  37 35 33 31 29 27 25 23 21 19
    //  17 15 13 11 9 7 5 3 1
  }
*/

/*
                        ----------------------
                        | std::set container |
                        ----------------------
*/

/*
  #include <functional>   // std::less
  #include <memory>       // std::allocator

  template <typename Key, 
            typename Compare = std::less<Key>, 
            typename A = std::allocator<Key>>
  class Set{};
*/

/*
  #include <set>
  #include <functional>   // std::less
  #include "../headers/nutility.h"

  int main()
  {

    std::set<int> iset1;
    std::set<int, std::less<int>> iset2;
    // Those 2 lines are equivalent.

    rfill(iset1, 10, Irand{ 0, 30 });

    for (const auto& elem : iset1)
      std::cout << elem << ' ';
    // output -> 5 8 16 17 18 20 21 24 25 28
  }
*/

/*
  #include <set>
  #include <cmath>      // std::abs
  #include "../headers/nutility.h"

  // std::set's 2nd template parameter 
  // Compare type is "Comp" functor class
  struct Comp {
    bool operator()(int x, int y) const
    {
      return std::abs(x) < std::abs(y);
    }
  };

  int main()
  {
    std::set<int, Comp> iset;

    rfill(iset, 10, Irand{ -50, 50 });

    for (const auto& elem : iset)
      std::cout << elem << ' ';
    // output -> -10 11 12 -13 -17 -21 34 35 -44 -50
  }
*/

/*
  #include <set>
  #include <cmath>      // std::abs
  #include "../headers/nutility.h"

  // std::set's 2nd template parameter 
  // Compare type is "fn_compare" global function
  bool fn_compare(int x, int y)
  {
    return std::abs(x) < std::abs(y);
  }

  int main()
  {
    std::set<int, bool(*)(int,int)> iset_1(&fn_compare);
    std::set<int, decltype(&fn_compare)> iset_2(&fn_compare);
    // Those 2 lines are equivalent.

    // address of the function should be passed to 
    // constructor as an argument

    // ----------------------------------------------

    rfill(iset_1, 10, Irand{ -100, 100 });
    for (const auto& elem : iset_1)
      std::cout << elem << ' ';
    // output -> 5 -16 -28 -35 53 -56 63 88 -90 -97

    std::cout << '\n';

    // ----------------------------------------------

    rfill(iset_2, 10, Irand{ -100, 100 });
    for (const auto& elem : iset_2)
      std::cout << elem << ' ';
    // output -> 1 4 9 30 48 56 -69 -75 -76 -83

    // ----------------------------------------------
  }
*/

/*
  #include <set>
  #include <cmath>  // std::abs
  #include "../headers/nutility.h"

  // std::set's 2nd template parameter 
  // Compare type is "fn" lambda expression

  int main()
  {
    auto fn = [](int x, int y){
      return std::abs(x) < std::abs(y);
    };

    // ---------------------------------------------

    std::set<int, decltype(fn)> i_set1;
    // syntax error before C++20

    // error: use of deleted function 
    // 'main()::<lambda(int, int)>::<lambda>()'
    // note: a lambda closure type 
    // has a deleted default constructor

    // when i_set1's default constructor is called,
    // it needs to call default constructor of the lambda class.
    // which is a deleted function before C++20.

    // ---------------------------------------------

    std::set<int, decltype(fn)> i_set2(fn);
    // VALID before C++20
    
    // ----------------------------------------------

    rfill(i_set1, 10, Irand{ -100, 100 });
    for (const auto& elem : i_set1)
      std::cout << elem << ' ';
    // output -> -5 28 -31 41 -44 52 -65 -92 -93 -97

    std::cout << '\n';

    // ----------------------------------------------

    rfill(i_set2, 10, Irand{ -100, 100 });
    for (const auto& elem : i_set2)
      std::cout << elem << ' ';
    // output -> 6 -15 16 43 -46 55 -68 -79 83 -89

    // ----------------------------------------------
  }
*/

/*
  #include <set>
  #include <string>
  #include <cstring>  // std::strcmp
  #include "../headers/nutility.h"

  bool str_pred(const std::string& s1, const std::string& s2)
  {
    return std::strcmp(s1.c_str(), s2.c_str()) < 0;
  }

  int main()
  {
    std::set<std::string, decltype(&str_pred)> str_set(str_pred);

    for (int i = 0; i < 15; ++i) 
      str_set.insert(rname() + ' ' + rfname());

    print(str_set, "\n");
    // output ->
    //  akin ulakci
    //  aycan elebasi
    //  bennur etci
    //  ceyhan altinorak
    //  ciler sarikafa
    //  eda fincan
    //  fikret selercan
    //  fuat safkan
    //  korhan bilgic
    //  malik lombak
    //  melike kulaksiz
    //  menekse kilicdar
    //  su pirlanta
    //  tunc zaimoglu
    //  ufuk silifkeli
  }
*/

/*
  COMPARATOR needs to be,
  -----------------------

  1. anti-simetric
    if  (x op y) == true ---> (y op x) == false
  2. irreflexive
    x < x == false
  3. transitive
    if (a < b == true) && (b < c == true) ---> (a < c == true)
  4. transitivity equivalance
    if (a < b == false) && (b < a == false) ---> (b = a == true)
    if (b < c == false) && (c < b == false) ---> (c = b == true)
    so (a = c == true)
*/

/*
  Question : 
    Why the same key needs to be in a container multiple times ?

  Answer : 
    i.e, there are lots of students in a school that have a same 
    name and their exam results wanted to be mapped with their names,
    so lots of people with the same name(key) can be in a container.
*/

/*
  #include <string>
  #include <set>    // std::set, std::multiset

  int main()
  {
    // ---------------------------------------------------

    std::set<std::string> set1{ 
      "world", "galaxy", "universe", "world", "galaxy" };

    std::cout << "set1.size() = " << set1.size() << '\n';
    // output -> myset.size() = 3

    for (const auto& elem : set1)
      std::cout << elem << ' ';
    // output -> galaxy universe world
    std::cout << '\n';

    // ---------------------------------------------------

    std::multiset<std::string> multiset1{ 
      "world", "galaxy", "universe", "world", "galaxy" };

    std::cout << "mymultiset.size() = " << multiset1.size() << '\n';
    // output -> mymultiset.size() = 5

    for (const auto& elem : multiset1)
      std::cout << elem << ' ';
    // output -> galaxy galaxy universe world world

    // ---------------------------------------------------
  }
*/

/*
  differences between 
    - global std::find function, 
    - set container's "find" member function

  1. Complexity
    global std::find function                 O(n)      - Linear
    set container's "find" member function		O(log(n)) - Logarithmic

  2. 
    global std::find function's equality and 
    set containers equivalance results can be different.
    
    global std::find will will check for equality 
    (*iter == value)

    set's "find" member function is using comparator 
    to understand value is equal to the element in the set.
    (-15) can be equal to (15) with using a comparator
    that compares absolute values.
*/

/*
  #include <set>
  #include <string>
  #include <iterator>   // std::distance
  #include "../headers/nutility.h"

  int main()
  {
    std::set<std::string> set_1;

    rfill(set_1, 200, rname);
    //print(set_1," ", std::cout);

    std::string key{ "hande" };

    if (auto iter = set_1.find(key); iter != set_1.end()) {
      std::cout << *iter << " is found at index = " 
                << std::distance(set_1.begin(), iter) << '\n';
    }
    else
      std::cout << key << " is not found\n";

    // output -> hande is found at index = 89
  }
*/

/*
  #include <set>
  #include <string>
  #include "../headers/nutility.h"

  int main()
  {
    std::set<std::string> set_1;

    rfill(set_1, 100, rname);
    // print(set_1, " ", std::cout);

    std::string key{ "adem" };

    // ----- before C++20 "count" member function -----

    if (set_1.count(key))
      std::cout << key << " is found\n";
    else
      std::cout << key << " is not found\n";
    // output -> adem is found

    // ----- since C++20 "contains" member function -----

    if (set_1.contains(key))
      std::cout << key << " is found\n";
    else
      std::cout << key << " is not found\n";
    // output -> adem is found

    // --------------------------------------------------
  }
*/

/*
  #include <set>
  #include <string>
  #include <iterator>   // std::next
  #include "../headers/nutility.h"

  int main()
  {
    std::set<std::string> set_1;
    rfill(set_1, 100, rname);

    // --------------------------------------------

    auto iter = std::next(set_1.begin(), 5);
    *iter = "hello";  // syntax error
    // error: no match for 'operator=' 
    // (operand types are 'const std::string<char>'  
    // and 'const char [6]')

    // "*iter" expression returns const T& type.
    // which is const string& in this case.

    // --------------------------------------------

    const_cast<std::string&>(*iter) = "world";
    // VALID but undefined behaviour(UB)
    // because data corruption will happen in the set continer
    // if the value is being changed.

    // --------------------------------------------
    
    // set container, holds its members as a binary search tree
    // elements are sorted in a tree structure.
    // so changing the value of an element will corrupt the tree.

    // 1 2 3 4 5 * 6 7 8 9
    // when * is being changed with 99,
    // next search in binary tree will become corrupted.

    // --------------------------------------------
  }
*/

/*
  #include <set>
  #include <utility>      // std::pair
  #include <iterator>     // std::distance
  #include "../headers/nutility.h"

  int main()
  {
    std::set<int> iset{ 11, 22, 33, 44, 55, 66, 77, 88, 99 };
    print(iset);
    // output -> 11 22 33 44 55 66 77 88 99

    using set_iter = std::set<int>::iterator;

    // ---------------------------------------------------

    std::pair<set_iter, bool> ret1 = iset.insert(25);

    if (ret1.second) {
      std::cout << *ret1.first  << " has been added at index = " 
                << std::distance(iset.begin(), ret1.first) << '\n';
    }
    else
      std::cout << "value can not be added\n";
    // output -> 25 has been added at index = 2

    print(iset);
    // output -> 11 22 25 33 44 55 66 77 88 99

    // ---------------------------------------------------

    auto ret2 = iset.insert(44);
  
    if (ret2.second) {
      std::cout << *ret2.first  << " has been added at index = " 
                << std::distance(iset.begin(), ret2.first) << '\n';
    }
    else {
      std::cout << *ret2.first << " is already exist at index = " 
                << std::distance(iset.begin(), ret2.first) << '\n';
    }
    
    // output -> 44 is already exist at index = 4

    print(iset);
    // output -> 11 22 25 33 44 55 66 77 88 99

    // ---------------------------------------------------

    if (iset.insert(87).second)
      std::cout << "new value has been added\n";

    print(iset);
    // output -> 11 22 25 33 44 55 66 77 87 88 99

    // ---------------------------------------------------


    auto [iter, is_inserted] = iset.insert(18);
    // structured binding

    if (is_inserted) {
      std::cout << *iter  << " has been added at index = " 
                << std::distance(iset.begin(), iter) << '\n';
    }
    else {
      std::cout << *iter << " is already exist at index = " 
                << std::distance(iset.begin(), iter) << '\n';
    }
    // output -> 18 has been added at index = 1

    print(iset);
    // output -> 11 18 22 25 33 44 55 66 77 87 88 99
    
    // ---------------------------------------------------
  }
*/

/*
  Because of multiset container does not hold unique keys,
  its "insert" member function returns an iterator, 
  not an <iterator, bool> pair.
*/

/*
  #include <set>
  #include <utility>    // std::pair, std::make_pair
  #include "../headers/nutility.h"

  int main()
  {
    std::set<std::pair<int, double>> pair_set;

    pair_set.insert(std::make_pair(11, 22.2));
    pair_set.emplace(33, 44.4);	

    // passing (33, 44.4) arguments to 
    // std::pair object's(which is inside std::set) constructor.

    print(pair_set);  // output -> [11, 22.2] [33, 44.4]
  }
*/

/*
  // hint insert overloads will decrease the cost.
  // when the hint is given
  // (where the element is likely to be inserted)

  #include <set>
  #include <iterator>  // std::next
  #include "../headers/nutility.h"

  int main()
  {
    std::set<int> iset{ 11, 22, 33, 44, 55, 66, 77 };

    // ---------------------------------------------

    iset.insert(std::next(iset.begin()), 17);
    // hint insert overload

    print(iset);  // output -> 11 17 22 33 44 55 66 77

    // ---------------------------------------------

    iset.emplace_hint(iset.begin(), 9);
    // hint emplace overload

    print(iset);  // output -> 9 11 17 22 33 44 55 66 77

    // ---------------------------------------------
  }
*/

/*
  #include <set>
  #include <iterator>   // std::next
  #include "../headers/nutility.h"

  int main()
  {

    std::set<int> iset{ 11, 22, 33, 44, 55, 66, 77, 88, 99 };
    print(iset);  // output -> 11 22 33 44 55 66 77 88 99

    // ------------------------------------------------

    iset.erase(iset.begin());
    print(iset);  // output -> 22 33 44 55 66 77 88 99

    // ------------------------------------------------

    iset.erase(std::next(iset.begin(), 3));
    print(iset);  // output -> 22 33 44 66 77 88 99

    // ------------------------------------------------
  }
*/

/*
  #include <set>
  #include "../headers/nutility.h"

  int main()
  {
    using namespace std;

    std::set<int> iset{ 11, 22, 33, 44, 55, 66, 77, 88, 99 };
    print(iset);  // output -> 11 22 33 44 55 66 77 88 99

    auto iter_beg = iset.find(44);
    auto iter_end = iset.find(88);

    iset.erase(iter_beg, iter_end); 
    // range-erase -> [44, 88) 
    
    print(iset);  // output -> 11 22 33 88 99
  }
*/

/*
  #include <set>
  #include <string>
  #include "../headers/nutility.h"

  int main()
  {
    // ---------------------------------------------------

    std::set<int> iset{ 11, 22, 33, 44, 55, 66, 77, 88, 99 };

    print(iset);  
    // output -> 11 22 33 44 55 66 77 88 99

    auto del_count1 = iset.erase(33);
    auto del_count2 = iset.erase(25);

    std::cout << "del_count1 = " << del_count1 << '\n';
    // output -> del_count1 = 1
    std::cout << "del_count2 = " << del_count2 << '\n';
    // output -> del_count2 = 0
    
    print(iset);  
    // output -> 11 22 44 55 66 77 88 99

    // ---------------------------------------------------

    std::multiset<int> imset{ 11, 22, 44, 55, 77, 22, 11, 
      33, 44, 55, 66, 77, 88, 99, 22 };

    print(imset);
    // output -> 11 11 22 22 22 33 44 44 55 55 66 77 77 88 99

    del_count1 = imset.erase(22);

    std::cout << "del_count1 = " << del_count1 << '\n';
    // output -> del_count1 = 3

    print(imset);
    // output -> 11 11 33 44 44 55 55 66 77 77 88 99

    // ---------------------------------------------------
  }
*/

/*
  #include <set>
  #include <functional>   // std::greater(function object)

  template <typename Key>
  using g_set = std::set<Key, std::greater<Key>>
  // "g_set" is an alias template 

  // gset<int> -> std::set<int, std::greater<int>>
*/

/*
  #include <set>
  #include <string>
  #include <utility>    // std::move
  #include "../headers/nutility.h"

  int main()
  {
    std::set<std::string> str_set{ 
      "hello", "world", "we", "are", "live", "from", "istanbul" };

    print(str_set);
    // output -> are from hello istanbul live we world

    // -----------------------------------------------------

    std::string old_key{ "world" };
    std::string new_key{ "galaxy" };

    // first approach for deleting old_key and inserting new_key

    // when "erase" member function is being called,
    // object's(std::string) destructor will be called 
    // and it will delete the node.
    // then "insert" member function will create a new node 
    // and construct another std::string object with new_key.

    if (auto iter = str_set.find(old_key); iter != str_set.end()) 
    {
      str_set.erase(iter);
      str_set.insert(new_key);
    }
    print(str_set);
    // output -> are from galaxy hello istanbul live we

    // -----------------------------------------------------

    old_key = "istanbul";
    new_key = "izmir";

    // better approach for deleting old_key_2 and inserting new_key_2

    // "extract" member function will extract the node 
    // and returns a handle to that node.
    // value that is stored in that node can be changed
    // without calling its destructor.

    // when "extract" member function is being called,
    // std::set container's s'ze will be decreased by 1.

    if (auto iter = str_set.find(old_key); iter != str_set.end()) 
    {
      auto handle = str_set.extract(iter);
      handle.value() = new_key;
      str_set.insert(std::move(handle));
    }

    print(str_set);
    // output -> are from galaxy hello izmir live we

    // -----------------------------------------------------
  }
*/

/*
                    ---------------------------
                    | std::map, std::multimap |
                    ---------------------------
*/

/*
  #include <functional>   // std::less
  #include <utility>      // std::pair
  #include <memory>       // std::allocator

  template<
      class Key,
      class T,
      class Comparator = std::less<Key>,
      class Allocator = std::allocator<std::pair<const Key, T>>
  > class Map{};

  - reaching an element in map is O(log n) operation.
*/

/*
  #include <map>
  #include <string>

  int main()
  {
    std::map<std::string, int> str_i_map{
      {"hello", 1},
      {"world", 2},
      {"we",    3},
      {"are",   4},
      {"live",  5},
      {"from",  6},
      {"izmir", 7},
    };

    for (const auto& str_i_pair : str_i_map) 
    {
      std::cout << str_i_pair.first << " " 
                << str_i_pair.second << '\n';
    }
    // output ->
    //  are 4
    //  from 6
    //  hello 1
    //  izmir 7
    //  live 5
    //  we 3
    //  world 2
  }
*/

/*
  // keys must be unique but values can be same
  // inside key-value pairs in std::map container.

  #include <map>
  #include <string>

  int main()
  {
    std::map<std::string, int> str_i_map{
      {"hello", 1},
      {"world", 1},
      {"we",    1},
      {"are",   1},
      {"live",  1},
      {"from",  1},
      {"izmir", 1},
    };

    for (const auto& str_i_pair : str_i_map) 
    {
      std::cout << str_i_pair.first << " " 
                << str_i_pair.second << '\n';
    }
    // output ->
    //  are 1
    //  from 1
    //  hello 1
    //  izmir 1
    //  live 1
    //  we 1
    //  world 1
  }
*/

/*
  #include <map>
  #include <string>
  #include <functional>   // std::greater

  int main()
  {
    using comp_type = std::greater<std::string>;

    std::map<std::string, int, comp_type> str_i_map{
      {"hello", 1},
      {"world", 2},
      {"we",    3},
      {"are",   4},
      {"live",  5},
      {"from",  6},
      {"izmir", 7},
    };

    for (const auto& str_i_pair : str_i_map) 
    {
      std::cout << str_i_pair.first << " " 
                << str_i_pair.second << '\n';
    }
    // output ->
    //  world 2
    //  we 3
    //  live 5
    //  izmir 7
    //  hello 1
    //  from 6
    //  are 4
  }
*/

/*
  #include <map>
  #include <string>
  #include <functional>  // std::greater

  int main()
  {
    using comp_type = std::greater<std::string>;

    std::map<std::string, int, comp_type> str_i_map{
      {"hello", 1},
      {"world", 2},
      {"we",    3},
      {"are",   4},
      {"live",  5},
      {"from",  6},
      {"izmir", 7},
    };

    // using structured binding
    for (const auto&[str, number] : str_i_map)
      std::cout << str << " " << number << '\n';
    
    // output ->
    //  world 2
    //  we 3
    //  live 5
    //  izmir 7
    //  hello 1
    //  from 6
    //  are 4
  }
*/

/*
  #include <map>
  #include <string>
  #include <utility>    // std::pair, std::make_pair

  int main()
  {
    using namespace std;

    std::map<std::string, int> str_i_map{
      {"hello", 1},
      {"world", 2},
      {"we",    3},
      {"are",   4},
      {"live",  5},
      {"from",  6},
      {"izmir", 7},
    };

    // ---------------------------------------------------

    str_i_map.insert(std::pair<std::string, int>{"yes", 8});
    // using temporary object to insert a pair to map container

    // ---------------------------------------------------

    str_i_map.insert(std::pair{ "no", 9 });   // CTAD
    // using temporary object to insert a pair to map container

    // ---------------------------------------------------

    str_i_map.insert(std::make_pair("galaxy",10));
    // using "std::make_pair" factory function 
    // to insert a pair to map container

    // ---------------------------------------------------

    str_i_map.emplace("universe", 11);
    // using "emplace" member function which will call 
    // std::pair's constructor directly inside map container.

    // ---------------------------------------------------

    for (const auto& [str, number] : str_i_map)
      cout << str << " " << number << '\n';
    // output ->
    //  are 4
    //  from 6
    //  galaxy 10
    //  hello 1
    //  izmir 7
    //  live 5
    //  no 9
    //  universe 11
    //  we 3
    //  world 2
    //  yes 8
  }
*/

/*
  #include <map>
  #include <string>
  #include <cstddef>  // std::size_t
  #include "../headers/nutility.h"

  int main()
  {
    // -----------------------------------------------

    // keys must be unique in std::map container.

    std::map<std::string, int> str_i_map;

    for (std::size_t i = 0; i < 1000; ++i)
      str_i_map.emplace(rname(), Irand{ 1000, 9000}());
    
    std::cout << "str_i_map.size() = " 
              << str_i_map.size() << '\n';
    // output -> str_i_map.size() = 317

    // -----------------------------------------------

    // keys can be same in std::multimap container.

    std::multimap<std::string, int> str_i_multimap;

    for (std::size_t i = 0; i < 1000; ++i)
      str_i_multimap.emplace(rname(), Irand{ 1000, 9000}());

    std::cout << "str_i_multimap.size() = " 
              << str_i_multimap.size() << '\n';
    // output -> str_i_multimap.size() = 1000   

    // -----------------------------------------------
  }
*/

/*
  #include <map>
  #include <string>
  #include "../headers/nutility.h"

  int main()
  {
    std::map<std::string, int> str_i_map;

    for (std::size_t i = 0; i < 10; ++i)
      str_i_map.emplace(rname(), Irand{ 1000, 9000}());

    std::string key = "galaxy";
    int num = 11;

    // -------------------------------------------------

    if (auto [iter, is_inserted] = str_i_map.insert({ key, num }); 
        is_inserted == true)
      std::cout << iter->first << " is inserted to map\n";
    else {
      std::cout << iter->first << " is already in map\n";
      std::cout << "its value is " << iter->second << '\n';
    }

    // output -> galaxy is inserted to map

    // -------------------------------------------------

    if (auto [iter, is_inserted] = str_i_map.insert({ key, num }); 
        is_inserted == true)
      std::cout << iter->first << " is inserted to map\n";
    else {
      std::cout << iter->first << " is already in map\n";
      std::cout << "its value is " << iter->second << '\n';
    }

    // output -> 
    //  galaxy is already in map
    //  its value is 11

    // -------------------------------------------------

    for (const auto& p : str_i_map)
      std::cout << p << '\n';
    // output ->
    //  [cemre, 6083]
    //  [cihat, 1838]
    //  [galaxy, 11]
    //  [kamil, 7790]
    //  [kenan, 8846]
    //  [muslum, 2691]
    //  [suheyla, 4738]
    //  [tarcan, 2577]
    //  [tayyip, 6568]
    //  [yasemin, 2158]
    //  [zeliha, 7689]
  }
*/

/*
  #include <map>
  #include <string>
  #include "../headers/nutility.h"

  int main()
  {
    std::map<std::string, int> str_i_map{
      {"world",     1},
      {"galaxy",    2},
      {"universe",  3},
    };

    // ----------------------------------------------------

    str_i_map.operator[]("world") = 111;
    str_i_map["galaxy"] = 222;
    // Those 2 lines are equivalent.

    // if the key is exists in std::map container
    // it will change its value.

    print(str_i_map, "\n");
    // output ->
    //  [galaxy, 222]
    //  [universe, 3]
    //  [world, 111]

    // ----------------------------------------------------

    str_i_map["istanbul"] = 99;
    // if the key is not exists in std::map container
    // it will create a new key-value pair.
    // and its value will be set to 99.

    // STEP_1 -> str_i_map.insert(std::pair{"istanbul", int{}})
    // STEP_2 -> its value will be set to 99

    print(str_i_map, "\n");
    // output ->
    //  [galaxy, 222]
    //  [istanbul, 99]
    //  [universe, 3]
    //  [world, 111]

    // ----------------------------------------------------

    str_i_map["ankara"];   // value initialize
    // str_i_map.insert(std::pair{"izmir", int{}});

    print(str_i_map, "\n");     // VALID, NOT UB
    //  [ankara, 0]
    //  [galaxy, 222]
    //  [istanbul, 99]
    //  [universe, 3]
    //  [world, 111]

    str_i_map["ankara"] += 88;   // VALID, NOT UB

    print(str_i_map, "\n");
    // output ->
    //  [ankara, 88]
    //  [galaxy, 222]
    //  [istanbul, 99]
    //  [universe, 3]
    //  [world, 111]

    // ----------------------------------------------------
  }
*/

/*
  #include <vector>
  #include <map>
  #include "../headers/nutility.h"

  int main()
  {
    std::vector<int> ivec;
    rfill(ivec, 10000, Irand{ 1, 20 });

    std::map<int, int> counter_map;

    for (const auto& key : ivec)
      ++counter_map[key];
    // if the key is not exists in map container
    // it will create a new key-value pair(std::pair{key, int{}})
    // and will increase key's value by 1.
    // if the key is exists in map container
    // it will increase its value by 1.
  
    print(counter_map, "\n");
    // output ->
    //  [1, 494]
    //  [2, 503]
    //  [3, 454]
    //  [4, 509]
    //  [5, 492]
    //  [6, 515]
    //  [7, 531]
    //  [8, 511]
    //  [9, 536]
    //  [10, 529]
    //  [11, 517]
    //  [12, 506]
    //  [13, 496]
    //  [14, 507]
    //  [15, 506]
    //  [16, 470]
    //  [17, 476]
    //  [18, 460]
    //  [19, 479]
    //  [20, 509]
  }
*/

/*
  // sorting std::map container by values, using a vector

  #include <vector>
  #include <map>
  #include <algorithm>      // std::sort
  #include "../headers/nutility.h"

  int main()
  {
    std::vector<int> ivec;
    rfill(ivec, 10000, Irand{ 1, 10 });

    std::map<int, int> counter_map;

    for (const auto& item : ivec)
      ++counter_map[item];

    // -----------------------------------------------

    std::vector<std::pair<int, int>> temp_vec{ 
      counter_map.begin(), counter_map.end() };

    std::sort(temp_vec.begin(), temp_vec.end(), 
              [](const auto& pair_1, const auto& pair_2){
                return pair_1.second > pair_2.second;
      });

    print(temp_vec, "\n");
    // output ->
    //  [9, 1055]
    //  [1, 1029]
    //  [8, 1017]
    //  [6, 1005]
    //  [3, 1000]
    //  [7, 994]
    //  [4, 987]
    //  [5, 981]
    //  [2, 969]
    //  [10, 963]
  }
*/

/*
  "operator[]()" member function is only defined in 
  std::map container.

  The purpose of this function is;
    - if there is no key -> create
    - if there was a key -> change its value

  in std::multimap container, because of keys are not unique
  all calls to "operator[]()" will create a new key  
  so it will do the same thing as "insert" member function.
*/

/*
  #include <map>
  #include <string>
  #include <cstddef>    // std::size_t
  #include <stdexcept>  // std::out_of_range
  #include "../headers/nutility.h"

  int main()
  {
    std::map<int, std::string> i_str_map;

    for (std::size_t i = 0; i < 10; ++i)
      i_str_map.emplace(Irand{ 1, 20 }(), rtown());

    try
    {
      i_str_map.at(17) = "istanbul";
      std::cout << "value at key(17) has been changed\n";
      // if there is a key -> change its value
      // if there is not a key -> throw exception
    }
    catch (const std::out_of_range& ex)
    {
      std::cout << "there is no key(17)\n";
      std::cout << "exception caught: " << ex.what() << '\n';
    }

    print(i_str_map, "\n");

    // ----------------------------------------------

    // Scenario_1 : key is not exist

    // output ->
    //  there is no key(17)
    //  exception caught: map::at
    //  [8, istanbul]
    //  [11, erzurum]
    //  [12, aydin]
    //  [13, ardahan]
    //  [14, manisa]
    //  [18, samsun]
    //  [20, burdur]

    // ----------------------------------------------

    // Scenario_2 : key exists

    // output ->
    //  value at key(17) has been changed
    //  [8, kocaeli]
    //  [9, artvin]
    //  [13, siirt]
    //  [14, tokat]
    //  [16, istanbul]
    //  [17, istanbul]
    //  [18, duzce]
    //  [19, yozgat]
    //  [20, canakkale]

    // ----------------------------------------------
  }
*/

/*
  #include <map>
  #include <string>
  #include "../headers/nutility.h"

  int main()
  {
    std::map<std::string, std::string> str_str_map{
      {"key_1", "val_1"},
      {"key_2", "val_2"},
      {"key_3", "val_3"},
      {"key_4", "val_4"}
    };

    // --------------------- old way ---------------------

    std::string old_key = "key_4";
    std::string new_key = "key_11";

    if (auto iter = str_str_map.find(old_key); 
        iter != str_str_map.end()) 
    {
      auto value = iter->second + "_changed_val";
      str_str_map.erase(iter);
      str_str_map.emplace(new_key, value);
      print(str_str_map, "\n");
    }
    else {
      std::cout << "key has not been found\n";
    }
    // output ->
    //  [key_1, val_1]
    //  [key_11, val_4_changed_val]   ---->
    //  [key_2, val_2]
    //  [key_3, val_3]

    // --------------------- new way ---------------------

    old_key = "key_3";
    new_key = "key_222";

    if (auto iter = str_str_map.find(old_key); 
        iter != str_str_map.end())
    {
      auto handle = str_str_map.extract(iter);
      handle.key() = new_key;
      handle.mapped() += "_changed_val";
      // retuning a reference to the mapped value
      str_str_map.insert(move(handle));
    }

    print(str_str_map, "\n");
    // output ->
    //  [key_1, val_1]
    //  [key_11, val_4_changed_val]
    //  [key_2, val_2]
    //  [key_222, val_3_changed_val]

    // --------------------------------------------------
  }
*/

/*
  // "equal_range" member function

  #include <map>
  #include <string>
  #include <iterator>   // std::distance
  #include "../headers/nutility.h"

  int main()
  {
    std::multimap<std::string, std::string> str_str_multimap;

    for (size_t i = 0; i < 1000; ++i)
      str_str_multimap.emplace(rtown(), rname());

    std::string str_town = "istanbul";

    // ----------------------------------------------

    auto [iter_lower, iter_upper] = 
      str_str_multimap.equal_range(str_town);

    std::cout << "count of " << str_town << " = " 
              << std::distance(iter_lower, iter_upper) << '\n';
    // output -> count of istanbul = 14

    print(iter_lower, iter_upper, "\n");
    // output ->
    //  [istanbul, aykut]
    //  [istanbul, emine]
    //  [istanbul, umit]
    //  [istanbul, murat]
    //  [istanbul, sarp]
    //  [istanbul, perihan]
    //  [istanbul, naz]
    //  [istanbul, gunay]
    //  [istanbul, kurthan]
    //  [istanbul, su]
    //  [istanbul, kerim]
    //  [istanbul, fuat]
    //  [istanbul, ayla]
    //  [istanbul, recep]

    // ----------------------------------------------
  }
*/

/*
                --------------------------------
                | std::unordered_set container |
                --------------------------------
*/

/*
  <---- check stl_general/std::hash function object---->
*/

/*
  #include <functional>   // std::hash, std::equal_to
  #include <memory>       // std::allocator

  template <typename Key, 
            typename Hash       = std::hash<Key>,
            typename KeyEqual   = std::equal_to<Key>, 
            typename Allocator  = std::allocator<Key>>
  class Unordered_Set {};

  - searching in std::unordered_set container with a known key 
    is O(1) complexity.
*/

/*
  #include <vector>
  #include <list>
  #include <string>
  #include <unordered_set>
  int main()

  {
    std::vector<std::list<std::string>> bucket_vec;
    // every std::list<std::string> is called bucket.
    // unordered containers are kind of container of buckets.

    std::unordered_set<std::string> uo_set(512); 
  }
*/

/*
  #include <unordered_set>
  #include <string>
  #include "../headers/nutility.h"

  int main()
  {
    std::cout << std::boolalpha;

    std::unordered_set<std::string> uo_str_set;

    for (int i = 0; i < 10; ++i)
      uo_str_set.insert(rtown());
    
    print(uo_str_set);
    // output ->
    //  bolu sirnak aksaray karabuk erzurum 
    //  amasya izmir kastamonu diyarbakir

    // ordering is random(unordered), NO lexicographical order.
    // i.e,  index[1] = "sirnak", index[1] = "aksaray"

    // --------------------- old way -------------------------

    std::string searched_town1 = "izmir";

    auto is_exist = uo_str_set.count(searched_town1);
    // for unordered_set container, "count" member function's 
    //  - return type is `int`
    //  - return value is 0 or 1

    // because of keys are unique in unordered_set container.

    std::cout << searched_town1 << " is exist in unordered_set = "
              << (is_exist ? "yes" : "no") << '\n';

    // output -> izmir is exist in unordered_set = yes

    // --------------------- new way -------------------------

    std::string searched_town2 = "istanbul";

    auto is_exist2 = uo_str_set.contains(searched_town2);
    // "contains" member function's return type is bool

    std::cout << searched_town2 << " is exist in unordered_set = "
              << is_exist2 << '\n';   
    // output -> istanbul is exist in unordered_set = false

    // ------------------------------------------------------

    auto iter_bool_pair = uo_str_set.insert(searched_town2);
    // return type of "insert" member function is
    // std::pair<iterator, bool>

    // ------------------------------------------------------
  }
*/

/*
  #include <functional>   // std::hash
  #include <string>
  #include <unordered_set>    

  class Myclass {
  public:
    int m_a;
    std::string m_b;
    double m_c;
  };

  // explicit(full) specialization of std::hash class template
  // for user-defined type(Myclass)
  template <>
  struct std::hash<Myclass> {
    std::size_t operator()(const Myclass& m) const
    {
      // minimal operation is hashing each data member and add them.
      return  std::hash<int>{}(m.m_a)         +
              std::hash<std::string>{}(m.m_b) +
              std::hash<double>{}(m.m_c);
    }
  };

  int main()
  {
    std::unordered_set<Myclass> uo_myclass_set1;
    std::unordered_set<Myclass, std::hash<Myclass>> uo_myclass_set2;
    // Those 2 lines are equivalent.
  }
*/

/*
  #include <functional>     // std::hash
  #include <unordered_set>
  #include <string>

  class Myclass {
  public:
    int m_a;
    std::string m_b;
    double m_c;
  };

  // using functor classes "operator()" function as a Hasher
  struct Hasher_Myclass
  {
    std::size_t operator()(const Myclass& m) const
    {
      return  std::hash<int>{}(m.m_a)         +
              std::hash<std::string>{}(m.m_b) +
              std::hash<double>{}(m.m_c);
    }
  };

  int main()
  {
    std::unordered_set<Myclass, Hasher_Myclass> uo_myclass_set;
  }
*/

/*
  #include <string>
  #include <unordered_set>
  #include <utility>

  class Myclass {
  public:
    int m_a;
    std::string m_b;
    double m_c;
  };

  // using global(free) function as a Hasher
  std::size_t myclass_hasher(const Myclass& m)
  {
    return  std::hash<int>{}(m.m_a)         +
            std::hash<std::string>{}(m.m_b) +
            std::hash<double>{}(m.m_c);
  }

  int main()
  {
    std::unordered_set< Myclass, 
                        decltype(&myclass_hasher)> uo_set1;

    std::unordered_set< Myclass, 
                        std::size_t(*)(const Myclass&)> uo_set2;
    // Those 2 lines are equivalent.
  }
*/

/*
  #include <string>
  #include <unordered_set>
  #include <functional>     // std::hash

  class Myclass {
  public:
    int m_a{};
    std::string m_b{};
    double m_c{};
  };

  int main()
  {
    // using lambda expression as a hasher
    auto fn = [](const Myclass& m) -> std::size_t
    {
      return  std::hash<int>{}(m.m_a)         +
              std::hash<std::string>{}(m.m_b) +
              std::hash<double>{}(m.m_c);
    };

    std::unordered_set<Myclass, decltype(fn)> uo_set1;    
    // since C++20
    std::unordered_set<Myclass, decltype(fn)> uo_set2(10, fn);
    // before C++20
  }
*/

/*
  #include "../headers/nutility.h"
  #include <unordered_set>
  #include <functional>     // std::hash, std::equal_to

  class Point {
  private:
    int m_x{}, m_y{}, m_z{};
  public:
    Point() = default;
    Point (int x, int y, int z) : m_x(x), m_y(y), m_z(z) {}

    // hidden friend function
    friend std::ostream& operator<<(std::ostream& os, 
                                    const Point& p)
    {
      return os << "("  << p.m_x << ", " 
                        << p.m_y << ", " 
                        << p.m_z << ")";
    }

    int get_x()const
    {
      return m_x;
    }
    int get_y()const
    {
      return m_y;
    }
    int get_z()const
    {
      return m_z;
    }
    bool operator==(const Point& other) const
    {
      return  m_x == other.m_x && 
              m_y == other.m_y &&
              m_z == other.m_z;
    }

    static Point get_random_point()
    {
      Irand rand{ 0, 9 };
      return Point{ rand(), rand(), rand() };
    }
  };

  struct Hasher_Point {
  public:
    std::size_t operator()(const Point& point) const
    {
      return  std::hash<int>{}(point.get_x()) +
              std::hash<int>{}(point.get_y()) +
              std::hash<int>{}(point.get_z());
    }
  };

  int main()
  {
    std::unordered_set< Point, 
                        Hasher_Point, 
                        std::equal_to<Point>> uo_point_set;

    for (int i = 0; i < 10; ++i)
      uo_point_set.insert(Point::get_random_point());

    // to hash Point(user-defined type), 
    // need to use an hash fucntion, in this scenario 
    // Point_Hasher functor class is being used.

    // to compare Point(user-defined type) objects,
    // which will be inserted to the unordered_set container,
    // Point class needs to have an operator==() overload.

    // ---------------------------------------------------

    for (const auto& p : uo_point_set)
      std::cout << p << '\n';
    // output ->
    //  (2, 8, 6)
    //  (2, 8, 4)
    //  (7, 5, 7)
    //  (8, 4, 9)
    //  (1, 1, 6)
    //  (0, 1, 4)
    //  (1, 6, 4)
    //  (3, 7, 1)
    //  (6, 1, 3)
    //  (2, 1, 4)
  }
*/

/*
  for holding custom(user-defined) type objects in 
  unordered_set, unordered_map containers

    - custom type must be hashable
      - creating an explicit specialization of  
        std::hash class template for custom type
      - using an hash function for custom type

    - member function or free function for operator==()
      for comparing custom type objects
*/

/*
  #include "../headers/nutility.h"
  #include <unordered_set>
  #include <functional>   // std::hash, std::equal_to

  class Point {
  private:
    int m_x{}, m_y{}, m_z{};
  public:
    Point() = default;
    Point (int x, int y, int z) : m_x(x), m_y(y), m_z(z) {}

    // hidden friend function
    friend std::ostream& operator<<(std::ostream& os, 
                                    const Point& p)
    {
      return os << "("  << p.m_x << ", " 
                        << p.m_y << ", " 
                        << p.m_z << ")";
    }

    int get_x()const
    {
      return m_x;
    }
    int get_y()const
    {
      return m_y;
    }
    int get_z()const
    {
      return m_z;
    }
    bool operator==(const Point& other) const
    {
      return  m_x == other.m_x && 
              m_y == other.m_y &&
              m_z == other.m_z;
    }

    static Point get_random_point()
    {
      Irand rand{ 0, 9 };
      return Point{ rand(), rand(), rand() };
    }
  };

  struct Hasher_Point {
  public:
    std::size_t operator()(const Point& point) const
    {
      return  std::hash<int>{}(point.get_x()) +
              std::hash<int>{}(point.get_y()) +
              std::hash<int>{}(point.get_z());
    }
  };

  int main()
  {
    std::unordered_set< Point, 
                        Hasher_Point, 
                        std::equal_to<Point>> uoset_point;

    for (int i = 0; i < 1000; ++i)
      uoset_point.insert(Point::get_random_point());

    // -----------------------------------------------------
    
    std::cout << "uoset_point.size() = " 
              << uoset_point.size() << '\n';
    // output -> uoset_point.size() = 630
    //  1000 - 630 = 370 collision happened.

    std::cout  << "uoset_point.bucket_count() = " 
          << uoset_point.bucket_count() << '\n';
    // output -> uoset_point.bucket_count() = 1109

    // -----------------------------------------------------
    
    // "bucket_count" can be passed 
    // as an argument to the constructor
    // std::unordered_set(std::size_t bucket_count) overload

    std::unordered_set< Point, 
                        Hasher_Point, 
                        std::equal_to<Point>> uoset2_point(500);

    std::cout << "uoset2_point.bucket_count() = " 
              << uoset2_point.bucket_count() << '\n';
    // output -> uoset2_point.bucket_count() = 503

    // -----------------------------------------------------
  }
*/

/*
  #include "../headers/nutility.h"
  #include <unordered_set>
  #include <functional>   // std::hash, std::equal_to

  class Point {
  private:
    int m_x{}, m_y{}, m_z{};
  public:
    Point() = default;
    Point (int x, int y, int z) : m_x(x), m_y(y), m_z(z) {}

    // hidden friend function
    friend std::ostream& operator<<(std::ostream& os, 
                                    const Point& p)
    {
      return os << "("  << p.m_x << ", " 
                        << p.m_y << ", " 
                        << p.m_z << ")";
    }

    int get_x()const
    {
      return m_x;
    }
    int get_y()const
    {
      return m_y;
    }
    int get_z()const
    {
      return m_z;
    }
    bool operator==(const Point& other) const
    {
      return  m_x == other.m_x && 
              m_y == other.m_y &&
              m_z == other.m_z;
    }

    static Point get_random_point()
    {
      Irand rand{ 0, 9 };
      return Point{ rand(), rand(), rand() };
    }
  };

  struct Hasher_Point {
  public:
    std::size_t operator()(const Point& point) const
    {
      return  std::hash<int>{}(point.get_x()) +
              std::hash<int>{}(point.get_y()) +
              std::hash<int>{}(point.get_z());
    }
  };

  int main()
  {
    std::unordered_set< Point, 
                        Hasher_Point, 
                        std::equal_to<Point>> uoset_point;

    for (int i = 0; i < 1000; ++i)
      uoset_point.insert(Point::get_random_point());

    // -----------------------------------------------------

    std::cout << "uoset_point.size() = " 
              << uoset_point.size() << '\n';
    // output -> uoset_point.size() = 630
    //  1000 - 630 = 370 collision happened.

    std::cout  << "uoset_point.bucket_count() = " 
          << uoset_point.bucket_count() << '\n';
    // output -> uoset_point.bucket_count() = 1109

    // -----------------------------------------------------

    //  size / bucket_count = load_factor
    //  630 / 1109 = 0.569883

    std::cout << "uoset_point.load_factor() = " 
              << uoset_point.load_factor() << '\n';
    // output -> uoset_point.load_factor() = 0.569883

    std::cout << "uoset_point.load_factor() = " 
              <<  static_cast<double>(uoset_point.size()) / 
                  static_cast<double>(uoset_point.bucket_count()) 
              << '\n';
    // output -> uoset_point.load_factor() = 0.569883

    // -----------------------------------------------------

    std::cout << "uoset_point.max_load_factor() = " 
              << uoset_point.max_load_factor() << '\n';
    // output -> uoset_point.max_load_factor() = 1

    // -----------------------------------------------------

    // when max_load_factor == 1 and 
    // size and bucket_count becomes equal in unordered_set
    // bucket_count will be increased (generally doubled)
    // and "re-hashing" will be done in unordered_set container.
    // because "re-hashing" operation is expensive,
    // prefered max_load_factor is between 0.7 and 0.8

    // efficiency is customizable by changing the
    // bucket_count and max_load_factor.

    // -----------------------------------------------------
  }
*/

/*
  #include <unordered_set>
  #include "../headers/nutility.h"
  #include <string>

  int main()
  {
    std::unordered_set<std::string> uoset_str;

    while (uoset_str.size() != 100)
      uoset_str.insert(rname());

    std::cout << "uoset_str.size() = " 
              << uoset_str.size() << '\n';
    // output -> uoset_str.size() = 100

    std::cout << "uoset_str.bucket_count() = " 
              << uoset_str.bucket_count() << '\n';
    // output -> uoset_str.bucket_count() = 127

    std::cout << "load_factor = " 
              << (float)uoset_str.size() / uoset_str.bucket_count() 
              << '\n';
    // output -> load_factor = 0.787402

    std::cout << "uoset_str.load_factor() = " 
              << uoset_str.load_factor() << '\n';
    // output -> uoset_str.load_factor() = 0.787402

    std::cout << "uoset_str.max_load_factor() = " 
              << uoset_str.max_load_factor() << '\n';
    // output -> uoset_str.max_load_factor() = 1

    uoset_str.max_load_factor(0.8f);

    std::cout << "uoset_str.max_load_factor() = " 
              << uoset_str.max_load_factor() << '\n';
    // output -> uoset_str.max_load_factor() = 0.8
  }
*/

/*
  #include <string>
  #include <unordered_set>
  #include <cstddef>      // std::size_t
  #include <iomanip>      // std::setw
  #include "../headers/nutility.h"

  int main()
  {
    std::unordered_set<std::string> uoset_str(16);

    while (uoset_str.size() != 10)
      uoset_str.insert(rname());

    std::cout << "uoset_str.size() = " 
              << uoset_str.size() << '\n';
    // output -> uoset_str.size() = 10

    std::cout << "uoset_str.bucket_count() = " 
              << uoset_str.bucket_count() << '\n';
    // output -> uoset_str.bucket_count() = 17

    std::cout << "uoset_str.load_factor() = " 
              << uoset_str.load_factor() << '\n';
    // output -> uoset_str.load_factor() = 0.588235

    std::cout << "uoset_str.max_load_factor() = " 
              << uoset_str.max_load_factor() << '\n';
    // output -> uoset_str.max_load_factor() = 1

    // -------------------------------------------------

    std::cout << std::left;

    for (std::size_t i{}; i < uoset_str.bucket_count(); ++i) 
    {
      std::cout << std::setw(4) << i 
                << " [" << uoset_str.bucket_size(i) << "] ";

      if (uoset_str.bucket_size(i) != 0)
      {
        for ( auto iter = uoset_str.begin(i); 
              iter != uoset_str.end(i); ++iter)
        {
          std::cout << *iter << ' ';
        }
      }
      std::cout << '\n';
    }

    // output ->
    //  0    [1] fuat
    //  1    [2] hande julide     ---> collision
    //  2    [0]
    //  3    [1] nahit
    //  4    [0]
    //  5    [0]
    //  6    [0]
    //  7    [0]
    //  8    [1] necmi
    //  9    [0]
    //  10   [1] nefes
    //  11   [0]
    //  12   [1] feramuz
    //  13   [1] cebrail
    //  14   [0]
    //  15   [0]
    //  16   [2] ece gizem        ---> collision

    // --------------------------------------------------

    // "hande"  ->
    // its index is 1 and there is a collision in index 1,
    // (there are 2 elements in the std::list container)
    // finding "hande" will be O(1) 
    // because it is first element on the list(index 1 list)

    // --------------------------------------------------

    // "julide" ->
    // it is in index 1 and there is a collision
    // because of it is not first element on the list(index 1 list)
    // finding "julide" will be amortized constant time not O(1)
    // first "hande" will be found than
    // it will move to next node "julide"

    // --------------------------------------------------

    // "nefes" ->
    // it is in index 10 and there is no collision
    // finding "nefes" will be O(1)

    // --------------------------------------------------

    // "osman" ->
    // if it has been hashed might be in index 7
    // but because of there is no element called "osman",
    // it won't be hashed so we couldn't found it in any index.

    // --------------------------------------------------
  }
*/

/*
  unordered(hashmap) containers will be re-hased when
    - "rehash" member function is called.
    - load_factor become equal to max_load_factor
*/

/*
                    ------------------------
                    | std::array container |
                    ------------------------
*/

/*
  ----------------------------------------------------

  - std::array is a wrapper class for C-style array 
    with zero cost abstraction.

  ----------------------------------------------------

  Question. why using std::array instead of C-style array?

  Answer_1. 
    std::array knows its member type.
    C-style array also knows its member type.
    std::array knows its member count(size).
    C-style array does not know its member count(size).

  Answer_2. 
    no array to pointer conversion applied to std::array

  Answer_3. 
    no exception thrown when reaching index 
    which is out of bounds of C-style array.
    exception thrown when we reaching index which is out of bounds
    of std::array with "at" member function

  Answer_4. 
    no type conversion from different size std::arrays
    i.e std::array<int,10> cannot implicitly convert to 
        std::array<int,11>

  ----------------------------------------------------
*/

/*
  struct Array {
    int m_iarr[10];
  };

  int main()
  {
    Array i_arr = { 11, 22, 33, 44 };
    // aggregate initialization
    // it WON'T call std::initializer_list constructor.
  }
*/

/*
  template <typename T, std::size_t size>
  struct Array {
    T m_arr[size];
  };

  int main()
  {
    Array<int, 5> i_arr5{ 11, 22, 33, 44, 55 };
  }
*/

/*
  #include <array>

  int main()
  {
    // ------------------------------------------------------

    std::array<int, 5> i_arr5;    
    // default initialization

    // because of default initialization,
    // elements of i_arr5 will be undetermined(garbage) value.


    for (auto elem : i_arr5)
      std::cout << elem << '\n';  // undefined behaviour(UB)
    // using garbage value is undefined behaviour.

    std::cout << '\n';

    // ------------------------------------------------------

    std::array<int, 6> i_arr6{};  
    // value initialization

    // because of value initialization,
    // elements of i_arr6 will be zero initialized.

    for (auto elem : i_arr6)
      std::cout << elem << ' ';
    // output -> 0 0 0 0 0 0

    std::cout << '\n';

    // ------------------------------------------------------

    std::array<int, 7> i_arr7{ 0 }; 
    // aggregate initialization

    // first element will be initialized with 0
    // other elements will be zero initialized.

    for (auto elem : i_arr7)
      std::cout << elem << ' ';
    // output -> 0 0 0 0 0 0 0

    std::cout << '\n';

    // ------------------------------------------------------

    std::array<int, 8> i_arr8{ 11, 22, 33 };  
    // aggregate initialization

    // first 3 elements will be initialized with 11, 22, 33
    // other elements will be zero initialized.

    for (auto elem : i_arr8)
      std::cout << elem << ' ';
    // output -> 11 22 33 0 0 0 0 0

    // ------------------------------------------------------
  }
*/

/*
  #include <array>

  int main()
  {
    std::array i_arr{ 10, 20, 30, 40, 50 };   // CTAD(C++17)
    std::array<int, 5> ar_2{ 10, 20, 30, 40, 50 };
    // Those 2 lines are equivalent.
  }
*/

/*
  #include <array>

  int main()
  {
    std::array<int> i_arr1{ 11, 22, 33 };   // syntax error
    // error: wrong number of template arguments (1, should be 2)
    // error: scalar object 'i_arr1' 
    //  requires one element in initializer

    std::array<> i_arr2{ 11, 22, 33 };        // syntax error
    // error: wrong number of template arguments (0, should be 2)
    // error: scalar object 'i_arr2' 
    //  requires one element in initializer
  }
*/
 
/*
  #include <array>

  int main()
  {
    std::array i_arr{ 11, 22, 33, 44, 55 };
    constexpr auto arr_size = i_arr.size();

    int* p = i_arr;   // syntax error
    // error: cannot convert 'std::array<int, 5>' to 
    //  'int*' in initialization

    // no array to pointer conversion applied to std::array

    // ------------------------------------------------------

    auto p1 = i_arr.data();   
    // "data" member function returns pointer to the first element
    // which can be used in C API's.
    auto p2 = &i_arr[0];
    auto p3 = &*(i_arr.begin());
    // Those 2 lines are equivalent.

    // ------------------------------------------------------
  }
*/

/*
  #include <array>

  int main()
  {
    std::array<int, 0> i_arr0;

    std::cout << "i_arr0.size() = " << i_arr0.size() << '\n';	
    // output -> i_arr0.size() = 0

    constexpr bool b1 = (i_arr0.data() == nullptr);
    // b1 -> true
  }
*/

/*
  #include <cstddef>  // std::size_t
  #include <ostream>  // std::ostream
  #include <array>
  #include <string>
  #include "../headers/nutility.h"

  template <typename T, std::size_t size>
  std::ostream& operator<<( std::ostream& os, 
                            const std::array<T, size>& arr)
  {
    os << '[';
    for (std::size_t i{}; i < size - 1; ++i) 
      os << arr[i] << ", ";
    os << arr.back() << ']';
    
    return os;
  }

  int main()
  {
    // ----------------------------------------------

    std::array i_arr{ 5, 6, 7, 1, 9, 3, 2 };

    std::cout << i_arr << '\n';
    // output -> [5, 6, 7, 1, 9, 3, 2]

    // ----------------------------------------------

    std::array d_arr{ 3.5, 2.6, 6.7, 5.1, 1.9, 8.3, 7.2 };

    std::cout << d_arr << '\n';
    // output -> [3.5, 2.6, 6.7, 5.1, 1.9, 8.3, 7.2]

    // ----------------------------------------------

    std::array<std::string, 5> str_arr{};
    for (auto& str : str_arr)
      str = rtown();

    std::cout << str_arr << '\n';
    // output -> [agri, bursa, bilecik, kilis, yozgat]

    // ----------------------------------------------
  }
*/

/*
  // std::array's iterator's type 
  // is std::random_access_iterator 

  #include <array>

  int main()
  {

    std::array<int, 5> i_arr{ 11, 22, 33, 44, 55 };
    for (auto iter = i_arr.crbegin(); iter != i_arr.crend(); ++iter)
      std::cout << *iter << ' ';
    // output -> 55 44 33 22 11
  }
*/

/*
  #include <array>

  int main()
  {
    std::array<int, 5> i_arr{ 11, 22, 33, 44, 55 };

    // "operator[]" member function
    for (size_t i{}; i < i_arr.size(); ++i)
      std::cout << i_arr[i] << ' ';
    // output -> 11 22 33 44 55

    std::cout << '\n';

    // ------------------------------------------------

    auto val = i_arr[5];  // undefined behaviour(UB)
    // using index which is out of bounds of std::array
    // is undefined behaviour.
    // no exception will be thrown.

    // ------------------------------------------------

    try {
      auto val2 = i_arr.at(5);    // VALID
      // reaching index which is out of bounds of std::array
      // with "at" member function will throw an exception.
    }
    catch (const std::exception& ex)
    {
      std::cout << "exception caught: " << ex.what() << '\n';
    }

    // output -> 
    //  exception caught: array::at: 
    //  __n (which is 5) >= _Nm (which is 5)

    // ------------------------------------------------
  }
*/

/*
  // "fill" member function of std::array container

  #include <array>
  #include <algorithm>  // std::copy
  #include <iterator>   // std::ostream_iterator

  int main()
  {
    std::array<int, 5> i_arr;
    i_arr.fill(11);   

    std::copy(i_arr.begin(), i_arr.end(), 
              std::ostream_iterator<int>(std::cout, " "));
    // output -> 11 11 11 11 11
  }
*/

/*
  #include <array>
  #include "../headers/nutility.h"

  std::array<int, 3> foo(int x, int y, int z)
  {
    return { 2 * x, 3 * y, 4 * z };
  }

  int main()
  {
    auto i_arr3 = foo(11, 22, 33);

    print(i_arr3);            // output -> 22 66 132
    print(foo(11, 22, 33));   // output -> 22 66 132
    // Those 2 lines are equivalent.
  }
*/

/*
  #include <cstddef>  // std::size_t
  #include <array>

  template <typename T, std::size_t size>
  std::ostream& operator<<( std::ostream& os, 
                            const std::array<T, size>& arr)
  {
    os << '[';
    for (std::size_t i{}; i < size - 1; ++i) {
      os << arr[i] << ", ";
    }
    return os << arr.back() << ']';
  }

  int main()
  {
    std::array<std::array<int, 3>, 4> arr{ 
      { 
        { 11, 11, 11 }, 
        { 22, 22, 22 }, 
        { 33, 33, 33 }, 
        { 44, 44, 44 },
      } 
    };
    
    std::cout << arr << '\n';
    // output -> 
    //  [[11, 11, 11], [22, 22, 22], [33, 33, 33], [44, 44, 44]]

    arr[2][2] = 99;
    std::cout << arr << '\n';
    // output ->
    //  [[11, 11, 11], [22, 22, 22], [33, 33, 99], [44, 44, 44]]
  }
*/

/*

  // using std::array with C API's
  #include <array>
  #include <cstdlib>  // std::rand
  #include <cstdio>   // std::printf

  void print_array(const int* p_arr, size_t size)
  {
    while (size--)
      std::printf("%d ", *p_arr++);
  }

  void set_array_random(int* p_arr, size_t size)
  {
    while (size--)
      *p_arr++ = std::rand() % 1000;
  }

  int main()
  {
    // ---------------------------------------------

    std::array i_arr{ 11, 22, 33, 44, 55 };

    print_array(i_arr.data(), i_arr.size());
    // output -> 11 22 33 44 55

    std::cout << '\n';

    // ---------------------------------------------
    set_array_random(i_arr.data(), i_arr.size());

    print_array(i_arr.data(), i_arr.size());
    // output -> 41 467 334 500 169

    // ---------------------------------------------
  }
*/

/*
  #include <array>    // std::get(std::array)

  int main()
  {
    using namespace std;

    std::array i_arr{ 11, 22, 33, 44, 55 };

    std::cout << std::get<0>(i_arr) << '\n';  
    // output -> 11

    // -------------------------------------------------------

    std::cout << std::get<7>(i_arr) << '\n';  // compile time error
    //  error: static assertion failed: 
    //          array index is within bounds

    // -------------------------------------------------------
  }
*/

/*
  #include <array>
  #include "../headers/nutility.h"

  int main()
  {
    std::array i_arr{ 11, 22, 33 };

    // ----------------------------------------------

    // using `auto&` with structure binding
    // will create reference to the elements of the array.

    auto& [elem1, elem2, elem3] = i_arr;
    ++elem1, ++elem2, ++elem3;

    print(i_arr); // output -> 12 23 34

    // ----------------------------------------------

    // using `auto` with structure binding
    // will create copy of the elements of the array.

    auto [val1, val2, val3] = i_arr;
    ++val1, ++val2, ++val3;

    print(i_arr); // output -> 12 23 34

    // ----------------------------------------------
  }
*/

/*
  #include <array>

  int main()
  {
    std::array i_arr{ 11, 22, 33, 44 };

    auto [elem1, elem2, elem3] = i_arr;   // syntax error
    // error: only 3 names provided for structured binding
    // note: while 'std::array<int, 4>' decomposes into 4 elements
  }
*/

/*
  // using '_' character is a convention for unused variables

  #include <array>

  int main()
  {
    std::array arr1{ 11, 22, 33, 44 };

    auto [x, y, z, _] = arr1;
  }
*/

/*
  #include <array>

  // Mystruct is an aggregate type
  struct Mystruct {
    int m_x, m_y, m_z;
  };  

  Mystruct foo()
  {
    return { 11, 22, 33 };
  }

  int main()
  {
    auto [elem1, elem2, elem3] = foo();

    std::cout << elem1 << '\n';   // output -> 11
    std::cout << elem2 << '\n';   // output -> 22
    std::cout << elem3 << '\n';   // output -> 33
  }
*/

/*
  #include <array>

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
  };

  int main()
  {
    std::array<Myclass, 3> arr_myclass_1;

    // -------------------------------------------

    auto arr_myclass_2 = arr_myclass_1;
    // output ->
    //  copy ctor
    //  copy ctor
    //  copy ctor

    // -------------------------------------------

    auto arr_myclass_3 = std::move(arr_myclass_1);
    // output ->
    //  move ctor
    //  move ctor
    //  move ctor

    // -------------------------------------------
  }
*/

/*
  #include <vector>
  #include <array>

  int main()
  {
    std::vector<int> ivec{ 11, 22, 33, 44, 55, 66, 77 };

    // -------------------------------------------------

    std::array arr{ ivec.begin(), ivec.end() };
    // std::array<std::vector<int>::iterator, 2> arr_vector_iter;

    // arr is holding std::vector<int> iterators, 
    // not the elements of the vector

    std::cout << *arr[0] << '\n';         // output -> 11
    std::cout << *ivec.begin() << '\n';   // output -> 11
    // Those 2 lines are equivalent.

    // -------------------------------------------------
  }
*/

/*
                --------------------------------
                | std::stack container adaptor |
                --------------------------------
*/

/*
  std::stack is a FILO(first in last out) container adaptor
  std::stack is a class template and it has 2 template parameters.

  1st param : type of the object that will hold in std::stack
  2nd param : type of the container that std::stack will use
  (default template argument -> std::deque)

  C++ standarts declaring that using a container 
  with push_back() member function as a second template parameter
*/

/*
  #include <deque>
  #include <utility>  // std::move, std::forward
  #include <cstddef>  // std::size_t

  template <typename T, typename Con = std::deque<T>>
  class Stack {
  protected:
    Con m_con;

  public:
    Stack() = default;
    Stack(const Con& con) : m_con(con) {}
    Stack(Con&& con) : m_con(std::move(con)) {}

    void push(const T& val)
    {
      m_con.push_back(val);
    }

    void pop()
    {
      if (m_con.empty())
        throw std::runtime_error{ "pop call forempty stack" };
      
      m_con.pop_back();
    }

    std::size_t size() const
    {
      return m_con.size();
    }

    std::size_t empty() const
    {
      return m_con.empty();
    }

    template <typename ...Args>
    void emplace(Args&&... args)
    {
      std::emplace_back(std::forward<Args>(args)...);
    }
  };
*/

/*
  #include <stack>
  #include <vector>
  #include <list>

  template <typename T>
  using vec_stack_t = std::stack<T, std::vector<T>>;
  // alias template

  template <typename T>
  using list_stack_t = std::stack<T, std::list<T>>;
  // alias template

  int main()
  {
    vec_stack_t<int> vec_stack;
    vec_stack.push(1);

    list_stack_t<int> list_stack;
    list_stack.push(2);
  }
*/

/*
  #include <stack>
  #include <iterator>   // std::begin, std::end
  #include <deque>
  #include <vector>

  int main()
  {
    // -------------------------------------------------

    std::stack<int> i_stack1;
    // std::stack has a default contructor

    // -------------------------------------------------

    //std::stack<int> i_stack2{ 11, 22, 33, 44, 55 }; // syntax error
    // error: no matching function for call to 
    // 'std::stack<int>::stack(<brace-enclosed initializer list>)'

    // std::stack does not have initializer_list constructor

    // -------------------------------------------------

    int i_arr[] = { 11, 22, 33, 44, 55, 66, 77, 88, 99 };

    std::stack<int> i_stack3{ std::begin(i_arr), 
                              std::end(i_arr) };
    // std::stack has a range constructor

    std::cout << "i_stack3.size() = " 
              << i_stack3.size() << '\n';
    // output -> i_stack3.size() = 9

    // -------------------------------------------------

    std::deque<int> ideque{ 11, 22, 33, 44, 55 };
    std::stack<int> i_stack4{ ideque };   // VALID

    // default container type is std::deque
    // so this is a valid syntax

    // -------------------------------------------------

    std::vector<int> ivec{ 66, 77, 88, 99 };

    std::stack<int> i_stack5{ ivec };   // syntax error
    //  error: no matching function for call to 
    //  'std::stack<int>::stack(<brace-enclosed initializer list>)'

    // because of default container type(2nd template parameter) 
    // is std::deque, this will cause a syntax error.

    std::stack<int, std::vector<int>> mystack_6{ ivec };  // VALID

    // -------------------------------------------------
  }
*/

/*
  #include <stack>

  class Mystack : public std::stack<int> {
  public:
    void multiply(int val)
    {
      for (auto& elem : c)
        elem *= val;
    }
    // c is a protected data member of base class(std::stack<int>)
    // which can be accessed by derived class(Mystack)
  };

  int main()
  {
    Mystack mystack;

    for (int i = 0; i < 10; ++i)
      mystack.push(i);

    mystack.multiply(10);

    while (!mystack.empty()) {
      std::cout << mystack.top() << ' ';
      mystack.pop();
    }
    // output -> 90 80 70 60 50 40 30 20 10 0

    // "pop" member function of std::stack's return type is void.
  }
*/

/*
  #include <stack>
  #include <string>
  #include "../headers/nutility.h"

  int main()
  {
    std::stack<std::string> str_stack;

    for (int i = 0; i < 3; i++) { 
      auto str = rname();
      std::cout << str << '\n';
      str_stack.push(str);
    }
    // output ->
    //  melisa
    //  dost
    //  kamil

    while (!str_stack.empty()) {
      std::cout << str_stack.top() << " is deleted\n";
      str_stack.pop();
    }
    // output ->
    //  kamil is deleted
    //  dost is deleted
    //  melisa is deleted
  }
*/

/*
  // std::stack implementation with std::vector container
  // as a data member

  #include <vector>
  #include <utility>  // std::move, std::forward

  template <typename T>
  class Stack {
  protected:
    std::vector<T> m_con;
  public:
    void push(const T& val)
    {
      m_con.push_back(val);
    }
    void push(T&& val)
    {
      m_con.push_back(std::move(val));
    }

    template <typename ...Args>
    void emplace(Args&&... args)
    {
      m_con.emplace_back(std::forward<Args>(args)...);
    }
  };
*/

/*
  #include <stack>

  int main()
  {
    std::stack<int> i_stack;

    i_stack.push(11);
    i_stack.push(22);
    i_stack.push(33);
    i_stack.push(44);

    i_stack.top() = 99;
    // "top" member function of std::stack is a reference type(T&)

    while (!i_stack.empty()) {
      std::cout << i_stack.top() << ' ';
      i_stack.pop();
    }
    // output -> 99 33 22 11
  }
*/

/*
  #include <cstddef>  // std::size_t
  #include <stack>
  #include <array>
  #include <string>

  //  {}
  //  []
  //  ()
  //  <>

  static const std::array<char, 4> open_arr{ '{', '[', '(', '<' };
  static const std::array<char, 4> close_arr{ '}', ']', ')', '>' };

  bool is_match(const std::string& str)
  {
    std::stack<char> ch_stack;

    for (auto ch : str) 
    {
      for (std::size_t i = 0; i < open_arr.size(); ++i) 
      {
        if (ch == open_arr[i]) {
          ch_stack.push(ch);
          continue;
        }
      }

      for (std::size_t i = 0; i < close_arr.size(); ++i) 
      {
        if (ch == close_arr[i]) 
        {
          if (ch_stack.empty())
            return false;

          if (ch_stack.top() == open_arr[i]){
            ch_stack.pop();
            continue;
          }
          else
            return false;
        }
      }
    }

    return ch_stack.empty();
  }

  int main()
  {
    std::cout << std::boolalpha;

    std::string str{ "((<hello[10]>)) {[x](y)}" };
    std::cout << is_match(str) << '\n';   // output -> true

    str = "((<hello[10]>)) {[x](y)";
    std::cout << is_match(str) << '\n';   // output -> false
  }
*/

/*
                  --------------------------------
                  | std::queue container adaptor |
                  --------------------------------
*/

/*
  - std::queue is a FIFO(first in first out) container adaptor.
  - default 2nd template parameter type is std::deque
*/

/*
  #include <queue>
  #include <vector>

  int main()
  {
    std::queue<int, std::vector<int>> i_queue;
    i_queue.push(12);

    // ---------------------------------------------------------

    i_queue.pop();  // syntax error
    // error: 'class std::vector<int>' has no member 
    // named 'pop_front'

    // std::vector CAN NOT be used as a container class type

    // ---------------------------------------------------------

    // std::list and std::deque CAN BE used 
    // as a container class type
  }
*/

/*
  #include <queue>
  #include <string>

  int main()
  {
    std::cout << std::boolalpha;

    std::queue<std::string> str_queue;

    str_queue.push("hello");
    str_queue.push("world");
    str_queue.push("live");
    str_queue.push("from");
    str_queue.push("izmir");

    // ------------------------------------------------

    std::cout << "str_queue.size() = " 
              << str_queue.size() << '\n';
    // output -> str_queue.size() = 5

    std::cout << "str_queue.empty() = " 
              << str_queue.empty() << '\n';
    // output -> str_queue.empty() = false

    // ------------------------------------------------

    std::cout << "begining of the queue = " 
              << str_queue.front() << '\n';
    // output -> begining of the queue = hello

    std::cout << "end of the queue = " 
              << str_queue.back() << '\n';
    // output -> end of the queue = izmir

    // ------------------------------------------------

    while (!str_queue.empty()) {
      std::cout << str_queue.front() << " is deleted\n";
      str_queue.pop();
    }
    // output ->
    //  hello is deleted
    //  world is deleted
    //  live is deleted
    //  from is deleted
    //  izmir is deleted

    // ------------------------------------------------
  }
*/

/*
            -----------------------------------------
            | std::priority_queue container adaptor |
            -----------------------------------------
*/

/*
  - std::list and std::vector containers can be used 
    as a container class type(2nd template parameter)
    because of std::random_access_iterator is needed.
*/

/*
  #include <queue>    // std::priority_queue
  #include <string>
  #include "../headers/nutility.h"

  int main()
  {
    std::priority_queue<std::string> str_pqueue;

    for (int i = 0; i < 10; ++i)
    {
      std::string str = rtown();
      std::cout << str << " is added\n";
      str_pqueue.push(str);
    }
    // output ->
    //  giresun is added
    //  karabuk is added
    //  adiyaman is added
    //  malatya is added
    //  erzincan is added
    //  van is added
    //  artvin is added
    //  ardahan is added
    //  kastamonu is added
    //  bilecik is is added

    std::cout << '\n';

    // ------------------------------------------------------

    // std::less<std::string> comparator has been used 
    // as a default template parameter(3rd param)

    // lexicographical compare will be applied 
    // for the value that will leave the container.

    while (!str_pqueue.empty()) {
      std::cout << str_pqueue.top() << " is deleted\n";
      str_pqueue.pop();
    }

    // output ->
    //  van is deleted
    //  malatya is deleted
    //  kastamonu is deleted
    //  karabuk is deleted
    //  giresun is deleted
    //  erzincan is deleted
    //  bilecik is deleted
    //  artvin is deleted
    //  ardahan is deleted
    //  adiyaman is deleted

    // ------------------------------------------------------
  }
*/

/*
  #include <queue>        // std::priority_queue
  #include <string>
  #include <vector>
  #include <functional>   // std::greater
  #include "../headers/nutility.h"

  int main()
  {
    std::priority_queue<std::string, 
                        std::vector<std::string>, 
                        std::greater<>> str_pqueue;

    for (int i = 0; i < 10; ++i) {
      std::string str = rtown();
      std::cout << str << " is added\n";
      str_pqueue.push(str);
    }
    // output ->
    //  diyarbakir is added
    //  isparta is added
    //  konya is added
    //  denizli is added
    //  manisa is added
    //  aydin is added
    //  sivas is added
    //  bayburt is added
    //  edirne is added
    //  bingol is added

    std::cout << '\n';

    // ------------------------------------------------------

    while (!str_pqueue.empty()) {
      std::cout << str_pqueue.top() << " is deleted\n";
      str_pqueue.pop();
    }
    // output ->
    //  aydin is deleted
    //  bayburt is deleted
    //  bingol is deleted
    //  denizli is deleted
    //  diyarbakir is deleted
    //  edirne is deleted
    //  isparta is deleted
    //  konya is deleted
    //  manisa is deleted
    //  sivas is deleted

    // ------------------------------------------------------
  }
*/

/*
  #include <cmath>    // std::abs
  #include <queue>    // std::priority_queue
  #include <vector>
  #include "../headers/nutility.h"

  int main()
  {
    const auto fn = [](int val_1, int val_2) {
      return abs(val_1) < abs(val_2);
    };

    std::priority_queue<int, 
                        std::vector<int>, 
                        decltype(fn)> int_pqueue;

    for (int i = 0; i < 10; ++i)
      int_pqueue.push(Irand{ -100, 100 }());

    while (!int_pqueue.empty()) {
      std::cout << int_pqueue.top() << ' ';
      int_pqueue.pop();
    }
    // output -> -75 66 -63 -52 -51 -44 -32 28 -12 -6
  }
*/