#ifndef MYCLASS_HPP
#define MYCLASS_HPP

#include <string>
#include <iostream>

class Myclass {
private:
  std::string m_str;
public:
  Myclass() = default;
  Myclass(std::string str) : m_str{ str } 
  {
    std::cout << *this << " object has been created\n";
  }

  ~Myclass()
  {
    std::cout << *this << " object has been deleted\n";
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

#endif // MYCLASS_HPP