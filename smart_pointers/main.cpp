#include <iostream>

/*
                        ==================
                        | Smart Pointers |
                        ==================
*/

/*
                    ---------------------------
                    | dynamic storage objects |
                    ---------------------------
*/

/*
  // C style dynamic memory allocation

  #include <cstdlib>
  // std::malloc, std::free, std::exit, EXIT_FAILURE

  struct Point {
    int m_a, m_b, m_c;
  };

  int main()
  {
    struct Point* px = (Point*)malloc(sizeof(struct Point));

    if (!px)
      exit(EXIT_FAILURE);

    px->m_a = 10;
    px->m_b = 11;
    px->m_c = 12;

    free(px);
  }
*/

/*
  #include <string>

  int main()
  {
    // --------------------------------------------

    std::string* p_str1 = new std::string;
    auto p_str2 = new std::string;
    // Those 2 lines are equivalent.

    // dynamic storage objects(std::string)
    // are default initialized.

    // --------------------------------------------

    new std::string{};    // value initialization

    // --------------------------------------------

    auto p_str3 = new std::string(10, 'a');

    // dynamic memory allocations in heap :
    // 1. storage of std::string object (sizeof(std::string)
    //      memory allocation
    // 2. storage for std::string object's value ("aaaaaaaaaa")
    //      resource allocation

    // --------------------------------------------
  }
*/

/*
  void* operator new(size_t);   // operator new function

  // - has same function signature as "malloc" function
  //  - if succeeds returns a void*
  //  - if fails throws a std::bad_alloc exception

  // - overloading "operator new" function
*/

/*
  #include <new>    // operator new

  class Myclass {
  private:
    unsigned char m_bufffer[1024]{};

  public:
    Myclass()
    {
      std::cout << "Myclass()\n";
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
      std::cout << "~Myclass()\n";
    }
  };

  int main()
  {
    std::cout << "sizeof(Myclass) = "
              << sizeof(Myclass) << '\n';
    // output -> sizeof(Myclass) = 1024

    // -------------------------------------------------

    Myclass* p_m1 = new Myclass;      // default initialization
    // output -> Myclass()
    Myclass* p_m2 = new Myclass();    // value initialization
    // output -> Myclass()
    Myclass* p_m3 = new Myclass{};    // value initialization
    // output -> Myclass()

    Myclass* p_m4 = new Myclass{ 12 };
    // output -> Myclass(int)
    Myclass* p_m5 = new Myclass{ 12, 56 };
    // output -> Myclass(int, int)

    // -------------------------------------------------

    // what happens when this statement executed
    // `Myclass* p_m1 = new Myclass;`

    void* vp = operator new(sizeof(Myclass));
    try {
      new (vp)Myclass;
    }
    catch (...) {
      operator delete(vp);
    }

    // -------------------------------------------------
  }
*/

/*
  #include <vector>
  #include <new>      // operator new

  class Myclass {
  private:
    unsigned char m_buffer[1024 * 1024]{};

  public:
    Myclass()
    {
      std::cout << "Myclass()\n";
    }
    ~Myclass()
    {
      std::cout << "~Myclass()\n";
    }
  };

  int main()
  {
    std::vector<void*> vp_vec;

    int counter;
    try {
      for (counter = 0; counter < 100'000; ++counter)
        vp_vec.push_back(operator new(sizeof(Myclass)));
    }
    catch (const std::exception& ex)
    {
      std::cout << "exception caught : " << ex.what() << '\n';
      std::cout << "counter = " << counter << '\n';
    }
    // output ->
    //  exception caught : std::bad_alloc
    //  counter = 80392
    // operator new() function throw an exception
  }
*/

/*
  #include <new>    // operator delete

  class Myclass {
  private:
    unsigned char m_buffer[1024 * 1024]{};
  };

  int main()
  {
    auto p_mx = new Myclass;

    // -------------------------------------------------

    // what happens when this statement executed
    // `delete p_mx;`

    p_mx->~Myclass();
    operator delete(p_mx);

    // -------------------------------------------------
  }
*/

/*
  #include <cstdlib>    // std::malloc, std::free
  #include <new>        // std::bad_alloc

  class Myclass {
  private:
    unsigned char m_buffer[1024]{};
  public:
    Myclass()
    {
      std::cout << "Myclass(), this = " << this << '\n';
    }
    ~Myclass()
    {
      std::cout << "~Myclass(), this = " << this << '\n';
    }
  };

  void* operator new(std::size_t size)
  {
    std::cout << "operator new(std::size_t size), size = "
              << size << '\n';

    void* v_p = std::malloc(size);

    if (!v_p)
      throw std::bad_alloc{};

    std::cout << "address of allocated block = " << v_p << '\n';
    return v_p;
  }

  void operator delete(void* vp) noexcept
  {
    if (!vp)
      return;

    std::cout << "operator delete(void* vp), vp = "
              << vp << '\n';
    std::free(vp);
  }

  int main()
  {
    std::cout << "[0] - main started\n";
    auto p_m = new Myclass;
    std::cout << "[1] - main continues\n";
    delete p_m;
    std::cout << "[2] - main ends\n";
  }
  // output ->
  //  [0] - main started
  //  operator new(std::size_t size), size = 1024
  //  address of allocated block = 0x2488120d2c0
  //  Myclass(), this = 0x2488120d2c0
  //  [1] - main continues
  //  ~Myclass(), this = 0x2488120d2c0
  //  [2] - main ends
*/

/*
  class Myclass {
  private:
    unsigned char m_buffer[256]{};
  public:
    Myclass()
    {
      std::cout << "Myclass(), this = " << this << '\n';
    }
    ~Myclass()
    {
      std::cout << "~Myclass(), this = " << this << '\n';
    }
  };

  int main()
  {
    // array new
    Myclass* p = new Myclass[5];
    // output ->
    //  Myclass(), this = 0x1edb934c568
    //  Myclass(), this = 0x1edb934c668
    //  Myclass(), this = 0x1edb934c768
    //  Myclass(), this = 0x1edb934c868
    //  Myclass(), this = 0x1edb934c968

    // array delete
    delete[] p;
    // output ->
    //  ~Myclass(), this = 0x1edb934c968
    //  ~Myclass(), this = 0x1edb934c868
    //  ~Myclass(), this = 0x1edb934c768
    //  ~Myclass(), this = 0x1edb934c668
    //  ~Myclass(), this = 0x1edb934c568
  }
*/

/*
  class Myclass {
  private:
    unsigned char m_buffer[256]{};
  public:
    Myclass()
    {
      std::cout << "Myclass(), this = " << this << '\n';
    }
    ~Myclass()
    {
      std::cout << "~Myclass(), this = " << this << '\n';
    }
  };

  int main()
  {
    // ----------------------------------------------

    const Myclass* p_cm1 = new const Myclass;
    auto p_cm2 = new const Myclass;
    // Those 2 lines are equivalent.

    // output ->
    //  Myclass(), this = 0x24f6d223530
    //  Myclass(), this = 0x24f6d223640

    // ----------------------------------------------

    delete p_cm1;
    delete p_cm2;

    // output ->
    //  ~Myclass(), this = 0x24f6d223530
    //  ~Myclass(), this = 0x24f6d223640

    // ----------------------------------------------
  }
*/

/*
  class Myclass {
  private:
    unsigned char m_buffer[256]{};
  public:
    Myclass()
    {
      std::cout << "Myclass(), this = " << this << '\n';
    }
    ~Myclass()
    {
      std::cout << "~Myclass(), this = " << this << '\n';
    }
  };

  int main()
  {
    Myclass* p_m1 = new Myclass;

    delete p_m1;
    // p_m1 becomes a dangling pointer after `delete`

    delete p_m1;    // double deletion (undefined behaviour)
  }
*/

/*
  // memory model for operator new function.

  #include <cstdlib>    // std::malloc
  #include <cstddef>    // std::size_t
  #include <new>        // std::bad_alloc

  using handler_t = void(*)();

  handler_t g_fp = nullptr;

  handler_t get_new_handler()
  {
    return g_fp;
  }

  handler_t set_new_handler(handler_t fn)
  {
    auto temp_handler = g_fp;
    g_fp = fn;
    return temp_handler;
  }

  void* operator new(std::size_t size)
  {
    for (;;)
    {
      void* v_p = std::malloc(size);
      if (v_p)
        return v_p;

      auto fn_ptr = get_new_handler();

      // if fn_ptr is nullptr it will throw std::bad_alloc
      // default behaviour.
      // if fn_ptr is not nullptr it will call that function

      if (!fn_ptr)
        throw std::bad_alloc{};
      else
        fn_ptr();
    }
  }
*/

/*
  #include <new>      // std::set_new_handler
  #include <vector>
  #include <cstdlib>  // std::exit, EXIT_FAILURE

  int g_counter{};

  void fn_handler()
  {
    std::cout << "first_handler called\n";
    std::cout << "g_counter = " << g_counter << '\n';
    std::exit(EXIT_FAILURE);
  }

  class Myclass {
    unsigned char m_buffer[2048 * 2048]{};
  };


  int main()
  {
    std::set_new_handler(&fn_handler);

    std::vector<Myclass*> pmx_vec;

    for (int i = 0; i < 100'000; ++i)
    {
      ++g_counter;
      pmx_vec.push_back(new Myclass);
    }

    // output ->
    //  first_handler called
    //  g_counter = 80392
  }
*/

/*
  handler function that set with std::set_new_handler function

  1) can execute the code that lets program
    to allocate new memory.
  2) can execute necessary code then throw std::bad_alloc
    or another exception that inherited from std::bad_alloc
  3) can set std::set_new_handler to nullptr
    so next time std::bad_alloc exception will be thrown.
  4) can set another handler by calling std::set_new_handler
    function again.
*/

/*
  // can execute necessary code then throw std::bad_alloc
  // or another exception that inherited from std::bad_alloc

  #include <new>      // std::bad_alloc, std::set_new_handler
  #include <vector>

  void fn_handler()
  {
    static int cnt{};
    std::cout << "fn_handler has been called for "
              << ++cnt << " times.\n";
    if (cnt == 3)
      throw std::bad_alloc{};
  }

  class Myclass {
    unsigned char m_buffer[4096 * 4096]{};
  };

  int main()
  {
    std::set_new_handler(&fn_handler);

    std::vector<Myclass*> pmx_vec;

    for (int i = 0; i < 100'000; ++i)
      pmx_vec.push_back(new Myclass);
  }
  // output ->
  //  fn_handler has been called for 1 times.
  //  fn_handler has been called for 2 times.
  //  fn_handler has been called for 3 times.
  //  terminate called after throwing an instance of 'std::bad_alloc'
  //    what():  std::bad_alloc
*/

/*
  // can set std::set_new_handler to nullptr
  // so next time std::bad_alloc exception will be thrown.

  #include <new>      // std::set_new_handler
  #include <vector>

  void fn_handler()
  {
    static int cnt{};
    std::cout << "fn_handler has been called for "
              << ++cnt << " times.\n";
    if (cnt == 3)
      std::set_new_handler(nullptr);
  }

  class Myclass {
    unsigned char buff[4096 * 4096]{};
  };

  int main()
  {
    std::set_new_handler(&fn_handler);
    std::vector<Myclass*> pmx_vec;

    try
    {
      for (int i = 0; i < 10000; ++i)
        pmx_vec.push_back(new Myclass);
    }
    catch (const std::exception& ex)
    {
      std::cout << "exception caught: " << ex.what() << '\n';
    }
    // output ->
    //  fn_handler has been called for 1 times.
    //  fn_handler has been called for 2 times.
    //  fn_handler has been called for 3 times.
    //  exception caught: std::bad_alloc
  }
*/

/*
  // can set another handler by calling
  // std::set_new_handler function again.

  #include <new>
  #include <vector>

  int g_counter{};

  void fn_handler_2()
  {
    static int cnt{};
    std::cout << "fn_handler_2 has been called for "
              << ++cnt << " times.\n";
    if (cnt == 2)
      std::set_new_handler(nullptr);
  }

  void fn_handler_1()
  {
    static int cnt{};
    std::cout << "fn_handler_1 has been called for "
              << ++cnt << " times.\n";
    if (cnt == 2)
      std::set_new_handler(&fn_handler_2);
  }

  class Myclass {
    unsigned char buff[4096 * 4096]{};
  };

  int main()
  {
    std::set_new_handler(&fn_handler_1);

    std::vector<Myclass*> pmx_vec;

    try
    {
      for (int i = 0; i < 10000; ++i)
      {
        g_counter++;
        pmx_vec.push_back(new Myclass);
      }
    }
    catch (const std::exception& ex)
    {
      std::cout << "exception caught: " << ex.what() << '\n';
      std::cout << "g_counter = " << g_counter << '\n';
    }
  }
  // output ->
  //  fn_handler_1 has been called for 1 times.
  //  fn_handler_1 has been called for 2 times.
  //  fn_handler_2 has been called for 1 times.
  //  fn_handler_2 has been called for 2 times.
  //  exception caught: std::bad_alloc
  //  g_counter = 5306
*/

/*
                  -----------------------------
                  | placement new expressions |
                  -----------------------------
*/

/*
  #include <cstdlib>    // std::malloc
  #include <new>        // operator new

  class Myclass {
  private:
    unsigned char m_buffer[1024]{};
  };

  void* operator new(std::size_t, int x, int y)
  {
    std::cout << "x = " << x << " y = " << y << '\n';
    return std::malloc(1000);
  }

  int main()
  {
    auto p_mx = new(111, 555)Myclass;
    // output -> x = 111 y = 555

    // more information can be sent to
    // "operator new" function overload
  }
*/

/*
  // CAN NOT BE OVERLOADED
  //  void* operator new(std::size_t, void* vp)
  //  {
  //    return vp;
  //  }

  class Myclass {
  private:
    unsigned char m_buff[1024]{};
  public:
    Myclass()
    {
      std::cout << "Myclass(), this = " << this << '\n';
    }
  };

  int main()
  {
    // -----------------------------------------------------

    unsigned char arr_buffer[1024];
    // arr_buffer is in stack memory.

    std::cout << "&arr_buffer = "
              <<  static_cast<void*>(arr_buffer) << '\n';
    // output -> &arr_buffer = 0x46db3ff450

    // -----------------------------------------------------

    Myclass* p_mx = new(arr_buffer)Myclass;
    // output -> Myclass(), this = 0x46db3ff450

    // passing &arr_buffer(array to pointer conversion)
    // to operator new function
    // so Myclass object will be constructed in &arr_buffer.

    // -----------------------------------------------------

    delete p_mx;  // undefined behaviour.

    // because of &arr_buffer is in stack memory
    // calling "operator delete" function
    // will be undefined behaviour.
    // in this case constructor of Myclass object
    // should be called by its name.

    p_mx->~Myclass();

    // -----------------------------------------------------
  }
*/

/*
  #include <new>    // std::nothrow

  class Myclass {
    char m_buffer[1024 * 1024];
  };

  int main()
  {
    // -----------------------------------------------

    new(std::nothrow) Myclass;
    // if it fails, it will not throw an exception,
    // it will return nullptr

    // -----------------------------------------------

    Myclass* p_mx = new(std::nothrow)Myclass;
    if (!p_mx)
      std::cout << "allocation failed\n";
    else
      std::cout << "allocation succeeded\n";

    // -----------------------------------------------
  }
*/

/*
  #include <cstddef>    // std::size_t

  class Myclass {
  private:
    char m_buffer[1024]{};

  public:
    void* operator new(std::size_t N)
    {
      this; // syntax error
      // error: 'this' is unavailable for static member functions
    }
  };

  int main()
  {
    auto p_mx = new Myclass;

    // memory for Myclass object needs to be allocated
    // before Myclass object's construction.

    // If "operator new" was a non-static member function
    // because of Myclass objects contruction is not completed
    // "this" pointer won't be available and non-static
    // member function can not be called withot `this` pointer
    // so "operator new" function is a static member function.
  }
*/

/*
  #include <cstddef>  // std::size_t

  class Myclass {
  private:
    char m_buffer[1024]{};
  public:
    // `static` keyword can be used.
    static void* operator new(std::size_t N)
    {
      return nullptr;
    }
  };

  int main()
  {
    auto p_mx = new Myclass;
  }
*/

/*
  #include <cstddef>    // std::size_t
  #include <cstdlib>    // std::malloc, std::free
  #include <new>        // std::bad_alloc

  class Myclass {
  private:
    char m_bufffer[1024]{};

  public:
    Myclass()
    {
      std::cout << "Myclass(), this = " << this << '\n';
    }

    ~Myclass()
    {
      std::cout << "~Myclass() = " << this << '\n';
    }

    static void* operator new(std::size_t N)
    {
      std::cout << "Myclass::operator new(std::size_t)\n";
      std::cout << "N = " << N << '\n';
      void* v_ptr = std::malloc(N);

      if (!v_ptr)
        throw std::bad_alloc{};

      std::cout << "address = " << v_ptr << '\n';
      return v_ptr;
    }

    static void operator delete(void* vp)
    {
      std::cout << "Myclass::operator delete(void*)\n";
      std::cout << "address = " << vp << '\n';
      std::free(vp);
    }
  };

  int main()
  {
    Myclass* p_mx = new Myclass;
    // output ->
    //  Myclass::operator new(std::size_t)      : operator new
    //  N = 1024
    //  address = 0x19da968b400
    //  Myclass(), this = 0x19da968b400         : constructor

    delete p_mx;
    // output ->
    //  ~Myclass() = 0x19da968b400              : destructor
    //  Myclass::operator delete(void*)         : operator delete
    //  address = 0x19da968b400
  }
*/

/*
  #include <cstddef>    // std::size_t
  #include <cstdlib>    // std::malloc
  #include <new>        // std::bad_alloc

  class Myclass {
  private:
    char m_bufffer[1024]{};

  public:
    static void* operator new(std::size_t N)
    {
      std::cout << "Myclass::operator new(std::size_t)\n";

      void* v_ptr = std::malloc(N);
      if (!v_ptr)
        throw std::bad_alloc{};

      return v_ptr;
    }

    static void operator delete(void* vp)
    {
      std::cout << "Myclass::operator delete(void*)\n";
      std::free(vp);
    }
  };

  int main()
  {
    // class Myclass have static "operator new"
    // and "operator delete" overloads.

    // standart libraries "operator new" and "operator delete"
    // can be called by using (::) unary scope resolution operator.

    Myclass* p_mx = ::new Myclass;
    ::delete p_mx;
    // no output
  }
*/

/*
                        -------------------
                        | std::unique_ptr |
                        -------------------
*/

/*
  - std::unique_ptr class template 
    is a wrapper class for a pointer.
*/

/*
  #include <memory>

  template <typename T>
  struct Default_Delete {
    void operator(T* p)
    {
      delete p;
    }
  };

  template <typename T, typename Deleter = Default_Delete<T>>
  class Unique_Ptr {
  private:
    T* m_p{};
  public:
    Unique_Ptr() = default;

    Unique_Ptr(T* p) : m_p{ p } 
    {}

    ~Unique_Ptr()
    {
      if (m_p)
        Deleter{}(m_p);
    }

    T& operator*()
    {
      return *m_p;
    }

    T* operator->()
    {
      return m_p;
    }
  };
*/

/*
  #include <memory>   // std::unique_ptr
  #include <string>

  class Myclass {
  private:
    std::string m_str;
  public:
    Myclass() = default;

    Myclass(std::string str) : m_str{ str } 
    {}

    ~Myclass()
    {
      std::cout << "object in address = " 
                << this << " has been deleted.\n";
    }

    std::string& operator*()
    {
      return m_str;
    }

    friend std::ostream& operator<<(std::ostream& os, 
                                    const Myclass& mx)
    {
      return os << mx.m_str;
    }
  };

  int main()
  {
    // ------------------------------------------

    std::unique_ptr<std::string> up_str;
    // default initalization

    // ------------------------------------------

    {
      std::unique_ptr<Myclass> up_mx(new Myclass{ "hello world" });
      std::cout << *up_mx << '\n';
      // output -> hello world
    }
    // output ->
    //  object in address = 0x25a55379340 has been deleted.

    // ------------------------------------------
  }
*/

/*
  #include <memory>   // std::unique_ptr
  #include <string>

  class Myclass {
  private:
    std::string m_str;
  public:
    Myclass() = default;

    Myclass(std::string str) : m_str{ str } 
    {}

    ~Myclass()
    {
      std::cout << "object in address = " 
                << this << " has been deleted.\n";
    }
  };

  int main()
  {
    // -----------------------------------------------

    std::unique_ptr<Myclass> up_mx_1;
    std::unique_ptr<Myclass> up_mx_2{};
    std::unique_ptr<Myclass> up_mx_3{ nullptr };
    std::unique_ptr<Myclass> up_mx_4 = nullptr;
    // Those 4 lines are equivalent.
    // default initialization

    // -----------------------------------------------

    // if(p1.operator bool())
    if (up_mx_1)
      std::cout << "up_mx_1 is full" << '\n';
    else
      std::cout << "up_mx_1 is empty" << '\n';
    // output -> up_mx_1 is empty

    if (up_mx_1.operator bool())
      std::cout << "up_mx_1 is full" << '\n';
    else
      std::cout << "up_mx_1 is empty" << '\n';
    // output -> up_mx_1 is empty
    
    // -----------------------------------------------

    if (up_mx_2 != nullptr)
      std::cout << "up_mx_2 is full" << '\n';
    else
      std::cout << "up_mx_2 is empty" << '\n';
    // output -> up_mx_2 is empty

    // -----------------------------------------------

    if (!(up_mx_1 && up_mx_2 && up_mx_3 && up_mx_4))
      std::cout << "all of them are empty" << '\n';
    // output -> all of them are empty

    // -----------------------------------------------

    {
      std::unique_ptr<Myclass> up_mx_5{ new Myclass };

      if (up_mx_5)
        std::cout << "up_mx_5 is full" << '\n';
      else
        std::cout << "up_mx_5 is empty" << '\n';
      // output -> up_mx_5 is full
    }
    // output -> 
    //  object in address = 0x281bddd3cc0 has been deleted.

    // -----------------------------------------------
  }
*/

/*
  #include "myclass.hpp"
  #include <memory>   // std::unique_ptr

  int main()
  {
    std::unique_ptr<Myclass> up;

    try {
      *up;   // undefined behaviour(UB)
    }
    catch(const std::exception& ex)
    {
      std::cout << "exception caught : " 
                << ex.what() << '\n';
    }
    // dereferencing an empty std::unique_ptr object
    // will NOT throw an exception, it is undefined behaviour(UB).
  }
*/

/*
  // std::unique_ptr is a move only type.

  #include "myclass.hpp"
  #include <memory>   // std::unique_ptr
  #include <vector>
  #include <utility>  // std::move


  int main()
  {
    std::unique_ptr<Myclass> up1{ new Myclass{ "hello" } };
    // output -> hello object has been created

    // ----------------------------------------------

    std::unique_ptr<Myclass> up2 = up1; // syntax error
    // error: use of deleted function 
    // 'std::unique_ptr(const std::unique_pt&)

    // std::unique_ptr's copy ctor is deleted.

    // ----------------------------------------------

    std::unique_ptr<Myclass> up3;
    up3 = up1;    // syntax error
    // error: use of deleted function 
    // 'std::unique_ptr::operator=(const std::unique_ptr&)

    // std::unique_ptr's copy assignment operator is deleted.

    // ----------------------------------------------

    std::vector<std::unique_ptr<Myclass>> up_mx_vec;
    std::unique_ptr<Myclass> up4;

    up_mx_vec.push_back(up4);   // syntax error
    // error: use of deleted function 
    // 'std::unique_ptr(const std::unique_ptr&) 

    // "push_back" member function is calling copy constructor
    // of std::unique_ptr class template.

    // ---------------------------------------------

    std::unique_ptr<Myclass> up5{ new Myclass{ "galaxy" }};
    // output -> galaxy object has been created

    std::unique_ptr<Myclass> up6 = std::move(up5);  
    // std::unique_ptr's move ctor is called.

    // ---------------------------------------------

    std::unique_ptr<Myclass> up7;
    std::unique_ptr<Myclass> up8{ new Myclass{ "universe" }};
    // output -> universe object has been created

    std::cout << (up7 ? "up7 = full" 
                      : "up7 = empty") << '\n';	
    // output -> up7: empty

    std::cout << (up8 ? "up8 = full"
                      : "up8 = empty") << '\n';
    // output -> up8: full

    // ---------------------------------------------

    up7 = std::move(up8);
    // std::unique_ptr's move assignment operator is called.

    std::cout << (up7 ? "up7 = full" 
                      : "up7 = empty") << '\n';	
    // output -> up7: full

    std::cout << (up8 ? "up8 = full"
                      : "up8 = empty") << '\n';
    // output -> up8: empty

    // ---------------------------------------------
  }
*/

/*
  #include "myclass.hpp"
  #include <memory>   // std::unique_ptr

  int main()
  {
    std::cout << "[0] - main started\n";

    // ----------------------------------------------------

    std::unique_ptr<Myclass> up1{ new Myclass{"world"} };
    // output -> world object has been created
    std::unique_ptr<Myclass> up2{ new Myclass{"galaxy"} };
    // output -> galaxy object has been created

    std::cout << "up1 = " << (up1 ? "full" : "empty") << ", ";
    std::cout << "up2 = " << (up2 ? "full" : "empty") << '\n';
    // output -> up1 = full, up2 = full

    std::cout << *up1 << ' ' << *up2 << '\n';
    // output -> world galaxy

    // ----------------------------------------------------

    up1 = std::move(up2);
    // output -> world object has been deleted
    // up1 gave back its resources than steal up2's resources.

    std::cout << "up1 = " << (up1 ? "full" : "empty") << ", ";
    std::cout << "up2 = " << (up2 ? "full" : "empty") << '\n';
    // output -> up1 = full, up2 = empty

    // ----------------------------------------------------

    std::cout << "[1] - main ends\n";
  }
  // output -> galaxy object has been deleted
*/

/*
  #include "myclass.hpp"
  #include <memory>
  #include <vector>

  int main()
  {
    std::unique_ptr<Myclass> up_mx{ new Myclass{"world"} };
    std::vector<std::unique_ptr<Myclass>> up_mx_vec;

    up_mx_vec.push_back(std::move(up_mx));
    // "push_back(std::unique_ptr<Myclass>&&)" overload called.
    // which will call std::unique_ptr's move ctor.
  }
*/

/*
  #include "myclass.hpp"
  #include <memory>   // std::unique_ptr

  void func(std::unique_ptr<Myclass>){}

  std::unique_ptr<Myclass> foo()
  {
    return new{ "explicit constructor" }; // syntax error
    // error: expected type-specifier before '{' token
  }

  int main()
  {
    // ----------------------------------------------------

    std::unique_ptr<Myclass> up1 = new Myclass{ "copy init" };
    // syntax error (copy initialization)
    //  error: conversion from 'Myclass*' to non-scalar type
    //  'std::unique_ptr<Myclass>' requested

    // "new Myclass{ "copy init" }" expression 
    // returns a pointer to Myclass object (Myclass*)
    // and because of unique_ptr's one parameter ctor
    // is an explicit ctor, 
    // implicit conversion from T* to unique_ptr<T>
    // will cause a syntax error.

    // ----------------------------------------------------

    using up_type = std::unique_ptr<Myclass>;

    up_type up2 = static_cast<up_type>(new Myclass{ "up2" });

    // explicit conversion from from Myclass* to 
    // std::unique_ptr<Myclass> with static_cast

    // ----------------------------------------------------

    std::unique_ptr<Myclass> up3(new Myclass{ "up3" });
    // direct initialization (VALID)

    // ----------------------------------------------------

    std::unique_ptr<Myclass> up4{ new Myclass{ "up4" } };
    // value initialization. (VALID)

    // ----------------------------------------------------

    func(new Myclass{ "syntax error" });    // syntax error
    // because of explicit constructor of std::unique_ptr
    // explicit conversion from Myclass* to std::unique_ptr<Myclass>
    // will cause a syntax error.

    // ----------------------------------------------------

    func(std::unique_ptr<Myclass>{ new Myclass{ "func" } });	

    // ----------------------------------------------------
  }
*/

/*
  #include <memory>
  #include "myclass.hpp"

  int main()
  {
    auto p_mx = new Myclass{ "hello world" };
    // p_mx's data type is Myclass*

    // ------------------------------------------------

    std::unique_ptr<Myclass> up1{ p_mx };   
    // first assignment VALID

    std::unique_ptr<Myclass> up2{ p_mx };
    // second assignment undefined behaviour(UB)

    // at the end of the scope, because of both 
    // unique_ptr objects will try to delete the same object
    // double deletion will be happen (undefined behaviour)

    // ------------------------------------------------
  }
*/

/*
  #include "myclass.hpp"
  #include <memory>   // std::unique_ptr, std::make_unique
  #include <utility>  // std::forward
  #include <vector>

  template <typename T, typename ...Args>
  std::unique_ptr<T> Make_Unique(Args&&... args)
  {
    return std::unique_ptr<T>{ new T(std::forward<Args>(args)...)};
  }

  std::unique_ptr<Myclass> foo()
  {
    return Make_Unique<Myclass>("foo");
  }
  
  int main()
  {
    // --------------------------------------------------

    auto up1 = Make_Unique<Myclass>("world");
    // output -> world object has been created
    // mandatory copy ellision

    auto up2 = foo();
    // output -> foo object has been created
    // mandatory copy ellision

    // --------------------------------------------------

    std::vector<std::unique_ptr<Myclass>> up_mx_vec;

    up_mx_vec.push_back(std::unique_ptr<Myclass>{});

    up_mx_vec.push_back(std::make_unique<Myclass>("galaxy"));
    // output -> galaxy object has been created
    up_mx_vec.emplace_back(new Myclass{ "universe" });
    // output -> universe object has been created

    // --------------------------------------------------
  }
*/

/*
  #include <memory>   // std::make_unique
  #include "myclass.hpp"

  int main()
  {
    auto up = std::make_unique<Myclass>("world");

    std::cout << *up << '\n';   // output -> world

    // --------------------------------------------------

    up = new Myclass{ "galaxy" };   // syntax error
    // error: no match for 'operator=' (operand types are 
    // 'std::unique_ptr<Myclass, std::default_delete<Myclass>>' 
    // and 'Myclass*')

    // std::unique_ptr does not have an 
    // assignment operator= function 
    // which gets T* as a parameter

    // --------------------------------------------------

    {
      std::cout << "[0] - inner scope started\n";

      auto up1 = std::make_unique<Myclass>("universe");
      up1.reset();
      // "reset" member function will call 
      // wrapped object's destructor

      std::cout << "[1] - inner scope ended\n";
    }
    // output ->
    //  [0] - inner scope started
    //  universe object has been created
    //  universe object has been deleted
    //  [1] - inner scope ended

    // --------------------------------------------------
  }
*/

/*
  #include <memory>   // std::make_unique, std::unique_ptr
  #include "myclass.hpp"

  int main()
  {
    {
      std::cout << "[0] - inner scope started\n";

      auto up1 = std::make_unique<Myclass>("up1");
      up1.reset();

      std::cout << "[1] - inner scope ended\n";
    }
    // output ->
    //  [0] - inner scope started
    //  up1 object has been created
    //  up1 object has been deleted
    //  [1] - inner scope ended

    {
      std::cout << "[0] - inner scope started\n";

      auto up2 = std::make_unique<Myclass>("up2");
      up2.reset(nullptr);
      
      std::cout << "[1] - inner scope ended\n";
    }
    // output ->
    //  [0] - inner scope started
    //  up2 object has been created
    //  up2 object has been deleted
    //  [1] - inner scope ended

    {
      std::cout << "[0] - inner scope started\n";

      auto up3 = std::make_unique<Myclass>("up3");
      up3 = nullptr;
      
      std::cout << "[1] - inner scope ended\n";
    }
    // output ->
    //  [0] - inner scope started
    //  up3 object has been created
    //  up3 object has been deleted
    //  [1] - inner scope ended

    {
      std::cout << "[0] - inner scope started\n";

      auto up4 = std::make_unique<Myclass>("up4");
      up4 = std::unique_ptr<Myclass>{};
      
      std::cout << "[1] - inner scope ended\n";
    }
    // output ->
    //  [0] - inner scope started
    //  up4 object has been created
    //  up4 object has been deleted
    //  [1] - inner scope ended

    {
      std::cout << "[0] - inner scope started\n";

      auto up5 = std::make_unique<Myclass>("up5");
      up5 = {};
      
      std::cout << "[1] - inner scope ended\n";
    }
    // output ->
    //  [0] - inner scope started
    //  up5 object has been created
    //  up5 object has been deleted
    //  [1] - inner scope ended
  }
*/

/*
  #include <memory>   // std::make_unique
  #include "myclass.hpp"

  int main()
  {
    std::cout << "[0] - main started\n";

    {
      std::cout << "[0] - inner scope started\n";

      auto up = std::make_unique<Myclass>("world");
      // output -> world object has been created

      std::cout << *up << '\n';   
      // output -> world

      up.reset(new Myclass{ "galaxy" });
      // output -> galaxy object has been created
      // output -> world object has been deleted

      std::cout << *up << '\n';
      // output -> galaxy

      std::cout << "[1] - inner scope ended\n";
    }
    // output -> galaxy object has been deleted

    std::cout << "[1] - main ended\n";
  }
*/

/*
  #include <memory>   // std::make_unique
  #include "myclass.hpp"

  int main()
  {
    std::cout << "[0] - main started\n";

    // ------------------------------------------------

    auto up = std::make_unique<Myclass>("world");
    // output -> world object has been created

    std::cout << "up = " << (up ? "full" : "empty") << "\n";
    // output -> up = full

    // ------------------------------------------------
    
    auto p_mx = up.release();
    // p_mx's type is Myclass* 
    // pointer that "up" unique_ptr object holds

    std::cout << "up = " << (up ? "full" : "empty") << "\n";
    // output -> upx = empty

    // ------------------------------------------------

    // "p_mx" is a raw pointer that is pointing
    // to a dynamically allocated Myclass object on heap.
    // and because of std::unique_ptr object's "release"
    // member function is called, it will not delete the object
    // at the end of the scope.
    // it need to be deleted manually.

    delete p_mx;
    // output -> world object has been deleted

    // ------------------------------------------------

    std::cout << "[1] - main ended\n";
  }
*/

/*
  #include <memory>
  #include "myclass.hpp"

  int main()
  {
    // ------------------------------------------------

    auto up = std::make_unique<Myclass>("world");
    // output -> world object has been created

    std::cout << "up = " << (up ? "full" : "empty") << "\n";
    // output -> upx = full

    // ------------------------------------------------

    auto p_mx = up.get();
    // "p_mx"'s data type is Myclass*

    // "up" unique_ptr object is still holding the pointer
    // that "p_mx" is pointing to.

    std::cout << "up = " << (up ? "full" : "empty") << "\n";
    // output -> up = full

    // ------------------------------------------------

    delete p_mx;  // undefined behaviour(UB)

    // because of "up" unique_ptr object is still holding
    // the pointer that "p_mx" is pointing to.
    // double deletion will be happen.
    // which is undefined behaviour(UB)

    // ------------------------------------------------
  }
*/

/*
  #include <memory>   // std::make_unique, std::unique_ptr
  #include "myclass.hpp"

  int main()
  {
    auto up1 = std::make_unique<Myclass>("world");

    std::cout << "up1 = " << (up1 ? "full" : "empty") << "\n";
    // output -> up1 = full

    auto p_mx = up1.get();

    std::unique_ptr<Myclass> up2{ p_mx };   
    // undefined behaviour(UB)

    // both "up1" and "up2" unique_ptr objects are holding
    // the same pointer that "p_mx" is pointing to.
    // at the end of the scope, both unique_ptr objects
    // will try to delete the same object.
    // double deletion will be happen.
    // which is undefined behaviour(UB)
  }
*/

/*
  #include <memory>
  #include "myclass.hpp"

  int main()
  {
    auto up = std::make_unique<Myclass>("world");

    // -----------------------------------------------

    std::cout << "Myclass object's address = " 
              << up.get() << '\n';
    // output -> Myclass object's address = 0x29425884cf0
              
    std::cout << "Myclass object's address = " 
              << up << '\n';
    // output -> Myclass object's address = 0x29425884cf0

    // Those 2 lines are equivalent.

    // -----------------------------------------------

    std::cout << "std::unique_ptr<Myclass> object's address = " 
              <<  &up << '\n';
    // output -> 
    //  std::unique_ptr<Myclass> object's address = 0xba2d7ffa98

    // -----------------------------------------------
  }
*/

/*
  #include <memory>
  #include "myclass.hpp"

  int main()
  {
    {
      auto up1 = std::make_unique<Myclass>("world");
      auto up2 = std::move(up1);

      std::cout << "up1 = " << (up1 ? "full" : "empty") << '\n';
      // output -> up1 = empty
      std::cout << "up2 = " << (up2 ? "full" : "empty") << '\n';
      // output -> up2 = full
    }
  }
*/

/*
  #include <memory>
  #include <string>

  int main()
  {
    using namespace std;

    std::unique_ptr<std::string> up_str;

    auto def_deleter = up_str.get_deleter();
    // "def_deleter"'s type is std::default_delete<std::string>
  }
*/

/*
  #include <memory>
  #include <string>

  struct Str_Deleter {
  public:
    void operator()(std::string* p_str)
    {
      std::cout << "object in address = " << p_str 
                << " has been deleted.\n";
      delete p_str;
    }
  };

  int main()
  {
    std::cout << "[0] - main started\n";

    {
      std::unique_ptr<std::string, Str_Deleter> up_str{ 
        new std::string {"hello"} };
      // output ->
      //  object in address = 0x21634980fc0 has been deleted.
    }

    std::cout << "[1] - main ended\n";
  }
*/

/*
  #include <memory>
  #include <string>

  void fn_deleter(std::string* p_str)
  {
    std::cout << "fn_deleter has been called.\n";
    std::cout << "object in address = " << p_str 
              << " has been deleted.\n";
    delete p_str;
  }

  int main()
  {
    std::cout << "[0] - main started\n";

    {
      std::unique_ptr<std::string, decltype(&fn_deleter)> up_str1{ 
        new std::string{"world"}, &fn_deleter };
      // output ->
      //  fn_deleter has been called.
      //  object in address = 0x20528242f20 has been deleted.
      
      std::unique_ptr<std::string, void(*)(std::string*)> up_str2{ 
        new std::string{"galaxy"}, &fn_deleter };
      // output ->
      //  fn_deleter has been called.
      //  object in address = 0x20528242ef0 has been deleted.
    }

    std::cout << "[1] - main ended\n";
  }
*/

/*
  #include <memory>
  #include <string>

  int main()
  {
    std::cout << "[0] - main started\n";

    auto fn_deleter = [](std::string* p_str) {
      std::cout << "fn_deleter function has been called\n";
      std::cout << "object in address = " << p_str 
                << " has been deleted.\n";
      delete p_str;
    };

    {
      // ------------------------------------------------

      std::unique_ptr<std::string, decltype(fn_deleter)> up_str1{ 
        new std::string{"world"}, fn_deleter };
      // output ->
      //  fn_deleter function has been called
      //  object in address = 0x1aae9e13b70 has been deleted.
      
      // before C++20 because of stateless lambda object 
      // does not have default ctor, we need to pass the
      // lambda object as a parameter to the unique_ptr ctor.

      // ------------------------------------------------

      std::unique_ptr<std::string, decltype(fn_deleter)> up_str2{ 
        new std::string {"galaxy"} };
      // output ->
      //  fn_deleter function has been called
      //  object in address = 0x1aae9e13c30 has been deleted.

      // since C++20 stateless lambda object have default ctor.
      // before C++20 syntax error will be occured.

      // ------------------------------------------------
    }

    std::cout << "[1] - main ended\n";
  }
*/

/*
  Since C++20 STATELESS lambda expressions,
    - does have default constructor
    - does have copy assignment operator function
    - can be used in unevaluated context
*/

/*
  #include <memory>
  #include <string>

  int main()
  {
    std::cout << "[0] - main started\n";

    {
      std::unique_ptr<std::string, 
                      decltype([](std::string* p_str) {
          std::cout << "stateless lambda expression used "
                        "in unevaluated context\n";
          delete p_str;
        }) > up_str{ new std::string{ "world" } };      
    }
    std::cout << "[1] - main ended\n";
  }
  // output ->
  //  [0] - main started
  //  stateless lambda expression used in unevaluated context
  //  [1] - main ended
*/

/*
  #include <cstdio>   // std::fopen, std::fprintf, std::fclose
  #include <string>

  int main()
  {
    // ----------------------------------------------

    // C style file handling
    {
      FILE* fp = std::fopen("out.txt", "w");

      std::fprintf(fp, "world\n");
      std::fprintf(fp, "galaxy\n");

      std::fclose(fp);
    }
    // - closing file can be forgotten.
    // - exception can be thrown before closing the file.

    // ----------------------------------------------

    using f_closer_t = decltype([](FILE* f){ std::fclose(f); });

    {
      std::unique_ptr<FILE, f_closer_t> up_file{ 
        std::fopen("out.txt", "a") 
      };

      std::fprintf(up_file.get(), "universe\n");
    }

    // ----------------------------------------------
  }
  // out.txt ->
  //  world
  //  galaxy
  //  universe
*/

/*
  #include <memory>   // std::unique_ptr
  #include <string>

  // primary template
  template <typename T>
  class Myclass {
  public:
    Myclass()
    {
      std::cout << "primary template\n";
    }
  };

  // partial specialization for C-style arrays
  template <typename T>
  class Myclass<T[]> {
  public:
    Myclass()
    {
      std::cout << "array partial specialization\n";
    }
  };

  // primary template
  template <typename T>
  struct Default_Delete {
    void operator()(T* p)
    {
      delete p;
    }
  };

  // partial specialization for C-style arrays
  template <typename T>
  struct Default_Delete<T[]> {
    void operator()(T* p)
    {
      delete[] p;   // array delete
    }
  };

  int main()
  {
    // ------------------------------------------------

    Myclass<int> m1;    
    // output -> primary template
    Myclass<int[]> m2;  
    // output -> array partial specialization

    // ------------------------------------------------

    auto fn_delete = [](std::string* p_str){ delete[] p_str; };

    std::unique_ptr<std::string, decltype(fn_delete)> up_str{ 
      new std::string[100] };
    // VALID but not a good solution.
  
    // ------------------------------------------------

    // std::unique_ptr has a partial specialization C-style arrays.
    // 2nd template parameter default_delete also have a 
    // C-style array partial specialization.

    std::unique_ptr<std::string[]> up_str2{ new std::string[100] };
    // VALID and a good solution.

    // ------------------------------------------------

    // "operator*" and "operator->" member functions 
    // are not available in 
    // C-style array partial specialization's interface.

    // "operator[]" member function is available in 
    // C-style array partial specialization's inteface.

    for (int i{}; i < 100; ++i)
      up_str2[i];

    // ------------------------------------------------
  }
*/

/*
  #include <vector>     
  #include <memory>       // std::unique_ptr
  #include <string>
  #include <algorithm>    // std::sort

  int main()
  {
    std::vector<std::unique_ptr<std::string>> up_str_vec;

    up_str_vec.emplace_back(new std::string{"cccc"});
    up_str_vec.emplace_back(new std::string{"bbbb"});
    up_str_vec.emplace_back(new std::string{"aaaa"});
    up_str_vec.emplace_back(new std::string{"dddd"});

    // ---------------------------------------------------

    std::sort(up_str_vec.begin(), up_str_vec.end());
    // sorting by pointer addresses 
    // not the strings inside pointers.

    for (const auto& up_str : up_str_vec)
      std::cout << *up_str << " - " << up_str << '\n';
    // output ->
    //  bbbb - 0x1d13a8957b0
    //  dddd - 0x1d13a8958d0
    //  aaaa - 0x1d13a895930
    //  cccc - 0x1d13a895a20

    std::cout << '\n';

    // ---------------------------------------------------

    std::sort(up_str_vec.begin(), up_str_vec.end(), 
              [](const auto& p_str1, const auto& p_str2){
                return *p_str1 < *p_str2;
              });

    for (const auto& up_str : up_str_vec)
      std::cout << *up_str << " - " << up_str << '\n';
    // output ->
    //  aaaa - 0x1d13a895930
    //  bbbb - 0x1d13a8957b0
    //  cccc - 0x1d13a895a20
    //  dddd - 0x1d13a8958d0

    // ---------------------------------------------------
  }
*/

/*
  #include <memory>   // std::unique_ptr
  #include <string>

  class Myclass {
    Myclass(std::string str, int num);
  };

  std::unique_ptr<Myclass> make_Myclass(std::string str, int num)
  {
    return std::make_unique<Myclass>(str, num);
    // mandatory copy ellision
  }

  int main()
  {
    auto up_mx = make_Myclass("world", 22);
    // make_Myclass is a factory function
  }
*/

/*
  #include <memory>   // std::unique_ptr, std::make_unique
  #include <string>

  using namespace std;

  // ---------------------------------------------------

  void sink(unique_ptr<string> up_str){}

  // sink functions, takes an argument use it and
  // its life will be end after using it.

  // ---------------------------------------------------

  unique_ptr<string> pass_through(unique_ptr<string> up_str)
  {
    std::cout << "length = " << up_str->length() << ", ";
    std::cout << "string = " << *up_str << '\n';

    return up_str;
  }
  // pass through functions, takes an argument, 
  // do some operations on it and returns that argument.

  // ---------------------------------------------------

  int main()
  {
    auto up_str = pass_through(make_unique<string>("world"));
    // output -> length = 5, string = world
  }
*/

/*
  #include <memory>     // std::make_unique
  #include <exception>  // std::exception
  #include <stdexcept>  // std::runtime_error

  struct Date {
    int m_d, m_m, m_y;

    Date(int d, int m, int y) : m_d(d), m_m(m), m_y(y)
    {
      std::cout << "object in address = " << this 
                << " has been created.\n";
    }
    ~Date()
    {
      std::cout << "object in address = " << this 
                << " has been deleted.\n";
    }
  };

  void bar()
  {
    throw std::runtime_error{ "exception thrown in bar" };
  }

  void func_1(int d, int m, int y)
  {
    Date* p_date = new Date(d, m, y);

    bar();
    // if any exception thrown in "bar" function,
    // dynamically allocate Date object's destructor 
    // can not be called, because of delete statement
    // will not be executed.

    delete p_date;
  }

  void func_2(int d, int m, int y)
  {
    auto up_date = std::make_unique<Date>(d, m, y);
    // if an exception will be thrown, 
    // unique_ptr's destructor will be called
    // in stack unwinding phase.
    // if no exception thrown, unique_ptr's destructor
    // will be called at the end of the scope.

    bar();
  }

  int main()
  {
    // ------------------------------------------------

    {
      try {
        func_1(1, 1, 2001);
      }
      catch (const std::exception& ex){
        std::cout << "exception caught: " << ex.what() << '\n';
      }
    }
    // output ->
    //  object in address = 0x1668ab74840 has been created.
    //  exception caught: exception thrown in bar

    // ------------------------------------------------

    {
      try {
        func_2(1, 1, 2001);
      }
      catch (const std::exception& ex){
        std::cout << "exception caught: " << ex.what() << '\n';
      }
    }
    // output ->
    //  object in address = 0x1668ab748a0 has been created.
    //  object in address = 0x1668ab748a0 has been deleted.
    //  exception caught: exception thrown in bar

    // ------------------------------------------------
  }
*/

/*
  #include <memory>   // std::unique_ptr
  #include <string>
  #include <utility>  // std::move

  class Person {
  public:
    std::unique_ptr<std::string> mup_name{};
  };
  // Person class becomes a move only class because 
  // it has a std::unique_ptr data member.
  // so compiler generated copy ctor and copy assignment
  // will be implicitly deleted.

  int main()
  {
    // ------------------------------------------------

    Person per1;
    auto per2 = per1;   // syntax error (copy constructor)
    // error: use of deleted function 
    // 'Person::Person(const Person&)'

    // error: use of deleted function 
    // 'std::unique_ptr(const std::unique_ptr&)

    // ------------------------------------------------


    Person per3;
    per1 = per3;    // syntax error (copy assignment)

    // error: use of deleted function 
    // 'Person& Person::operator=(const Person&)'

    //  error: use of deleted function 
    // 'unique_ptr& unique_ptr::operator=(const std::unique_ptr&)

    // ------------------------------------------------

    per1 = std::move(per3);         // VALID (move assignment)
    auto per4 = std::move(per1);    // VALID (move constructor)

    // ------------------------------------------------
  }
*/

/*
                        -------------------
                        | std::shared_ptr |
                        -------------------
*/

/*
  ----------------------------------------------------

  - reference counting technique has been used in
    std::shared_ptr class template

  ----------------------------------------------------

  - std::shared_ptr have 2 pointer data members,
    -> a pointer to dynamic storage duration object
    -> Pointer to control a block
      - reference rount, 
      - weak count, 
      - custom deleter, allocator.. (other data)

  <---- check shared_ptr.png ---->  

  ----------------------------------------------------

  - control block is being created when a std::shared_ptr
    object is created.
  - if std::shared_ptr object is copied, control block
    WILL NOT be created again.

  - std::shared_ptr have an overhead compared to std::unique_ptr
    because of the control block.
    It is expensive to create the control block.

  ----------------------------------------------------

  - only when "std::make_shared" factory function is called 
    to create a std::shared_ptr object, 
    control block and dynamic storage duration object 
    will be allocated contiguously(one block of memory).

  ----------------------------------------------------

  - deleter is a template parameter in std::unique_ptr 
    but not in std::shared_ptr.
  - std::shared_ptr's constructor will get deleter as an argument.

  ----------------------------------------------------
*/

/*
  #include <memory>   // std::unique_ptr, std::shared_ptr
  #include <string>

  int main()
  {
    // ------------------------------------------------

    using up_str = std::unique_ptr<std::string>;

    std::cout << "sizeof(up_str) = " 
              << sizeof(up_str) << '\n';
    // sizeof(up_str) = 8

    // ------------------------------------------------

    using sp_str = std::shared_ptr<std::string>;

    std::cout << "sizeof(sp_str) = " 
    << sizeof(sp_str) << '\n';
    // sizeof(sp_str) = 16

    // ------------------------------------------------
  }
*/

/*
  #include <memory>   // std::shared_ptr
  #include <string>

  int main()
  {
    std::shared_ptr<std::string> sp1{ new std::string{ "world"} };

    auto sp2 = sp1;   // copy constructor
    auto sp3 = sp1;   // copy constructor
    auto sp4 = sp1;   // copy constructor

    *sp1 += " galaxy";
    std::cout << *sp2 << '\n';    
    // output -> world galaxy

    *sp3 += " universe";
    std::cout << *sp4 << '\n';   
    // output -> world galaxy universe
  }
*/

/*
  #include <memory>   // std::shared_ptr
  #include <string>

  int main()
  {
    // ------------------------------------------------

    std::shared_ptr<std::string> sp1{ new std::string{"world"} };

    std::cout << "sp1.use_count() = " << sp1.use_count() << '\n';
    // output -> sp1.use_count() = 1

    // ------------------------------------------------

    auto sp2 = sp1;   // copy constructor

    std::cout << "sp1.use_count() = " << sp1.use_count() << '\n';
    // output -> sp1.use_count() = 2

    // ------------------------------------------------

    {
      auto sp3 = sp1;   // copy constructor

      std::cout << "sp1.use_count() = " << sp1.use_count() << '\n';
      // output -> sp1.use_count() = 3
    }

    std::cout << "sp1.use_count() = " << sp1.use_count() << '\n';
    // output -> sp1.use_count() = 2    

    // ------------------------------------------------

    auto sp4 = sp1;
    std::cout << "sp1.use_count() = " << sp1.use_count() << '\n';
    // output -> sp1.use_count() = 3

    // ------------------------------------------------
  }
*/

/*
  // "reset" member function of std::shared_ptr

  #include <memory>   // std::shared_ptr
  #include <string>

  int main()
  {
    // -------------------------------------------------

    std::shared_ptr<std::string> sp1{ new std::string{"world"} };

    std::cout << "sp1.use_count() = " << sp1.use_count() << '\n';
    //  output -> sp1.use_count() = 1

    // -------------------------------------------------

    auto sp2 = sp1;   // copy constructor

    std::cout << "sp1.use_count() = " << sp1.use_count() << '\n';
    std::cout << "sp2.use_count() = " << sp2.use_count() << '\n';
    // output ->
    //  sp1.use_count() = 2
    //  sp2.use_count() = 2

    // -------------------------------------------------

    sp1.reset();

    std::cout << "sp1.use_count() = " << sp1.use_count() << '\n';
    std::cout << "sp2.use_count() = " << sp2.use_count() << '\n';
    // output ->
    //  sp1.use_count() = 0
    //  sp2.use_count() = 1

    // sp2 becomes the sole owner of the 
    // dynamic storage duration object.

    std::cout << *sp2 << '\n';  // output -> world

    // -------------------------------------------------
  }
*/

/*
  // "operator bool" member function of std::shared_ptr

  #include <memory>
  #include <string>

  int main()
  {
    // -------------------------------------------

    std::shared_ptr<std::string> sp1;

    std::cout << "sp1 = " 
              << (sp1 ? "full" : "empty") << '\n';
    // output -> sp1 = empty

    // -------------------------------------------

    std::shared_ptr<std::string> sp2(new std::string{ "world" });

    std::cout << "sp2 = " 
              << (sp2 ? "full" : "empty") << '\n';
    // output -> sp2 = full

    // -------------------------------------------
  }
*/

/*
  - "unique" member function of std::shared_ptr 
    is no longer exists until C++20.

  - "use_count" returns 1, 
    "unique" returns true 
  (same behaviour)
*/

/*
  #include <memory>   // std::shared_ptr
  #include <string>

  int main()
  {
    std::cout << "[0] - main started\n";
    {
      std::shared_ptr<std::string> sp1( new std::string{ "world" }, 
                                        [](std::string* p_str){
                        std::cout << "custom deleter\n"; 
                        delete p_str;
                      });
    }
    std::cout << "[1] - main ended\n";

    // passing lambda expression as a custom deleter
    // to std::shared_ptr's constructor
  }
  // output ->
  //  [0] - main started
  //  custom deleter
  //  [1] - main ended
*/

/*
  #include <memory>   // std::make_shared
  #include <string>

  struct Date {
    Date(int d, int m, int y) : m_day(d), m_mon(m), m_year(y) {}
    int m_day, m_mon, m_year;
  };

  int main()
  {
    // ------------------------------------------------

    auto sp_str = std::make_shared<std::string>(10, 'A');
    std::cout << *sp_str << '\n';
    // output -> AAAAAAAAAA

    // ------------------------------------------------

    auto sp_date = std::make_shared<Date>(1, 1, 2001);

    std::cout << "day = " << sp_date->m_day << '\n';
    // output -> day = 1
    std::cout << "month = " << sp_date->m_mon << '\n';
    // output -> month = 1
    std::cout << "year = " << sp_date->m_year << '\n';
    // output -> year = 2001

    // ------------------------------------------------
  }
*/

/*
  #include <cstddef>      // std::size_t
  #include <cstdlib>      // std::malloc
  #include <new>          // std::bad_alloc
  #include <memory>       // std::shared_ptr, std::make_shared

  void* operator new(std::size_t size)
  {
    std::cout << "operator new called, size = " << size << '\n';

    void* vp = std::malloc(size);

    if (!vp)
      throw std::bad_alloc{};

    return vp;
  }

  struct Date {
    int m_day, m_mon, m_year;
    Date(int d, int m, int y) : m_day(d), m_mon(m), m_year(y) 
    {}
  };

  int main()
  {
    // ---------------------------------------------

    std::cout << "sizeof(Date) = " << sizeof(Date) << '\n';
    // output -> sizeof(Date) = 12

    // ---------------------------------------------

    std::shared_ptr<Date> sp_date1{ new Date{ 1, 1, 2001 } };
    // output ->
    //  operator new called, size = 12
    //  - allocation for Date object
    //  operator new called, size = 24
    //  - allocation for control block

    std::cout << '\n';

    // ---------------------------------------------

    auto sp_date2 = std::make_shared<Date>(1, 1, 1991);
    // output -> operator new called, size = 32
    //  - allocation for Date object + control block

    // ---------------------------------------------
  }
*/

/*
  #include <memory>   // std::shared_ptr, std::make_shared

  struct Date {
    int m_day, m_mon, m_year;
    Date() = default;
    Date(int d, int m, int y) : m_day(d), m_mon(m), m_year(y) 
    {}
  };

  int main()
  {
    std::shared_ptr<Date[]> sp_date_arr1(new Date[10]);
    auto sp_date_arr2 = std::make_shared<Date[]>(10);

    // ---------------------------------------------

    sp_date_arr1.operator[](1) = Date(1, 1, 2001);
    // "operator[]" member function for 
    // C-style array specialization of std::shared_ptr

    sp_date_arr2.operator[](2) = Date(2, 2, 2002);

    // ---------------------------------------------

    *sp_date_arr1;    // syntax error
    // error: no match for 'operator*' 
    // (operand type is 'std::shared_ptr<Date []>')

    // ---------------------------------------------
  }
*/

/*
  #include <memory>   // std::shared_ptr
  #include <string>

  int main()
  {
    using namespace std;

    shared_ptr<string> sp_str1( new string{ "world" }, 
                                [](string* p_str){
            cout << *p_str << " will be deleted\n"; 
            delete p_str;
          });

    shared_ptr<string> sp_str2(new string{ "galaxy" });

    // --------------------------------------------------

    cout  << "sp_str1.use_count() = " 
          << sp_str1.use_count() << '\n';
    cout  << "sp_str2.use_count() = " 
          << sp_str2.use_count() << '\n';
    // output -> 
    //  sp_str1.use_count() = 1
    //  sp_str2.use_count() = 1

    cout << *sp_str1 << '\n';
    // output -> world
    cout << *sp_str2 << '\n';
    // output -> galaxy

    // --------------------------------------------------

    sp_str1 = sp_str2;  
    // output -> world will be deleted

    cout  << "sp_str1.use_count() = " 
          << sp_str1.use_count() << '\n';
    cout  << "sp_str2.use_count() = " 
          << sp_str2.use_count() << '\n';
    // output ->
    //  sp_str1.use_count() = 2
    //  sp_str2.use_count() = 2

    cout << *sp_str1 << '\n';
    // output -> galaxy
    cout << *sp_str2 << '\n';
    // output -> galaxy

    // --------------------------------------------------
  }
*/

/*
  #include <memory>   // std::shared_ptr
  #include <string>
  #include <utility>  // std::move

  int main()
  {
    using namespace std;

    shared_ptr<string> sp_str1( new string{ "world" }, 
                                [](string* p_str){
            cout << *p_str << " will be deleted\n"; 
            delete p_str;
          });

    shared_ptr<string> sp_str2(new string{ "galaxy" });

    // --------------------------------------------------

    cout  << "sp_str1.use_count() = " 
          << sp_str1.use_count() << '\n';
    cout  << "sp_str2.use_count() = " 
          << sp_str2.use_count() << '\n';
    // output -> 
    //  sp_str1.use_count() = 1
    //  sp_str2.use_count() = 1

    cout << *sp_str1 << '\n';
    // output -> world
    cout << *sp_str2 << '\n';
    // output -> galaxy

    // --------------------------------------------------

    sp_str1 = std::move(sp_str2);  
    // output -> world will be deleted

    cout  << "sp_str1.use_count() = " 
          << sp_str1.use_count() << '\n';
    cout  << "sp_str2.use_count() = " 
          << sp_str2.use_count() << '\n';
    // output ->
    //  sp_str1.use_count() = 1
    //  sp_str2.use_count() = 0

    cout << *sp_str1 << '\n';
    // output -> galaxy

    // --------------------------------------------------
  }
*/

/*
  #include <vector>
  #include <memory>   // std::shared_ptr
  #include <list>
  #include "../headers/nutility.h"

  int main()
  {
    // ---------------------------------------------

    std::vector<std::shared_ptr<std::string>> sp_str_vec;

    for (int i = 0; i < 5; ++i)
      sp_str_vec.emplace_back(new std::string(rtown()));

    std::cout << "sp_str_vec.size() = " 
              << sp_str_vec.size() << '\n';

    // ---------------------------------------------

    for (const auto& sp_str : sp_str_vec)
      std::cout << *sp_str << '\n';
    // output ->
    //  bilecik
    //  usak
    //  ordu
    //  trabzon
    //  artvin

    // ---------------------------------------------

    std::list<std::shared_ptr<std::string>> sp_str_list(
      sp_str_vec.begin(), sp_str_vec.end());
      
    for (auto& sp_str : sp_str_list)
      *sp_str += " - world";

    for (const auto& sp_str : sp_str_vec)
      std::cout << *sp_str << '\n';
    
    // output ->
    //  bilecik - world
    //  usak - world
    //  ordu - world
    //  trabzon - world
    //  artvin - world

    // ---------------------------------------------

    // both std::shared_ptr objects in std::vector and std::list 
    // containers are pointing to the same std::string objects.

    // ---------------------------------------------
  }
*/

/*
  #include <memory>   // std::make_shared
  #include <string>

  int main()
  {
    auto sp_str = std::make_shared<std::string>("world");

    std::cout << "address of string = " << sp_str << '\n';
    // output -> address of string = 0x1b99d4b7840
    std::cout << "address of string = " << sp_str.get() << '\n';
    // output -> address of string = 0x1b99d4b7840

    // Those 2 lines are equivalent.
  }
*/

/*
  #include <memory>   // std::make_shared
  #include <string>

  int main()
  {
    auto sp_str = std::make_shared<std::string>("world");

    sp_str = nullptr;
    sp_str = {};
    sp_str.reset();
    // Those 3 lines are equivalent.

    // They both are making the std::shared_ptr object empty.
  }
*/

/*
  #include <memory>       // std::shared_ptr
  #include <list>
  #include <string>
  #include <vector>
  #include <algorithm>    // std::sort

  class City {
  private:
    std::string m_city_name;

  public:
    City(std::string str) : m_city_name(str) 
    {}

    friend std::ostream& operator<<(std::ostream& os, 
                                    const City& city)
    {
      return os << city.m_city_name << ' ';
    }
    auto operator<=>(const City& city)const = default;
  };

  int main()
  {

    using sp_city = std::shared_ptr<City>;

    std::list<sp_city> sp_city_list;

    sp_city_list.emplace_back(new City{ "istanbul" });
    sp_city_list.emplace_back(new City{ "ankara" });
    sp_city_list.emplace_back(new City{ "izmir" });
    sp_city_list.emplace_back(new City{ "eskisehir" });
    sp_city_list.emplace_back(new City{ "rize" });

    for (auto& sp_city : sp_city_list)
      std::cout << *sp_city;
    // output -> istanbul ankara izmir eskisehir rize

    std::cout << '\n';

    // ------------------------------------------------

    std::vector<sp_city> sp_city_vec( sp_city_list.begin(), 
                                      sp_city_list.end());

    std::sort(sp_city_vec.begin(), sp_city_vec.end(), 
              [](const auto& sp_city1, const auto& sp_city2){
                  return *sp_city1 < *sp_city2;
            });

    for (auto& sp_city : sp_city_vec)
      std::cout << *sp_city;
    // output -> ankara eskisehir istanbul izmir rize

    // ------------------------------------------------
  }
*/

/*
  #include <memory>
  // std::enable_shared_from_this, std:make_shared

  class Myclass : public std::enable_shared_from_this<Myclass> {	
  public:
    Myclass()
    {
      std::cout << "Myclass(), this = " << this << '\n';
    }

    void func()
    {
      std::cout << "Myclass::func(), this =  " << this << '\n';
      auto sp = shared_from_this();
      std::cout << "sp.use_count() = " << sp.use_count() << '\n';
    }

    // being sure that "func" member function is called 
    // with std::shared_ptr object.

    ~Myclass()
    {
      std::cout << "~Myclass(), this = " << this << '\n';
    }
  };

  int main()
  {
    // -------------------------------------------------

    auto sp_mx = std::make_shared<Myclass>();
    // output -> Myclass(), this = 0x19f0e325780

    sp_mx->func();
    // output -> 
    //  Myclass::func(), this =  0x19f0e325780
    //  sp.use_count() = 2

    // -------------------------------------------------

    Myclass* p_mx = new Myclass;
    // output -> Myclass(), this = 0x19f0e322e70

    try
    {
      p_mx->func();
    }
    catch (const std::exception& ex)
    {
      std::cout << "exception caught: " << ex.what() << '\n';
    }
    // output ->
    //  Myclass::func(), this =  0x19f0e322e70
    //  exception caught: bad_weak_ptr

    // when "func" member function is called with raw pointer,
    // std::bad_weak_ptr exception will be thrown.
    // destructor of the Myclass object that "p_mx" points to
    // will not be called.

    // -------------------------------------------------
  }
*/

/*
                          -----------------
                          | std::weak_ptr |
                          -----------------
*/

/*
  #include <memory>   // std::make_shared, std::weak_ptr

  struct Date {
    int m_day, m_mon, m_year;
    Date() = default;
    Date(int d, int m, int y) : m_day(d), m_mon(m), m_year(y) 
    {}
  };

  int main()
  {
    // -------------------------------------------------

    auto sp = std::make_shared<Date>(1, 1, 2001);

    std::cout << "sp.use_count() = " << sp.use_count() << '\n';
    // output -> sp.use_count() = 1

    // -------------------------------------------------

    std::weak_ptr<Date> wp1(sp);
    std::weak_ptr<Date> wp2(sp);

    std::cout << "sp.use_count() = " << sp.use_count() << '\n';
    // output -> sp.use_count() = 1
    std::cout << "wp1.use_count() = " << wp1.use_count() << '\n';
    // output -> wp1.use_count() = 1
    std::cout << "wp2.use_count() = " << wp2.use_count() << '\n';
    // output -> wp2.use_count() = 1

    // -------------------------------------------------

    *sp;    // VALID

    // reaching the object that std::shared_ptr points to
    // with dereferencing operator is valid.

    *wp1;   // syntax error
    // error: no match for 'operator*' 
    // (operand type is 'std::weak_ptr<Date>')

    // reaching the object that std::weak_ptr points to
    // with dereferencing operator is syntax error.

    // -------------------------------------------------
  }
*/

/*
  // "reset" member function of std::weak_ptr

  #include <memory>   // std::make_shared, std::weak_ptr

  struct Date {
    int m_day, m_mon, m_year;
    Date() = default;
    Date(int d, int m, int y) : m_day(d), m_mon(m), m_year(y) 
    {}
  };

  int main()
  {
    // -------------------------------------------------

    auto sp = std::make_shared<Date>(1, 1, 2001);
    std::weak_ptr<Date> wp(sp);

    if (wp.expired())
      std::cout << "object does not exist\n";
    else
      std::cout << "object exists\n";
    // output -> object exists

    // -------------------------------------------------

    wp.reset();

    if (wp.expired())
      std::cout << "object does not exist\n";
    else
      std::cout << "object exists\n";
    // output -> object does not exist

    // -------------------------------------------------
  }
*/

/*
  #include <memory>   // std::make_shared, std::weak_ptr
  #include "../headers/date.h"

  int main()
  {
    auto sp = std::make_shared<Date>(1, 1, 2001);
    std::weak_ptr<Date> wp(sp);

    std::cout << "sp.use_count() = " << sp.use_count() << '\n';
    // sp.use_count() = 1

    // ------------------------------------------------

    // "lock" member function of std::weak_ptr checks 
    // checks if there is an object managed by std::weak_ptr
    //  - if yes, returns a new std::shared_ptr to the same object.
    //  - else, returns nullptr.

    if (auto sp_x = wp.lock()) 
    {
      std::cout << "an object is managed by 'wp'\n";
      std::cout << "sp.use_count() = " << sp.use_count() << '\n';
      std::cout << "sp_x = " << *sp_x << "\n";
      std::cout << "sp   = " << *sp << "\n";
    }
    else
      std::cout << "'wp' does not manage an object\n";

    // output ->
    //  an object is managed by 'wp'
    //  sp.use_count() = 2
    //  sp_x = 01 Ocak 2001 Pazartesi
    //  sp   = 01 Ocak 2001 Pazartesi

    std::cout << "sp.use_count() = " << sp.use_count() << '\n';
    // output -> sp.use_count() = 1

    // ------------------------------------------------

    wp.reset();
    // https://en.cppreference.com/w/cpp/memory/weak_ptr/reset

    if (auto sp_x = wp.lock())
      std::cout << "an object is managed by 'wp'\n";
    else
      std::cout << "'wp' does not manage an object\n";
    // output -> 'wp' does not manage an object

    std::cout << "sp.use_count() = " << sp.use_count() << '\n';
    // output -> sp.use_count() = 1

    // ------------------------------------------------
  }
*/

/*
  #include <memory>       
  // std::make_shared, std::shared_ptr, std::weak_ptr
  #include <exception>    // std::exception
  #include <string>

  int main()
  {
    auto sp = std::make_shared<std::string>("world");
    std::weak_ptr<std::string> wp(sp);

    // -------------------------------------------------

    sp.reset();
    // reseting the std::shared_ptr resource 
    // that used for constructing std::weak_ptr object with

    try {
      std::shared_ptr<std::string> sp2(wp);
    }
    catch (const std::exception& ex) 
    {
      std::cout << "exception caught: " << ex.what() << '\n';
    }
    // output -> exception caught: bad_weak_ptr

    // -------------------------------------------------

    if (!wp.expired())
      std::shared_ptr<std::string> sp2(wp);
    
    // it is not possible to throw exception in this scenario.
    // checking if the std::weak_ptr object is "expired" or not.

    // -------------------------------------------------
  }
*/

/*
  #include <memory>   // std::shared_ptr, std::weak_ptr

  struct BStruct;   // forward declaration

  struct AStruct {
    std::shared_ptr<BStruct> msp_BStruct;
    ~AStruct() 
    {
      std::cout << "~AStruct()\n";
    }
  };

  struct BStruct {
    std::shared_ptr<AStruct> msp_AStruct;
    ~BStruct() 
    {
      std::cout << "~BStruct()\n";
    }
  };

  int main()
  {
    std::cout << "[0] - main started\n";
    {
      std::shared_ptr<AStruct> sp_a{ new AStruct };
      std::shared_ptr<BStruct> sp_b{ new BStruct };

      // --------------------------------------------------------

      std::cout << "sp_a.use_count() = " 
                << sp_a.use_count() << '\n';
      // output -> sp_a.use_count() = 1

      std::cout << "sp_b.use_count() = " 
                << sp_b.use_count() << '\n';
      // output -> sp_b.use_count() = 1

      // --------------------------------------------------------

      sp_a->msp_BStruct = sp_b;

      std::cout << "sp_a.use_count() = " 
                << sp_a.use_count() << '\n';
      // output -> sp_a.use_count() = 1

      std::cout << "sp_b.use_count() = " 
                << sp_b.use_count() << '\n';
      // output -> sp_b.use_count() = 2

      // --------------------------------------------------------
    }
    // output ->
    //  ~AStruct()
    //  ~BStruct()

    std::cout << "[1] - main ended\n";
  }
*/

/*
  // in this scenario destuctors of AStruct and BStruct
  // will not be called because of the circular reference.

  #include <memory>   // std::shared_ptr

  struct BStruct;   // forward declaration

  struct AStruct {
    std::shared_ptr<BStruct> msp_BStruct;
    ~AStruct() 
    {
      std::cout << "~AStruct()\n";
    }
  };

  struct BStruct {
    std::shared_ptr<AStruct> msp_AStruct;
    ~BStruct() 
    {
      std::cout << "~BStruct()\n";
    }
  };

  int main()
  {
    std::cout << "[0] - main started\n";

    {
      std::shared_ptr<AStruct> sp_a{ new AStruct };
      std::shared_ptr<BStruct> sp_b{ new BStruct };

      sp_a->msp_BStruct = sp_b;
      sp_b->msp_AStruct = sp_a;

      std::cout << "sp_a.use_count() = " 
                << sp_a.use_count() << '\n';
      // output -> sp_a.use_count() = 2

      std::cout << "sp_b.use_count() = "
                << sp_b.use_count() << '\n';
      // output -> sp_b.use_count() = 2
    }

    std::cout << "[1] - main ended\n";
  }
*/

/*
  // using std::weak_ptr to break the circular reference
  // <---- check circular_ref_weak_ptr.png ---->

  #include <memory>   // std::shared_ptr, std::weak_ptr

  struct BStruct;   // forward declaration

  struct AStruct {
    std::weak_ptr<BStruct> mwp_BStruct;
    ~AStruct() 
    {
      std::cout << "~AStruct()\n";
    }
  };

  struct BStruct {
    std::shared_ptr<AStruct> msp_AStruct;
    ~BStruct() 
    {
      std::cout << "~BStruct()\n";
    }
  };

  int main()
  {
    std::cout << "[0] - main started\n";

    {
      std::shared_ptr<AStruct> sp_a{ new AStruct };
      std::shared_ptr<BStruct> sp_b{ new BStruct };

      sp_a->mwp_BStruct = sp_b;
      sp_b->msp_AStruct = sp_a;

      std::cout << "sp_a.use_count() = " 
                << sp_a.use_count() << '\n';
      // output -> sp_a.use_count() = 2

      std::cout << "sp_b.use_count() = "
                << sp_b.use_count() << '\n';
      // output -> sp_b.use_count() = 1
    }
    // output ->
    //  ~BStruct()
    //  ~AStruct()

    std::cout << "[1] - main ended\n";
  }
*/

/*
  #include <memory>   
  // std::weak_ptr, std::make_shared, std::shared_ptr
  #include <string>
  #include <utility>  // std::move

  class Dog {
  private:
    std::weak_ptr<Dog> mwp_friend;
    std::string m_name;

  public:
    Dog(std::string name) : m_name(std::move(name))
    {
      std::cout << m_name << " born.\n";
    }
    ~Dog()
    {
      std::cout << m_name << " dead.\n";
    }

    void bark()
    {
      std::cout << m_name << " barked.\n";
    }

    void make_friend(std::shared_ptr<Dog> other)
    {
      mwp_friend = other;

      std::cout << m_name << " - "  
                << other->m_name << " are friends.\n";
    }

    bool has_friend() const
    {
      return !mwp_friend.expired();
    }

    void print() const
    {
      std::cout << "dog name = " << m_name;

      if (!mwp_friend.expired())
      {
        std::cout << " has a friend called " 
                  << mwp_friend.lock()->m_name << '\n';
      }
      else
        std::cout << " does not have a friend.\n";
    }
  };

  int main()
  {
    using namespace std;

    std::cout << "[0] - main started\n";

    {
      shared_ptr<Dog> sp_dog1(make_shared<Dog>("dog1"));
      // output -> dog1 born.
      shared_ptr<Dog> sp_dog2(make_shared<Dog>("dog2"));
      // output -> dog2 born.

      sp_dog1->make_friend(sp_dog2);
      // output -> dog1 - dog2 are friends.

      sp_dog2->make_friend(sp_dog1);
      // output -> dog2 - dog1 are friends.

      std::cout << "sp_dog1.use_count = " 
                << sp_dog1.use_count() << '\n';
      // output -> sp_dog1.use_count = 1

      std::cout << "sp_dog2.use_count = "
                << sp_dog2.use_count() << '\n';
      // output -> sp_dog2.use_count = 1

      sp_dog1->print();
      // output -> dog name = dog1 has a friend called dog2
      
      sp_dog2->print();
      // output -> dog name = dog2 has a friend called dog1
    }
    // output -> 
    //  dog2 dead.
    //  dog1 dead.

    std::cout << "[1] - main ended\n";
  }
*/