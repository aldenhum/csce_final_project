#include "std_lib_facilities_3.h"	

/*
	If you know the day of the week of *any* day (e.g. Jan 16, 2010 is a Saturday) and how to
	calculate leapyear() (exercise 9-10), you can find the day of the week of every day (of the
	current calendar). For example, 7 days after 1/16/2010 is another Saturday, 10 days after
	1/16/2010 is a "Saturday+3"; that is, a Tuesday. 10 days before 1/16/2010 is a "Saturday-3";
	that is, a Wednesday.
	
	Primary school children can do that by counting on their fingers; Our job is to translate
	what those children do into code (formulas) so that we can deal with larger numbers.

	So as not to try to invent everything from scratch, try typing "day of the week" into google (or equivalent).
	For more than you ever wanted to know about calendars, see http://www.tondering.dk/claus/calendar.html
	(e.g. where and when did they have a February 30th?)
*/

//_____________________________________
/*
	for simplicity of distribution on the web, I have copied the code of a Date class into this file.
	Had my aim been realism and proper code organization, I would have used a Date.h and a Date.cpp.
*/

//
// This is example code from Chapter 9.8 "The Date class" of 
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include <iostream>

using namespace std;

// file Chrono.h

namespace Chrono {

//------------------------------------------------------------------------------

class Date {
public:
    enum Month {
        jan=1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
    };

	class Invalid { };                 // to throw as exception

    Date(int y, Month m, int d);       // check for valid date and initialize
    Date();                            // default constructor
    // the default copy operations are fine

    // non-modifying operations:
    int   day()   const { return d; }
    Month month() const { return m; }
    int   year()  const { return y; }

    // modifying operations:
    void add_day(int n);        
    void add_month(int n);
    void add_year(int n);
    Date& operator++();
private:
    int   y;
    Month m;
    int   d;
};


bool is_date(int y, Date::Month m, int d); // true for valid date

bool leapyear(int y);                  // true if y is a leap year

bool operator==(const Date& a, const Date& b);
bool operator!=(const Date& a, const Date& b);

ostream& operator<<(ostream& os, const Date& d);
istream& operator>>(istream& is, Date& dd);


const Date& default_date();

} // Chrono