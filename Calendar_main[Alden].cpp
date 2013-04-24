#include "std_lib_facilities_3.h"
#include "Window.h"
#include "Graph.h"
#include "GUI.h"
#include "Point.h"
#include "Chrono.h"
//#include <time.h> //not needed //still not needed

using namespace Graph_lib;

struct Calendar_window : Graph_lib::Window 	// Lines_window inherits from Window
{
	Calendar_window(Point xy, int w, int h, const string& title) // Constructor...
	:Graph_lib::Window(xy,w,h,title),
	prev_button(Point(0,0),  		 128, 20, "Previous Month", cb_prev),
	next_button(Point(133,0), 		 100, 20, "Next Month",	   cb_next),
	quit_button(Point(x_max()-70,0), 70, 20, "QUIT", 	  	   cb_quit)
	{
		attach(prev_button);
		attach(next_button);
		attach(quit_button);
	}

	//void  draw_days(Window& win);

	private:
		Button prev_button;
		Button next_button;		// declare some buttons – type Button
		Button quit_button;

		void prev();			//what to do when prev_button is pushed
		void next(); 			//what to do when next_button is pushed
		void quit(); 			//what to do when quit_button is pushed

		static void cb_prev(Address, Address window); // callback for the previous month button
		static void cb_next(Address, Address window); // callback for the next month button
		static void cb_quit(Address, Address window); 	// callback for quit_button
}; 

//The callback functions... Just pass data along to "worker" functions
void Calendar_window::cb_quit(Address, Address window)
{
	reference_to<Calendar_window> (window).quit();
}

void Calendar_window::cb_prev(Address, Address window)
{
	reference_to<Calendar_window> (window).prev();
}

void Calendar_window::cb_next(Address, Address window)
{
	reference_to<Calendar_window> (window).next();
}

//Our "worker" functions
void Calendar_window::quit()
{
	hide(); //FLTK's way of deleting the window
}

void Calendar_window::prev()
{
	//stuff: start.add_month(-1);
	redraw();
}

void Calendar_window::next()
{
	//TODO:
	/*
	Figure out which month follows the current one...
	Update the display with the next month's info
	*/
	redraw();
}

//struct Calendar_Day 
//{
	//This should ACTUALLY just contain info about the days
	//TODO: Add a constructor which (somehow) takes a formatted date string
	//Probably need to have a read from file in here somewhere...
	//TODO: public members here
	//We need to make it so the day knows things such as what day of the week it is, what day of the month it is, and what (if anything) is special about it
	/*Calendar_Day(Point tl, int w, int h, string date_info, string day_of_week, int date)
	{
		//TODO: implement this constructor... we can start by using Rectangle's constructor
	}
	private:
		int month_start_day = 1;*/
//};

class Appt_date
{
	int day;
	int month;
	int year;
	string title;
	public:
	Appt_date(int d, int m, int y, string t) :day(d), month(m), year(y), title(t) {}
};

string days_array[] {"Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
string months_array[] {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
int choose_day(int q, int m, int K, int J)
{
	if(m==2 && q==29)
	{
		return (q+((13*(m+1))/5)+K+(K/4)+(J/4)+5*J)%7 + 2;
	}
	else
	{
		return (q+((13*(m+1))/5)+K+(K/4)+(J/4)+5*J)%7;
	}
}
int main()
{
	try
	{
		Chrono::Date start;
		int y;
		int m;
		int d;
		cout << "Please enter a date (YYYY MM DD):: ";
		cin >> y >> m >> d;
		cout << endl;
		start = Chrono::Date(y,(Chrono::Date::Month)(m),d);
		
		int width = 700;
		int square_size = 100;
		int old_width;
		Rectangle* my_rect;
		Point* p;
		vector <vector <Point *> > board(6,vector <Point *> (7));
		vector <Point *> pts_row;
		if(H112 != 201206L)
			error("Error: incorrect std_lib_facilities_3.h version ", H112);
		
		Calendar_window my_window(Point(10,10),width,690,"Calendar"); //declare window
		
		string input_file = "appointments.txt";
		string collect_str;
		ifstream ist(input_file.c_str());
		if(!ist) error("can't open input file",input_file);
		else
		{
			vector<Appt_date> temps;
			int day = 01;
			int month = 01;
			int year = 2013;
			string title;
			while(ist.good())
			{
				day = collect_str.substr(0,2);
				month = collect_str.substr(3,2);
				if(collect_str[5] == '/')
				{
					year = collect_str.substr(6,4);
					title = collect_str.substr(11);
				}
				else
				{
					title = collect_str.substr(6);
				}
				temps.push_back(Appt_date(day, month, year, title));
			}
		}
		
		
		Text random_number(Point(250,250), days_array[choose_day(d,m,y%100,y/100)]);
		
		Text mon(Point(128,56), "Monday");
		Text tue(Point(224,56), "Tuesday");
		Text wed(Point(316,56), "Wednesday");
		Text thu(Point(420,56), "Thursday");
		Text fri(Point(528,56), "Friday");
		Text sat(Point(624,56), "Saturday");
		Text sun(Point(28,56),"Sunday");
		
		random_number.set_font_size(12);
		
		sun.set_color(Color::green);
		sun.set_font_size(12);
		mon.set_color(Color::green);
		mon.set_font_size(12);
		tue.set_color(Color::green);
		tue.set_font_size(12);
		wed.set_color(Color::green);
		wed.set_font_size(12);
		thu.set_color(Color::green);
		thu.set_font_size(12);
		fri.set_color(Color::green);
		fri.set_font_size(12);
		sat.set_color(Color::green);
		sat.set_font_size(12);
		
		my_window.attach(random_number);
		my_window.attach(mon);
		my_window.attach(tue);
		my_window.attach(wed);
		my_window.attach(thu);
		my_window.attach(fri);
		my_window.attach(sat);
		my_window.attach(sun);
		
		int row = 0;
		for (int y = 0; y < 6/*board.size()*/; y++)
		{
			row = y; //row number
			for (int x = 0; x < 7/*board[row].size()*/; x++)
			{
				p = new Point(x*100,y*100+64);
				pts_row.push_back(p); //add board to the row
			}

			board[row] = pts_row; //give the points to the matrix..
			pts_row.clear(); //clear our "temporary" row vector for reuse
		} //move down to the next row in the matrix of board

		//Our matrix now contains points
		//We need to create the squares which will comprise our board

		for (int r = 0; r < board.size(); r++)
		{
			for (int c = 0; c < board[r].size(); c++)
			{
				my_rect = new Rectangle(*(board[r][c]),square_size,square_size);
				my_window.attach((*my_rect));
			}
		}

		/*Line horizontal(Point(100,100),Point(200,100));  // make a horizontal line
		Line vertical(Point(150,50),Point(150,150));     // make a vertical line
		my_window.attach(horizontal); //attach horizontal line to window
		my_window.attach(vertical); //attach vertical line to window
		vertical.set_color(Color::magenta); */
	  
		//resize handling code (only checks width)
		while(true)
		{
			my_window.redraw();
			width = my_window.Fl_Widget::w();
			old_width = width;
			cout << old_width << endl;
			do
			{
				Fl::wait(1);	//wait up to 1 second
				width = my_window.Fl_Widget::w();
			}
			while(width == old_width);
		}
	  
		return 0;
	}

	catch(exception& e)
	{
		cerr << "exception: " << e.what() << '\n';
		return 1;
	}

	catch (...)
	{
		cerr << "Some exception\n";
		return 2;
	}
}

/*void Calendar_window::draw_days(Window& win)
{
	Text sun(Point(5,60),"Sunday");
	Text mon(Point(105,60), "Monday");
	Text tue(Point(205,60), "Tuesday");
	Text wed(Point(305,60), "Wednesday");
	Text thu(Point(405,60), "Thursday");
	Text fri(Point(505,60), "Friday");
	Text sat(Point(605,60), "Saturday");
	win.attach(sun);
}*/