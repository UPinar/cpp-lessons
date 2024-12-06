#include <iostream>

/*
                        ===================
                        | <bitset> module |
                        ===================
*/

/*
  - std::bitset is a class template
  - std::bitset is a zero cost abstraction class
  - generally used in embedded systems and system programming.
*/

/*
  template <std::size_t N>  // NTTP(Non Type Template Parameter)
  class Bitset {};
*/

/*
  // inserter function (operator<<)

  #include <bitset>

  int main()
  {
    std::bitset<8> bs_1;
    std::cout << bs_1 << '\n';    
    // output -> 00000000
    
    std::bitset<32> bs_2(872345u);
    std::cout << bs_2 << '\n';
    // output -> 00000000000011010100111110011001

    std::bitset<8> bs_3("11111111");
    std::cout << bs_3 << '\n';
    // output -> 11111111
  }
*/

/*
  #include <bitset>

  int main()
  {
    // ------------------------------------------

    std::bitset<8> bs("11111111");
    std::cout << bs << '\n';
    // output -> 11111111

    bs[7] = 0;
    std::cout << bs << '\n';
    // output -> 01111111

    bs.operator[](4) = 0;
    std::cout << bs << '\n';
    // output -> 01101111

    // ------------------------------------------

    // std::bitset classes opetator[] member function
    // returns a proxy class that have those member functions,
    //  - flip
    //  - operator bool
    //  - operator=
    //  - operator~

    // ------------------------------------------

    bs[6] = false;       
    // "operator=" member function

    std::cout << bs << '\n';  
    // output -> 00101111

    bs[5] = bs[6];
    // "operator=" member function

    std::cout << bs << '\n';
    // output -> 00001111

    // ------------------------------------------

    bs[3] = bs.operator[](3).operator~();
    // "operator~" member function

    std::cout << bs << '\n';
    // output -> 00000111

    // ------------------------------------------

    std::cout << std::boolalpha;

    std::cout << bs[4] << '\n';     
    // output -> false
    // "operator bool" member function
    
    std::cout << bs.operator[](1).operator bool() << '\n';
    // output -> true
    // "operator bool" member function

    // ------------------------------------------
  }
*/

/*
  #include <bitset>

  int main()
  {
    std::bitset<16> bs("010101101010011");

    auto elem = bs[5];
    // elem's data type is std::bitset<16>::reference
    // which is a proxy class

    bool b1 = bs[5].operator bool();
    // proxy class(std::bitset<16>::reference) 
    // does have an "operator bool" member function
    // its return type is bool

    std::cout << std::boolalpha << b1 << '\n';
    // b1 -> false
  }
*/

/*
  #include <bitset>

  int main()
  {

    constexpr std::bitset<8> bs_1("00101000");
    constexpr std::bitset<8> bs_2("00000000");
    constexpr std::bitset<8> bs_3;
    constexpr std::bitset<8> bs_4("11111111");

    // --------------------------------------------------

    // std::bitset classes "any" member function,  
    // returns true if any bit is set
    // returns false if all bits are cleared.

    constexpr bool any_1 = bs_1.any();    // any_1 - > true
    constexpr bool any_2 = bs_2.any();    // any_2 - > false
    constexpr bool any_3 = bs_3.any();    // any_3 - > false
    constexpr bool any_4 = bs_4.any();    // any_4 - > true

    // --------------------------------------------------

    // std::bitset classes "none" member function,
    // returns true if all bits are cleared
    // returns false if any bit is set.

    constexpr bool none_1 = bs_1.none();  // none_1 -> false
    constexpr bool none_2 = bs_2.none();  // none_2 -> true
    constexpr bool none_3 = bs_3.none();  // none_3 -> true
    constexpr bool none_4 = bs_4.none();  // none_4 -> false

    // --------------------------------------------------

    // std::bitset classes "all" member function,
    // returns true if all bits are set
    // returns false if any bit is cleared.

    constexpr bool all_1 = bs_1.all();    // all_1 -> false
    constexpr bool all_2 = bs_2.all();    // all_2 -> false
    constexpr bool all_3 = bs_3.all();    // all_3 -> false
    constexpr bool all_4 = bs_4.all();    // all_4 -> true

    // --------------------------------------------------

    // std::bitset classes "count" member function,
    // returns the number of set bits.

    constexpr size_t count_1 = bs_1.count();  // count_1 -> 3
    constexpr size_t count_2 = bs_2.count();  // count_2 -> 0
    constexpr size_t count_3 = bs_3.count();  // count_3 -> 0
    constexpr size_t count_4 = bs_4.count();  // count_4 -> 8

    // --------------------------------------------------

    // std::bitset classes "set" member function returns *this
    // if no argument passed all bits will be set.

    std::bitset<8> bs_5;
    std::bitset<8> bs_6("00001111");

    bs_5.set();
    bs_6.set();
    
    std::cout << bs_5 << '\n';  // output -> 11111111
    std::cout << bs_6 << '\n';  // output -> 11111111

    // set(size_t, bool = true) member function

    std::bitset<8> bs_7("00001111");
    std::cout << bs_7 << '\n';  // output -> 00001111

    bs_7.set(7, 1);
    // bit 7 will be set(1)
    std::cout << bs_7 << '\n';  // output -> 10001111

    bs_7.set(6);
    // bit 6 will be set(1)
    std::cout << bs_7 << '\n';  // output -> 11001111

    bs_7.set(0, 0);
    // bit 0 will be cleared(0)
    std::cout << bs_7 << '\n';  // output -> 11001110

    // --------------------------------------------------

    // std::bitset classes "operator~" member function 

    std::bitset<8> bs_8; // default initialization
    // all bits are cleared

    bs_8 = ~bs_8;
    std::cout << bs_8 << '\n';  // output -> 11111111

    bs_8 = bs_8.operator~();
    std::cout << bs_8 << '\n';  // output -> 00000000

    // Those 2 lines are equivalent.

    // --------------------------------------------------

    // std::bitset classes "reset" member function

    std::bitset<8> bs_9("11111111");

    bs_9.reset(3);
    // bit 3 will be cleared(0)
    std::cout << bs_9 << '\n';    // output -> 11110111

    bs_9.reset();
    // all bits will be cleared(0)
    std::cout << bs_9 << '\n';    // output -> 00000000

    // --------------------------------------------------

    // std::bitset classes "flip" member function

    std::bitset<8> bs_10;

    bs_10.flip();
    // all bits will be flipped
    std::cout << bs_10 << '\n';   // output -> 11111111

    bs_10.flip(3);
    // bit 3 will be flipped
    std::cout << bs_10 << '\n';   // output -> 11110111

    // --------------------------------------------------
  }
*/

/*
  #include <bitset>

  int main()
  {
    std::bitset<32> b_x{ 87345u };
    std::bitset<32> b_y{ 803459344u };

    // --------------------------------------------

    std::cout << b_x << '\n';
    std::cout << b_y << '\n';
    std::cout << (b_x & b_y) << '\n';
    // output ->
    //  00000000000000010101010100110001
    //  00101111111000111101000100010000
    //  00000000000000010101000100010000

    std::cout << '\n';

    // --------------------------------------------

    std::cout << b_x << '\n';
    std::cout << b_y << '\n';
    std::cout << (b_x | b_y) << '\n';

    // output ->
    //  00000000000000010101010100110001
    //  00101111111000111101000100010000
    //  00101111111000111101010100110001

    std::cout << '\n';

    // --------------------------------------------

    std::cout << b_x << '\n';
    std::cout << b_y << '\n';
    std::cout << (b_x ^ b_y) << '\n';

    // output ->
    //  00000000000000010101010100110001
    //  00101111111000111101000100010000
    //  00101111111000101000010000100001

    // --------------------------------------------
  }
*/

/*
  #include <bitset>

  int main()
  {
    std::bitset<8> bx{ "00001111"};

    std::cout << bx << '\n';
    // output -> 00001111

    bx <<= 3;
    std::cout << bx << '\n';  
    // output -> 01111000

    // --------------------------------------------

    bx.set();
    std::cout << bx << 5 << '\n';   
    // output -> 111111115

    // --------------------------------------------

    std::cout << (bx << 5) << '\n';   
    // output -> 11100000

    bx.set();
    operator<<(std::cout, bx.operator<<(5));
    // output -> 11100000

    // Those 2 lines are equivalent.

    // --------------------------------------------
  }
*/

/*
  #include <bitset>

  int main()
  {
    try
    {
      std::bitset<16> bs{ "1010001020100101" };
      // '2' inside the string is invalid
    }
    catch (const std::exception& ex)
    {
      std::cout << "exception caught : " << ex.what() << '\n';
    }
    // output -> exception caught : bitset::_M_copy_from_ptr
  }
*/

/*
  #include <bitset>
  #include <string>
  #include <algorithm>  // std::copy
  #include <iterator>   // std::ostream_iterator

  int main()
  {

    std::bitset<16> bs{ 2362369u };

    std::string str = bs.to_string();

    std::copy(str.begin(), str.end(), 
              std::ostream_iterator<char>{ std::cout, " " });
    // output -> 0 0 0 0 1 1 0 0 0 0 0 0 0 0 0 1
  }
*/

/*
  #include <bitset>

  int main()
  {
    std::bitset<16> bs{ "110100101001011" };

    unsigned long ulval = bs.to_ulong();
    std::cout << ulval << '\n';   // output -> 26955
  }
*/

/*
  #include <bitset>
  #include <set>

  int main()
  {
    std::bitset<32> bs_1{ "110100101001" };
    std::bitset<32> bs_2{ "111100101001" };

    // --------------------------------------------------

    bool b1 = (bs_1 == bs_2);
    // std::bitset have operator== and operator!= member functions

    // --------------------------------------------------

    bool b2 = (bs_1 < bs_2);  // syntax error
    // error: no match for 'operator<' 
    // (operand types are 'std::bitset<32>' and 'std::bitset<32>')

    // --------------------------------------------------

    std::set<std::bitset<16>> bs_set;

    bs_set.insert(8712);  // syntax error
    // error: no match for 'operator<' 
    // (operand types are 'const std::bitset<16>' and 
    //                    'const std::bitset<16>')

    // std::set container's 2nd template parameter is 
    // Comparator parameter, because of default comparator
    // is std::less<std::bitset<16>> will call 
    // operator< member function of std::bitset<16> class.
    // which is not defined, it will cause a syntax error.

    // --------------------------------------------------
  }
*/

/*
  #include <bitset>
  #include <set>

  int main()
  {
    auto fn_cmp = [](std::bitset<16> bs_1, std::bitset<16> bs_2){
      return bs_1.to_ulong() < bs_2.to_ulong();
    };

    std::set<std::bitset<16>, decltype(fn_cmp)> bs_set;
    bs_set.insert(8172);
    bs_set.insert(3456);
    bs_set.insert(121);
    bs_set.insert(254);
    bs_set.insert(29054);

    for (auto bs : bs_set)
      std::cout << bs << " - " << bs.to_ulong() <<  '\n';
    // output ->
    //  0000000001111001 - 121
    //  0000000011111110 - 254
    //  0000110110000000 - 3456
    //  0001111111101100 - 8172
    //  0111000101111110 - 29054
  }
*/