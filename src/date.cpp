#include "../headers/date.h"
#include <ostream>
#include <istream>
#include <sstream>
#include <iomanip>
#include "../headers/nutility.h"

using namespace std;

//------------------------------------------------------
//------------------------------------------------------

Date::Date(const char* p)
{
  set(atoi(p), atoi(p + 3), atoi(p + 6));
}

//------------------------------------------------------
//------------------------------------------------------

std::ostream& operator<<(std::ostream& os, const Date& date)
{
  static constexpr const char *pmons[] =
      {"", "Ocak", "Subat", "Mart", "Nisan", "Mayis", "Haziran",
       "Temmuz", "Agustos", "Eylul", "Ekim", "Kasim", "Aralik"};

  static constexpr const char *pdays[] = {
      "Pazar",
      "Pazartesi",
      "Sali",
      "Carsamba",
      "Persembe",
      "Cuma",
      "Cumartesi",
  };

  ostringstream ossr;

  ossr << setfill('0') << setw(2) << date.d_;
  ossr << setfill(' ') << left;

  ossr << " " << pmons[date.m_]
       << " " << date.y_ << " "
       << pdays[date.week_day()];

  return os << ossr.str();
}

//------------------------------------------------------
//------------------------------------------------------

std::istream& operator>>(std::istream& is, Date& date)
{
  int d, m, y;
  is >> d >> m >> y;
  date = Date{d, m, y};
  return is;
}

//------------------------------------------------------
//------------------------------------------------------

Date& Date::operator++()
{
  if (d_ < 28)
    ++d_;

  else if (d_ == 31)
  {
    d_ = 1;
    m_ = m_ == 12 ? 1 : m_ + 1;
    if (m_ == 1)
      ++y_;
  }
  else if (d_ == 30 && (m_ == 4 || m_ == 6 || m_ == 9 || m_ == 11))
  {
    d_ = 1;
    ++m_;
  }
  else if (d_ == 29)
  {
    if (m_ == 2)
    {
      d_ = 1, m_ = 3;
    }
    else
      ++d_;
  }
  else
  {
    d_ = m_ == 2 ? (isleap(y_) ? 29 : 1) : d_ + 1;
    if (d_ == 1)
      ++m_;
  }

  return *this;
}

//------------------------------------------------------
//------------------------------------------------------

Date& Date::operator--()
{
  int d = d_, m = m_, y = y_;

  if (d != 1)
    --d;
  else if (m != 1)
  {
    --m;
    d = daytabs[static_cast<int>(isleap(y))][m];
  }
  else
  {
    if (y == yearbase)
      throw bad_date{};
    m = 12;
    d = 31;
    --y;
  }
  d_ = d;
  m_ = m;
  y_ = y;

  return *this;
}

//------------------------------------------------------
//------------------------------------------------------

Date Date::operator++(int)
{
  Date temp{*this};
  ++*this;
  return temp;
}

//------------------------------------------------------
//------------------------------------------------------

Date Date::operator--(int)
{
  Date temp{*this};
  --*this;
  return temp;
}

//------------------------------------------------------
//------------------------------------------------------

Date Date::random()
{

  int y = Irand{1950, 2020}();

  int m = Irand{1, 12}();
  int d = Irand{1, daytabs[static_cast<int>(isleap(y))][m]}();

  return Date{d, m, y};
}

//------------------------------------------------------
//------------------------------------------------------

bool operator<(const Date& d1, const Date& d2)
{
  return d1.y_ != d2.y_   ? d1.y_ < d2.y_
         : d1.m_ != d2.m_ ? d1.m_ < d2.m_
                          : d1.d_ < d2.d_;
}
//------------------------------------------------------
//------------------------------------------------------

bool operator==(const Date& d1, const Date& d2)
{
  return d1.y_ == d2.y_ && d1.m_ == d2.m_ && d1.d_ == d2.d_;
}

//------------------------------------------------------
//------------------------------------------------------

int operator-(const Date& d1, const Date& d2)
{
  return d1.totaldays() - d2.totaldays();
}

//------------------------------------------------------
//------------------------------------------------------