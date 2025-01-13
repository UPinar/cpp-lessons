#include <iostream>

/*
                  ===============================
                  | User Defined Literals (UDL) |
                  ===============================
*/

/*
  https://en.cppreference.com/w/cpp/language/user_literal

  -------------------------------------------------------

  - user defined literals must have an '_'(underscore) character.
    operator""_identifier

  -------------------------------------------------------

  - there are rules for UDL function parameter,
    -> for integer types        -> unsigned long long
    -> for floating point types -> long double


  -------------------------------------------------------

  cooked UDL : 46_KB 
    46 will pass to the function as an argument.

  uncooked UDL : 46_KB = 
    "46_KB" string will pass to the function as an argument.

  -------------------------------------------------------
*/

/*
                          --------------
                          | cooked UDL |
                          --------------
*/

/*
  constexpr double operator""_cm(long double val)
  {
    return static_cast<double>(val / 100);
  }

  constexpr double operator""_m(long double val)
  {
    return static_cast<double>(val);
  }

  constexpr double operator""_km(long double val)
  {
    return static_cast<double>(val * 1000);
  }

  int main()
  {
    constexpr auto distance1 = 234.34_m + 0.123_km + 345.91_cm;
    constexpr auto distance2 =  operator""_m(234.34) + 
                                operator""_km(0.123) + 
                                operator""_cm(345.91);
    // distance1 -> 360.7991
    // distance2 -> 360.7991

    // Those 2 lines are equivalent.
  }
*/

/*
  #include <algorithm>  // std::replace
  #include <sstream>    // std::istringstream
  #include <string>

  class Date {
  private:
    int m_day{};
    int m_mon{};
    int m_year{};
  public:
    Date() = default;
    Date(int d, int m, int y) 
      : m_day{ d }, m_mon{ m }, m_year{ y } {}

    Date(std::string str)
    {
      std::replace(str.begin(), str.end(), '_', ' ');

      std::istringstream iss{ str };
      int temp = 0;

      while (iss >> temp)
      {
        if (!m_day)
          m_day = temp;
        else if (!m_mon)
          m_mon = temp;
        else
          m_year = temp;
      }
    }

    friend std::ostream& operator<<(std::ostream& os, 
                                    const Date& date)
    {
      return os << "( " << date.m_day 
                << ", " << date.m_mon 
                << ", " << date.m_year << " )";
    }
  };

  Date operator""_dt(const char* p_str, size_t N)
  {
    std::cout << "N = " << N << '\n';
    return Date{ p_str };
  }

  int main()
  {
    std::cout << "12_05_1987"_dt;
    // output -> 
    //  N = 10
    //  ( 12, 5, 1987 )
  }
*/

/*
  #include <numbers>  // std::numbers::pi_v

  constexpr long double operator""_deg_to_rad(long double deg)
  {
    using namespace std::numbers;
    long double radians = deg * pi_v<long double> / 100;
    return radians;
  }

  int main()
  {
    constexpr auto rad = 180._deg_to_rad;
    // rad -> 5.654866776461628L

    std::cout << "rad = " << rad << '\n';
    // output -> rad = 5.65487
  }
*/

/*
  constexpr int operator""_i(char ch)
  {
    return ch;
  }

  int main()
  {
    std::cout << 'A'_i <<  '\n';    // output -> 65
    std::cout << '\n'_i <<  '\n';   // output -> 10
    std::cout << '+'_i <<  '\n';    // output -> 43

    constexpr auto ch = 'A'_i;
    // ch -> 65
  }
*/

/*
/*
  #include <complex>

  int main()
  {
    using namespace std;

    auto complex = 5.6i;    // operator""i(5.6)"
    // c's type is -> std::complex<double>
  }
*/

/*
  #include <string>
  #include <cstddef>  // std::size_t

  std::string operator""_s2(const char* p_str, std::size_t)
  {
    return std::string{ p_str } + p_str;
    // '+' operator is left associative
    // std::string + const char* -> std::string
  }

  std::string operator""_s3(const char* p_str, std::size_t)
  {
    return std::string{ p_str } + p_str + p_str;
  }

  std::string operator""_s4(const char* p_str, std::size_t)
  {
    return std::string{ p_str } + p_str + p_str + p_str;
  }

  int main()
  {
    std::cout << "hello"_s2 << '\n';
    // output -> hellohello
    std::cout << "hello"_s3 << '\n';
    // output -> hellohellohello
    std::cout << "hello"_s4 << '\n';
    // output -> hellohellohellohello
  }
*/

/*
  #include <iostream>   // std::ostream

  class Meters {
  private:
    double m_meters;

  public:
    class PreventUsage {};
    explicit constexpr Meters(PreventUsage, double m) 
      : m_meters{ m } {}

    explicit constexpr operator double() const 
    { 
      return m_meters; 
    }
  };

  constexpr Meters operator""_meter(long double m) 
  {
    return Meters(Meters::PreventUsage(), 
                  static_cast<double>(m));
  }

  std::ostream& operator<<( std::ostream& os, 
                            const Meters& m)
  {
    return os << static_cast<double>(m) << " meters";
  }

  int main()
  {
    // ------------------------------------------------------

    Meters m1{ 11.22 }; // syntax error
    // error: no matching function for call to 
    // 'Meters::Meters(<brace-enclosed initializer list>)'

    // ------------------------------------------------------

    constexpr auto m1 = 22.33_meter;
    // "operator""_meter" function is calling 
    // constexpr Meters constructor.

    // ------------------------------------------------------

    double dval = m1;   // syntax error
    // error: cannot convert 'const Meters' to 'double' 
    // in initialization
    // note: explicit conversion function was not considered

    double dval_valid = static_cast<double>(m1);  // VALID

    // ------------------------------------------------------
  }
*/

/*
                        ----------------
                        | uncooked UDL |
                        ----------------
*/

/*
  #include <cstring>    // std::strlen
  #include <cctype>     
  // std::isdigit, std::isxdigit, std::toupper
  #include <string>
  #include <stdexcept>  // std::runtime_error

  int operator""_len(const char* p_str)
  {
    std::cout << "std::strlen(p_str) = " 
              << std::strlen(p_str) << '\n';
    return 0;
  }

  int operator""_hex_to_dec(const char* p_str)
  {
    int ret{};

    while (*p_str) 
    {
      if (std::isdigit(*p_str))
        ret = ret * 16 + (*p_str - '0');
      else if (std::isxdigit(*p_str))
        ret = ret * 16 + std::toupper(*p_str) - 'A' + 10;

      ++p_str;
    }

    return ret;
  }

  constexpr int operator""_bin_to_dec(const char* p_str)
  {
    int ret{};

    while (*p_str) 
    {
      if (!(*p_str == '0' || *p_str == '1'))
        throw std::runtime_error{ "bad binary constant" };
      ret = ret * 2 + *p_str - '0';
      ++p_str;
    }
    return ret;
  }

  int main()
  {
    // ------------------------------------------------------

    12345_len;  // output -> std::strlen(p) = 5
    123_len;    // output -> std::strlen(p) = 3

    // ------------------------------------------------------

    auto val1 = 1234_hex_to_dec;  
    std::cout << "val1 = " << val1 << '\n';
    // output -> val1 = 4660

    auto val2 = 8373_hex_to_dec;
    std::cout << "val2 = " << val2 << '\n';
    // output -> 33651

    // ------------------------------------------------------

    auto val3 = 1111_bin_to_dec;
    std::cout << "val3 = " << val3 << '\n';
    // output -> 15

    auto val4 = 11111111_bin_to_dec;
    std::cout << "val4 = " << val4 << '\n';
    // output -> 255

    try {
      auto val5 = 1113111_bin_to_dec;
      std::cout << "val5 = " << val5 << '\n';
    }
    catch (const std::exception& ex){
      std::cout << "exception caught: " << ex.what() << '\n';
    }
    // output -> exception caught: bad binary constant

    // ------------------------------------------------------
  }
*/