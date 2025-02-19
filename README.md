<h1 align="center"> CppLessons </h1>

### [Reference Semantics](https://github.com/UPinar/CppLessons/tree/main/reference_semantics)
  - L value references
  - pointer semantics 
  - reference semantics
  
### [Type Deduction](https://github.com/UPinar/CppLessons/tree/main/type_deduction)
  - `auto` type deduction
    - `auto`   x = expr
    - `auto&`  y = expr
    - `auto&&` z = expr (forwarding reference)
  - reference collapsing
  - trailing return type
  - auto return type
  - `decltype` specifier type deduction
    - decltype(identifier)
    - decltype(expression)
  - unevaluated context (İşlem kodu üretilmeyen bağlam) 
  
### [Default Argument](https://github.com/UPinar/CppLessons/tree/main/default_argument)
  - default arguments
  - maximal munch
  
### [Typecast Operators](https://github.com/UPinar/CppLessons/tree/main/typecast_operators)
  - (target type) Cstyle cast
  - static_cast
  - const_cast
  - reinterpret_cast
  - dynamic_cast
  
### [Enumeration Types](https://github.com/UPinar/CppLessons/tree/main/enumeration_types)
  - old-school(conventional) enum's problems
  - incomplete type
  - scoped & unscoped enums
  
### [`constexpr` Keyword](https://github.com/UPinar/CppLessons/tree/main/constexpr)
  - constexpr variables
  - constexpr functions
  
### [Inline Functions](https://github.com/UPinar/CppLessons/tree/main/inline_functions)
  - inline functions
    - inline expansion optimization
    - One Definition Rule - (ODR)
    - `static` vs `inline` functions
  - inline variables **C++17**
  
### [Function Overloading](https://github.com/UPinar/CppLessons/tree/main/function_overloading)
  - function signature
  - Function Overload Resolution
    - variadic conversion 
    - user-defined conversion
    - standart conversion
      - exact match
      - promotion
      - conversion
  - name decoration(mangling)
  
### [Classes](https://github.com/UPinar/CppLessons/tree/main/classes)
  - name lookup - context control - access control
  - qualified names scopes
  - non-static data members
  - member functions
  - access specifiers
  - `this` pointer
  - `const` member functions
  - `mutable` keyword
  - constructor & destructor
  - RAII idiom (Resource Acquisition Is Initialization)
  - special member functions
    - Not declared special member functions
    - User declared special member functions
      - User declared defined / to be defined
      - User declared defaulted
      - User declared deleted
    - Implicitly declared special member functions
      - Implicitly declared defaulted
      - Implicitly declared deleted
  
### [Storage Class](https://github.com/UPinar/CppLessons/tree/main/storage_class)
  - Storage Classes(Lifetime)
     - Static storage class
     	 - global variables 
     	 - static local variables
     - Automatic storage class
       - function's local variables
       - local and non-static variables in block scopes
     - Dynamic storage class 
       - new/delete keyword
     
### [Special Member Functions](https://github.com/UPinar/CppLessons/tree/main/special_member_functions)
  - implicitly declared default ctor
  - constructor(member) initializer list - (MIL)
  - deep and shallow copy in copy constructor
  - deep and shallow copy in copy assignment
  - move members
  
### [Terms For Classes](https://github.com/UPinar/CppLessons/tree/main/terms_for_classes)
  - moved-from state
  - default member initializer
  - delegated constructor
  - temporary objects
  - conversion constructor
  - explicit constructor
  - copy elision
     - Mandatory Copy Elision scenarios
     - Named Return Value Optimization - (NRVO)
  - pessimistic move
  - reference qualifiers (Modern C++)
  
### [`friend` Declarations](https://github.com/UPinar/CppLessons/tree/main/friend_declarations)
  - `friend` declared global(free) function
  - `friend` declared other class's specific member function
  - `friend` declared other class(all of other classes member functions)
  
### [Operator Overloading](https://github.com/UPinar/CppLessons/tree/main/operator_overloading)
  - global and member operator overload functions
  - `const` correctness for operator overloading 
  - overloading assignment operators
  - overloading arithmetic operators
  - overloading increment and decrement operators
  - `[[nodiscard]]` attribute
  - overloading subscript operator
  - overloading dereferencing & arrow operators
  - overloading function call operator
  - overloading type-cast operator function
  - enum type's global operator overload functions
  
### [`static` in Classes](https://github.com/UPinar/CppLessons/tree/main/static_in_class)
  - static member variable
  - `inline` static member variable
  - `constexpr` static member variable
  - static member functions
  - member function pointer
  - named constructor idiom
  - dynamic object only class
  - singleton design pattern
  
### [Composition / Containment](https://github.com/UPinar/CppLessons/tree/main/composition_containment)
  - composition / containment
  - special member functions incomposition
  
### [Nested Types](https://github.com/UPinar/CppLessons/tree/main/nested_types)
  - nested types
  - Pimpl idiom (pointer to implementation)
 
### [`namespace`](https://github.com/UPinar/CppLessons/tree/main/namespace)
  - `using` declaration
  - `using namespace` (directive) declaration
  - unnamed namespace
  - namespace alias
  - argument dependent lookup - (ADL)
  - `inline` namespace
  - versioning with `inline` namespaces
  
### [`std::string`](https://github.com/UPinar/CppLessons/tree/main/std_string)
  - `std::string` class interface
  - constexpr static data member `std::string::npos`
  - search member functions of `std::string` class
  - remove-erase idiom
  - `std::string_view` class (C++ 17)
  
### [Inheritance](https://github.com/UPinar/CppLessons/tree/main/inheritance)
  - inheritance and name lookup
  - inheritance and access control
  - special member functions in inheritance
  - `using` declerations in inheritance
  - inherited constructor
  - run-time polymorphism
  - virtual dispatch mechanism
  - non-virtual interface idiom - (NVI)
  - `virtual` constuctor(clone) idiom
  - variant return type (covariance)
  - virtual destructor
  - `final` keyword
  - run time type identification(information) - (RTTI)
    - `dynamic_cast` operator
    - `typeid` operator
  - private inheritance
    - empty base optimization - (EBO)
  - restricted polymorphism
  - protected inheritance
  - multiple inheritence
	  - dreadful diamond on derivation - (DDD)
	  - virtual inheritance

### [Exception Handling](https://github.com/UPinar/CppLessons/tree/main/exception_handling)
  - stack unwinding
  - rethrow statement
  - exception dispatcher
  - translating an exception
  - exception guarantees
  - `noexcept` keyword
    - `noexcept` specifier
    - `noexcept` operator
  - constructors & exceptions
  - some exception classes
    - `std::bad_alloc`
    - `std::bad_cast`
    - `std::bad_typeid`
  - function try block
  
### [Templates](https://github.com/UPinar/CppLessons/tree/main/Templates)
  - template argument deduction
  - trailing return type
  - member function template
  - class templates
  - class template argument deduction (CTAD)
  - explicit(full) specialization 
  - partial specialization
  - alias templates
     - typedef declerations
     - using declerations
  - default template parameter
  - variable templates
    - SFINAE(Substitution Failure Is Not An Error)
  - variadic templates
    - pack expansion
    - compile-time recursivity (eksiltme teknigi)
    - std::initializer_list technique
    - fold expressions (C++17)
      - unary fold  (left, right)
      - binary fold (left, right)
    - static if (C++17) 

### [Standart Template Library(STL)](https://github.com/UPinar/CppLessons/tree/main/standart_template_library)
  - standart function objects(standart functors)
    - `std::less`, `std::greater`, `std::plus`, `std::negate` etc
  - lambda expressions(functions)
    - generalized lambda expression
    - lambda init capture (C++14)
    - positive lambda idiom
    - immediately invoked function(lambda) expression (IIFE) idiom
  - `std::hash`
  - `std::reference_wrapper`
  - member function pointers
  - data member pointers
  - `std::function`
  - `std::invoke`
  - function adaptors
    - `std::bind`
    - `std::mem_fn`
    - `std::not_fn`
  
### [STL Iterators](https://github.com/UPinar/CppLessons/tree/main/stl_iterators)
  - iterator categories
  - const_iterator - iterator adaptor
  - iterator manipulator functions
    - `std::advance`
      - tag dispatch technique
    - `std::distance`
    - `std::next`, `std::prev`
    - `std::iter_swap`
  - `std::reverse_iterator` - iterator adaptor
  - iterator invalidation
  - `std::ostream_iterator` class
  - `std::move_iterator` iterator adaptor

### [STL Algorithms](https://github.com/UPinar/CppLessons/tree/main/stl_algorithms)
  - `std::copy`, `std::copy_if`
  - `std::sort`
  - `std::find`, `std::find_if`
  - `std::back_inserter`, `std::front_inserter`
  - `std::count`, `std::count_if`
  - `std::transform`
  - `std::for_each`
  - `std::all_of`, `std::any_of`, `std::none_of`
  - `std::max_element`
  - `std::minmax_element`
  - `std::replace`, `std::replace_if`
  - `std::reverse`, `std::reverse_copy`
  - `std::remove_copy`, `std::remove_copy_if`
  - `std::lexicographical_compare`
  - `std::generate_n`
  - `std::remove`, `std::remove_if`
    - remove-erase idiom
  - `std::unique`
  - sorting algorithms
    - `std::sort`
    - `std::stable_sort`
    - `std::partial_sort`, `std::partial_sort_copy`
    - `std::nth_element` 
    - `std::partition` 
    - `std::stable_partition` 
    - `std::partition_copy` 
    - `std::is_sorted`, `std::is_sorted_until`
  - `std::make_heap`, `std::pop_heap`, `std::push_heap`, `std::sort_heap`
  - `std::lower_bound`, `std::upper_bound`, `std::equal_range`
  - `std::set_intersection`, `std::set_union`
  - `std::set_difference`, `std::set_symmetric_difference`
  - `std::binary_search`

### [STL Containers](https://github.com/UPinar/CppLessons/tree/main/stl_containers)
  - containers
    - `std::vector` dynamic array
    - `std::deque` double ended queue
    - `std::list` doubly-linked list
    - `std::forward_list` singly-linked list
    - `std::set`, `std::multiset`
    - `std::map`, `std::multimap`
    - `std::unordered_set`
    - `std::array`
  - container adaptors
    - `std::stack`
    - `std::queue`
    - `std::priority_queue`
  
### [`<tuple>` module](https://github.com/UPinar/CppLessons/tree/main/tuple_module)
  - `std::get(tuple)`
  - `std::ignore`
  - `std::tie`
  - `std::apply`
  - `std::tuple_size`, `std::tuple_element`
  - structured binding (C++17)

### [`<bitset>` module](https://github.com/UPinar/CppLessons/tree/main/bitset_module)

### [Smart Pointers](https://github.com/UPinar/CppLessons/tree/main/smart_pointers)
  - dynamic storage objects
  - placement new expression
  - `std::unique_ptr`
  - `std::shared_ptr`
  - `std::weak_ptr`

### [Input - Output Operations](https://github.com/UPinar/CppLessons/tree/main/input_output)
  - Formatted IO Operations
    - `std::ios::fmtflags`
  - File IO Operations

### [User Defined Literals](https://github.com/UPinar/CppLessons/tree/main/user_defined_literals)
  - cooked UDL
  - uncooked UDL

### [`<random>` module](https://github.com/UPinar/CppLessons/tree/main/random_module)
  - `std::mt19937`, `std::mt19937_64`
  - std::uniform_int_distribution
  - std::uniform_real_distribution
  - std::discrete_distribution
  - std::bernoulli_distribution
  - algorithms used in random number generation
    - `std::generate`, `std::generate_n`
    - `std::shuffle` 
    - `std::sample`

### [`std::string_view` (C++17)](https://github.com/UPinar/CppLessons/tree/main/string_view)

### [Vocabulary Types (C++17)](https://github.com/UPinar/CppLessons/tree/main/VocabularyTypes)
  - `std::optional`
  - `std::variant`
  - visitor design pattern
  - overloader idiom
  - mono state pattern
  - variant polymorphism
  - variant comparison
  - `std::any`

### [Ratio Library](https://github.com/UPinar/CppLessons/tree/main/RatioLibrary)

### [Chrono Library](https://github.com/UPinar/CppLessons/tree/main/ChronoLibrary)
  - duration
  - time point
  - clock

### [Concurrency](https://github.com/UPinar/CppLessons/tree/main/Concurrency)
  - `<thread>` module
  - `std::this_thread` namespace
  - exception handling - threads relationship
  - thread-local storage duration | `thread_local` keyword
  - `std::async` function template
  - `std::future` class template
  - `std::shared_future` class template
  - `std::packaged_task` class template
  - shared resources in threads
  - mutex (mutual exclusion)
    - `std::mutex` class
    - `std::timed_mutex` class
    - `std::lock_guard` class template
    - `std::recursive_mutex` class
    - `std::unique_lock` class template
    - `std::lock` function template
    - `std::scoped_lock` variadic class template **(C++17)**
  - `std::call_once` & `std::once_flag`
  - condition variable
  - atomic 
    - `std::atomic_flag`
    - compare and swap(CAS)

### [Not Related](https://github.com/UPinar/CppLessons/tree/main/not_related)
  - range based for loop
  - pointer to an array
  - if with initializer (C++17)
  - `std::initializer_list` class template
  - `std::pair` class template
  - perfect forwarding
  - type alias
  - `decltype(auto)`
  - CRTP(Curiously Recurring Template Pattern) idiom