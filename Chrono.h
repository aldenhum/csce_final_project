#include "std_lib_facilities_3.h"
namespace Chrono {


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
	
	Date& operator++()
	// 1 day beyond d
	{
		add_day(1);
		return *this;
	}

	Date operator++(int)
		// 1 day beyond d
	{
		add_day(1);
		return *this;
	}
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

}



//-------------------------------------------------------------------------------------




namespace Chrono {

// member function definitions:


Date::Date(int yy, Month mm, int dd)
    : y(yy), m(mm), d(dd)
{
    if (!is_date(yy,mm,dd)) throw Invalid();
}

const Date& default_date();


Date::Date()
    :y(default_date().year()),
     m(default_date().month()),
     d(default_date().day())
{
}

int days_in_month(int y, Date::Month m);

void Date::add_day(int n)
{
	
	if (n<0) error("add_day(): can't handle negative n");	// not yet
	while (days_in_month(y,m)<n) {	// move one month at a time
		add_month(1);
		n -= days_in_month(y,m);
	}
	d += n;
}


void Date::add_month(int n)
{
	
	int m_new = m + n;
	if (m_new> 12) {
		add_year(1);
		m= Month(m_new-12);
	}
	else m = Month(m_new);
}

void Date::add_year(int n)
{
    if (m==feb && d==29 && !leapyear(y+n)) { // beware of leap years!
			// makes sense for both positive and negative n (n==0 should be impossible here)
			m = mar;        // use March 1 instead of February 29
			d = 1;
    }
    y+=n;
}




//------------------------------------------------------------------------------

// helper functions, etc.:



enum Day {	// sunday==0
    sunday, monday, tuesday, wednesday, thursday, friday, saturday
};

const Date first_date(1601,Date::jan,1);	

const Day first_day = monday;				

const Date& default_date()
{
    static const Date dd(2001,Date::jan,1); 
    return dd;
}

int days_in_month(int y, Date::Month m)
{
    switch (m) {
	case Date::feb:                        // the length of February varies
		return (leapyear(y))?29:28;
	case Date::apr: case Date::jun: case Date::sep: case Date::nov:
		return 30;
	default:
		return 31;
    }
}

bool is_date(int y, Date::Month  m, int d)
{
    // assume that y is valid

    if (d<=0) return false;            // d must be positive
    if (days_in_month(y,m)<d) return false;

    return true;
} 

bool leapyear(int y)
{
   

	if (y%4) return false;
	if (y%100==0 && y%400) return false;
	return true;
}

ostream& operator<<(ostream& os, const Date& d)
{
    return os << '(' << d.year()
              << ',' << d.month()
              << ',' << d.day() 
              << ')';
}


istream& operator>>(istream& is, Date& dd)
{
    int y, m, d;
    char ch1, ch2, ch3, ch4;
    is >> ch1 >> y >> ch2 >> m >> ch3 >> d >> ch4;
    if (!is) return is;
    if (ch1!='(' || ch2!=',' || ch3!=',' || ch4!=')') { 
        is.clear(ios_base::failbit);                    
        return is;
    }
    dd = Date(y,Date::Month(m),d);   
    return is;
}

}

