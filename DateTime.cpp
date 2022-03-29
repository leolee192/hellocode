
/** ----- date utils ----- **/
int daysInMonth[13] = { 0,
                        31, 28, 31,
                        30, 31, 30,
                        31, 31, 30,
                        31, 30, 31,
                        };

inline bool isLeapYear(int year) {
  return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

inline int getLastDayInMonth(int year, int month) {
  if (month != 2) {
    return daysInMonth[month];
  } else {
    return isLeapYear(year) ? 29 : 28;
  }
}
