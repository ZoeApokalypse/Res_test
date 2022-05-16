//
// Created by Zoe Apokalypse on 2022/4/10.
//

#ifndef RES_TEST_DATE_H
#define RES_TEST_DATE_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Date
        {
        private:
            int year;
            int month;
            int day;
        public:
            Date(int Year, int Month, int Day);
            int get_year() { return year; }
            int get_month() { return month; }
            int get_day() { return day; }
        };

Date::Date(int Year, int Month, int Day)
{
    year = Year;
    month = Month;
    day = Day;
}

#endif//RES_TEST_DATE_H
