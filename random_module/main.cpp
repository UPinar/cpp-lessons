#include <iostream>

/*
                        ===================
                        | <random> module |
                        ===================
*/

/*
  #include <random> // std::mt19937

  int main()
  {
    std::mt19937;
    // std::mersenne_twister_engine<unsigned int, 32, 
    // 624, 397, 31, 0x9908b0df, 11, 0xffffffff, 7,
    // 0x9d2c5680, 15, 0xefc60000, 18, 1812433253>;

    // std::mt19937 is a template specialization of
    // std::mersenne_twister_engine class template.
  }
*/

/*
  #include <random> // std::mt19937

  int main()
  {
    std::mt19937 eng;
    // std::mt19937 is a functor class 
    // (have an operator call function)

    for (int i = 0; i < 5; ++i)
      std::cout << eng() << '\n';
    // output ->
    //  3499211612
    //  581869302
    //  3890346734
    //  3586334585
    //  545404204
  }
*/

/*
  https://en.cppreference.com/w/cpp/numeric/
  random/mersenne_twister_engine

  The Nth consecutive invocation of a default-constructed engine
  is required to produce the following values:
  10000  std::mt19937    4123659995
  10000  std::mt19937_64   9981545732273789042
*/


/*
  #include <random>   // std::mt19937

  int main()
  {
    // --------------------------------------------

    std::mt19937 eng1;

    for (int i = 0; i < 10000 - 1; ++i)
      eng1();
    
    std::cout << eng1() << '\n';
    // output -> 4123659995

    // --------------------------------------------

    std::mt19937_64 eng2;

    for (int i = 0; i < 10000 - 1; ++i)
      eng2();

    std::cout << eng2() << '\n';
    // output -> 9981545732273789042

    // --------------------------------------------
  }
*/

/*
  #include <random>   // std::mt19937

  int main()
  {
    std::mt19937 eng;
    std::cout << "sizeof(eng) = " << sizeof(eng) << '\n';
    // output -> sizeof(eng) = 2504

    // its size is 2504 bytes which is too big
    // better not to copy it!
  }
*/

/*
  #include <random>   // std::mt19937
  #include <bitset>

  int main()
  {
    std::mt19937 eng;

    for (int i = 0; i < 5; ++i)
      std::cout << std::bitset<32>(eng()) << '\n';
    // output ->
    //  11010000100100011011101101011100
    //  00100010101011101001111011110110
    //  11100111111000011111101011101110
    //  11010101110000110001111101111001
    //  00100000100000100011010100101100

    // random engine's job is generating 32 bits random numbers
  }
*/

/*
  #include <random>   // std::mt19937

  int main()
  {
    // --------------------------------------------

    std::mt19937 eng1;
    std::mt19937 eng2{ 5489 };
    // Those 2 lines are equivalent.

    eng1.default_seed;
    // constexpr static data member "default_seed" -> 5489U

    // --------------------------------------------

    std::mt19937 eng3{ 87345345u };
    // passing a seed value to the constructor

    eng3.seed(34985u);
    // changing seed value after construction
    // with "seed" member function

    // --------------------------------------------
  }
*/

/*
  #include <random>   // std::mt19937

  int main()
  {
    std::mt19937 eng;
    // value chain that std::mt19937 template specialization 
    // will generate is deterministic.

    eng.discard(9999);
    // "discard" member function can be used 
    // for discarding first N elements in chain

    std::cout << eng() << '\n'; 
    // output -> 4123659995

    // 4123659995 is the 10000th element in the chain
  }
*/

/*
  #include <random>   // std::mt19937, std::mt19937_64

  int main()
  {
    // "min" and "max" static member functions

    // --------------------------------------------

    std::cout << std::mt19937::min() << '\n';
    // output -> 0
    std::cout << std::mt19937::max() << '\n';
    // output -> 4294967295 (4 byte unsigned int max)

    // --------------------------------------------

    std::cout << std::mt19937_64::min() << '\n';
    // output -> 0

    std::cout << std::mt19937_64::max() << '\n';
    // output -> 18446744073709551615 (8 byte unsigned int max)

    // --------------------------------------------
  }
*/

/*
  #include <random>  // std::mt19937

  void check_states(std::mt19937& lhs, std::mt19937& rhs)
  {
    if (lhs == rhs)
      std::cout << "same states.\n";
    else
      std::cout << "different states.\n";
  }

  int main()
  {
    std::mt19937 eng1;
    std::mt19937 eng2;

    check_states(eng1, eng2);
    // output -> same states

    auto x = eng1();
    check_states(eng1, eng2);
    // output -> different states

    x = eng2();
    check_states(eng1, eng2);
    // output -> same states
  }
*/

/*
  // serialization AND deserialization

  #include <random>   // std::mt19937
  #include <sstream>  // std::stringstream

  int main()
  {
    std::mt19937 eng;

    std::stringstream ss;
    ss << eng;
    // inserting RNG object's default state 
    // to std::stringstream object

    for (int i = 0; i < 5; ++i) 
      std::cout << eng() << '\n';
    // output ->
    //  3499211612
    //  581869302
    //  3890346734
    //  3586334585
    //  545404204

    std::cout << '\n';

    ss >> eng;
    // transfering back the default state to "eng" object

    for (int i = 0; i < 5; ++i) 
      std::cout << eng() << '\n';
    // output ->
    //  3499211612
    //  581869302
    //  3890346734
    //  3586334585
    //  545404204
  }
*/

/*
  #include <random>   // std::random_device

  int main()
  {
    std::random_device rd;
    // if compiler is supporting non-deterministic RNG
    // otherwise deterministic RNG will be used.

    for (int i = 0; i < 5; ++i)
      std::cout << rd() << '\n';
    // output 1st time when program executed ->
    //  88988871
    //  3258420904
    //  2083117009
    //  3600273088
    //  923013841

    // output 2nd time when program executed ->
    //  3841257185
    //  3895678581
    //  904337688
    //  113850685
    //  134465762

    // --------------------------------------------

    std::cout << rd.entropy() << '\n';
    // output -> 0
    // if class generates deterministic numbers
    // "entropy" member function will return 0
    // else class generates non-deterministic numbers

    // https://en.cppreference.com/w/cpp/numeric/random/
    // random_device/entropy

    // --------------------------------------------
  }
*/

/*
  #include <random>   // std::mt19937, std::random_device

  int main()
  {
    std::mt19937 eng{ std::random_device{}() };
    // everytime program is being executed,
    // RNG will be seeded with a non-deterministic value,
    // which has been generated by 
    // std::random_device object's "operator()" function

    for (int i = 0; i < 5; ++i)
      std::cout << eng() << '\n';
    
    // output 1st time when program executed ->
    //  3410814925
    //  2553118525
    //  2558982597
    //  2843193181
    //  3712505266

    // output 2nd time when program executed ->
    //  3106130106
    //  2609663701
    //  1258939597
    //  2786524694
    //  373778663
  }
*/

/*
  #include <random>   // std::mt19937, std::random_device
  #include <chrono>

  int main()
  {
    using namespace std;
    using namespace std::chrono;

    cout << system_clock::now().time_since_epoch().count() << '\n';
    // returns non-deterministic value 
    // depends on the time change.

    mt19937 eng(system_clock::now().time_since_epoch().count());

    for (int i = 0; i < 5; ++i)
      cout << eng() << '\n';
    // output 1st time when program executed ->
    //  1736813295484835700
    //  3410814925
    //  2553118525
    //  2558982597
    //  2843193181
    //  3712505266

    // output 2nd time when program executed ->
    //  1736813316619836900
    //  1045429647
    //  3926864955
    //  2280380637
    //  507196519
    //  1865700600
  }
*/

/*
  // generating backgammon dice values

  #include <random>  
  // std::mt19937, std::minstd_rand, std::uniform_int_distribution

  int main()
  {
    // --------------------------------------------

    std::uniform_int_distribution<int> dist1{ 1, 6 };
    std::uniform_int_distribution<> dist2{ 1, 6 };
    std::uniform_int_distribution dist3{ 1, 6 };  // CTAD
    // Those 3 lines are equivalent.

    // --------------------------------------------

    std::mt19937 eng1;
    for (int i = 0; i < 6; ++i)
      std::cout << dist1(eng1) << ' ';
    // output -> 1 6 6 1 6 6

    std::cout << '\n';

    // --------------------------------------------
    std::minstd_rand eng2;

    for (int i = 0; i < 6; ++i)
      std::cout << dist1(eng2) << ' ';
    // output -> 1 1 4 6 6 2

    // --------------------------------------------
  }
*/

/*
  #include <map>
  #include <random>   
  // std::mt19937, std::uniform_int_distribution

  int main()
  {
    std::mt19937 eng;
    std::uniform_int_distribution<int> dist{ 1, 6 };

    std::map<int, int> count_map;

    for (int i = 0; i < 10'000'000; ++i)
      ++count_map[dist(eng)];

    for (const auto& [value, count] : count_map)
      std::cout << value << " - " << count << '\n';

    // output ->
    //  1 - 1666708
    //  2 - 1666465
    //  3 - 1667497
    //  4 - 1664921
    //  5 - 1667321
    //  6 - 1667088
  }
*/

/*
  // generating temperature values

  #include <iomanip>  // std::fixed, std::setprecision
  #include <random>  
  // std::mt19937, std::uniform_real_distribution

  int main()
  {
    std::mt19937 eng;
    std::uniform_real_distribution<double> dist{ 10.0, 45.0 };

    std::cout << std::fixed << std::setprecision(2) << '\n';

    for (int i = 0; i < 10; ++i)
      std::cout << dist(eng) << '\n';
    // output ->
    //  14.74
    //  39.23
    //  43.91
    //  17.74
    //  20.79
    //  29.15
    //  16.59
    //  44.75
    //  44.88
    //  43.87
  }
*/

/*
  // <---- check histogram.png ---->  

  #include <random>   // std::mt19937, std::normal_distribution
  #include <map>
  #include <fstream>  // std::ofstream
  #include <cstdlib>  // std::exit, EXIT_FAILURE
  #include <iomanip>  
  // std::fixed, std::setprecision, std::setfill, std::setw
  #include <cmath>    // std::round
  #include <string>

  int main()
  {
    std::mt19937 eng;
    std::normal_distribution<> norm_dist{ 50., 5. };

    std::ofstream ofs{ "out.txt" };
    if (!ofs) {
      std::cerr << "couldn't create out.txt\n";
      std::exit(EXIT_FAILURE);
    }
    ofs << std::fixed << std::setprecision(4);

    std::map<int, int> count_map;
    constexpr int N = 1'000'000;

    for (int i = 0; i < N; ++i)
      ++count_map[static_cast<int>(std::round(norm_dist(eng)))];

    ofs << std::setfill('0');
    for (const auto& [key, count] : count_map) {
      ofs << std::setw(2) << key << " " 
          << std::string(count / 1000, '*') << '\n';
    }
  }
*/


/*
  #include <random>
  // std::mt19937, std::normal_distribution, 
  // std::uniform_int_distribution

  int main()
  {
    // ---------------------------------------------------

    std::normal_distribution<> norm_dist1{ 70., 10. };

    std::normal_distribution<> norm_dist2(dist1.param());
    // "param" member function returns distribution object's 
    // parameters which can be used to initialize another.

    // ---------------------------------------------------

    dist.mean();    // arithmetic mean
    // 1st parameter of the std::normal_distribution 
    // object's constructor.

    dist.sigma();   // standard deviation
    // 2nd parameter of the std::normal_distribution
    // object's constructor.

    // ---------------------------------------------------

    std::uniform_int_distribution<> uni_dist{ 20,70 };

    dist3.min();
    // 1st parameter of the std::uniform_int_distribution 
    // object's constructor.

    dist3.max();
    // 2nd parameter of the std::uniform_int_distribution
    // object's constructor.

    // ---------------------------------------------------
  }
*/

/*
  #include <random>  // std::mt19937, std::discrete_distribution
  #include <map>

  int main()
  {
    std::mt19937 eng;
    std::discrete_distribution<int> dist{ 1, 1, 1, 1, 1, 2 };

    std::map<int, int> count_map;

    for (int i = 0; i < 1'000'000; ++i)
      ++count_map[dist(eng)];
    
    for (const auto& [val, count] : count_map)
      std::cout << val << " " << count << '\n';

    // output ->
    //  0 142876
    //  1 142569
    //  2 143129
    //  3 142766
    //  4 142826
    //  5 285834    ---> 
  }
*/

/*
  // tricked dice simulation using std::discrete_distribution

  #include <random>  // std::mt19937, std::discrete_distribution
  #include <map>

  int main()
  {
    std::mt19937 eng;
    std::discrete_distribution<int> dist{ 0, 10, 10, 10, 10, 10, 11 };

    std::map<int, int> count_map;

    for (int i = 0; i < 1'000'000; ++i)
      ++count_map[dist(eng)];
    
    for (const auto& [val, count] : count_map)
      std::cout << val << " " << count << '\n';

    // output ->
    //  1 163789
    //  2 163732
    //  3 164235
    //  4 164140
    //  5 163863
    //  6 180241  ---> 
  }
*/

/*
  #include <iostream>
  #include <random>
  #include <iterator> // std::begin, std::end
  #include <map>  
  #include <iomanip>  // std::setfill, std::setw

  int main()
  {
    double arr[12] = { 
      10, 10, 11, 10, 10, 11, 10, 10, 11, 10, 10, 11 };
    // months of the year

    std::mt19937 eng;
    std::discrete_distribution<> dist{  std::begin(arr), 
                                        std::end(arr) };

    std::map<int, int> count_map;

    for (int i = 0; i < 10'000'000; ++i)
      ++count_map[dist(eng)];

    std::cout << std::setfill('0');
    for (const auto& [val, count] : count_map)
      std::cout << std::setw(2) << val + 1 << " " << count << '\n';

    // output ->
    //  01 805604
    //  02 807578
    //  03 887043 --->
    //  04 807440
    //  05 807375
    //  06 888123 --->
    //  07 803674
    //  08 806384
    //  09 886595 --->
    //  10 807402
    //  11 806618
    //  12 886164 --->
  }
*/

/*
  // Produces random boolean values, 
  // according to the discrete probability function.

  #include <random>
  // std::bernoulli_distribution, std::mt19937

  void func(auto& dist_obj)
  {
    std::mt19937 eng;
    int count{};
    for (int i = 0; i < 10'000'000; ++i)
      count += dist_obj(eng) ? 1 : 0;

    std::cout << count << '\n';
  }

  int main()
  {
    std::bernoulli_distribution dist1{ 0.5 };
    func(dist1);  // output -> 5003163
    // 0.5 is uniform distribution

    std::bernoulli_distribution dist2{ 0.8 };
    func(dist2);  // output -> 8000408
  }
*/

/*
            -----------------------------------------------
            | algorithms used in random number generation |
            -----------------------------------------------
*/

/*
                  ----------------------------------
                  | std::generate, std::generate_n |
                  ----------------------------------
*/

/*
  #include <list>
  #include <string>
  #include <algorithm>  // std::generate
  #include "../headers/nutility.h"

  template <typename ForIter, typename Func>
  ForIter Generate(ForIter iter_beg, ForIter iter_end, Func fn)
  {
    while (iter_beg != iter_end)
      *iter_beg++ = fn();
  
    return iter_end;
  }

  int main()
  {

    std::list<std::string> str_list(10);

    std::generate(str_list.begin(), str_list.end(), &rtown);

    for (const auto& city : str_list)
      std::cout << city << '\n';
    // output ->
    //  agri
    //  bitlis
    //  elazig
    //  nevsehir
    //  rize
    //  adana
    //  nigde
    //  isparta
    //  giresun
    //  mus
  }
*/

/*
  #include <vector>
  #include <random>   
  // std::mt19937, std::uniform_int_distribution
  #include <algorithm>

  int main()
  {
    std::vector<int> ivec1(5);
    std::vector<int> ivec2(5);

    std::mt19937 eng;
    std::uniform_int_distribution dist{ 1940, 2000 };

    // -----------------------------------------------------

    // std::generate(ivec.begin(), ivec.end(), 
    //               [=]{ return dist(eng); });  // syntax error
    // error: no match for call to 
    // '(const uniform_int_distribution<int>)(const mt19937&)'

    // -----------------------------------------------------

    std::generate(ivec1.begin(), ivec1.end(), 
                  [=] mutable { return dist(eng); });
    // VALID but expensive copying std::mt19937 object

    for (auto val : ivec1)
      std::cout << val << ' ';
    // output -> 1989 1948 1995 1990 1947

    std::cout << '\n';

    // -----------------------------------------------------

    std::generate(ivec2.begin(), ivec2.end(), 
                  [&]{ return dist(eng); });
    // using reference semantics is better than copying.

    for (auto val : ivec2)
      std::cout << val << ' ';
    // output -> 1989 1948 1995 1990 1947

    std::cout << '\n';

    // -----------------------------------------------------

    // in first "std::generate" call, "std::mt19937" 
    // object is copied so copied object's state 
    // and the original object's state which has been used 
    // in the second "std::generate" call are same states.
    // That is why the outputs are same.

    // -----------------------------------------------------
  }
*/

/*
  #include <random>  
  // std::mt19937, std::uniform_real_distribution
  #include <vector>
  #include <algorithm>  // std::generate_n
  #include <iterator>   // std::back_inserter

  int main()
  {
    std::mt19937 eng;
    std::uniform_real_distribution dist{ 10.0, 20.0 };
    std::vector<double> dvec;

    std::generate_n(std::back_inserter(dvec), 5, 
                    [&]{ return dist(eng); });

                  
    for (auto& val : dvec)
      std::cout << val << ' ';
    // output -> 11.3548 18.3501 19.6887 12.2103 13.0817
  }
*/

/*
                          ----------------
                          | std::shuffle |
                          ----------------
*/

/*
  #include <vector>
  #include <random>     // std::mt19937
  #include <algorithm>  // std::shuffle
  #include "../headers/nutility.h"

  int main()
  {
    std::vector<int> ivec{ 11, 22, 33, 44, 55, 66 };
    print(ivec);  
    // output -> 11 22 33 44 55 66

    std::mt19937 eng;
    std::shuffle(ivec.begin(), ivec.end(), eng);

    // because of std::shuffle's 3rd parameter 
    // is universal reference parameter, 
    // std::mt19937 object will NOT be copied.

    // when l value passed as an argument,
    // parameter type will become l value reference
    // (T&& & -> T&) reference collapsing

    // when r value passed as an argument,
    // parameter type will become r value reference
    // (T&& && -> T&&)

    print(ivec);
    // output -> 33 44 11 66 55 22
  }
*/

/*
  #include <string>
  #include <random>     // std::mt19937, std::random_device
  #include <algorithm>  // std::shuffle

  int main()
  {
    using namespace std;

    std::string str{ "hello world" };
    std::mt19937 eng{ std::random_device{}()};

    for (int i = 0; i < 5; ++i) 
    {
      std::cout << "|" << str << "|\n";
      std::shuffle(str.begin(), str.end(), eng);
    }
    // output ->
    //  |hello world|
    //  |loor lwldhe|
    //  |rw eolhldol|
    //  |lrolo whdel|
    //  |ledwrloo lh|
  }
*/

/*
                    -----------------------
                    | std::sample (C++17) |
                    -----------------------
*/

/*
  #include <string>
  #include <algorithm>    // std::sample
  #include <iterator>     // std::back_inserter
  #include <random>       // std::mt19937, std::random_device

  int main()
  {
    std::string str_in{ "ABCDEFGHIJK" };
    std::string str_out;

    std::sample(str_in.begin(), str_in.end(), 
                std::back_inserter(str_out), 
                4,
                std::mt19937{ std::random_device{}() });

    std::cout << "4 random letters out of " << str_in 
              << " = " << str_out << '\n';
    // output -> 4 random letters out of ABCDEFGHIJK = BDEG
  }
*/

/*
  #include <vector>
  #include <string>
  #include <algorithm>  // std::sample
  #include <iterator>   // std::ostream_iterator
  #include <random>     // std::mt19937, std::random_device

  int main()
  {
    const std::vector<std::string> months = { 
      "January", "February", "March", "April", 
      "May", "June", "July", "August", 
      "September", "October", "November", "December" };

    int N = 5;

    std::sample(
        months.begin(), months.end(), 
        std::ostream_iterator<std::string>{ std::cout, " "}, 
        N, 
        std::mt19937{ std::random_device{}() });
    // output -> January March April June August
  }
*/