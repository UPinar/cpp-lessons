/*
                    =============================
                    | Input - Output Operations |
                    =============================
*/

/*
  1 . Formatted I/O Operations
    reading from standart input, writing to standart output.
      - std::basic_ostream inherited from std::basic_ios
      - std::basic_istream inherited from std::basic_ios
    reading from a file, writing to a file.
      - std::basic_ifstream inherited from std::basic_istream
      - std::basic_ofstream inherited from std::basic_ostream
      - std::basic_fstream  inherited from std::basic_iostream
    reading from a memory, writing to a memory.
      - std::basic_istringstream inherited from std::basic_istream
      - std::basic_ostringstream inherited from std::basic_ostream
      - std::basic_stringstream inherited from std::basic_iostream
  2. Unformatted I/O operations.
  3. exception handling in stream operation.
  4. file operations
*/

/*
        <---- check images/input_output_hierarchy.png ---->
  - std::ios_base is a class.
  - std::basic_ios is a class template 
    inherits from std::ios_base.
*/

/*
  #include <iostream>

  int main()
  {
    // ---------------------------------------------

    std::basic_ios<char>;
    std::ios;
    // Those 2 lines are equivalent.

    std::basic_ios<wchar_t>;
    std::wios;
    // Those 2 lines are equivalent.

    // ---------------------------------------------

    std::basic_ostream<char>;
    std::ostream;
    // Those 2 lines are equivalent.

    std::basic_ostream<wchar_t>;
    std::wostream;
    // Those 2 lines are equivalent.

    // ---------------------------------------------

    std::basic_istream<char>;
    std::istream;
    // Those 2 lines are equivalent.

    std::basic_istream<wchar_t>;
    std::wistream;
    // Those 2 lines are equivalent.

    // ---------------------------------------------
  }
*/

/*
                    ---------------------------
                    | Formatted IO Operations |
                    ---------------------------
*/

/*
  Formatted Output : 
    converting data to text then sending to stream.
  Unformatted Output : 
    directly sending binary data to stream
*/

/*
  // -------------------------------------------------------

  #include <iostream>

  class Basic_Ostream {
  public:
    // inserter member functions (return type is *this)
    Basic_Ostream& operator<<(int);
    Basic_Ostream& operator<<(double);
  };

  // -------------------------------------------------------

  // there are some global inserter(operator<<) functions
  // which are defined in different header files, 
  // for classes and basic types related with that header file.

  #include <string>
  // std::ostream& operator<<(std::ostream&, const std::string&)
  // return type is a reference to its first parameter variable

  // -------------------------------------------------------
*/

/*
  #include <iostream>

  void new_line()
  {
    std::cout << '\n';
  }

  int main()
  {
    // -----------------------------------------------

    int ival{ 254 };
    double dval{ 2.3 };

    // "operator<<" function is returning std::ostream& 
    // which can be used for chaining.
    
    std::cout << ival << dval;    
    // output -> 2542.3
    // std::ostream& operator<<(std::ostream&, int);
    // std::ostream& operator<<(std::ostream&, double);
    // global function

    new_line();

    std::cout.operator<<(ival).operator<<(dval);  
    // output -> 2542.3
    // std::ostream& std::ostream::operator<<(int);
    // std::ostream& std::ostream::operator<<(double);
    // member function

    new_line();

    // -----------------------------------------------

    // const char[6] will decay to const char*

    std::cout << "world";   
    // output -> world           
    // std::ostream& operator<<(std::ostream&, const char*);
    // global function

    new_line();

    std::operator<<(std::cout, "world");  
    // output -> world           
    // std::ostream& operator<<(std::ostream&, const char*);
    // global function

    new_line();

    // -----------------------------------------------

    std::cout.operator<<("galaxy");       
    // output -> 0x7ff6ac7e5056
    // std::ostream& std::ostream::operator<<(const void*);
    // member function

    new_line();

    // -----------------------------------------------

    std::cout << 'A';                       
    // output -> A
    // std::ostream& operator<<(std::ostream&, char);
    // global function

    new_line();

    std::operator<<(std::cout , 'A');
    // output -> A
    // std::ostream& operator<<(std::ostream&, char);
    // global function

    new_line();

    // -----------------------------------------------

    std::cout.operator<<('A');              
    // output -> 65
    // std::ostream& std::ostream::operator<<(int)
    // member function

    // -----------------------------------------------
  }
*/

/*
  // std::ostream and std::istream classes
  // both have "operator bool" function in their interface 
  // that is inherited from the base class (std::basic_ios)

  #include <iostream>

  int main()
  {
    // -----------------------------------------------------

    // calling "operator bool" function in logic context

    if (std::cout && std::cin){}
    if (std::cout.operator bool() && std::cin.operator bool()){}
  
    std::cout ? 10 : 20;

    // -----------------------------------------------------

    bool b1 = std::cout;  // syntax error
    // error: 
    //  cannot convert 'std::ostream' {'std::basic_ostream<char>'}
    //  to 'bool' in initialization

    bool b2 = std::cin;   // syntax error
    // error: 
    //  cannot convert 'std::istream' {'std::basic_istream<char>'} 
    //  to 'bool' in initialization


    bool b3 = static_cast<bool>(std::cout );  // VALID
    bool b4 = static_cast<bool>(std::cin);    // VALID
    // because of "operator bool" function is explicit
    // implicit conversion from std::cout to bool is NOT VALID.

    // -----------------------------------------------------
  }
*/

/*
  #include <iostream>
  #include <string>
  #include <memory>     // std::make_unique
  #include <bitset>
  #include <complex>
  #include <utility>    // std::pair

  int main()
  {
    // ------------------------------------------------

    std::cout << std::string{ "world" } << '\n';
    // output -> world
    // std::ostream& operator<<(std::ostream&, const std::string&);
    // global "operator<<" function inside <string> header

    // ------------------------------------------------

    auto up_str = std::make_unique<std::string>("galaxy");
    std::cout << up_str << '\n';
    // output -> 0x21193180d20
    // std::ostream& operator<<(std::ostream&, 
    //                          const std::unique_ptr<T>&);
    // global "operator<<" function inside <memory> header

    // ------------------------------------------------

    std::cout << std::bitset<8>{ 11u } << '\n';
    // output -> 00001011
    // std::ostream& operator<<(std::ostream&, 
    //                          const std::bitset<T>&);
    // global "operator<<" function inside <bitset> 

    // ------------------------------------------------

    std::cout << std::complex<double>{ 3.3, 6.6 } << '\n';
    // output -> (3.3,6.6)
    // std::ostream& operator<<(std::ostream&, std::complex<T>&);
    // global "operator<<" function inside <complex> header

    // ------------------------------------------------

    std::cout << std::pair<int, int>{ 22, 44 };   // syntax error
    // error: no match for 'operator<<' 
    // (operand types are 'std::ostream'{'std::basic_ostream<char>'} 
    // and 'std::pair<int, int>'

    // there is NO global "operator<<" function for std::pair

    // ------------------------------------------------
  }
*/

/*
  // writing a global inserter function for std::pair

  #include <iostream>
  #include <utility>    // std::pair

  template <typename T, typename U>
  std::ostream& operator<<( std::ostream& os, 
                            const std::pair<T, U>& pair)
  {
    return os << '[' << pair.first << ", " << pair.second << ']';
  }

  int main()
  {
    std::cout << std::pair<int, int>{ 22, 44 };
    // output -> [22, 44]
  }
*/

/*
  #include "../headers/nutility.h"
  #include <vector>
  #include <fstream>	  // std::ofstream
  #include <cstdlib>    // std::exit, EXIT_FAILURE
  #include <sstream>    // std::ostringstream
  #include <string>
  #include <algorithm>  // std::reverse

  int main()
  {
    std::vector<std::string> str_vec;
    rfill(str_vec, 5, rtown);

    // ----------------------------------------------

    // writing to standart output

    for (const auto& str : str_vec)
      std::cout << str << '-';
    // standart output(console in this case) -> 
    //  kahramanmaras-tokat-bayburt-kayseri-duzce-

    std::cout << '\n';

    // ----------------------------------------------

    // writing to a file

    std::ofstream ofs{ "out.txt" };
    if (!ofs) {
      std::cerr << "can not create out.txt file\n";
      std::exit(EXIT_FAILURE);
    }

    for (const auto& str : str_vec)
      ofs << str << '-';
    // out.txt -> kahramanmaras-tokat-bayburt-kayseri-duzce-

    // ----------------------------------------------

    // writing to a memory

    std::ostringstream oss;

    for (const auto& str : str_vec)
      oss << str << '-';
  
    std::string str = oss.str();
    std::reverse(str.begin(), str.end());

    std::cout << str << '\n';
    // output -> -eczud-iresyak-trubyab-takot-saramnamarhak

    // ----------------------------------------------
  }
*/

/*
  class Ostream {
  public:
    // inserter member functions for different types
    Ostream& operator<<(int);
    Ostream& operator<<(double);
    Ostream& operator<<(long);
    Ostream& operator<<(void*); // inserter for pointer types

    Ostream& operator<<(Ostream&(*fp)(Ostream&))
    {
      return fp(*this);
    }
    // its parameter is a function pointer(callback function)
  };
*/


/*
  #include <iostream> // std::cout
  #include <ostream>  // std::ostream, std::endl
  #include <string>

  // ostream manipulator functions
  // have a return type of std::ostream& and 
  // takes std::ostream& as a parameter

  std::ostream& manipulator_endl(std::ostream& os)
  {
    os.put('\n');
    os.flush();
    return os;
  }

  std::ostream& manipulator_dash(std::ostream& os)
  {
    return os << "\n-----------------------------------\n";
  }

  int main()
  {
    // ----------------------------------------------

    std::cout << std::endl;
    std::endl(std::cout);
    // Those 2 lines are equivalent.

    // passing std::cout(global std::ostream object) 
    // to "std::endl" function.

    // ----------------------------------------------

    int ival{ 11 };
    double dval{ 22.22 };
    std::string str{ "world" };

    std::cout << ival << manipulator_dash 
              << dval << manipulator_dash 
              << str << manipulator_endl;
    // output ->
    //  11
    //  -----------------------------------
    //  22.22
    //  -----------------------------------
    //  world

    // ----------------------------------------------
  }
*/

/*
  #include <random>   // std::mt19937
  #include <iostream>

  int main()
  {
    std::mt19937 eng;

    std::cout << eng() << '\n';   // output -> 3499211612

    std::cout << eng << '\n';
    // output ->
    // 2601187879 3919438689 2270374771 3254473187 
    // 705526435 752899028 4259895275 1635503293 
    // ...

    // std::ostream& operator<<(std::mt19937& eng) in <random> header
    // serialization :
    // different machines to understand RNG engines state
  }
*/

/*
  #include <chrono>
  #include <iostream>

  int main()
  {
    // ----------------------------------------------

    std::chrono::milliseconds msx{ 444 };

    std::cout << msx << '\n';
    // output -> 444ms

    // ----------------------------------------------

    using namespace std::chrono_literals;

    std::cout << 11min + 22s + 33ms + 44us << '\n';
    // output -> 682033044us

    constexpr auto val =  std::chrono::minutes{ 11 }      + 
                          std::chrono::seconds{ 22 }      +
                          std::chrono::milliseconds{ 33 } + 
                          std::chrono::microseconds{ 44 };
    // val -> 682033044us
    
    // ----------------------------------------------
  }
*/

/*
  - stream objects have a format state.
  - format state can be changed.
  - how stream object will be written to stdoutput/file/memory
    will be declared by their format state.
*/

/*
  #include <iostream>   // std::boolalpha

  int main()
  {
    std::cout << (22 > 11) << '\n';    // output -> 1
    // global ostream object(std::cout)'s format state 
    // will define how that object will write bool values to output.
    // it can be be written as 1-0 or true-false
    // default state is 1-0

    std::cout.setf(std::ios::boolalpha);
    // std::cout object's format state has been changed.

    std::cout << (22 > 11) << '\n';   // output -> true
  }
*/

/*
  #include <iostream>   
  // std::hex, std::basefield, std::uppercase

  int main()
  {
    int ival = 47802;

    std::cout << ival << '\n';  
    // output -> 47802  (default state is decimal)

    std::cout.setf(std::ios::hex, std::ios::basefield);
    std::cout << ival << '\n';
    // output -> baba

    std::cout.setf(std::ios::uppercase);
    std::cout << ival << '\n';
    // output -> BABA
  }
*/

/*
  #include <iostream>   // std::boolalpha

  // std::boolalpha ostream manipulator function
  std::ostream& Boolalpha(std::ostream& os)
  {
    os.setf(std::ios::boolalpha);
    return os;
  }

  std::ostream& Noboolalpha(std::ostream& os)
  {
    os.unsetf(std::ios::boolalpha);
    return os;
  }

  int main()
  {
    std::cout << std::boolalpha << (22 > 11) << '\n';
    // output -> true
    // "std::boolalpha" is a global ostream manipulator function
    // which is formatting the state of the stream object
    // by calling "setf"(set format) function.

    std::cout << std::noboolalpha << (22 > 11) << '\n';
    // output -> 1

    std::cout << Boolalpha << (22 > 11) << '\n';
    // output -> true

    std::cout << Noboolalpha << (22 > 11) << '\n';
    // output -> 1
  }
*/

/*
  #include <ostream>

  void func(std::ostream& os)
  {
    //  How to understand the state of the stream object
    // i.e, is this stream object will write boolean values 
    //  as 1-0 or true-false

    // and if the state of the stream object is changed
    // inside the "func" function's scope, 
    // it is better to return it back to its old state
    // before the scope ends.
  }
*/

/*
                      ----------------------
                      | std::ios::fmtflags | 
                      ----------------------
*/

/*
  // state of the stream object is hold in a type called
  // `std::ios::fmtflags`

  #include <iostream>

  int main()
  {
    // ------------------------------------------------

    std::ios_base::fmtflags;            // base class
    std::basic_ios<char>::fmtflags;
    std::ios::fmtflags;

    // ------------------------------------------------

    auto saved_flags = std::cout.flags();
    // "saved_flags" object holds global "std::cout" object's state.
    // this state can be applied to another stream object.

    // ------------------------------------------------
  }
*/

/*
  #include <iostream>

  int main()
  {
    // ------------------------------------------------

    std::ios_base::boolalpha;  
    // boolalpha is static constexpr fmtflag
    // -> 0100 0000 0000 0000 (bitmask)

    // ------------------------------------------------

    std::cout.flags(std::cout.flags() | std::ios::boolalpha);
    // passing the result of the bitwise OR operation
    // to the "flags" member function of the "std::cout" 
    // global std::ostream object.

    // ------------------------------------------------

    std::cout.setf(std::ios_base::boolalpha);
    std::cout.flags(std::cout.flags() | std::ios::boolalpha);
    // Those 2 lines are equivalent.

    // ------------------------------------------------
  }
*/

/*
  #include <iostream>   // std::ios::boolalpha

  int main()
  {
    bool b = true;

    // ------------------------------------------------

    std::cout << b << '\n';   // output -> 1
    // default state of the boolalpha fmtflag is 0(off)(cleared)
    // boolean values will be written as 0/1

    // ------------------------------------------------

    std::cout.setf(std::ios::boolalpha);
    std::cout << b << '\n';   // output -> true
    // state of the boolalpha fmtflag becomes 1(on)(set)
    // boolean values will be written as true/false

    // ------------------------------------------------

    std::cout.flags(std::cout.flags() & ~std::ios::boolalpha);
    std::cout.unsetf(std::ios::boolalpha);
    // Those 2 lines are equivalent.

    // state of the boolalpha fmtflag becomes 0(off)(cleared)
    // boolean values will be written as 0/1

    std::cout << b << '\n';   // output -> 1

    // ------------------------------------------------
  }
*/

/*
  // passing more than 1 fmtflag to the setf function
  // by using bitwise OR operator

  #include <iostream>

  int main()
  {

    std::cout.setf( std::ios::boolalpha | 
                    std::ios::uppercase | 
                    std::ios::showbase  | 
                    std::ios::showpos);

    // will set the boolalpha, uppercase, 
    // showbase and showpos fmtflags
  }
*/

/*
  boolean flags (on/off)(set/cleared)
  ------------------------------------
  - std::ios::boolalpha
  - std::ios::showpos   (show positive sign)
  - std::ios::uppercase 
  - std::ios::showbase
  - std::ios::showpoint
  - std::ios::skipws    (skip white space)(input)

  stream.setf(showpos | showpoint);
  stream.unsetf(showpos | showpoint);
*/

/*
  #include <iostream>  // std::ios::showpos

  int main()
  {
    std::cout << 1234 << '\n';  
    // output -> 1234

    std::cout.setf(std::ios::showpos);
    std::cout << 1234 << '\n';  
    // output -> +1234
  }
*/

/*
  #include <iostream> 
  // std::ios::hex, std::ios::basefield
  // std::ios::showbase, std::ios::uppercase,

  int main()
  {
    std::cout.setf(std::ios::hex, std::ios::basefield);
    std::cout << 47802 << '\n';
    // output -> baba

    std::cout.setf(std::ios::uppercase);
    std::cout << 47802 << '\n';
    // output -> BABA

    std::cout.setf(std::ios::showbase);
    std::cout << 47802 << '\n';
    // output -> 0XBABA
  }
*/

/*
  #include <iostream>

  void func(std::ostream& os)
  {
    os  << "std::ios::boolalpha = "
        << (os.flags() & std::ios::boolalpha  ? "set" 
                                              : "unset") 
        << '\n';

    os  << "std::ios::uppercase = "
        << (os.flags() & std::ios::uppercase  ? "set" 
                                              : "unset") 
        << '\n';

    os  << "std::ios::showpos = "
        << (os.flags() & std::ios::showpos  ? "set" 
                                            : "unset") 
        << '\n';

    os  << "std::ios::showpoint = "
        << (os.flags() & std::ios::showpoint  ? "set" 
                                              : "unset") 
        << '\n';

    os  << "std::ios::showbase = "
        << (os.flags() & std::ios::showbase ? "set" 
                                            : "unset") 
        << '\n';
  }

  int main()
  {
    // --------------------------------------------------

    func(std::cout);
    // output ->
    //  std::ios::boolalpha = unset
    //  std::ios::uppercase = unset
    //  std::ios::showpos = unset
    //  std::ios::showpoint = unset
    //  std::ios::showbase = unset

    std::cout << '\n';

    // --------------------------------------------------

    std::cout.setf(std::ios::boolalpha | std::ios::uppercase);
    func(std::cout);
    // output ->
    //  std::ios::boolalpha = set
    //  std::ios::uppercase = set
    //  std::ios::showpos = unset
    //  std::ios::showpoint = unset
    //  std::ios::showbase = unset

    // --------------------------------------------------
  }
*/

/*
  // recovering the stream object's state
  // before the function scope ends.
  
  #include <iostream>   // std::ios::fmtflags, std::ostream


  void func_1(std::ostream& os)
  {
    auto old_fmtflags = os.flags();

    os.setf(std::ios::boolalpha | std::ios::uppercase);
    // changed the state of the stream object

    os.flags(old_fmtflags);
    // if an exception thrown before this line
    // stream object's state will be lost.
  }

  // RAII class for recovering the stream object's state
  class fmt_guard {
  private:
    std::ostream& m_os;
    std::ios::fmtflags m_flags;
  public:
    fmt_guard(std::ostream& os) : m_os{ os }, m_flags{ os.flags() }
    {}

    ~fmt_guard()
    {
      m_os.flags(m_flags);
    }
  };

  void func_2(std::ostream& os)
  {
    fmt_guard fmt_guard_obj{ os };

    os.setf(std::ios::boolalpha | std::ios::uppercase);
    // changed the state of the stream object

    // because of RAII class is being used to hold stream objects
    // state information, if an exception thrown
    // old state can be recovered 
    // when "fmt_guard_obj" object's destructor is called
    // in stack unwinding phase.
  }
*/

/*
  field flags
  -------------
  - std::ios::basefield
    std::ios::hex       (hexadecimal)
    std::ios::dec       (decimal)
    std::ios::oct       (octal)

  - std::ios::adjustfield
    std::ios::left
    std::ios::right
    std::ios::internal

  - std::ios::floatfield
    std::ios::fixed
    std::ios::scientific
*/

/*
  #include <iostream>
  #include <bitset>

  int main()
  {
    using namespace std;

    // -----------------------------------------------

    cout << bitset<32>{ ios::basefield } << '\n';
    // output -> 00000000000000000000000001001010
    cout << bitset<32>{ ios::hex } << '\n';;
    // output -> 00000000000000000000000000001000
    cout << bitset<32>{ ios::oct } << '\n';;
    // output -> 00000000000000000000000001000000
    cout << bitset<32>{ ios::dec } << '\n';;
    // output -> 00000000000000000000000000000010

    // -----------------------------------------------

    // ios::basefield is the bitmask used for clearing all 
    // ios::hex, ios::oct and ios::dec bits

    // 1. bitwise AND with ~ios::basefield 
    //  will clear ios::hex, ios::oct and ios::dec bits

    // 2. bitwise OR with ios::hex 
    //  will set ios::hex bit.

    // -----------------------------------------------

    cout << 47802 << '\n';
    // output -> 47802
    // default is decimal (ios::dec bit is set)

    cout.setf(ios::hex, ios::basefield);
    // clearing all ios::hex, ios::oct and ios::dec bits
    // and setting ios::hex bit
    cout << 47802 << '\n';
    // output -> baba

    cout.flags(cout.flags() & ~ios::basefield);
    // clearing all ios::hex, ios::oct and ios::dec bits
    cout.flags(cout.flags() | ios::dec);
    // set ios::dec bit
    
    cout << 47802 << '\n';
    // output -> 47802

    // -----------------------------------------------

    cout.setf(ios::oct, ios::basefield);
    // clearing all ios::hex, ios::oct and ios::dec bits
    // setting ios::oct bit
    cout << 47802 << '\n';
    // output -> 135272

    // -----------------------------------------------

    cout.setf(ios::dec, ios::basefield);
    // clearing all ios::hex, ios::oct and ios::dec bits
    // setting ios::dec bit
    cout << 47802 << '\n';
    // output -> 47802

    // -----------------------------------------------
  }
*/

/*
  #include <iostream>
  // std::ios::hex, std::ios::oct, std::ios::dec
  // std::ios::basefield, std::ostream 

  void print_state(std::ostream& os)
  {
    using namespace std;

    cout  << "hex bit = " << (os.flags() & ios::hex ? "set" 
                                                    : "unset") 
          << '\n';

    cout  << "oct bit = " << (os.flags() & ios::oct ? "set" 
                                                    : "unset") 
      << '\n';

    cout  << "dec bit = " << (os.flags() & ios::dec ? "set" 
                                                    : "unset") 
      << '\n';

    cout << '\n';
  }

  int main()
  {
    // ---------------------------------------------

    print_state(std::cout);
    // output ->
    //  hex bit = unset
    //  oct bit = unset
    //  dec bit = set

    // ---------------------------------------------

    std::cout.setf(std::ios::hex, std::ios::basefield);

    print_state(std::cout);
    // output ->
    //  hex bit = set
    //  oct bit = unset
    //  dec bit = unset

    // ---------------------------------------------

    std::cout.setf(std::ios::oct, std::ios::basefield);
    
    print_state(std::cout);
    // output ->
    //  hex bit = unset
    //  oct bit = set
    //  dec bit = unset

    // ---------------------------------------------
  }
*/

/*
  #include <iostream>
  // std::ios::fixed, std::ios::scientific, std::ios::floatfield
  // std::ostream

  void print_state(std::ostream& os)
  {
    using namespace std;

    cout  << "fixed      = " 
          << (os.flags() & ios::fixed  ? "set" : "unset")
          << '\n';

    cout  << "scientific = " 
          << (os.flags() & ios::scientific ? "set" : "unset") 
          << "\n\n"; 
  }

  int main()
  {
    // ---------------------------------------------------

    print_state(std::cout);
    // output ->
    //  fixed      = unset
    //  scientific = unset

    // 00 -> depends on the number(default state)
    // it will be written as fixed or scientific.

    std::cout << 2.3 << '\n';
    // output -> 2.3 (fixed)
    std::cout << 57625635263.91238 << "\n\n";
    // output -> 5.76256e+10 (scientific)

    // ---------------------------------------------------

    std::cout.setf(std::ios::fixed, std::ios::floatfield);

    print_state(std::cout);
    // output ->
    //  fixed      = set
    //  scientific = unset

    std::cout << 2.3 << '\n';
    // output -> 2.300000 (fixed)
    std::cout << 57625635263.91238 << "\n\n";
    // output -> 57625635263.912376 (fixed)

    // ---------------------------------------------------

    std::cout.setf(std::ios::scientific, std::ios::floatfield);
    print_state(std::cout);
    // output ->
    //  fixed      = unset
    //  scientific = set

    std::cout << 2.3 << '\n';
    // output -> 2.300000e+00 (scientific)
    std::cout << 57625635263.91238 << "\n\n";
    // output -> 5.762564e+10 (scientific)

    // ---------------------------------------------------

    std::cout.setf(std::ios::fixed | std::ios::scientific);

    print_state(std::cout);
    // output ->
    //  fixed      = set
    //  scientific = set

    std::cout << 2.3 << '\n';
    // output -> 0x1.2666666666666p+1 (hex-float)
    std::cout << 57625635263.91238 << "\n\n";
    // output -> 0x1.ad582d37fd323p+35 (hex-float)

    // ---------------------------------------------------
  }
*/

/*
  left - right - internal | adjustfield

  -> "width" member function to get and set the width.
  -> "fill" member function to get and set the fill character.

  ???????435 right
  435??????? left

  +      981
  -    35678
  +   12      internal
*/

/*
  #include <iostream>

  int main()
  {
    // ----------------------------------------------

    std::cout.width(20);
    // std::cout stream object's default width is 0

    std::cout.fill('_');
    // std::cout stream object's default fill character is ' '

    // ----------------------------------------------

    std::cout << "|world|" << '\n';
    // output ->_____________|world|
    // default std::ios::adjustfield bit is std::ios::right

    // ----------------------------------------------

    std::cout.width(20);
    std::cout.setf(std::ios::left, std::ios::adjustfield);

    std::cout << "|world|" << '\n';
    // output -> |world|_____________

    // ----------------------------------------------
  }
*/

/*
  #include <iostream>

  int main()
  {
    std::cout.fill('_');

    // ------------------------------------------------

    std::cout.width(3);

    // if the width of the object that will be written
    // is greater than the width of the stream object
    // it will act like 0(default).

    int ival{ 879'376'293 };
    std::cout << ival << '\n';
    // output -> 879376293

    // ------------------------------------------------

    std::cout.width(20);
    // if the width of the object that will be written
    // is smaller than the width of the stream object
    // width will be the value that it has been set.

    std::cout << ival << '\n';
    // output -> ___________879376293

    // ------------------------------------------------
  }
*/

/*
  // "width" is TEMPORARY and its default value is 0.

  #include <iostream>

  int main()
  {
    std::cout.fill('_');

    // ------------------------------------------------

    std::cout.width(20);
    auto N = std::cout.width();

    std::cout << "N = " << N << '\n';
    // output -> ________________N = 20

    // ------------------------------------------------
    N = std::cout.width();

    std::cout << "N = " << N << '\n';
    // output -> N = 0 

    // ------------------------------------------------
  }
*/

/*
  #include <iostream> 
  // std::ios::left, std::ios::adjustfield

  class Point {
  private:
    int m_x{}, m_y{}, m_z{};
  public:
    Point(int x, int y, int z) : m_x{ x }, m_y{ y }, m_z{ z } 
    {}

    friend std::ostream& operator<<(std::ostream& os, const Point& p)
    {
      return os << "(" << p.m_x 
                << ", " << p.m_y 
                << ", " << p.m_z << ")\n";
    }
  };

  int main()
  {
    Point p1{ 11, 22, 33 };

    // ---------------------------------------------------

    std::cout << p1;    
    // output -> (11, 22, 33)

    // ---------------------------------------------------

    std::cout.fill('_');

    std::cout.width(20);
    std::cout.setf(std::ios::left, std::ios::adjustfield);
    std::cout << p1;
    // output -> (___________________11, 22, 33)


    // There are 7 stream operation in this function call.
    //  1. os << "("
    //  2. os << p.m_x
    //  3. os << ", "
    //  4. os << p.m_y
    //  5. os << ", "
    //  6. os << p.m_z
    //  7. os << ")\n"

    // after the first insertion[os << "("], width will become 0.

    // ---------------------------------------------------
  }
*/

/*
  #include <iostream>
  // std::ios::left, std::ios::adjustfield
  #include <sstream>    // std::ostringstream

  class Point {
  private:
    int m_x{}, m_y{}, m_z{};
  public:
    Point(int x, int y, int z) : m_x{ x }, m_y{ y }, m_z{ z } 
    {}

    friend std::ostream& operator<<(std::ostream& os, const Point& p)
    {
      std::ostringstream oss;
      oss << "(" << p.m_x 
          << ", " << p.m_y 
          << ", " << p.m_z << ")\n";

      return os << oss.str();
    }
  };

  int main()
  {
    Point p1{ 11, 22, 33 };

    // if the width wanted to be applied for all stream operations.
    // characters can be written to memory, 
    // then that memory can be converted to string
    // then that string can be written by std::ostream object.
    // only 1 stream operation NOT 7.

    std::cout.fill('_');
    std::cout.width(20);
    std::cout << p1;
    // output ->_______(11, 22, 33)
  }
*/

/*
  #include <iostream>
  // std::ios::left, std::ios::adjustfield

  int main()
  {
    // -------------------------------------------

    auto fill_ch = std::cout.fill();
    std::cout << "fill_ch = " << static_cast<int>(fill_ch) << '\n';
    // output -> fill_ch = 32 (ASCII of space character)

    // -------------------------------------------

    std::cout.fill('$');
    std::cout.width(30);
    std::cout.setf(std::ios::left, std::ios::adjustfield);
    std::cout << "hello";
    // output -> hello$$$$$$$$$$$$$$$$$$$$$$$$$

    // -------------------------------------------
  }
*/

/*
  formatting by calling "setf" or "unsetf" functions
  are creating verbose code, also it prevents chaining.
  better solution is calling ostream manipulator functions.

  #include <iostream>

  int main()
  {
    using namespace std;

    int ival_1{ 1111 }, ival_2{ 2222 }, ival_3{ 3333 };

    cout << ival_1 << ' ';

    cout.setf(ios::hex, ios::basefield);
    cout.setf(ios::uppercase);
    cout.setf(ios::showbase);
    cout << ival_2 << ' ';

    cout.setf(ios::oct, ios::basefield);
    cout << ival_3 << ' ';

    // output -> 1111 0X8AE 06405
  }
*/

/*
  #include <iostream>  // std::boolalpha, std::noboolalpha

  // ostream manipulator (std::boolalpha)
  std::ostream& Boolalpha(std::ostream& os)
  {
    os.setf(std::ios::boolalpha);
    return os;
  }

  // ostream manipulator (std::noboolalpha)
  std::ostream& NoBoolalpha(std::ostream& os)
  {
    os.unsetf(std::ios::boolalpha);
    return os;
  }

  int main()
  {
    // -------------------------------------------

    std::cout << (22 > 11) << ' ' 
              << Boolalpha << (22 > 11) << ' '
              << NoBoolalpha << (22 > 11) << '\n';
    // output -> 1 true 1

    // -------------------------------------------

    // standart library ostream manipulator functions
    std::cout << (22 < 11) << ' ' 
              << std::boolalpha << (22 < 11) << ' ' 
              << std::noboolalpha << (22 < 11) << '\n';
    // output -> 0 false 0

    // -------------------------------------------
  }
*/

/*
  #include <iostream>   // std::hex, std::dec, std::oct

  // ostream manipulator (std::hex)
  std::ostream& Hex(std::ostream& os)
  {
    os.setf(std::ios::hex, std::ios::basefield);
    return os;
  }

  // ostream manipulator (std::dec)
  std::ostream& Dec(std::ostream& os)
  {
    os.setf(std::ios::dec, std::ios::basefield);
    return os;
  }

  // ostream manipulator (std::oct)
  std::ostream& Oct(std::ostream& os)
  {
    os.setf(std::ios::oct, std::ios::basefield);
    return os;
  }

  // writing a ostream manipulator function
  std::ostream& func_manipulator(std::ostream& os)
  {
    os.setf(std::ios::hex, std::ios::basefield);
    os.setf(std::ios::uppercase | std::ios::showbase);
    return os;
  }

  int main()
  {    
    // -------------------------------------------

    std::cout << Hex << 47802 << ' ' 
              << Oct << 47802 << ' ' 
              << Dec << 47802 << '\n';
    // output -> baba 135272 47802

    // -------------------------------------------

    // standart library ostream manipulator functions
    std::cout << std::hex << 47802 << ' ' 
              << std::oct << 47802 << ' ' 
              << std::dec << 47802 << '\n';
    // output -> baba 135272 47802

    // -------------------------------------------

    std::cout << 47802 << func_manipulator << ' ' 
              << 47802 << '\n';
    // output -> 47802 0XBABA

    // -------------------------------------------
  }
*/

/*
  #include <iostream>   
  // std::left, std::right, std::fixed, std::scientific, 
  // std::hexfloat

  int main()
  {
    // --------------------------------------------

    std::cout.fill('_');
    std::cout.width(20);
    std::cout << std::left << 111 << 222 << '\n';
    // output -> 111_________________222

    // --------------------------------------------

    std::cout.width(20);
    std::cout << std::right << 111 << 222 << '\n';
    // output -> _________________111222

    // --------------------------------------------

    double dval = 243.2376483;

    std::cout << std::fixed << dval << '\n' 
              << std::scientific << dval << '\n' 
              << std::hexfloat << dval << '\n';
    // output ->
    //  243.237648
    //  2.432376e+02
    //  0x1.e679ad09b8e66p+7

    // --------------------------------------------
  }
*/

/*
  #include <iostream>   // std::fixed

  int main()
  {
    // -------------------------------------------

    auto N = std::cout.precision();
    // default precision is 6
    std::cout << "N = " << N << '\n';
    // output -> N = 6

    // -------------------------------------------

    std::cout << std::fixed << 345.8723938 << '\n';
    // output -> 345.872394

    // -------------------------------------------

    std::cout.precision(10);
    std::cout << std::fixed << 345.8723938 << '\n';
    // output -> 345.8723938000
    
    // -------------------------------------------
  }
*/

/*
  #include <iomanip>  
  // std::setw, std::setfill, std::setprecision
  #include <iostream> // std::left, std::fixed

  int main()
  {
    int ival = 11;
    double dval = 8723.12391893;

    // ---------------------------------------------------

    std::cout << std::setfill('_') << std::left << std::setw(12) 
              << ival << '\n';
    // output -> 11__________

    // ---------------------------------------------------

    std::cout << std::setprecision(15) << std::fixed 
              << dval << '\n';
    // output -> 8723.123918929999491

    // ---------------------------------------------------
  }
*/

/*
  #include <ctime>    // std::time, std::localtime
  #include <iomanip>  // std::setw
  #include <iostream>
  #include <sstream>

  std::string get_current_datetime()
  {
    auto t1 = std::time(nullptr);
    auto p_tm = std::localtime(&t1);

    std::ostringstream oss;
    oss.fill('0');
    oss << p_tm->tm_year + 1900 << '_' 
        << std::setw(2) <<  p_tm->tm_mon + 1 << '_' 
        << std::setw(2) << p_tm->tm_mday << '_' 
        << std::setw(2) << p_tm->tm_hour << '_' 
        << std::setw(2) << p_tm->tm_min << '_'
        << std::setw(2) << p_tm->tm_sec << ".txt";

    return oss.str();
  }

  int main()
  {
    // format : yyyy_mm_dd_hh_mm_ss.txt

    std::cout << '|' << get_current_datetime() << "|\n";
    // output -> |2025_01_11_20_04_48.txt|
  }
*/

/*
  #include <iostream>
  #include <string>

  class add_space {
  private:
    int m_space_count{};
  public:
    add_space() = default;
    explicit add_space(int val) : m_space_count{ val } {}

    // hidden friend ostream manipulator function
    friend std::ostream& operator<<(std::ostream& os, 
                                    const add_space& space_obj)
    {
      auto N = space_obj.m_space_count;
      while (N--)
        os.put(' ');

      return os;
    }
  };

  int main()
  {
    int ival1{ 11 };
    int ival2{ 22 };
    std::string str{ "world" };

    std::cout << ival1  << add_space(5) 
              << str    << add_space(5) 
              << ival2  << add_space(5) 
              << "galaxy";
    // output -> 11     world     22     galaxy
  }
*/

/*
  #include <iostream>   // std::hex, std::oct, std::dec

  int main()
  {
    int ival1, ival2, ival3;

    std::cout << "enter 3 integers : ";
    std::cin  >> std::hex >> ival1 
              >> std::oct >> ival2 
              >> std::dec >> ival3;

    std::cout << "ival1 = "   << ival1
              << ", ival2 = " << ival2 
              << ", ival3 = " << ival3 << '\n';

    // input -> enter 3 integers : 41 41 41
    // output -> ival1 = 65, ival2 = 33, ival3 = 41
  }
*/

/*
  #include <iostream>
  #include <iomanip>    // std::setw

  int main()
  {
    char str[50];

    std::cout << "enter a string : ";

    std::cin >> std::setw(5) >> str;
    std::cout << str << '\n';
    // input -> world galaxy universe
    // output -> worl

    // std::setw(5) will read 5 characters from the input
    // 'w', 'o', 'r', 'l', '\0' in this case. 
    // (null character included)
  }
*/

/*
  #include <iostream>

  class Myclass {
  private:
    int m_val{};
  public:
    Myclass() = default;
    Myclass(int x) : m_val{ x } 
    {}

    friend std::ostream& operator<<(std::ostream& os, 
                                    const Myclass& mx)
    {
      return os << "(" << mx.m_val << ")";
    }
  };

  template <typename T>
  void func(T x, T y)
  {
    std::cout << x << " " << y << '\n';
  }

  int main()
  {
    // ---------------------------------------------------
    
    int ival = 55;
    func(ival, {});   // output -> 55 0

    // ---------------------------------------------------

    int x = int{ 20 };
    int y = int{};    // value initialization
    int z = {};       // value initialization

    // ---------------------------------------------------

    std::cout << Myclass{ 35 } << '\n';   // output -> (35)
    std::cout << Myclass{} << '\n';       // output -> (0)

    func(Myclass{ 35 }, {});    // output -> (35) (0)

    // for the first template parameter,
    // T will be deduce to Myclass, 
    // for the second argument default constructor 
    // of Myclass will be called which will value initialize
    // "m_val" member variable.

    // ---------------------------------------------------
  }
*/

/*
  #include <iostream>
  #include <sstream>    // std::ostringstream
  #include <algorithm>  // std::sort, std::reverse

  int main()
  {
    std::ostringstream oss;

    for (int i = 0; i < 10; ++i)
      oss << i << '.';

    auto str = oss.str();
    std::cout << '|' << str << "|\n";
    // output -> |0.1.2.3.4.5.6.7.8.9.|

    std::sort(str.begin(), str.end());
    std::cout << '|' << str << "|\n";
    // output -> |..........0123456789|

    std::reverse(str.begin(), str.end());
    std::cout << '|' << str << "|\n";
    // output -> |9876543210..........|
  }
*/

/*
  #include <iostream>
  #include <sstream>  // std::ostringstream
  #include <bitset>

  int main()
  {
    std::ostringstream oss;

    int ival = 555;
    oss << std::bitset<16>(ival) << ival;

    std::cout << oss.str() << '\n';
    // output -> 0000001000101011555
  }
*/

/*
  #include <sstream>  // std::ostringstream
  #include <iomanip>  // std::setw, std::setfill
  #include <iostream>

  int main()
  {
    // ------------------------------------------------

    std::ostringstream oss;
    oss << std::setfill('0');

    for (int i = 1; i < 5; ++i) {
      oss << "hello_" << std::setw(2) << i << ".txt ";
      std::cout << oss.str() << '\n';
    }
    // output ->
    //  hello_01.txt
    //  hello_01.txt hello_02.txt
    //  hello_01.txt hello_02.txt hello_03.txt
    //  hello_01.txt hello_02.txt hello_03.txt hello_04.txt

    // ------------------------------------------------

    for (int i = 1; i < 5; ++i) {
      std::ostringstream oss_2;
      oss_2 << std::setfill('0');
      oss_2 << "hello_" << std::setw(2) << i << ".txt ";
      std::cout << oss_2.str() << '\n';
    }
    // output ->
    //  hello_01.txt
    //  hello_02.txt
    //  hello_03.txt
    //  hello_04.txt

    // ------------------------------------------------

    std::ostringstream oss_3;
    oss_3 << std::setfill('0');

    for (int i = 1; i < 5; ++i) {
      oss_3 << "hello_" << std::setw(2) << i << ".txt ";
      std::cout << oss_3.str() << '\n';
      oss_3.str("");
    }

    // output ->
    //  hello_01.txt
    //  hello_02.txt
    //  hello_03.txt
    //  hello_04.txt

    // ------------------------------------------------
  }
*/

/*
  #include <sstream>    // std::ostringstream
  #include <iostream>   
  // std::::uppercase, std::boolalpha, std::hex

  int main()
  {
    std::ostringstream oss;
    oss << std::uppercase << std::hex << std::boolalpha;

    oss << 47802 << ' ' << (22 > 11);
    std::cout << oss.str() << '\n';
    // output -> BABA true
  }
*/

/*
  #include <sstream>    // std::istringstream
  #include <string>
  #include <iostream>
  #include <algorithm>  // std::reverse

  int main()
  {
    using namespace std;

    std::istringstream iss{ "world galaxy universe" };
    std::string str;

    while (iss >> str) {
      std::reverse(str.begin(), str.end());
      cout << str << '\n';
    }
    // output ->
    //  dlrow
    //  yxalag
    //  esrevinu
  }
*/

/*
  #include <string>
  #include <sstream>  // std::istringstream
  #include <set>      // std::multiset
  #include <utility>  // std::move
  #include <iostream>

  int main()
  {
    std::string line{ "ccc bbb eee zzz kkk ccc eee ooo ddd eee" };
    std::istringstream iss(line);

    std::string str;
    std::multiset<std::string> str_multiset;

    while (iss >> str)
      str_multiset.insert(std::move(str));

    for (const auto& str : str_multiset)
      std::cout << str << ' ';
    // output -> bbb ccc ccc ddd eee eee eee kkk ooo zzz
  }
*/

/*
  #include <sstream>    // std::stringstream
  #include <iostream>

  int main()
  {
    std::string str;

    std::stringstream ss; 
    // std::stringstream can be used for both 
    // input and output operation

    ss << "12345";
    ss >> str;

    std::cout << "str = " << str << '\n';
    // str = 12345
  }
*/

/*
  #include <iostream>   
  // std::hex, std::boolalpha, std::uppercase, 
  // std::showbase, std::showpoint, std::ostream
  
  int main()
  {
    // ----------------------------------------------

    std::ostream os{ std::cout.rdbuf()};
    // initializing an ostream object with 
    // another ostream object's buffer.

    std::cout << 47802      << ' ' 
              << (22 > 11)  << ' ' 
              << 4.         << '\n';
    // output -> 47802 1 4

    os  << 47802    << ' ' 
        << (10 > 5) << ' ' 
        << 4.       << '\n';
    // output -> 47802 1 4

    // ----------------------------------------------

    os  << std::hex << std::boolalpha 
        << std::uppercase << std::showbase << std::showpoint;


    os  << 47802    << ' ' 
        << (10 > 5) << ' ' 
        << 4.       << '\n';
    // output -> 0XBABA true 4.00000

    // ----------------------------------------------
  }
*/

/*
  condition state
  -------------------
  cin.good()
  cin.bad()
  cin.fail()
  cin.operator!()

  static constexpr data members of base class (iostate manipulators)
  ios::goodbit
  ios::badbit
  ios::failbit
  ios::eofbit
*/

/*
  #include <iostream>

  int main()
  {
    std::cin.eof();
    // returns true if stream object is in eof state
    // return false if stream object is not in eof state

    std::cin.fail();
    // returns true, if stream object is in fail state
    // return false if stream object is not in fail state
  }
*/

/*
  #include <iostream>

  int main()
  {
    int ival;
    std::cout << "enter an integer: ";
    std::cin >> ival;

    if (std::cin.good())
      std::cout << "stream's condition is in good state.\n";
    else
      std::cout << "stream's condition is NOT in good state.\n";

    if (std::cin.fail())
      std::cout << "stream's condition is in fail state.\n";
    else
      std::cout << "stream's condition is NOT in fail state.\n";

    // input -> 5
    // output -> 
    //  stream's condition is in good state.
    //  stream's condition is NOT in fail state.

    // input -> hello
    // output ->
    //  stream's condition is NOT in good state.
    //  stream's condition is in fail state.
  }
*/

/*
  #include <iostream>   // std::hex

  int main()
  {
    int ival;
    std::cout << "enter an integer: ";
    std::cin >> std::hex >> ival;

    if (std::cin.good())
      std::cout << "stream's condition is in good state.\n";
    else
      std::cout << "stream's condition is NOT in good state.\n";

    if (std::cin.fail())
      std::cout << "stream's condition is in fail state.\n";
    else
      std::cout << "stream's condition is NOT in fail state.\n";

    // input -> 5
    // output ->
    //  stream's condition is in good state.
    //  stream's condition is NOT in fail state.

    // input -> apple
    // output ->
    //  stream's condition is in good state.
    //  stream's condition is NOT in fail state.

    // condition is in good state because  
    // 'a' is a valid character in hexadecimal system.
    // [0-9A-F]
  }
*/

/*
  #include <iostream>

  int main()
  {
    int ival;
    std::cout << "enter an integer: ";
    std::cin >> ival;

    // "good" and "operator bool" member functions are equivalent.

    if (std::cin.good())
      std::cout << "stream's condition is in good state.\n";
    else
      std::cout << "stream's condition is NOT in good state.\n";

    if (std::cin.operator bool())
      std::cout << "stream's condition is in good state.\n";
    else
      std::cout << "stream's condition is NOT in good state.\n";

    // input -> 5
    // output ->
    //  stream's condition is in good state.
    //  stream's condition is in good state.

    // input -> hello
    // output ->
    //  stream's condition is NOT in good state.
    //  stream's condition is NOT in good state.
  }
*/

/*
  #include <bitset>
  #include <iostream>   
  // std::ios::badbit, std::ios::eofbit,
  // std::ios::failbit, std::ios::goodbit

  int main()
  {
    using namespace std;

    cout << bitset<16>(ios::badbit)   << '\n';
    // output -> 0000000000000001
    cout << bitset<16>(ios::eofbit)   << '\n';
    // output -> 0000000000000010
    cout << bitset<16>(ios::failbit)  << '\n';
    // output -> 0000000000000100
    cout << bitset<16>(ios::goodbit)  << '\n';
    // output -> 0000000000000000
  }
*/

/*
  #include <iostream>

  int main()
  {
    using namespace std;

    if (cin.rdstate() == 0){}
    // checking if any of the error bits are set or not.

    if (cin.rdstate() & ios::badbit){}
    // checking if ios::badbit is set or cleared
  }
*/

/*
  #include <iostream>

  int main()
  {
    // ----------------------------------------------

    int ival{};

    std::cout << "enter a string : ";

    while (std::cin >> ival) {
      std::cout << ival << " * " << ival << " = " 
                << ival * ival << '\n';
    }

    // input -> 
    //  enter a string : 11 12 13 14 15 hello 16 17 18
    // output ->
    //  11 * 11 = 121
    //  12 * 12 = 144
    //  13 * 13 = 169
    //  14 * 14 = 196
    //  15 * 15 = 225

    // ----------------------------------------------

    while (std::cin.operator>>(ival).operator bool()){}
    while (std::cin >> ival){}
    // Those 2 lines are equivalent.

    // ----------------------------------------------
  }
*/

/*
  #include <iostream>   // std::boolalpha

  int main()
  {
    std::cout << std::boolalpha;

    // ----------------------------------------------

    int ival{};

    std::cout << "cin.bad()  = " << std::cin.bad() << '\n';
    std::cout << "cin.eof()  = " << std::cin.eof() << '\n';
    std::cout << "cin.fail() = " << std::cin.fail() << '\n';
    std::cout << "cin.good() = " << std::cin.good() << '\n';
    // output ->
    //  cin.bad()  = false
    //  cin.eof()  = false
    //  cin.fail() = false
    //  cin.good() = true

    // ----------------------------------------------

    std::cout << "enter an integer : ";
    std::cin >> ival;

    std::cout << "cin.bad()  = " << std::cin.bad() << '\n';
    std::cout << "cin.eof()  = " << std::cin.eof() << '\n';
    std::cout << "cin.fail() = " << std::cin.fail() << '\n';
    std::cout << "cin.good() = " << std::cin.good() << '\n';

    // input -> enter an integer : 10
    // output ->
    //  cin.bad()  = false
    //  cin.eof()  = false
    //  cin.fail() = false
    //  cin.good() = true

    // ----------------------------------------------

    std::cout << "enter an integer : ";
    std::cin >> ival;
    
    std::cout << "cin.bad()  = " << std::cin.bad() << '\n';
    std::cout << "cin.eof()  = " << std::cin.eof() << '\n';
    std::cout << "cin.fail() = " << std::cin.fail() << '\n';
    std::cout << "cin.good() = " << std::cin.good() << '\n';

    // input -> h
    // output ->
    //  cin.bad()  = false
    //  cin.eof()  = false
    //  cin.fail() = true
    //  cin.good() = false

    // ----------------------------------------------

    std::cout << "enter an integer : ";
    std::cin >> ival;

    std::cout << "cin.bad()  = " << std::cin.bad() << '\n';
    std::cout << "cin.eof()  = " << std::cin.eof() << '\n';
    std::cout << "cin.fail() = " << std::cin.fail() << '\n';
    std::cout << "cin.good() = " << std::cin.good() << '\n';

    // input -> ^Z(Ctrl + Z)
    // output ->
    //  cin.bad()  = false
    //  cin.eof()  = true
    //  cin.fail() = true
    //  cin.good() = false

    // ----------------------------------------------
  }
*/

/*
  #include <iostream>   // std::boolalpha
  #include <string>

  int main()
  {
    std::cout << std::boolalpha;

    // ----------------------------------------------

    if (std::cin.fail()) {}
    if (!std::cin) {}
    // Those 2 lines are equivalent.

    if (std::cin) {}
    if (std::cin.good()){}
    // Those 2 lines are equivalent.

    // ----------------------------------------------

    int ival{};

    while (true)
    {
      std::cout << "enter an integer : ";
      std::cin >> ival;

      if (std::cin.good()){
        std::cout << "entered integer is valid.\n";
        break;
      }

      if (std::cin.eof()) {
        std::cout << "nothing entered, buffer is empty.\n";
        std::cin.clear();
      }

      if (std::cin.fail()) {
        std::cout << "entered value is not a valid integer.\n";
        std::cin.clear();

        // buffer still holds entered value.
        std::string str;
        std::cin >> str;
        std::cout << "entered value = " << str << '\n';
      }
    }
    // input -> enter an integer : hello
    // output ->
    //  entered value is not a valid integer.
    //  entered value = hello

    // input -> enter an integer : ^Z(Ctrl + Z)
    // output -> nothing entered, buffer is empty.

    // input -> enter an integer : 11
    // output -> entered integer is valid.
  }
*/

/*
  #include <iostream>
  #include <string>     // std::getline
  #include <algorithm>  // std::reverse

  int main()
  {
    using namespace std;

    std::string str_line;

    while (std::getline(cin, str_line)) 
    {
      std::reverse(str_line.begin(), str_line.end());
      std::cout << str_line << '\n';
    }
    // input -> world galaxy universe
    // output -> esrevinu yxalag dlrow
    // input ->istanbul izmir ankara
    // output -> arakna rimzi lubnatsi
  }
*/

/*
  #include <iostream> // std:ios::goodbit
  
  int main()
  {
    using namespace std;

    // ---------------------------------------------

    int ival = 11;
    cout << "enter an integer : ";
    cin >> ival;
    // input -> enter an integer : hello

    cout << (cin ? "good" : "fail") << '\n';
    // output -> fail

    // ---------------------------------------------

    cin.clear();
    cin.clear(ios::goodbit);
    // Those 2 lines are equivalent.

    cout << (cin ? "good" : "fail") << '\n';
    // output -> good

    // ---------------------------------------------
  }
*/

/*
  #include <iostream>

  int main()
  {
    using namespace std;

    cout << boolalpha;

    cin.clear(ios::eofbit);
    cout << "eof bit  = " << cin.eof() << '\n';
    cout << "bad bit  = " << cin.bad() << '\n';
    cout << "good bit = " << cin.good() << '\n';
    cout << "fail bit = " << cin.fail() << '\n';
    cout << "op !     = " << cin.operator !() << '\n';
    cout << "op bool  = " << cin.operator bool() << '\n';

    // output ->
    //  eof bit  = true
    //  bad bit  = false
    //  good bit = false
    //  fail bit = false
    //  op !     = false
    //  op bool  = true
  }
*/

/*
  #include <iostream>

  int main()
  {
    using namespace std;

    cout << boolalpha;

    // --------------------------------------------------

    cin.clear(ios::failbit | ios::eofbit | ios::badbit);
    // "clear" member function can be used to set 
    // one or more condition(ios) states.

    cin.setstate(ios::failbit);
    cin.setstate(ios::eofbit);
    cin.setstate(ios::badbit);
    // condition(ios) states can individually be set by calling
    // "setstate" member function of the stream object.

    // --------------------------------------------------

    cout << "eof bit  = " << cin.eof() << '\n';
    cout << "bad bit  = " << cin.bad() << '\n';
    cout << "good bit = " << cin.good() << '\n';
    cout << "fail bit = " << cin.fail() << '\n';
    cout << "op !     = " << cin.operator !() << '\n';
    cout << "op bool  = " << cin.operator bool() << '\n';
    // output ->
    //  eof bit  = true
    //  bad bit  = true
    //  good bit = false
    //  fail bit = true
    //  op !     = true
    //  op bool  = false
  }
*/

/*
  #include <iostream>
  #include <string>   // std::getline

  int main()
  {
    using namespace std;

    int ival{};

    while ((cout << "enter an integer : ") && !(cin >> ival)) 
    {
      if (cin.eof()) {
        std::cout << "nothing entered.\n";
        cin.clear();
      }
      else {
        cin.clear();
        string line;
        getline(cin, line);
        cout << '[' << line << "] is NOT a valid integer.\n";
      }
    }

    cout << "entered integer = " << ival << '\n';
  }
  // input  -> enter an integer : hello
  // output -> [hello] is NOT a valid integer.
  
  // input  -> ^Z(Ctrl + Z)
  // output -> nothing entered.

  // input  -> enter an integer : 11
  // output -> entered integer = 11
*/

/*
  // to check if there is any integer left in stream object.

  #include <iterator>   // std::istream_iterator
  #include <iostream>   

  int main() 
  {
    std::cout << "enter an integer : ";

    std::istream_iterator<int> iter{ std::cin };
    std::istream_iterator<int> end{};   // default contructed

    int ival{};

    while (iter != end) {
      ival = *iter;
      std::cout << "ival = " << ival << '\n';
      ++iter;
    }

    // input -> enter an integer : 11 22 33 44 hello
    // output ->
    //  ival = 11
    //  ival = 22
    //  ival = 33
    //  ival = 44
  }
*/

/*
  #include <fstream>    // std::ifstream
  #include <iterator>   
  // std::istream_iterator, std::ostream_iterator
  #include <iostream>
  #include <vector>
  #include <string>
  #include <algorithm>  // std::copy

  int main() 
  {
    using namespace std;

    // out.txt -> world galaxy universe

    ifstream ifs{ "out.txt" };
    if (!ifs) {
      cerr << "file can not be opened!\n";
      return 1;
    }

    using istream_iter = istream_iterator<string>;

    vector<string> str_vec{ istream_iter{ ifs }, istream_iter{} };
    // vector<string> str_vec{ istream_iter{ ifs }, {} };
    // Those 2 lines are equivalent. (range constructor)

    cout  << "str_vec.size() = " 
          << str_vec.size() << '\n';
    // output -> svec.size() = 3

    std::copy(str_vec.begin(), str_vec.end(),           // source
              ostream_iterator<string>(cout, " - "));   // destination
    // output -> world - galaxy - universe -
  }
*/

/*
  #include <sstream>    // std::istringstream
  #include <iostream>
  #include <algorithm>  // std::copy
  #include <iterator>   // std::back_inserter
  #include <vector>
  #include <numeric>    // std::accumulate
  #include <string>

  int main()
  {
    using namespace std;

    // ----------------------------------------------------

    istringstream iss{ "11 22 33 44 55 66 77 88 99" };

    std::copy(istream_iterator<int>(iss), {},       // source
              ostream_iterator<int>(cout, " - "));  // destination
    // output -> 11 - 22 - 33 - 44 - 55 - 66 - 77 - 88 - 99 -

    cout << '\n';

    // ----------------------------------------------------

    istringstream iss2{ "11 22 33 44 55 66 77 88 99" };

    vector<int> ivec;
    std::copy(istream_iterator<int>(iss2), {},    // source
              std::back_inserter(ivec));          // destination

    std::copy(ivec.begin(), ivec.end(),             // source
              ostream_iterator<int>(cout, " - "));  // destination  
    // output -> 11 - 22 - 33 - 44 - 55 - 66 - 77 - 88 - 99 -

    cout << '\n';

    // ----------------------------------------------------

    istringstream iss_3{ "11 22 33 44 55 66 77 88 99" };

    int res = std::accumulate(istream_iterator<int>(iss_3), {}, 0);
    cout  << res << '\n';
    // output -> 495

    // ----------------------------------------------------

    istringstream iss_4{ "11 22 33 44 55 66 77 88 99" };
    string str{};

    cout  << accumulate(istream_iterator<string>{iss_4}, {}, str);
    // output -> 112233445566778899

    // ----------------------------------------------------
  }
*/

/*
  // finding first word that starts with 'f' character

  #include <fstream>    // std::ifstream
  #include <iterator>   // std::istream_iterator
  #include <algorithm>  // std::find_if
  #include <iostream>
  #include <string>

  int main()
  {
    using namespace std;

    // out.txt -> 
    //  world galaxy universe we are live from istanbul

    ifstream ifs{ "out.txt" };
    if (!ifs) {
      cerr << "file can not be opened!\n";
      return 1;
    }

    char ch = 'f';
    auto iter = std::find_if( istream_iterator<string>{ ifs }, {},
                              [ch](const string& str){ 
                                  return str[0] == ch;
                            });

    if (iter != istream_iterator<string>{})
      cout << "found -> " << *iter << '\n';
    else
      cout << "can not found\n";
    // output -> found -> from
  }
*/

/*
  // found the biggest integer

  #include <iostream>
  #include <iterator>   // std::istream_iterator
  #include <algorithm>  // std::max_element

  int main()
  {
    using namespace std;

    cout << "enter integers : ";
    // input -> enter integers : 11 22 99 444 55 66 88 77
    // ^Z(Ctrl + Z) to end the input

    cout << *std::max_element(istream_iterator<int>{ cin }, {});
    // output -> 444
  }
*/

/*
  // find the sum of the integers

  #include <iostream>
  #include <iterator>   // std::istream_iterator
  #include <numeric>    // std::accumulate

  int main()
  {
    using namespace std;

    cout << "enter integers : ";
    // input -> enter integers : 11 22 99 444 55 66 88 77
    // ^Z(Ctrl + Z) to end the input

    cout << std::accumulate(istream_iterator<int>{cin}, {}, 0);
    // output -> 862
  }
*/

/*
  // example from cppreference.com

  #include <sstream>    // std::istringstream
  #include <numeric>    // std::partial_sum
  #include <iterator>   // std::istream_iterator
  #include <iostream>
  #include <algorithm>

  int main()
  {
    using namespace std;

    // --------------------------------------------------

    istringstream str("0.1 0.2 0.3 0.4 0.5");

    std::partial_sum( 
          istream_iterator<double>(str),        // src_beg
          istream_iterator<double>{},           // src_end
          ostream_iterator<double>(cout, " ")); // dest

    // output -> 0.1 0.3 0.6 1 1.5

    cout << '\n';

    // --------------------------------------------------

    istringstream str2("1 3 5 7 8 9 10");

    auto it = std::find_if(
                istream_iterator<int>(str2),        // src_beg
                istream_iterator<int>(),            // src_end
                [](int i){ return i % 2 == 0; });   // pred

    if (it != istream_iterator<int>())
      cout << "The first even number is = " << *it << "\n";
    // output -> The first even number is = 8

    // " 9 10" left in the stream

    // --------------------------------------------------
  }
*/

/*
                      ----------------------
                      | File IO Operations |
                      ----------------------
*/

/*
  std::ofstream  -> write operation to a file
  std::ifstream  -> read operation from a file
  std::fstream   -> both read and write operation in a file
*/

/*
  #include <fstream>    // std::ofstream
  #include <string>

  int main()
  {
    std::ofstream ofs1("out.txt");
    // (const char*) parameter constructor

    std::string filename{ "hello.txt" };
    std::ofstream ofs2(filename);
    // (std::string) parameter constructor
  }
*/

/*
  file open mode masks
  ---------------------
    - ios::in       -> read mode
    - ios::out      -> write mode
    - ios::app      -> append (write to the end of the file)
    - ios::trunc    -> truncate
    - ios::binary   -> binary mode
    - ios::ate      -> attend (file_pointer at the end of the file)
*/

/*
  #include <fstream>  // std::ofstream
  #include <iostream> // std::cerr

  int main()
  {
    std::ofstream ofs("place.txt", std::ios::out | std::ios::trunc);
    std::ofstream ofs("place.txt");
    // Those 2 lines are equivalent.

    if (ofs.fail()) {
      std::cerr << "place.txt can not be created\n";
      return 1;
    }

    ofs << "world\n";
    ofs << "galaxy\n";
    ofs << "universe\n";

    for (int i = 0; i < 10; ++i)
      ofs << i << " ";

    // place.txt ->
    //  world
    //  galaxy
    //  universe
    //  0 1 2 3 4 5 6 7 8 9 
  }
*/

/*
  std::fstream objects are RAII objects.
  if user does not close the file, its will be closed
  at the end of its scope when its destructor is called.
*/

/*
  #include <fstream>    // std::ofstream
  #include <iostream>

  int main()
  {
    using namespace std;
    cout << boolalpha;

    // --------------------------------------------

    ofstream ofs("out.txt");
    // if exists it will be truncated,
    // if not exist it will be created.

    cout << ofs.is_open() << '\n';  // output -> true

    ofs.close();
    cout << ofs.is_open() << '\n';  // output -> false

    // --------------------------------------------

    ofstream ofs2;  // default constructed

    cout << ofs2.is_open() << '\n'; // output -> false

    // --------------------------------------------
  }
*/

/*
  #include <fstream>    // std::ofstream

  int main()
  {
    std::ofstream ofs;

    ofs.open("out.txt");
    ofs << "world galaxy universe";
    ofs.close();
    // out.txt -> world galaxy universe

    ofs.open("cities.txt");
    ofs << "istanbul ankara izmir";
    // cities.txt -> istanbul ankara izmir
  }
*/

/*
  #include <fstream>                // std::ofstream
  #include "../headers/nutility.h"

  int main()
  {
    std::ofstream ofs("out.txt");

    for (int i = 0; i < 10; ++i)
      ofs << rname() + ' ' + rtown() << '\n';
    // out.txt ->
    //  hande nevsehir
    //  yesim zonguldak
    //  tonguc tunceli
    //  handan karabuk
    //  pakize sirnak
    //  gazi denizli
    //  edip yozgat
    //  akin igdir
    //  burhan van
    //  cezmi artvin
  }
*/

/*
  #include "../headers/nutility.h"
  #include <vector>
  #include <string>
  #include <fstream>    // std::ofstream
  #include <algorithm>  // std::copy
  #include <iterator>   // std::ostream_iterator

  int main()
  {

    std::vector<std::string> str_vec;
    rfill(str_vec, 10, rtown);
    
    std::cout << "str_vec.size() = " 
              << str_vec.size() << '\n';
    // output -> str_vec.size() = 10

    std::ofstream ofs("out.txt");

    std::copy(str_vec.begin(), str_vec.end(), 
              std::ostream_iterator<std::string>{ ofs, "\n" });
    // out.txt ->
    //  samsun
    //  mersin
    //  kutahya
    //  tunceli
    //  sivas
    //  afyonkarahisar
    //  afyonkarahisar
    //  kastamonu
    //  aksaray
    //  erzincan
  }
*/

/*
  #include "../headers/file.h"
  #include "../headers/nutility.h"
  #include <iostream>

  int main()
  {
    // ------------------------------------------

    auto ofs = create_text_file("out.txt");

    for (int i = 0; i < 10; ++i)
      ofs << Irand{ 0, 10'000 }() << '\n';
    // out.txt ->
    //  4270
    //  806
    //  8962
    //  7317
    //  7606
    //  2460
    //  5326
    //  8812
    //  2791
    //  5297

    // ------------------------------------------

    try {
      auto ifs = open_text_file("nofile.txt");
    }
    catch (const std::exception& ex)
    {
      std::cout << "exception caught : " << ex.what() << '\n';
    }
    // output -> 
    //  exception caught : nofile.txt can not be opened.

    // ------------------------------------------
  }
*/

/*
  #include "../headers/file.h"
  #include "../headers/nutility.h"
  #include <iostream>

  int main()
  {
    // out.txt ->
    //  4270
    //  806
    //  8962
    //  7317
    //  7606
    //  2460
    //  5326
    //  8812
    //  2791
    //  5297
    
    auto ifs = open_text_file("out.txt");
    int ival;

    while (ifs >> ival) 
    {
      if (isprime(ival))
        std::cout << ival << " ";
    }
    // output -> 2791 5297
  }
*/

/*
  #include "../headers/file.h"
  #include <algorithm>    // std::copy_if
  #include <iterator>     
  // std::istream_iterator, std::ostream_iterator
  #include <iostream>

  int main()
  {
    // out.txt ->
    //  4270
    //  806
    //  8962
    //  7317
    //  7606
    //  2460
    //  5326
    //  8812
    //  2791
    //  5297

    auto ifs = open_text_file("out.txt");

    int val = 3;
    
    std::copy_if( 
        std::istream_iterator<int>{ ifs }, {},        // source
        std::ostream_iterator<int>{ std::cout, " "},  // destination
        [val](int x){ return x % val == 0; });        // predicate
    // output -> 7317 2460
    
    // writing values that are divisible by 3 
    // to standart output(console).
  }
*/

/*
  #include "../headers/file.h"
  #include "../headers/nutility.h"
  #include <string>     // std::getline
  #include <vector>
  #include <algorithm>  // std::sort, std::copy
  #include <iterator>   // std::ostream_iterator

  int main()
  {
    // ----------------------------------------------

    auto ofs = create_text_file("out.txt");

    for (int i = 0; i < 10; ++i)
      ofs << rname() << " " << rfname() << " " << rtown() << '\n';
    ofs.close();

    // out.txt ->
    //  cezmi yasmak tunceli
    //  adem barutcu bolu
    //  bulent poturgeli elazig
    //  samet edepsiz trabzon
    //  melisa portakal mugla
    //  aylin kayabasi gaziantep
    //  leyla dokuzcan yalova
    //  perihan yarma ankara
    //  ercument tokatci balikesir
    //  halime issiz nigde

    // ----------------------------------------------

    auto ifs = open_text_file("out.txt");

    std::vector<std::string> str_vec;
    std::string str_line;

    while (std::getline(ifs, str_line))
      str_vec.push_back(std::move(str_line));
  
    ifs.close();

    // ----------------------------------------------

    std::sort(str_vec.begin(), str_vec.end());

    ofs = create_text_file("sorted_out.txt");
    std::copy(str_vec.begin(), str_vec.end(), 
              std::ostream_iterator<std::string>{ ofs, "\n" });
    ofs.close();

    // sorted_out.txt ->
    //  adem barutcu bolu
    //  aylin kayabasi gaziantep
    //  bulent poturgeli elazig
    //  cezmi yasmak tunceli
    //  ercument tokatci balikesir
    //  halime issiz nigde
    //  leyla dokuzcan yalova
    //  melisa portakal mugla
    //  perihan yarma ankara
    //  samet edepsiz trabzon

    // ----------------------------------------------
  }
*/

/*
  #include <fstream>  // std::ofstream
  #include "../headers/nutility.h"

  int main()
  {
    // out.txt ->
    //  cezmi yasmak tunceli
    //  adem barutcu bolu
    //  bulent poturgeli elazig
    //  samet edepsiz trabzon
    //  melisa portakal mugla
    //  aylin kayabasi gaziantep
    //  leyla dokuzcan yalova
    //  perihan yarma ankara
    //  ercument tokatci balikesir
    //  halime issiz nigde

    // trying to open "out.txt" file in append mode
    std::ofstream ofs{ "out.txt", std::ios::app };
    if (!ofs) {
      std::cerr << "file can not be opened\n";
      return 1;
    }

    for (auto i = 0; i < 3; ++i)
      ofs << rtown() << '\n';

    // out.txt ->
    //  cezmi yasmak tunceli
    //  adem barutcu bolu
    //  bulent poturgeli elazig
    //  samet edepsiz trabzon
    //  melisa portakal mugla
    //  aylin kayabasi gaziantep
    //  leyla dokuzcan yalova
    //  perihan yarma ankara
    //  ercument tokatci balikesir
    //  halime issiz nigde
    //  artvin                --------->
    //  istanbul              --------->
    //  ardahan               --------->
  }
*/

/*
  #include <fstream>    // std::ofstream, std::ifstream
  #include "../headers/file.h"
  #include "../headers/nutility.h"
  #include <set>
  #include <string>
  #include <iterator>   // std::istream_iterator

  int main()
  {
    std::ofstream ofs = create_text_file("out.txt");

    for (int i = 0; i < 10000; ++i)
      ofs << rname() << '\n';

    std::ifstream ifs = open_text_file("out.txt");

    std::set<std::string> str_set{ 
              std::istream_iterator<std::string>{ ifs }, 
              std::istream_iterator<std::string>{}};
    // holding unique values.
              
    std::cout << "str_set.size() = " << str_set.size() << '\n';
    // output -> str_set.size() = 333
  }
*/

/*
  #include <fstream>  // std::ifstream
  #include "../headers/file.h"
  #include <iostream>

  int main()
  {
    // cities.txt ->
    //  istanbul izmir
    //  ankara

    // out.txt -> 
    //  aaa bbb
    //  ccc ddd

    // ---------------------------------------------------

    std::ifstream ifs = open_text_file("cities.txt");

    char ch;
    while (ifs.get(ch))
      std::cout.put(ch);
    // output ->
    //  istanbul izmir
    //  ankara

    std::cout << '\n';

    ifs.close();

    // ---------------------------------------------------

    ifs = open_text_file("out.txt");

    int ival;
    while ((ival = ifs.get()) != EOF)
      std::cout << (char)ival;

    // output ->
    //  aaa bbb
    //  ccc ddd

    // ---------------------------------------------------
  }
*/

/*
  #include <fstream>    // std::ofstream, std::ifstream
  #include "../headers/file.h"
  #include "../headers/nutility.h"
  #include <iostream>
  #include <string>              // std::getline

  int main()
  {
    // ---------------------------------------------------

    std::ofstream ofs = create_text_file("out.txt");

    for (int i = 0; i < 5; ++i)
      ofs << rname() << '_';
    // out.txt -> gulden_hakan_metin_tuncer_gulsah_

    ofs.close();

    // ---------------------------------------------------

    std::ifstream ifs = open_text_file("out.txt");

    std::string str;
    while (std::getline(ifs, str, '_'))
      std::cout << str << '\n';
    // output ->
    //  gulden
    //  hakan
    //  metin
    //  tuncer
    //  gulsah

    // ---------------------------------------------------
  }
*/

/*
  // writing first 10000 prime numbers to a file

  #include <fstream>  // std::ofstream
  #include <iostream> // std::cerr, std::left
  #include "../headers/nutility.h"
  #include <iomanip>  // std::setw

  int main()
  {
    std::ofstream ofs{ "out.txt" };
    if (!ofs) {
      std::cerr << "file can not be created\n";
      return 1;
    }

    constexpr int N = 10'000;
    int prime_count{};
    int ival{ 2 };

    ofs << std::left;

    while (prime_count < N) 
    {
      if (isprime(ival)) 
      {
        if (prime_count != 0 && prime_count % 5 == 0) 
          ofs << '\n';

        ofs << std::setw(6) << ival << ' ';
        ++prime_count;
      }

      ++ival;
    }
    
    // out.txt ->
    //  2      3      5      7      11     
    //  13     17     19     23     29     
    //  31     37     41     43     47     
    //  53     59     61     67     71     
    //  73     79     83     89     97     
    //  101    103    107    109    113
    //  ...
    //  104491 104513 104527 104537 104543 
    //  104549 104551 104561 104579 104593 
    //  104597 104623 104639 104651 104659 
    //  104677 104681 104683 104693 104701 
    //  104707 104711 104717 104723 104729
  }
*/

/*
  #include "../headers/file.h"
  #include <vector>
  #include <iterator>  // std::istream_iterator
  #include <iostream>

  int main()
  {
    auto ifs = open_text_file("out.txt");
    std::vector<int> ivec{ std::istream_iterator<int>{ ifs }, 
                           std::istream_iterator<int>{}};

    std::cout << "ivec.size() = " << ivec.size() << '\n';
    // output -> ivec.size() = 10000
  }
*/

/*
  #include "../headers/file.h"
  #include <cstddef>    // std::size_t
  #include <algorithm>  // std::copy_if
  #include <iterator>  
  // std::istream_iterator, std::ostream_iterator
  #include <string>
  #include <iostream>

  int main()
  {
    auto ifs = open_text_file("out.txt");

    std::size_t len{ 5 };

    std::copy_if(
      std::istream_iterator<std::string>{ ifs }, {},        // src 
      std::ostream_iterator<std::string>{ std::cout, "\n"}, // dest
      [len](const std::string& str){                        // pred
        return str.length() == len && str.front() == str.back();
      });

    // output ->
    // ...
    //  19501
    //  19531
    //  19541
    //  ...
    //  38543
    //  38593
    //  38603
    //  ...
    //  79357
    //  79367
    //  79397
    //  ...
    //  99719
    //  99809
    //  99829
  }
*/

/*
  // writing integers to a binary file

  #include "../headers/file.h"
  #include "../headers/nutility.h"
  #include <iostream>

  int main()
  {
    auto ofs = create_binary_file("out.dat");

    for (int i = 0; i < 1000; ++i) {
      int ival = Irand{ 0, 10000 }();
      ofs.write(reinterpret_cast< const char*>(&ival), 
                sizeof(ival));
    }
    // out.dat file's size = 4'000 byte
    // all integers are written to out.dat in binary format.
  }
*/

/*
  // reading integers from a binary file

  #include <iostream>
  #include "../headers/file.h"
  #include "../headers/nutility.h"

  int main()
  {
    auto ifs = open_binary_file("out.dat");

    int ival;
    int total_count{};

    while (ifs.read((char*)&ival, sizeof(int))) {
      std::cout << ival << '\n';
      ++total_count;
    }
    // output ->
    // ...
    //  5051
    //  3656
    //  8092

    std::cout << "total_count = " << total_count << '\n';
    // output -> total_count = 1000
  }
*/

/*
  #include "../headers/file.h"
  #include "../headers/nutility.h"

  int main()
  {
    auto ofs = create_binary_file("out.dat");

    int prime_count{};
    int ival{ 2 };    // first prime number

    while (prime_count < 1'000'000) 
    {
      if (isprime(ival)) {
        ofs.write((char*)&ival, sizeof(int));
        ++prime_count;
      }
      ++ival;
    }
    // out.dat file's size = 4'000'000 byte
  }
*/

/*
    ifs.seekg(std::streamoff, std::ios_base::seekdir);
    ifs.seekg(std::streamoff);
      - "seekg" member function has 2 overloads.

    std::ios_base::seekdir
     - std::ios::beg
     - std::ios::end
     - std::ios::cur (current)
    for changing file pointers location.
*/

/*
  #include "../headers/file.h"
  #include <iostream>   // std::ios::beg

  int main()
  {
    auto ifs = open_binary_file("out.dat");

    int N = 1111;
    int ival{};

    std::cout << N << "th prime number = ";

    ifs.seekg((N - 1) * sizeof(int));
    ifs.seekg((N - 1) * sizeof(int), std::ios::beg);
    // Those 2 lines are equivalent.

    ifs.read(reinterpret_cast<char*>(&ival), sizeof(int));
    std::cout << ival << '\n';

    // output -> 1th prime number = 2
    // output -> 11th prime number = 31
    // output -> 111th prime number = 607
    // output -> 1111th prime number = 8933
  }
*/

/*
  #include <iostream> // std::cerr, std::ios::binary
  #include <fstream>  // std::ifstream, std::ofstream
  #include <sstream>  // std::ostringstream
  #include <iomanip>  // std::setfill, std::setw

  int main(int argc, char** argv)
  {
    if (argc != 3) {
      std::cerr << 
        "usage: <file_div.exe> <filename> <chunk_size>\n";
      return 1;
    }

    std::ifstream ifs{ argv[1], std::ios::binary };
    if (!ifs) {
      std::cerr << argv[1] << " file can not be opened.\n";
      return 2;
    }

    char ch;
    int file_count{};
    int chunk_size = std::atoi(argv[2]);
    int byte_count{};

    std::ofstream ofs;

    while (ifs.get(ch)) 
    {
      if (!ofs.is_open()) {
        std::ostringstream oss;
        oss << std::setfill('0');
        oss << "part_" << std::setw(3) << ++file_count << ".par";

        ofs.open(oss.str(), std::ios::binary);
        if (!ofs) {
          std::cerr << oss.str() << " file can not be created.\n";
          return 3;
        }
      }

      ofs.put(ch);
      ++byte_count;

      if (byte_count % chunk_size == 0)
        ofs.close();
    }

    std::cout << argv[1] << " file divided into " 
              << file_count << " file each "
              << chunk_size << "bytes.";
  }
  
  // cmd -> file_div.exe out.dat 1000
  // output -> 
  //  out.dat file divided into 4000 file each 1000bytes.
*/

/*
  #include <iostream> // std::cerr, std::ios::binary
  #include <fstream>  // std::ofstream, std::ifstream
  #include <iomanip>  // std::setfill, std::setw
  #include <sstream>  // std::ostringstream
  #include <cstdio>   // std::remove

  int main(int argc, char** argv)
  {
    if (argc != 2) {
      std::cerr << "using: <file_comb.exe> <filename>\n";
      return 1;
    }

    std::ofstream ofs{ argv[1], std::ios::binary };
    if (!ofs) {
      std::cerr << argv[1] << " file can not be created.\n";
      return 2;
    }

    int file_count{};
    int byte_count{};

    while (true) 
    {
      std::ostringstream oss;
      oss << std::setfill('0');
      oss << "part_" << std::setw(3) << file_count + 1 << ".par";

      std::ifstream ifs{ oss.str(), std::ios::binary };

      if (!ifs)
        break;

      char ch;

      while (ifs.get(ch)) {
        ofs.put(ch);
        ++byte_count;
      }
      ifs.close();
      ++file_count;

      if (std::remove(oss.str().c_str())) {
        std::cerr << oss.str() << " file can not be deleted.\n";
        return 3;
      }
    }

    std::cout << file_count << " files combined to " << argv[1];
  }

  // cmd -> file_comb.exe out2.dat
  // output -> 4000 files combined to out2.dat
*/

/*
  // "rdbuf" member function returns 
  // a pointer to the buffer of a stream object.

  #include <iostream> 
  // std::ostream, std::ios::boolalpha, std::ios::uppercase
  // std::ios::showbase, std::ios::hex, std::ios::scientific
  // std::ios::floatfield

  int main()
  {
    // --------------------------------------------

    std::ostream os{ std::cout.rdbuf() };
    // "os" will use "std::cout" global stream object's buffer
    // so it will also write to standart output(console) 
    // as same as "std::cout" global std::ostream object.
    // Its format state can be differ than std::cout object.

    os.setf(std::ios::boolalpha | 
            std::ios::uppercase | 
            std::ios::showbase);

    os.setf(std::ios::hex, std::ios::basefield);
    os.setf(std::ios::scientific, std::ios::floatfield);
    os.precision(2);

    // --------------------------------------------

    int ival1 = 47802, ival2 = 57054;
    double dval = 4177.7233;

    std::cout << ival1 << ' ' 
              << ival2 << ' ' 
              << dval  << ' ' 
              << (ival1 > ival2) << '\n';
    // output -> 47802 57054 4177.72 0
      
    os  << ival1 << ' ' 
        << ival2 << ' ' 
        << dval  << ' ' 
        << (ival1 > ival2) << '\n';
    // output -> 0XBABA 0XDEDE 4.18E+03 false

    // --------------------------------------------
  }
*/

/*
  // writing main.cpp file to standart output(console)

  #include <iostream>
  #include <fstream>  // std::ifstream
  #include "../headers/file.h"

  int main()
  {
    std::ifstream ifs{ open_text_file("main.cpp") };

    std::cout << ifs.rdbuf() << '\n';
    // std::ostrem& operator<<(std::streambuf*); 
  }
*/

/*
  #include <iostream> // std::cerr
  #include <fstream>  // std::ifstream, std::ofstream

  int main(int argc, char** argv)
  {
    if (argc != 3) {
      std::cerr << "usage: <copy_file.exe> <src_file> <dest_file\n";
      return 1;
    }

    std::ifstream ifs{ argv[1], std::ios::binary };
    if (!ifs) {
      std::cerr << argv[1] << " can not be opened.\n";
      return 2;
    }

    std::ofstream ofs{ argv[2], std::ios::binary };
    if (!ofs) {
      std::cerr << argv[2] << " can not be created.\n";
      return 3;
    }

    ofs << ifs.rdbuf();
  }
  // cmd -> copy_file.exe out.dat out2.dat
*/

/*
  #include <iostream>
  #include <sstream>    // std::ostringstream

  int main()
  {
    std::ostringstream oss;

    auto cout_old_buffer = std::cout.rdbuf();
    // holding "std::cout" global object's buffer 
    // in a variable before changing it.

    std::cout.rdbuf(oss.rdbuf());
    // "std::cout" objects buffer becomes 
    // local std::ostringstream object(oss)'s buffer.

    std::cout << "world\n";
    // console output -> EMPTY
    // "world" is written to oss object's buffer
    // that is why console output is empty.

    std::cout.rdbuf(cout_old_buffer);
    std::cout << "universe\n";
    // output -> universe

    auto str = oss.str();
    std::cout << str << '\n';
    // output -> world
  }
*/

/*
  #include "../headers/file.h"
  #include <fstream>    // std::ifstream
  #include <sstream>    // std::ostringstream
  #include <ctype.h>    // std::isspace
  #include <algorithm>  // std::remove_if, std::erase_if
  #include <iostream> 

  int main()
  {
    std::ifstream ifs{ open_text_file("main.cpp") };

    std::ostringstream oss;
    oss << ifs.rdbuf();
    // oss object's buffer is filled with ifs object's buffer.

    auto str = oss.str();

    // ---------- remove-erase idiom OLD WAY ----------

    str.erase(std::remove_if(str.begin(), str.end(), 
                            [](char ch){ return std::isspace(ch);}), 
              str.end());

    // ---------- remove-erase idiom NEW WAY ----------

    std::erase_if(str, [](char ch){ return std::isspace(ch); });

    // ------------------------------------------------

    std::cout << str << '\n';
  }
*/

/*
  #include <iostream>

  int main()
  {
    using namespace std;

    try
    {
      int x{};
      std::cout << "enter an integer: ";
      cin >> x;
      std::cout << "x = " << x << '\n';
    }
    catch (const ios_base::failure& ex)
    {
      cout << "ios_base::failure caught: " << ex.what() << '\n';
    }
    catch (const std::exception& ex)
    {
      cout << "exception caught: " << ex.what() << '\n';
    }

    // input -> enter an integer: hello
    // x = 0 
    // terminate called after throwing an instance of 
    //  'std::__ios_failure'
    // what():  basic_ios::clear: iostream error

    // exception CAN NOT be caught.
  }
*/

/*
  #include <iostream>

  int main()
  {
    using namespace std;

    cin.exceptions(ios::failbit | ios::eofbit | ios::badbit);

    try
    {
      int x{};
      std::cout << "enter an integer: ";
      cin >> x;
      std::cout << "x = " << x << '\n';
    }
    catch (const ios_base::failure& ex)
    {
      cout << "ios_base::failure caught: " << ex.what() << '\n';
    }
    catch (const std::exception& ex)
    {
      cout << "exception caught: " << ex.what() << '\n';
    }

    // input -> enter an integer: hello
    // ios_base::failure caught: basic_ios::clear: iostream error

    // exception CAN be caught.
  }
*/

/*
  #include <iostream>

  int main()
  {
    using namespace std;

    auto default_iostate = cin.exceptions();

    if (default_iostate == 0)
      std::cout << "it will NOT throw an exception.\n";
    // output -> it will NOT throw an exception.

    // ----------------------------------------------

    if (default_iostate & ios::failbit)
      std::cout << "failbit is set, will throw exception.\n";
    else
      std::cout << "failbit is not set. NO exception thrown.\n";
    // output -> failbit is not set. NO exception thrown.

    // ----------------------------------------------

    default_iostate = default_iostate | ios::failbit;

    if (default_iostate & ios::failbit)
      std::cout << "failbit is set, will throw exception.\n";
    // output -> failbit is set, will throw exception.

    // ----------------------------------------------
  }
*/

/*
  #include <iostream>   
  // std::istream, std::ios::failbit, std::ios::badbit
  #include <sstream>    // std::istringstream
  #include <stdexcept>  // std::exception

  double readsum(std::istream& is)
  {
    auto is_old_iostate = is.exceptions();
    is.exceptions(std::ios::failbit | std::ios::badbit);
    
    double dval, sum{};

    try {
      while (is >> dval)
        sum += dval;
    }
    catch (...) {
      if (!is.eof()) {
        is.exceptions(is_old_iostate);
        throw;
      }
    }

    is.exceptions(is_old_iostate);

    return sum;
  }

  int main()
  {
    // -------------------------------------------------

    std::istringstream iss1{ "1.1 2.2 3.3 4.4 5.5 6.6" };

    double sum1;
    try {
      sum1 = readsum(iss1);
      std::cout << "sum1 = " << sum1 << '\n';
    }
    catch (const std::ios::failure& ex) {
      std::cerr << "input output error: " << ex.what() << '\n';
      return 1;
    }
    catch (const std::exception& ex) {
      std::cerr << "standart library error: " << ex.what() << '\n';
      return 2;
    }
    catch (...) {
      std::cerr << "unknown error\n";
      return 3;
    }
    // output -> sum1 = 23.1

    // -------------------------------------------------

    std::istringstream iss2{ "1.1 2.2 3.3 4.4 hello 5.5 6.6" };

    double sum2;
    try {
      sum2 = readsum(iss2);
      std::cout << "sum2 = " << sum2 << '\n';
    }
    catch (const std::ios::failure& ex) {
      std::cerr << "input output error: " << ex.what() << '\n';
      return 1;
    }
    catch (const std::exception& ex) {
      std::cerr << "standart library error: " << ex.what() << '\n';
      return 2;
    }
    catch (...) {
      std::cerr << "unknown error\n";
      return 3;
    }
    // output -> 
    //  input output error: basic_ios::clear: iostream error

    // -------------------------------------------------
  }
*/