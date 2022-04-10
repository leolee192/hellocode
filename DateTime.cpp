
/** ----- Gregorian Date System ----- **/

inline bool isLeapYear(int year) {
  return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

const int daysInMonth[2][13] = {
    { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    };

inline int endOfMonthDay(int year, int month) {
  return daysInMonth[isLeapYear(year)][month];
}

enum weekday_enum {Sunday=0, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday};
const char* weekdayLongString[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

struct date_t {
  int year, month, day;
  date_t(int _year, int _month, int _day): year(_year), month(_month), day(_day) { }
  inline bool operator < (const date_t& rhs) const {
    if (year != rhs.year) return year < rhs.year;
    if (month != rhs.month) return month < rhs.month;
    return day < rhs.day;
  }
  // Define prefix increment operator.
  inline date_t& operator ++ () {
    if (day == endOfMonthDay(year, month)) {
      if (month == 12) {
        ++year, month=1, day=1;
      } else {
        ++month, day=1;
      }
    } else {
      ++day;
    }
    return *this;
  }
  // Define prefix decrement operator
  inline date_t& operator -- () {
    if (day == 1) {
      if (month == 1) {
        --year, month=12, day=31;
      } else {
        day = endOfMonthDay(year, --month);
      }
    } else {
      --day;
    }
    return *this;
  }
  // Return a date difference by subtracting two dates
  inline int operator - (const date_t& rhs) const {
    int startYear = min(year, rhs.year)-1;
    return _get_days(*this, startYear) - _get_days(rhs, startYear);
  }

  // Get the day of the week (Sunday, Monday, etc.) for dates on or after 0000-03-01
  // refer to https://datatracker.ietf.org/doc/html/rfc3339#appendix-B
  weekday_enum day_of_week() const {
    int y = year, m = month, d = day;
    /* adjust months so February is the last one */
    m -= 2;
    if (m < 1) {
      m += 12;
      --y;
    }
    /* split by century */
    int cent = y / 100;
    y %= 100;
    return static_cast<weekday_enum>(((26 * m - 2) / 10 + d + y
    + y / 4 + cent / 4 + 5 * cent) % 7);
  }

  // Get the day of the year. Number from 1 to 366
  int day_of_year() const {
    int leap = isLeapYear(year), res = 0;
    for (int i = 1; i <= month - 1; ++i) {
      res += daysInMonth[leap][i];
    }
    return res + day;
  }

 private:
  static int _get_days(const date_t& date, int startYear) {
    int r=0;
    for(int i=startYear; i<date.year;i++) {
      r += ((isLeapYear(i)) ? 366: 365);
    }
    bool leap = isLeapYear(date.year);
    for(int i=1;i<date.month;i++){
      r += daysInMonth[leap][i];
    }
    r += date.day;
    return r;
  }
};

/** END of Gregorian Date System **/

/** ----- timing ----- */
std::clock_t    _start = std::clock();
// your test
std::cout << "Time: " << (std::clock() - _start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;
/** ----- END of timing ----- */
